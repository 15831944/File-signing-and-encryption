#pragma once


// Dialog5 �Ի���

class Dialog5 : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog5)

public:
	Dialog5(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dialog5();

// �Ի�������
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
