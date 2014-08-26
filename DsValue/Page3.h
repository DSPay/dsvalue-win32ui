#pragma once
#include "afxwin.h"
#include <string.h>
#include <iostream>
using namespace std;

// CPage3 对话框

class CPage3 : public CDialog
{
	DECLARE_DYNAMIC(CPage3)

public:
	CPage3(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPage3();

// 对话框数据
	enum { IDD = IDD_PAGE3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 
	DECLARE_MESSAGE_MAP()
private:
		bool is_Getaddress;
public:
	afx_msg void OnBnClickedButton1();
	CString getvchSelect(int selectsize,int totalsize);
	CEdit m_preNumber;
	CEdit m_ret;
	CEdit m_number2;
	string m_commandstr;
	afx_msg void OnCbnSelchangeCombo1();
	CEdit m_address;
	CEdit m_sendmoney;
	CComboBox m_betc;
	CComboBox m_blue;
	bool isGetaddress();
	void SetAddressFlag();
	afx_msg void OnCbnSelchangeSelectNum();
	afx_msg void OnCbnSelchangeBlue();
	afx_msg void OnBnClickedGetaddress();
	CString HextoStr(CString str);
	void ComputeAmountPeerBet(CString nSelectNumber,CString blue,double value);
	CEdit m_amoutbet;
	void Clear();
	afx_msg void OnEnChangeAcount();
	afx_msg void OnEnChangePeerbet();
	void ComputeAmountBet(CString nSelectNumber,CString blue,double value);
	double ComputeAmuont(CString nSelectNumber,CString blue,double value);
	double ComputePeerBet(CString nSelectNumber,CString blue,double value);
	long nCurrentTime;
	long nPCurrentTime;
	CStatic m_staticTotalBet;
	afx_msg void OnEnChangeComputeTotalBet();
	afx_msg void OnEnChangeMulitCountBet();
};
