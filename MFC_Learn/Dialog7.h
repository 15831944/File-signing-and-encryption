#pragma once


// Dialog7 �Ի���

class Dialog7 : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog7)

public:
	Dialog7(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dialog7();

// �Ի�������
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
