// DsValueDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "mySocket.h"
#include <string.h>
#include <iostream>
#include "afxcmn.h"
#include "Page1.h"
#include "Page2.h"
#include "Page3.h"
#include "Page4.h"
#include "Page5.h"
using namespace std;

#define WM_MY_SendMoney (WM_USER+100)  
#define WM_MY_SendBet (WM_USER+101) 
#define WM_MY_SendQuery (WM_USER+102)
#define WM_MY_GetAddress (WM_USER+103)
#define WM_MY_GetAddressRward (WM_USER+104)
// CDsValueDlg dialog
class CDsValueDlg : public CDialog
{
// Construction
public:
	CDsValueDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CDsValueDlg();
// Dialog Data
	enum { IDD = IDD_DSVALUE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	afx_msg LRESULT OnSendMessage(WPARAM wParam, LPARAM lParam); 
	afx_msg LRESULT OnSendBetMessage(WPARAM wParam, LPARAM lParam);  
	afx_msg LRESULT OnSendQueryLuckNumMessage(WPARAM wParam, LPARAM lParam); 
	afx_msg LRESULT OnGetWalletAddressMessage(WPARAM wParam, LPARAM lParam); 
	afx_msg LRESULT OnGetAddressRewardMessage(WPARAM wParam, LPARAM lParam); 

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void OnSend();
	void OnRecive();
	CString GetResultStr(CString message);
private:
	CmySocket m_connectsocket;
public:
	afx_msg void OnClose();
	void ConnetSever();
	CTabCtrl m_tab;
	CPage1 m_page1;
	CPage2 m_page2;
	CPage3 m_page3;
	CPage4 m_page4;
	CPage5 m_page5;
	string m_sendPreHeadstr;
	string m_sendendHeadstr;
	string m_sendCommand;
	string m_recivestr;
	string rpcuser;
	string rpcpassword;
	bool m_noTab;
	bool m_Timer;
	bool m_isming;
	bool is_connect;
	PROCESS_INFORMATION sever_pi; 
	CRITICAL_SECTION g_cs;
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	void ShowResult();
	void StartSeverProcess();
	void CloseProcess(string exename);
	void ProductHttpHead(CString configdir);

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	string EncodeBase64(const unsigned char* pch, size_t len);
	string EncodeBase64(const string& str);
	void ParseJsonToList(CString strValue);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void SendRpcCommand();
	CEdit m_rpc;
	afx_msg void OnBnClickedClear();
	void SendRPCCommand();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton3();
	void Close();
	CEdit m_edit;
};
bool isdigit(string pstr);