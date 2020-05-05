// Dialog6.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_Learn.h"
#include "Dialog6.h"
#include "afxdialogex.h"


// Dialog6 对话框

IMPLEMENT_DYNAMIC(Dialog6, CDialogEx)

Dialog6::Dialog6(CWnd* pParent /*=NULL*/)
	: CDialogEx(Dialog6::IDD, pParent)
{

}

Dialog6::~Dialog6()
{
}

void Dialog6::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Dialog6, CDialogEx)
END_MESSAGE_MAP()


// Dialog6 消息处理程序
