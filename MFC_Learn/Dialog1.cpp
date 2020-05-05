// Dialog1.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_Learn.h"
#include "Dialog1.h"
#include "afxdialogex.h"
#include "Dialog3.h"
#include "Dialog5.h"
#include "rsa.h"
#include "des.h"

// Dialog1 对话框

IMPLEMENT_DYNAMIC(Dialog1, CDialogEx)

Dialog1::Dialog1(CWnd* pParent /*=NULL*/)
	: CDialogEx(Dialog1::IDD, pParent)
{

}

Dialog1::~Dialog1()
{
}

void Dialog1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edit1);
	DDX_Control(pDX, IDC_EDIT2, edit2);
	DDX_Control(pDX, IDC_EDIT3, edit3);
	DDX_Control(pDX, IDC_EDIT4, edit4);
}


BEGIN_MESSAGE_MAP(Dialog1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Dialog1::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &Dialog1::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON2, &Dialog1::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Dialog1::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Dialog1::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &Dialog1::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON7, &Dialog1::OnBnClickedButton7)
END_MESSAGE_MAP()


// Dialog1 消息处理程序


void Dialog1::OnBnClickedButton1()
{
	CFileDialog dlg(TRUE);
	dlg.DoModal();
	CString path;
	path = dlg.GetPathName();
	if(path.IsEmpty() != true)
	{
		CFile file;
		bool isOk = file.Open(path, CFile::modeRead|CFile::typeBinary);  
		if (isOk == true)
		{
			vector <char>().swap(fileinArray); 
			file.SeekToBegin(); 
			unsigned int len = file.GetLength();
			char* buffer = new char [len + 1];
			buffer[len] = '\0';							//读取时候缓存区最后一位要设为0，否则不会停止读取
			file.Read (buffer, len);
			fileinArray.resize(len);
			char* p = &fileinArray[0];                  //操作地址速度会变快
			char* q = &buffer[0];
			for(int i = 0; i < len; i++)
			{
				*p++ = *q++;
			}
			delete[] buffer;

		}
		file.Close();	
	}
	edit1.SetWindowTextW(path);
}


void Dialog1::OnBnClickedButton6()
{
	for(int i =0; i < 128; i++)
	{
		dlg3.UK[i] = '\0';
		dlg3.RK[i] = '\0';
		dlg3.Rn[i] = '\0';
		dlg3.DKey[i] = '\0';
	}
	getRsakey(dlg3.UK, dlg3.RK, dlg3.Rn, dlg3.len);
	getDeskey(dlg3.DKey);
	Dialog5 dlg5;
	dlg5.DoModal();
	dlg3.DoModal();

}


void Dialog1::OnBnClickedButton2()
{
	CFileDialog dlg(TRUE);
	dlg.DoModal();
	CString path;
	path = dlg.GetPathName();
	if(path.IsEmpty() != true)
	{
		CFile file;
		bool isOk = file.Open(path, CFile::modeRead);  
		if (isOk == true)
		{
			for (int i = 0 ; i < 32;i ++)
				deskeyArray[i]='\0'; 
			file.SeekToBegin(); 
			unsigned int len = file.GetLength();
			char* buffer = new char [len + 1];
			buffer[len] = '\0';							//读取时候缓存区最后一位要设为0，否则不会停止读取
			file.Read (buffer, len);
			char* p = &deskeyArray[0];                  //操作地址速度会变快
			char* q = &buffer[0];
			for(int i = 0; i < len; i++)
			{
				*p++ = *q++;
			}
			CString str(buffer);
			edit2.SetWindowTextW(str);
			delete[] buffer;

		}
		file.Close();	
	}
	//edit2.SetWindowTextW(path);

}


void Dialog1::OnBnClickedButton3()
{
	CFileDialog dlg(TRUE);
	dlg.DoModal();
	CString path;
	path = dlg.GetPathName();
	if(path.IsEmpty() != true)
	{
		CFile file;
		bool isOk = file.Open(path, CFile::modeRead);  
		if (isOk == true)
		{
			for (int i = 0 ; i < 128;i ++)
				rsakeyArray[i]='\0';
			unsigned int len = file.GetLength();
			char* buffer = new char [len + 1];			
			buffer[len] = '0';							//读取时候缓存区最后一位要设为0，否则不会停止读取
			file.Read (buffer, len);
			char* p = &rsakeyArray[0];                  //操作地址速度会变快
			char* q = &buffer[0];
			for(int i = 0; i < len; i++)
			{
				*p++ = *q++;
			}
			delete[] buffer;

		}
		file.Close();	
	}
	//edit3.SetWindowTextW(path);
	CString str(rsakeyArray);
	edit3.SetWindowTextW(str);
}


