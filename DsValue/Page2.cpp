// Page2.cpp : 实现文件
//

#include "stdafx.h"
#include "DsValue.h"
#include "Page2.h"
#include "json/json.h"
#include "DsValueDlg.h"
// CPage2 对话框

IMPLEMENT_DYNAMIC(CPage2, CDialog)

CPage2::CPage2(CWnd* pParent /*=NULL*/)
	: CDialog(CPage2::IDD, pParent)
{
	m_commandstr = "";
}

CPage2::~CPage2()
{
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_EDIT2, m_count);
	DDX_Control(pDX, IDC_EDIT3, m_listret);
}


BEGIN_MESSAGE_MAP(CPage2, CDialog)
	ON_BN_CLICKED(ID_Send, &CPage2::OnBnClickedSend)
END_MESSAGE_MAP()


// CPage2 消息处理程序


void CPage2::OnBnClickedSend()
{
	Json::Value root;
	Json::Value arrayObj;  
	Json::Value item;
	CString key = "";
	m_edit.GetWindowText(key);
	if (key.IsEmpty())
	{
		//AfxMessageBox(_T("address can't empty"));
	}
	CString acount = "";
	m_count.GetWindowText(acount);
	if (!isdigit(acount.GetString()))
	{
		//AfxMessageBox(_T("send money must be numebuer"));
	}
	double sendtoMoney = atof(acount.GetString());
	if (sendtoMoney < 0 )
	{
		//AfxMessageBox(_T("send money can't empty"));
	}
	CString str;
	int i = 1;
	str.Format("{\"%s\":\"%s\",\"%s\":","method","sendtoaddress","params");
	str.AppendFormat("[\"%s\",%.8f],\"id\":%d}\n",key.GetString(),sendtoMoney,i);

	m_commandstr = str;
	CWnd* m_pMainWnd = AfxGetApp()->m_pMainWnd;
	m_pMainWnd->SendMessage(WM_MY_SendMoney,0,0);
}
