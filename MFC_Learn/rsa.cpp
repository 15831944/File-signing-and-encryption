#include "stdafx.h"
#include "rsa.h"
#include "zzn.h"
#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>

using namespace std; 

int Encryption(char* Plaintext , char* RKey, char* Rn, char* Encryptext)
{
	int len;
	char SN[128];
	for (int i = 0 ; i < 128 ;i ++)
		SN[i]	='\0';
	char ret[128];
	for (int i = 0 ; i < 128 ;i ++)
		ret[i]	='\0';
		
	strcpy_s(SN, Plaintext);				 //�����ַ���

	miracl *mip = mirsys(512,16);		 //��ʼ��һ��512λ16���ƵĴ���ϵͳ
	mip->IOBASE=16;

	big in = mirvar(0); 
	big out = mirvar(0); 
	big key = mirvar(0); 
	big n = mirvar(0); 

		//�������RSA�㷨���ܺͽ������� 
	cinstr(in, SN);
	cinstr(key, RKey);
	cinstr(n, Rn);
	powmod(in,key,n,out);   		     
	len = cotstr(out,ret);		//������ת���ɵ�ǰ���Ƶ��ַ���
	for (int i = 0 ; i < 128; i++)
		Encryptext[i]	='0';
	for (int i = 0 ; i < len; i++)
		Encryptext[i + 128 - len] = ret[i];
 
	mirkill(in);			//�ͷŴ�������   
	mirkill(out);   
	mirkill(key);  
	mirkill(n);      
	mirexit();
	return len;
}

int Decryption(char* Encryptext , char* RKey, char* Rn, char* Plaintext)
{
	int len;
	char SN[129];
	for (int i = 0 ; i < 129 ;i ++)
		SN[i] = Encryptext[i];
	SN[128] = '\0';                           //�ַ�������ҲҪ����'\0'
	char ret[128];
	for (int i = 0 ; i < 128 ;i ++)
		ret[i] = '\0';

	miracl *mip = mirsys(512,16);		 //��ʼ��һ��512λ16���ƵĴ���ϵͳ
	mip->IOBASE=16;

	big in = mirvar(0); 
	big out = mirvar(0); 
	big key = mirvar(0); 
	big n = mirvar(0); 

		//�������RSA�㷨���ܺͽ������� 
	cinstr(in, SN);
	cinstr(key, RKey);
	cinstr(n, Rn);
	powmod(in,key,n,out);   		     
	len = cotstr(out,Plaintext);		//������ת���ɵ�ǰ���Ƶ��ַ���
 
	mirkill(in);			//�ͷŴ�������   
	mirkill(out);   
	mirkill(key);  
	mirkill(n);      
	mirexit();
	return len;
}

void getRsakey(char* UK, char* RK, char* Rn, int* len)
{
	miracl *mip = mirsys(512,16); //��ʼ��һ��512λ16���ƵĴ���ϵͳ 
	mip->IOBASE=16;
		/************************   ��һ�� ��ȡ��ʼֵ  *********************************/
	big m=mirvar(0); //m ����  
	big c=mirvar(0); //c ����    
	big p=mirvar(0); //������p  
	big q=mirvar(0); //������q    
	big n=mirvar(0); //n ģ��   
	big pn=mirvar(0); //ŷ������ֵpn = (p - 1)(q - 1)    
	big d=mirvar(0); //d ˽Կ  
	big e=mirvar(0); //e ��Կ 
	big z=mirvar(0);
	int x=0;


	/************************         step1 ��ȡp��q��ֵ          *********************************/
	bigbits(208, p);
	while(!isprime(p))
	{
		bigbits(208, p);
	}

	bigbits(208, q);
	while(!isprime(q))
	{
		bigbits(208, q);
	}		
 
		/************************  step2 ��ȡnֵ = [ n=p*q ]          *********************************/
	multiply(p, q, n);   
 
		/************************  step3 ��ȡpnֵ = [ n=(p-1)*(q-1) ] *********************************/ 
	decr(p, 1, p);  //p = p - 1  
	decr(q, 1, q);  //q = q - 1  
	multiply(p, q, pn); //pn = (p - 1)(q - 1)
 
		/************************            step4 ��ȡeֵ           *********************************/ 
	convert(x, z);
	bigbits(208, e);
	while(x!=1)
	{
		bigbits(208, e);
		x = egcd(e, pn, z);
	}

		/************************  step5 ��ȡdֵ = [ d= e^-1 mod pn] *********************************/ 
	xgcd(e, pn, d, d, d); //����d = e^-1 mod n  
	len[0] = cotstr(e,UK);
	len[1] = cotstr(d,RK);
	len[2] = cotstr(n,Rn);
	mirkill(m);   //�ͷŴ�������   
	mirkill(c);   
	mirkill(p);  
	mirkill(q);   
	mirkill(d);  
	mirkill(e);   
	mirkill(n);  
	mirkill(pn);
	mirkill(z);  
	mirexit();

}

int Change(char* s, int len, char* bits) {
	int i,n = 0;
	for(i = 0; i < len; i += 2) {
		if(s[i] >= 'A' && s[i] <= 'F')
			bits[n] = s[i] - 'A' + 10;
		else bits[n] = s[i] - '0';
		if(s[i + 1] >= 'A' && s[i + 1] <= 'F')
			bits[n] = (bits[n] << 4) | (s[i + 1] - 'A' + 10);
		else bits[n] = (bits[n] << 4) | (s[i + 1] - '0');
		++n;
	}
	return n;
}