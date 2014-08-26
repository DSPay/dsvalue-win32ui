// ClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DsValue.h"
#include "ClientDlg.h"


// CClientDlg 对话框

IMPLEMENT_DYNAMIC(CClientDlg, CDialog)

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{

}

CClientDlg::~CClientDlg()
{
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	ON_BN_CLICKED(IDC_Send, &CClientDlg::OnSend)
	ON_BN_CLICKED(IDC_Recive, &CClientDlg::OnRecive)
END_MESSAGE_MAP()


// CClientDlg 消息处理程序

void CClientDlg::OnSend()
{
	int b = 5;
}

void CClientDlg::OnRecive()
{
	int c = 8;
}
