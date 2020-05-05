#include "stdafx.h"
#include "des.h"
#include "zzn.h"
//下面是DES算法中调用的函数：
// 字节转换函数
void ByteToBit(bool *Out, const char *In, int bits)
{
    for(int i=0; i<bits; ++i)
        Out[i] = (In[i>>3]>>(i&7)) & 1;//In[i/8] 这个作用是取出1个字节：i=0~7的时候就取In[0]， i=8~15的时候就取In[1]，……
//In[i/8] >> (i%8)，是把取出来的1个字节右移0~7位，也就是依次取出那个字节的每一个bit
//整个函数的作用是：把In里面的每个字节依次转换为8个bit，最后的结果存到Out里面
}
 
 
// 比特转换函数
void BitToByte(char *Out, const bool *In, int bits)
{
    memset(Out, 0, bits>>3);//把每个字节都初始化为0
    for(int i=0; i<bits; ++i)
        Out[i>>3] |= In[i]<<(i&7);//i>>3位运算，按位右移三位等于i除以8，i&7按位与运算等于i求余8；
}
 
 
// 变换函数
void Transform(bool *Out, bool *In, const char *Table, int len)
{
    for(int i=0; i<len; ++i)
        Tmp[i] = In[ Table[i]-1 ];
    memcpy(Out, Tmp, len);
}
 
 
// 异或函数的实现
void Xor(bool *InA, const bool *InB, int len)
{
    for(int i=0; i<len; ++i)
        InA[i] ^= InB[i];//异或运算，相同为0，不同为1
}
 
 
// 轮转函数
void RotateL(bool *In, int len, int loop)
{
    memcpy(Tmp, In, loop);//Tmp接受左移除的loop个字节
    memcpy(In, In+loop, len-loop);//In更新即剩下的字节向前移动loop个字节
    memcpy(In+len-loop, Tmp, loop);//左移除的字节添加到In的len-loop的位置
}
 
 
// S函数的实现
void S_func(bool Out[32], const bool In[48])  //将8组，每组6 bits的串，转化为8组，每组4 bits
{
    for(char i=0,j,k; i<8; ++i,In+=6,Out+=4)
	{
        j = (In[0]<<1) + In[5];//取第一位和第六位组成的二进制数为S盒的纵坐标
        k = (In[1]<<3) + (In[2]<<2) + (In[3]<<1) + In[4];//取第二、三、四、五位组成的二进制数为S盒的横坐标
		ByteToBit(Out, &S_Box[i][j][k], 4);
    }
}
 
 
// F函数的实现
void F_func(bool In[32], const bool Ki[48])
{
    static bool MR[48];
    Transform(MR, In, Extension_Table, 48);   //先进行 E 扩展
    Xor(MR, Ki, 48);                          //再异或
    S_func(In, MR);                           //各组字符串分别经过各自的 S 盒
    Transform(In, In, P_Table, 32);           //最后 P 变换
}
 
 
 
// 设置子密钥
void SetSubKey(PSubKey pSubKey, const char Key[8])
{
    static bool K[64], *KL=&K[0], *KR=&K[28]; //将64位密钥串去掉8位奇偶位后，分成两份
    ByteToBit(K, Key, 64);                    //转换格式
    Transform(K, K, PC1_Table, 56);
 
    for(int i=0; i<16; ++i)                   // 由56位密钥产生48位子密钥
	{
        RotateL(KL, 28, LOOP_Table[i]);       //两份子密钥分别进行左移转换
        RotateL(KR, 28, LOOP_Table[i]);
        Transform((*pSubKey)[i], K, PC2_Table, 48);
    }
}
 
 
// 设置密钥
void SetKey(const char* Key, int len)
{
	memset(deskey, 0, 16);
	memcpy(deskey, Key, len>16?16:len);//memcpy(a,b,c)函数，将从b地址开始到c长度的字节的内容复制到a
	SetSubKey(&SubKey[0], &deskey[0]);// 设置子密钥，SubKey存deskey产生的16轮密钥
	Is3DES = len>8 ? (SetSubKey(&SubKey[1], &deskey[8]), true) : false;//是否给了两个key，一个key长度为8，两个key长度为16
}
 
 
// DES加解密函数
void DES(char Out[8], char In[8], const PSubKey pSubKey, bool Type)
{
    static bool M[64], tmp[32], *Li=&M[0], *Ri=&M[32];  //64 bits明文 经过IP置换后，分成左右两份
    ByteToBit(M, In, 64);								//char[8]转为bool[64]
    Transform(M, M, IP_Table, 64);
    if( Type == enCRYPT )                               //加密
	{
        for(int i=0; i<16; ++i)                         //加密时：子密钥 K0~K15
		{
            memcpy(tmp, Ri, 32);
            F_func(Ri, (*pSubKey)[i]);                  // 调用F函数
            Xor(Ri, Li, 32);                            //Li与Ri异或
            memcpy(Li, tmp, 32);
        }
    }
	else                 //解密
	{
        for(int i=15; i>=0; --i)                        // 解密时：Ki的顺序与加密相反
		{
            memcpy(tmp, Li, 32);
            F_func(Li, (*pSubKey)[i]);
            Xor(Li, Ri, 32);
            memcpy(Ri, tmp, 32);
        }
	}
    Transform(M, M, IP1_Table, 64);                     //最后经过逆初始置换IP-1，得到密文/明文
    BitToByte(Out, M, 64);
}
 
 
// DES加解密函数（可以对长明文分段加密）
bool DES_Act(char *Out, char *In, long datalen, const char *Key, int keylen, bool Type)
{
    if( !( Out && In && Key && (datalen=(datalen+7)&0xfffffff8) ) )
		return false;
	SetKey(Key, keylen);
	if( !Is3DES )
	{                                                   // 1次DES
		for(long i=0,j=datalen>>3; i<j; ++i,Out+=8,In+=8)    
			DES(Out, In, &SubKey[0], Type);
	}
	else
	{                // 3次DES 加密:加(key0)-解(key1)-加(key0) 解密::解(key0)-加(key1)-解(key0)
		for(long i=0,j=datalen>>3; i<j; ++i,Out+=8,In+=8) {
			DES(Out, In,  &SubKey[0], Type);
			DES(Out, Out, &SubKey[1], !Type);
			DES(Out, Out, &SubKey[0], Type);
		}
	}
	return true;
}

void getDeskey(char* DKey) 
{
	miracl *mip = mirsys(512,16); //初始化一个512位16进制的大数系统 
	mip->IOBASE=16;

	big k=mirvar(0);  
	bigbits(128, k);
	cotstr(k,DKey);
	mirkill(k);   //释放大数变量
	mirexit();
}