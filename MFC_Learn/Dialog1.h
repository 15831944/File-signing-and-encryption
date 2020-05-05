#pragma once
#include <vector>
#include "afxwin.h"
#include "Dialog3.h"

using namespace std;
// Dialog1 对话框

class Dialog1 : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog1)

public:
	Dialog1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dialog1();
// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton6();
private:
	vector <char> fileinArray;
	vector <char> fileoutArray;
	char deskeyArray[32];
	char rsakeyArray[128];
	char rsanArray[128];
	Dialog3 dlg3;
public:
	CEdit edit1;
	CEdit edit2;
	CEdit edit3;
	CEdit edit4;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton7();
	CEdit edit5;
};
