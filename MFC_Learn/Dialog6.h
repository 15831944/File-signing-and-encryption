#pragma once


// Dialog6 �Ի���

class Dialog6 : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog6)

public:
	Dialog6(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dialog6();

// �Ի�������
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
