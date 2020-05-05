// Dialog4.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_Learn.h"
#include "Dialog4.h"
#include "Dialog2.h"
#include "afxdialogex.h"


// Dialog4 对话框

IMPLEMENT_DYNAMIC(Dialog4, CDialogEx)

Dialog4::Dialog4(CWnd* pParent /*=NULL*/)
	: CDialogEx(Dialog4::IDD, pParent)
{

}

Dialog4::~Dialog4()
{
}

void Dialog4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Dialog4, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &Dialog4::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Dialog4::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Dialog4::OnBnClickedButton4)
END_MESSAGE_MAP()


// Dialog4 消息处理程序


void Dialog4::OnBnClickedButton2()
{
	CFileDialog dlg(FALSE);
	dlg.DoModal();
	CString path;
	path = dlg.GetPathName();
	if(path.IsEmpty() != true)
	{
		CFile file;
		bool isOk = file.Open(path, CFile::modeWrite|CFile::modeCreate);  
		if (isOk == true)
		{
			char* buffer = new char [len[1] + 1];
			for(int i =0; i < len[1] + 1; i++)
			{
				buffer[i] = '\0';
			}
			char* p = &buffer[0];                  //操作地址速度会变快
			char* q = &RK[0];
			for(int i = 0; i < len[1]; i++)
			{
				*p++ = *q++;
			}
			file.SeekToBegin();
			file.Write(buffer, len[1]);
			delete[] buffer;
		}
		file.Close();	
	}
}


void Dialog4::OnBnClickedButton3()
{
	CFileDialog dlg(FALSE);
	dlg.DoModal();
	CString path;
	path = dlg.GetPathName();
	if(path.IsEmpty() != true)
	{
		CFile file;
		bool isOk = file.Open(path, CFile::modeWrite|CFile::modeCreate);  
		if (isOk == true)
		{
			char* buffer = new char [len[0] + 1];
			for(int i =0; i < len[0] + 1; i++)
			{
				buffer[i] = '\0';
			}
			char* p = &buffer[0];                  //操作地址速度会变快
			char* q = &UK[0];
			for(int i = 0; i < len[0]; i++)
			{
				*p++ = *q++;
			}
			file.SeekToBegin();
			file.Write(buffer, len[0]);
			delete[] buffer;
		}
		file.Close();	
	}	
	
}


void Dialog4::OnBnClickedButton4()
{
	CFileDialog dlg(FALSE);
	dlg.DoModal();
	CString path;
	path = dlg.GetPathName();
	if(path.IsEmpty() != true)
	{
		CFile file;
		bool isOk = file.Open(path, CFile::modeWrite|CFile::modeCreate);  
		if (isOk == true)
		{
			char* buffer = new char [len[2] + 1];
			for(int i =0; i < len[2] + 1; i++)
			{
				buffer[i] = '\0';
			}
			char* p = &buffer[0];                  //操作地址速度会变快
			char* q = &Rn[0];
			for(int i = 0; i < len[2]; i++)
			{
				*p++ = *q++;
			}
			file.SeekToBegin();
			file.Write(buffer, len[2]);
			delete[] buffer;
		}
		file.Close();
	}
}