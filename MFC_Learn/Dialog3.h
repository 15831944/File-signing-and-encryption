#pragma once


// Dialog3 对话框

class Dialog3 : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog3)

public:
	Dialog3(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dialog3();
	friend class Dialog1;
// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
