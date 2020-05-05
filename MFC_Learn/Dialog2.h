#pragma once
#include <vector>
#include "afxwin.h"
#include "Dialog4.h"
using namespace std;
// Dialog2 对话框

class Dialog2 : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog2)

public:
	Dialog2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dialog2();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	vector <char> fileinArray;
	vector <char> fileoutArray;
	char rsakeyArray[128];
	char rsanArray[128];
	Dialog4 dlg4;
public:
	CEdit edit1;
	CEdit edit2;
	CEdit edit3;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
};
