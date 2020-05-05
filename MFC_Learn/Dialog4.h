#pragma once


// Dialog4 对话框

class Dialog4 : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog4)

public:
	Dialog4(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dialog4();
	friend class Dialog2;
// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	char UK[128];
	char RK[128];
	char Rn[128];
	int len[3];

public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
