#pragma once


// Dialog7 对话框

class Dialog7 : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog7)

public:
	Dialog7(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dialog7();

// 对话框数据
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
