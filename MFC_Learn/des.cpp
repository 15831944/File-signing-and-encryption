#include "stdafx.h"
#include "des.h"
#include "zzn.h"
//������DES�㷨�е��õĺ�����
// �ֽ�ת������
void ByteToBit(bool *Out, const char *In, int bits)
{
    for(int i=0; i<bits; ++i)
        Out[i] = (In[i>>3]>>(i&7)) & 1;//In[i/8] ���������ȡ��1���ֽڣ�i=0~7��ʱ���ȡIn[0]�� i=8~15��ʱ���ȡIn[1]������
//In[i/8] >> (i%8)���ǰ�ȡ������1���ֽ�����0~7λ��Ҳ��������ȡ���Ǹ��ֽڵ�ÿһ��bit
//���������������ǣ���In�����ÿ���ֽ�����ת��Ϊ8��bit�����Ľ���浽Out����
}
 
 
// ����ת������
void BitToByte(char *Out, const bool *In, int bits)
{
    memset(Out, 0, bits>>3);//��ÿ���ֽڶ���ʼ��Ϊ0
    for(int i=0; i<bits; ++i)
        Out[i>>3] |= In[i]<<(i&7);//i>>3λ���㣬��λ������λ����i����8��i&7��λ���������i����8��
}
 
 
// �任����
void Transform(bool *Out, bool *In, const char *Table, int len)
{
    for(int i=0; i<len; ++i)
        Tmp[i] = In[ Table[i]-1 ];
    memcpy(Out, Tmp, len);
}
 
 
// �������ʵ��
void Xor(bool *InA, const bool *InB, int len)
{
    for(int i=0; i<len; ++i)
        InA[i] ^= InB[i];//������㣬��ͬΪ0����ͬΪ1
}
 
 
// ��ת����
void RotateL(bool *In, int len, int loop)
{
    memcpy(Tmp, In, loop);//Tmp�������Ƴ���loop���ֽ�
    memcpy(In, In+loop, len-loop);//In���¼�ʣ�µ��ֽ���ǰ�ƶ�loop���ֽ�
    memcpy(In+len-loop, Tmp, loop);//���Ƴ����ֽ���ӵ�In��len-loop��λ��
}
 
 
// S������ʵ��
void S_func(bool Out[32], const bool In[48])  //��8�飬ÿ��6 bits�Ĵ���ת��Ϊ8�飬ÿ��4 bits
{
    for(char i=0,j,k; i<8; ++i,In+=6,Out+=4)
	{
        j = (In[0]<<1) + In[5];//ȡ��һλ�͵���λ��ɵĶ�������ΪS�е�������
        k = (In[1]<<3) + (In[2]<<2) + (In[3]<<1) + In[4];//ȡ�ڶ��������ġ���λ��ɵĶ�������ΪS�еĺ�����
		ByteToBit(Out, &S_Box[i][j][k], 4);
    }
}
 
 
// F������ʵ��
void F_func(bool In[32], const bool Ki[48])
{
    static bool MR[48];
    Transform(MR, In, Extension_Table, 48);   //�Ƚ��� E ��չ
    Xor(MR, Ki, 48);                          //�����
    S_func(In, MR);                           //�����ַ����ֱ𾭹����Ե� S ��
    Transform(In, In, P_Table, 32);           //��� P �任
}
 
 
 
// ��������Կ
void SetSubKey(PSubKey pSubKey, const char Key[8])
{
    static bool K[64], *KL=&K[0], *KR=&K[28]; //��64λ��Կ��ȥ��8λ��żλ�󣬷ֳ�����
    ByteToBit(K, Key, 64);                    //ת����ʽ
    Transform(K, K, PC1_Table, 56);
 
    for(int i=0; i<16; ++i)                   // ��56λ��Կ����48λ����Կ
	{
        RotateL(KL, 28, LOOP_Table[i]);       //��������Կ�ֱ��������ת��
        RotateL(KR, 28, LOOP_Table[i]);
        Transform((*pSubKey)[i], K, PC2_Table, 48);
    }
}
 
 
// ������Կ
void SetKey(const char* Key, int len)
{
	memset(deskey, 0, 16);
	memcpy(deskey, Key, len>16?16:len);//memcpy(a,b,c)����������b��ַ��ʼ��c���ȵ��ֽڵ����ݸ��Ƶ�a
	SetSubKey(&SubKey[0], &deskey[0]);// ��������Կ��SubKey��deskey������16����Կ
	Is3DES = len>8 ? (SetSubKey(&SubKey[1], &deskey[8]), true) : false;//�Ƿ��������key��һ��key����Ϊ8������key����Ϊ16
}
 
 
// DES�ӽ��ܺ���
void DES(char Out[8], char In[8], const PSubKey pSubKey, bool Type)
{
    static bool M[64], tmp[32], *Li=&M[0], *Ri=&M[32];  //64 bits���� ����IP�û��󣬷ֳ���������
    ByteToBit(M, In, 64);								//char[8]תΪbool[64]
    Transform(M, M, IP_Table, 64);
    if( Type == enCRYPT )                               //����
	{
        for(int i=0; i<16; ++i)                         //����ʱ������Կ K0~K15
		{
            memcpy(tmp, Ri, 32);
            F_func(Ri, (*pSubKey)[i]);                  // ����F����
            Xor(Ri, Li, 32);                            //Li��Ri���
            memcpy(Li, tmp, 32);
        }
    }
	else                 //����
	{
        for(int i=15; i>=0; --i)                        // ����ʱ��Ki��˳��������෴
		{
            memcpy(tmp, Li, 32);
            F_func(Li, (*pSubKey)[i]);
            Xor(Li, Ri, 32);
            memcpy(Ri, tmp, 32);
        }
	}
    Transform(M, M, IP1_Table, 64);                     //��󾭹����ʼ�û�IP-1���õ�����/����
    BitToByte(Out, M, 64);
}
 
 
// DES�ӽ��ܺ��������ԶԳ����ķֶμ��ܣ�
bool DES_Act(char *Out, char *In, long datalen, const char *Key, int keylen, bool Type)
{
    if( !( Out && In && Key && (datalen=(datalen+7)&0xfffffff8) ) )
		return false;
	SetKey(Key, keylen);
	if( !Is3DES )
	{                                                   // 1��DES
		for(long i=0,j=datalen>>3; i<j; ++i,Out+=8,In+=8)    
			DES(Out, In, &SubKey[0], Type);
	}
	else
	{                // 3��DES ����:��(key0)-��(key1)-��(key0) ����::��(key0)-��(key1)-��(key0)
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
	miracl *mip = mirsys(512,16); //��ʼ��һ��512λ16���ƵĴ���ϵͳ 
	mip->IOBASE=16;

	big k=mirvar(0);  
	bigbits(128, k);
	cotstr(k,DKey);
	mirkill(k);   //�ͷŴ�������
	mirexit();
}