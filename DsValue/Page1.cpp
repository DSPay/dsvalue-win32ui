// Page1.cpp : 实现文件
//

#include "stdafx.h"
#include "DsValue.h"
#include "Page1.h"


// CPage1 对话框

IMPLEMENT_DYNAMIC(CPage1, CDialog)

CPage1::CPage1(CWnd* pParent /*=NULL*/)
	: CDialog(CPage1::IDD, pParent)
{

}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC3, m_txt);
}


BEGIN_MESSAGE_MAP(CPage1, CDialog)
END_MESSAGE_MAP()


// CPage1 消息处理程序
