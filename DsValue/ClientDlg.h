#pragma once


// CClientDlg 对话框

class CClientDlg : public CDialog
{
	DECLARE_DYNAMIC(CClientDlg)

public:
	CClientDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CClientDlg();

// 对话框数据
	enum { IDD = IDD_DSVALUE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSend();
	afx_msg void OnRecive();
};
