// Page4.cpp : 实现文件
//

#include "stdafx.h"
#include "DsValue.h"
#include "Page4.h"
#include "DsValueDlg.h"

// CPage4 对话框

IMPLEMENT_DYNAMIC(CPage4, CDialog)

CPage4::CPage4(CWnd* pParent /*=NULL*/)
	: CDialog(CPage4::IDD, pParent)
{

}

CPage4::~CPage4()
{
}

void CPage4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_height);
}


BEGIN_MESSAGE_MAP(CPage4, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CPage4::OnBnClickedButton1)
END_MESSAGE_MAP()


// CPage4 消息处理程序
void CPage4::OnBnClickedButton1()
{
	CString str = "";
	CString temp = "";
	int height = 0;
	m_height.GetWindowText(temp);
	if (temp.IsEmpty() || !isdigit(temp.GetString()))
	{
		//AfxMessageBox("the heigt must be number");
		m_height.SetFocus();
	}
	height = atoi(temp);
	height = (height+1)*60 + 58;
	int i = 1;
	str.Format("{\"%s\":\"%s\",\"%s\":","method","getluckynum","params");
	str.AppendFormat("[%d],\"id\":%d}\n",height,i);
	m_commandstr = str;
	CWnd* m_pMainWnd = AfxGetApp()->m_pMainWnd;
	m_pMainWnd->SendMessage(WM_MY_SendQuery,0,0);
}
void CPage4::OnSetLuckNumber(CString str15_6,CString red,CString blue)
{
	
	((CEdit*)GetDlgItem(IDC_EDIT2))->SetWindowText(str15_6);
	((CEdit*)GetDlgItem(IDC_EDIT3))->SetWindowText(red);
	((CEdit*)GetDlgItem(IDC_EDIT4))->SetWindowText(blue);

}

void CPage4::SetNull()
{

	((CEdit*)GetDlgItem(IDC_EDIT2))->SetWindowText("");
	((CEdit*)GetDlgItem(IDC_EDIT3))->SetWindowText("");
	((CEdit*)GetDlgItem(IDC_EDIT4))->SetWindowText("");

}

void CPage4::OnErrorMessage(CString strError)
{

	((CStatic*)GetDlgItem(IDC_ERROR))->SetWindowText(strError);

}