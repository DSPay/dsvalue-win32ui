#pragma once
#include "afxwin.h"
#include <string.h>
#include <iostream>
#include <sstream>
using namespace std;

// CPage4 �Ի���

class CPage4 : public CDialog
{
	DECLARE_DYNAMIC(CPage4)

public:
	CPage4(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPage4();

// �Ի�������
	enum { IDD = IDD_PAGE4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	void OnSetLuckNumber(CString str15_6,CString red,CString blue);
	void OnErrorMessage(CString strError);
	void SetNull();
	CEdit m_height;
	string m_commandstr;
};
