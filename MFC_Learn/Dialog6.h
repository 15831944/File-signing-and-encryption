#pragma once


// Dialog6 对话框

class Dialog6 : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog6)

public:
	Dialog6(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dialog6();

// 对话框数据
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
