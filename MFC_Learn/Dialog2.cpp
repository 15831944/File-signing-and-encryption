// Dialog2.cpp : 实现文件

#include "stdafx.h"
#include "MFC_Learn.h"
#include "Dialog2.h"
#include "afxdialogex.h"
#include "Dialog4.h"
#include "Dialog5.h"
#include "Dialog6.h"
#include "Dialog7.h"
#include "rsa.h"
#include "MD5.h"
// Dialog2 对话框

IMPLEMENT_DYNAMIC(Dialog2, CDialogEx)

Dialog2::Dialog2(CWnd* pParent /*=NULL*/)
	: CDialogEx(Dialog2::IDD, pParent)
{

}

Dialog2::~Dialog2()
{
}

void Dialog2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, edit1);
	DDX_Control(pDX, IDC_EDIT3, edit2);
	DDX_Control(pDX, IDC_EDIT4, edit3);
}


BEGIN_MESSAGE_MAP(Dialog2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &Dialog2::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Dialog2::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Dialog2::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &Dialog2::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &Dialog2::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &Dialog2::OnBnClickedButton7)
END_MESSAGE_MAP()


// Dialog2 消息处理程序


void Dialog2::OnBnClickedButton2()
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


void Dialog2::OnBnClickedButton3()
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
	edit2.SetWindowTextW(str);
}


void Dialog2::OnBnClickedButton4()
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
	edit3.SetWindowTextW(str);
}


void Dialog2::OnBnClickedButton5()
{
	CFileDialog dlg(FALSE);
	dlg.DoModal();
	CString path;
	path = dlg.GetPathName();
	if(path.IsEmpty() != true)
	{
		CFile file;
		bool isOk = file.Open(path, CFile::modeWrite|CFile::modeCreate|CFile::typeBinary);  
		if (isOk == true)
		{
			char MD5Hash[128];
			char rsaMD5Hash[128];
			MD5 test;
			string str;
			for(int i = 0; i < 128; i++)
			{
				MD5Hash[i] = '\0';
				rsaMD5Hash[i] = '\0';
			}
			long len = fileinArray.size();			
			char* in = new char [len];	
			char* dst = &in[0];                  //操作地址速度会变快
			char* src = &fileinArray[0];
			for(int k = 0; k < len; k++)
			{
				*dst++ = *src++;
			}
			str = test.encode(in, len);  //对输入文件进行数字签名
			for(int i = 0; i < 32; i++)
			{
				MD5Hash[i] = str[i];
			}
			Encryption(MD5Hash , rsakeyArray, rsanArray, rsaMD5Hash);  //对Hash码进行rsa加密
			long len2 = len + 128;
			char* buffer = new char [len2 + 1];
			char* p = &buffer[0];                  //操作地址速度会变快
			char* q = &in[0];
			for(int m = 0; m < len; m++)
			{
				*p++ = *q++;
			}
			q = &rsaMD5Hash[0];
			for(int n = 0; n < 128; n++)
			{
				*p++ = *q++;
			}
			file.SeekToBegin();
			buffer[len2] = '\0';              //写居然也需要置0操作
			file.Write(buffer, len2);
			delete[] buffer;
			delete[] in;
		}
		file.Close();	
	}
	Dialog5 dlg5;
	dlg5.DoModal();
}


void Dialog2::OnBnClickedButton6()
{
	for(int i =0; i < 128; i++)
	{
		dlg4.UK[i] = '\0';
		dlg4.RK[i] = '\0';
		dlg4.Rn[i] = '\0';
	}
	getRsakey(dlg4.UK, dlg4.RK, dlg4.Rn, dlg4.len);
	dlg4.DoModal();
}


void Dialog2::OnBnClickedButton7()
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
			char MD5Hash[128];
			char rsaMD5Hash[128];
			int same = 0;
			MD5 test;
			string str;
			for(int i = 0; i < 128; i++)
			{
				MD5Hash[i] = '\0';
				rsaMD5Hash[i] = '\0';
			}
			long len = fileinArray.size();
			long len1 = len - 128;
			char* in = new char [len1];	
			char* dst = &in[0];                  //操作地址速度会变快
			char* src = &fileinArray[0];
			for(int k = 0; k < len1; k++)
			{
				*dst++ = *src++;
			}
			dst = &rsaMD5Hash[0];
			for(int n = 0; n < 128; n++)
			{
				*dst++ = *src++;
			}			
			Decryption(rsaMD5Hash, rsakeyArray, rsanArray, MD5Hash);  //对Hash码进行rsa解密
			str = test.encode(in, len1);  //对输入文件进行数字签名
			for(int i = 0; i < 32; i++)
			{
				if(str[i] != MD5Hash[i])
				{
					same++;
				}
			}
			if (same == 0)
			{
				Dialog6 dlg6;
				dlg6.DoModal();			
			}
			else
			{
				Dialog7 dlg7;
				dlg7.DoModal();
			}
			char* buffer = new char [len1 + 1];
			char* p = &buffer[0];                  //操作地址速度会变快
			char* q = &in[0];
			for(int m = 0; m < len1; m++)
			{
				*p++ = *q++;
			}
			file.SeekToBegin();
			buffer[len1] = '\0';              //写居然也需要置0操作
			file.Write(buffer, len1);
			delete[] buffer;
			delete[] in;
		}
		file.Close();	
	}
}
