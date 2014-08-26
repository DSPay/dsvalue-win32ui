// Page5.cpp : 实现文件
//

#include "stdafx.h"
#include "DsValue.h"
#include "Page5.h"
#include "DsValueDlg.h"
#include "json\json.h"

// CPage5 对话框

IMPLEMENT_DYNAMIC(CPage5, CDialog)

CPage5::CPage5(CWnd* pParent /*=NULL*/)
	: CDialog(CPage5::IDD, pParent)
{

}

CPage5::~CPage5()
{
}

void CPage5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_address);
	DDX_Control(pDX, IDC_EDIT3, m_edit);
}


BEGIN_MESSAGE_MAP(CPage5, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CPage5::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPage5::OnBnClickedButton2)
END_MESSAGE_MAP()


// CPage5 消息处理程序

void CPage5::OnBnClickedButton1()
{
	CString str = "";
	m_address.GetWindowText(str);

	Json::Value root;

	root["method"] = "getrewardbyaddr";
	root["params"].append(str.GetString());

	m_commandstr = root.toStyledString();
	CWnd* m_pMainWnd = AfxGetApp()->m_pMainWnd;
	m_pMainWnd->SendMessage(WM_MY_GetAddressRward,0,0);
}
void CPage5::SetResult(CString str)
{
	UpdateData(TRUE);
	str.TrimLeft("\"");
	CString strValue = str.Mid(0,str.GetLength()-2);
	CString nTemp = "";
	int pos = strValue.Find(",");
	CString strold = "";
	m_edit.GetWindowText(strold);
	while(pos >=0)
	{
		CString addstr = strValue.Left(pos+1);
		strValue = strValue.Mid(pos+1);
		pos = strValue.Find(",");
		//m_list.InsertString(-1, addstr);
		nTemp.AppendFormat("%s\r\n",addstr);
		//m_list.SetTopIndex(m_list.GetCount() - 1);
		

	}
	//m_list.InsertString(-1, strValue);
	//m_list.SetTopIndex(m_list.GetCount() - 1);
	nTemp.AppendFormat("%s\r\n",strValue);
	strold.AppendFormat("%s",nTemp);
	m_edit.SetWindowText(strold);
	//m_edit.SetWindowText(strValue);
	UpdateData(false);

}
void CPage5::OnBnClickedButton2()
{
	m_edit.SetWindowText("");
}
