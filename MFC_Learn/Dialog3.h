#pragma once


// Dialog3 �Ի���

class Dialog3 : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog3)

public:
	Dialog3(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dialog3();
	friend class Dialog1;
// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	char UK[128];
	char RK[128];
	char Rn[128];
	char DKey[128];
	int len[3];
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
