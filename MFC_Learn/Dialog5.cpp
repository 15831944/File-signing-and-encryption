// Dialog5.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_Learn.h"
#include "Dialog5.h"
#include "afxdialogex.h"


// Dialog5 �Ի���

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


// Dialog5 ��Ϣ�������


void Dialog5::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
