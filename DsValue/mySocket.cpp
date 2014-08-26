// mySocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DsValue.h"
#include "mySocket.h"
#include "DsValueDlg.h"

// mySocket

CmySocket::CmySocket()
: m_pWnd(NULL)
{
}

CmySocket::~CmySocket()
{
	if(m_hSocket !=INVALID_SOCKET) 
	{
		Close();
	}
}


// mySocket ��Ա����

void CmySocket::SetParent(CDialog *pWnd)
{
	m_pWnd = pWnd;
}
void CmySocket::OnReceive(int nErrorCode)
{

	((CDsValueDlg*)m_pWnd)->OnRecive();
	CAsyncSocket::OnReceive(nErrorCode);
}

 void CmySocket::OnClose(int nErrorCode) 
 {
	 // TODO: Add your specialized code here and/or call the base class
	 ((CDsValueDlg*)m_pWnd)->Close();
	 CAsyncSocket::OnClose(nErrorCode);
 }

