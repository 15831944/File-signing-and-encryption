// Dialog7.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_Learn.h"
#include "Dialog7.h"
#include "afxdialogex.h"


// Dialog7 对话框

IMPLEMENT_DYNAMIC(Dialog7, CDialogEx)

Dialog7::Dialog7(CWnd* pParent /*=NULL*/)
	: CDialogEx(Dialog7::IDD, pParent)
{

}

Dialog7::~Dialog7()
{
}

void Dialog7::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Dialog7, CDialogEx)
END_MESSAGE_MAP()


// Dialog7 消息处理程序
