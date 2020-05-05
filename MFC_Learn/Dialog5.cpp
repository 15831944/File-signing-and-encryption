// Dialog5.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_Learn.h"
#include "Dialog5.h"
#include "afxdialogex.h"


// Dialog5 对话框

IMPLEMENT_DYNAMIC(Dialog5, CDialogEx)

Dialog5::Dialog5(CWnd* pParent /*=NULL*/)
	: CDialogEx(Dialog5::IDD, pParent)
{

}

Dialog5::~Dialog5()
{
}

void Dialog5::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Dialog5, CDialogEx)
	ON_BN_CLICKED(IDOK, &Dialog5::OnBnClickedOk)
END_MESSAGE_MAP()


// Dialog5 消息处理程序


void Dialog5::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
