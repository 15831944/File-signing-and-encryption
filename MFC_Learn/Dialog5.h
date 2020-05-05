#pragma once


// Dialog5 对话框

class Dialog5 : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog5)

public:
	Dialog5(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dialog5();

// 对话框数据
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
