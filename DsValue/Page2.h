#pragma once
#include "afxwin.h"
#include <string.h>
#include <iostream>
using namespace std;
// CPage2 �Ի���

class CPage2 : public CDialog
{
	DECLARE_DYNAMIC(CPage2)

public:
	CPage2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPage2();

// �Ի�������
	enum { IDD = IDD_PAGE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit;
	CEdit m_count;
	string m_commandstr;
	afx_msg void OnBnClickedSend();
	CEdit m_listret;
};