void Dialog1::OnBnClickedButton4()
{
	CFileDialog dlg(TRUE);
	dlg.DoModal();
	CString path;
	path = dlg.GetPathName();
	if(path.IsEmpty() != true)
	{
		CFile file;
		bool isOk = file.Open(path, CFile::modeRead);  
		if (isOk == true)
		{
			for (int i = 0 ; i < 128;i ++)
				rsanArray[i]='\0'; 
			unsigned int len = file.GetLength();
			char* buffer = new char [len + 1];
			buffer[len] = '0';							//读取时候缓存区最后一位要设为0，否则不会停止读取
			file.Read (buffer, len);
			char* p = &rsanArray[0];                  //操作地址速度会变快
			char* q = &buffer[0];
			for(int i = 0; i < len; i++)
			{
				*p++ = *q++;
			}
			delete[] buffer;

		}
		file.Close();	
	}
	//edit4.SetWindowTextW(path);
	CString str(rsanArray);
	edit4.SetWindowTextW(str);
}


void Dialog1::OnBnClickedButton5()
{
	CFileDialog dlg(FALSE);
	dlg.DoModal();
	//请等待......
	CString path;
	path = dlg.GetPathName();
	if(path.IsEmpty() != true)
	{
		CFile file;
		bool isOk = file.Open(path, CFile::modeWrite|CFile::modeCreate|CFile::typeBinary);  
		if (isOk == true)
		{
			char desKey[128];
			char desBitkey[16];
			char rsaDeskey[128];
			for(int i = 0; i < 128; i++)
			{
				desKey[i] = '\0';
				rsaDeskey[i] = '\0';
			}
			for (int j = 0; j < 32; j++)
			{
				desKey[j] = deskeyArray[j];			
			}
			long len = fileinArray.size();
			long len1 = len%8;
			long len2 = len/8;
			long len3;	
			if(len1 == 0)
				len3 = len;			
			else
				len3 = len + 8 - len1;			
			char* in = new char [len3];	
			char* out = new char [len3];
			char* dst = &in[0];                  //操作地址速度会变快
			char* src = &fileinArray[0];
			for(int k = 0; k < len; k++)
			{
				*dst++ = *src++;
			}
			if(len1 != 0)
			{
				for(int l = 0; l < 8 - len1; l++)
				{
					in[len + l] = 'A';                        //补'A'
				}
			}
			Change(desKey, 32, desBitkey);
			DES_Act(out, in, len3, desBitkey, 16, enCRYPT);  //对输入文件进行DES加密
			Encryption(desKey , rsakeyArray, rsanArray, rsaDeskey);  //对des密钥进行rsa加密
			//混合加密算法，对fileinArray补全为8byte整数倍，进行DES加密，对deskeyArray进行RSA流加密，将两者存入fileoutArray
			long len4 = len3 + 128;
			char* buffer = new char [len4 + 1];
			char* p = &buffer[0];                  //操作地址速度会变快
			char* q = &out[0];
			for(int m = 0; m < len3; m++)
			{
				*p++ = *q++;
			}
			q = &rsaDeskey[0];
			for(int n = 0; n < 128; n++)
			{
				*p++ = *q++;
			}
			file.SeekToBegin();
			buffer[len4] = '\0';              //写居然也需要置0操作
			file.Write(buffer, len4);
			delete[] buffer;
			delete[] in;
			delete[] out;
		}
		file.Close();	
	}
	Dialog5 dlg5;
	dlg5.DoModal();
}


void Dialog1::OnBnClickedButton7()
{
	CFileDialog dlg(FALSE);
	dlg.DoModal();
	//请等待......
	CString path;
	path = dlg.GetPathName();
	if(path.IsEmpty() != true)
	{
		CFile file;
		bool isOk = file.Open(path, CFile::modeWrite|CFile::modeCreate|CFile::typeBinary);  
		if (isOk == true)
		{
			char desKey[128];
			char desBitkey[16];
			char rsaDeskey[128];
			for(int i = 0; i < 128; i++)
			{
				desKey[i] = '\0';
				rsaDeskey[i] = '\0';
			}
			long len = fileinArray.size();
			long len1 = len - 128;
			char* in = new char [len1];	
			char* out = new char [len1];
			char* dst = &in[0];                  //操作地址速度会变快
			char* src = &fileinArray[0];
			for(int k = 0; k < len1; k++)
			{
				*dst++ = *src++;
			}
			dst = &rsaDeskey[0];
			for(int n = 0; n < 128; n++)
			{
				*dst++ = *src++;
			}			
			Decryption(rsaDeskey, rsakeyArray, rsanArray, desKey);  //对des密钥进行rsa解密
			Change(desKey, 32, desBitkey);
			DES_Act(out, in, len1, desBitkey, 16, deCRYPT);  //对输入文件进行DES加密
			//混合加密算法，对fileinArray补全为8byte整数倍，进行DES加密，对deskeyArray进行RSA流加密，将两者存入fileoutArray
			char* buffer = new char [len1 + 1];
			char* p = &buffer[0];                  //操作地址速度会变快
			char* q = &out[0];
			for(int m = 0; m < len1; m++)
			{
				*p++ = *q++;
			}
			file.SeekToBegin();
			buffer[len1] = '\0';              //写居然也需要置0操作
			file.Write(buffer, len1);
			delete[] buffer;
			delete[] in;
			delete[] out;
		}
		file.Close();	
	}
	Dialog5 dlg5;
	dlg5.DoModal();
}
