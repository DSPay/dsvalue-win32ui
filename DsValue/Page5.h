#pragma once
#include <string.h>
#include <iostream>
#include "afxcmn.h"
#include "afxwin.h"
using namespace std;

// CPage5 对话框

class CPage5 : public CDialog
{
	DECLARE_DYNAMIC(CPage5)

public:
	CPage5(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPage5();

// 对话框数据
	enum { IDD = IDD_PAGE5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_address;
	string m_commandstr;
	afx_msg void OnBnClickedButton1();
	void SetResult(CString str);
	CEdit m_edit;
	afx_msg void OnBnClickedButton2();
};
