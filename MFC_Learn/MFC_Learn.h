
// MFC_Learn.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFC_LearnApp:
// �йش����ʵ�֣������ MFC_Learn.cpp
//

class CMFC_LearnApp : public CWinApp
{
public:
	CMFC_LearnApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFC_LearnApp theApp;