// ClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DsValue.h"
#include "ClientDlg.h"


// CClientDlg �Ի���

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


// CClientDlg ��Ϣ�������

void CClientDlg::OnSend()
{
	int b = 5;
}

void CClientDlg::OnRecive()
{
	int c = 8;
}
