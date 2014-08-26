// DsValueDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DsValue.h"
#include "DsValueDlg.h"
#include "json\json.h"
#include <Windows.h>
#include <fstream>
#include <Tlhelp32.h>  
#include <shlwapi.h>
#include <afxmt.h >
#pragma comment(lib,"Shlwapi.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CDsValueDlg dialog




CDsValueDlg::CDsValueDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDsValueDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_sendPreHeadstr = "";
	m_sendendHeadstr = "";
	m_sendCommand = "";
	m_recivestr = "";
	rpcuser = "";
	rpcpassword = "";
	m_noTab = false;
	m_Timer = false;
	m_isming = false;
	is_connect = false;
}
CDsValueDlg:: ~CDsValueDlg()
{
	if(sever_pi.hProcess)
		CloseHandle(sever_pi.hProcess);
	if(sever_pi.hThread)
		CloseHandle( sever_pi.hThread);
	CloseProcess("dspayd.exe");
}
void CDsValueDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Control(pDX, IDC_MESSAGE, m_rpc);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}

BEGIN_MESSAGE_MAP(CDsValueDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CDsValueDlg::OnTcnSelchangeTab)
	ON_MESSAGE(WM_MY_SendMoney, OnSendMessage)
	ON_MESSAGE(WM_MY_SendBet, OnSendBetMessage)
	ON_MESSAGE(WM_MY_SendQuery, OnSendQueryLuckNumMessage)
	ON_MESSAGE(WM_MY_GetAddress, OnGetWalletAddressMessage)
	ON_MESSAGE(WM_MY_GetAddressRward, OnGetAddressRewardMessage)
	ON_BN_CLICKED(IDC_BUTTON1, &CDsValueDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDsValueDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_CLEAR, &CDsValueDlg::OnBnClickedClear)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &CDsValueDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CDsValueDlg message handlers

BOOL CDsValueDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	InitializeCriticalSection(&g_cs); 
	CloseProcess("dspayd.exe");
	StartSeverProcess();
	Sleep(8000);
	if (!AfxSocketInit())
	{
		MessageBox("WindowSocket initial failed!", "Receive", MB_ICONSTOP);
	}
	m_connectsocket.SetParent(this);
	ConnetSever();

	m_tab.InsertItem(0,_T("WalletCount"));
	m_tab.InsertItem(1,_T("SendMoney"));
	m_tab.InsertItem(2,_T("SendBet"));
	m_tab.InsertItem(3,_T("Query luckNO."));
	m_tab.InsertItem(4,_T("Query Address Reward"));
	m_page1.Create(IDD_PAGE1,GetDlgItem(IDC_TAB1));
	m_page2.Create(IDD_PAGE2,GetDlgItem(IDC_TAB1));
	m_page3.Create(IDD_PAGE3,GetDlgItem(IDC_TAB1));
	m_page4.Create(IDD_PAGE4,GetDlgItem(IDC_TAB1));
	m_page5.Create(IDD_PAGE5,GetDlgItem(IDC_TAB1));
	CRect rs;
	m_tab.GetClientRect(&rs);
	rs.top +=30;
	rs.bottom -=60;
	rs.left +=1;
	rs.right -=2;

	m_page1.MoveWindow(&rs);
	m_page2.MoveWindow(&rs);
	m_page3.MoveWindow(&rs);
	m_page4.MoveWindow(&rs);
	m_page5.MoveWindow(&rs);

	m_page1.ShowWindow(true);
	m_page2.ShowWindow(false);
	m_page3.ShowWindow(false);
	m_page4.ShowWindow(false);
	m_page5.ShowWindow(false);

	m_tab.SetCurSel(0);

	m_sendCommand = "{\"method\":\"getbalance\",\"params\":[],\"id\":1}\n";
	//m_sendCommand ="{\"method\":\"sendtoaddress\",\"params\":[\"DpsRwrmb9UVHRQv7YoRqooHq9jACbB3hhP\",1.00000000],\"id\":1}";
	OnSend();
	m_recivestr = "";
	//SetTimer(1,10000,NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDsValueDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDsValueDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDsValueDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDsValueDlg::OnSend()
{
	UpdateData(TRUE);
	int nLen = 0;
	int nSend = 0;

	string nSendStr = "";
	nSendStr += m_sendPreHeadstr;
	CString nMidStr = "Content-Length: ";
	nMidStr.AppendFormat("%d\r\n",m_sendCommand.length());
	nSendStr += nMidStr.GetString();
	nSendStr += m_sendendHeadstr + m_sendCommand;
	int len = m_sendCommand.length();
	if (nSendStr.c_str() != NULL)
	{
		nLen = nSendStr.length();
		EnterCriticalSection(&g_cs);
		nSend = m_connectsocket.Send(nSendStr.c_str(),nLen);
		if (nSend == SOCKET_ERROR)
		{
			AfxMessageBox("socket error");
		}
		LeaveCriticalSection(&g_cs);
	}
}

void CDsValueDlg::OnRecive()
{

	//mutexObj.Lock(); 
	static int b = 0;
	TRACE("%d\r\n",b);
	b++;
	char *recBuffer = NULL;
	recBuffer = (char *)malloc(4096*4);
	if (recBuffer == NULL)
	{
		AfxMessageBox("memeroy filaid");
	}
	memset(recBuffer,0,4096*4);
	int bufferSize = 4096*4 - 1;
	int iRcvd; 
	CString str;

	iRcvd = m_connectsocket.Receive(recBuffer,bufferSize);
	if (iRcvd > 0)
	{
		recBuffer[iRcvd] = '\0';
		m_recivestr = "";
		recBuffer[iRcvd] = NULL;
		str= recBuffer;
		m_recivestr = GetResultStr(str);
		if (m_noTab)
		{
			ParseJsonToList(m_recivestr.c_str());
			m_noTab = false;
		}
		else if (m_Timer)
		{
			EnterCriticalSection(&g_cs);
			Json::Reader reader; 
			Json::Value value;
			if(reader.parse(m_recivestr,value))
			{  
				string str = "";
				if (!value.isNull())
				{
					Json::Value obj = value["result"];
					str = obj.toStyledString();
				}
				m_page1.m_txt.SetWindowText(str.c_str());
			} 
			LeaveCriticalSection(&g_cs);
			m_Timer = false;
		}
		else if (m_isming)
		{
			m_isming = false;
		}
		else
		{
			ShowResult();
		}
		UpdateData(FALSE);
	}
	if (recBuffer != NULL)
	{
		free(recBuffer);
		recBuffer = NULL;
	} 
}

void CDsValueDlg::OnClose()
{
	EnterCriticalSection(&g_cs);
	m_connectsocket.Close();
	is_connect  = false;
	LeaveCriticalSection(&g_cs);
	CDialog::OnClose();
}
void CDsValueDlg::Close()
{
	EnterCriticalSection(&g_cs);
	m_connectsocket.Close();
	is_connect  = false;
	LeaveCriticalSection(&g_cs);
}
CString CDsValueDlg::GetResultStr(CString message)
{
	CString ret = "";
	int pos = message.Find("Server:");
	if (pos >=0)
	{
		pos = message.Find('\n',pos);
		if (pos >=0)
		{
			ret = message.Mid(pos);
	
		}
	}
	return ret;
}
void CDsValueDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	int CurSel = m_tab.GetCurSel();
	switch(CurSel)
	{
		case 0:
		{
			m_page1.ShowWindow(true);
			m_page2.ShowWindow(false);
			m_page3.ShowWindow(false);
			m_page4.ShowWindow(false);
			m_page5.ShowWindow(false);
			m_sendCommand = "{\"method\":\"getbalance\",\"params\":[],\"id\":1}\n";
			ConnetSever();
			OnSend();
			break;
		}
		case 1:
		{
			m_page1.ShowWindow(false);
			m_page2.ShowWindow(true);
			m_page3.ShowWindow(false);
			m_page4.ShowWindow(false);
			m_page5.ShowWindow(false);
			break;
		}
		case 2:
		{
			m_page1.ShowWindow(false);
			m_page2.ShowWindow(false);
			m_page3.ShowWindow(true);
			m_page4.ShowWindow(false);
			m_page5.ShowWindow(false);
			m_page3.Clear();
			break;
		}
		case 3:
			{
				m_page1.ShowWindow(false);
				m_page2.ShowWindow(false);
				m_page3.ShowWindow(false);
				m_page4.ShowWindow(true);
				m_page5.ShowWindow(false);
				break;
			}
		case 4:
			{
				m_page1.ShowWindow(false);
				m_page2.ShowWindow(false);
				m_page3.ShowWindow(false);
				m_page4.ShowWindow(false);
				m_page5.ShowWindow(true);
				break;
			}
		default:break;
	}
	*pResult = 0;
}
void  CDsValueDlg::ShowResult()
{
	
	int CurSel = m_tab.GetCurSel();
	if (m_recivestr == "")
	{
		return;
	}
	switch(CurSel)
	{
	case 0:
		{

			EnterCriticalSection(&g_cs);
			Json::Reader reader; 
			Json::Value value;
			if(reader.parse(m_recivestr,value))
			{  
				string str;
				if (!value.isNull())//&&value.isDouble())
				{
					str = value["result"].toStyledString();
				}
				 
				m_page1.m_txt.SetWindowText(str.c_str());
			} 
			LeaveCriticalSection(&g_cs);
			break;
		}
	case 1:
		{
			EnterCriticalSection(&g_cs);
			Json::Reader reader; 
			Json::Value value;
			if(reader.parse(m_recivestr,value))
			{  
				string txHash = "";
				if (!value.isNull())
				{
					txHash = value["result"].toStyledString();
				}
				if (txHash != "")
				{
					m_page2.m_listret.SetWindowText(txHash.c_str());
				}
				else
				{
					m_page2.m_listret.SetWindowText("not enough money");
				}
			}  
			LeaveCriticalSection(&g_cs);
			break;
		}
	case 2:
			{
				EnterCriticalSection(&g_cs);

				Json::Reader reader; 
				Json::Value value;
				if(reader.parse(m_recivestr,value))
				{  
					if (m_page3.isGetaddress())
					{
						if (!value.isNull())
						{
							Json::Value::UInt i;
							i = 0;
							Json::Value obj = value["result"][i];
							CString str = obj.toStyledString().c_str();
							str.Replace('\"',' ');
							str.TrimLeft();
							str.TrimRight();
							m_page3.SetAddressFlag();
							m_page3.m_address.SetWindowText(str);
						}
					}
					else
					{
						string txHash = "";
						if (!value.isNull())//&&value.isString())
						{
							txHash = value["result"].toStyledString();
						}
						if (txHash != "")
						{
							m_page3.m_ret.SetWindowText(txHash.c_str());
						}
						else
						{
							m_page3.m_ret.SetWindowText("not enough money");
						}

					}
				}  

				LeaveCriticalSection(&g_cs);
				break;
			}
		case 3:
			{
				EnterCriticalSection(&g_cs);
				Json::Reader reader; 
				Json::Value value;
				if(reader.parse(m_recivestr,value))
				{  
					CString txHash = "";
					if (!value.isNull()&& value.isObject())
					{
						Json::Value obj = value["result"];
						if (obj.isValidIndex(1))
						{
							CString str156 = obj["0"].asCString();
							CString strMui = obj["1"].asCString();
							string str= strMui.GetString();
							int pos = str.find_last_of("ff");
							if (pos >0)
							{
								string temp = str.substr(pos+1);
								CString blue=temp.c_str();
								temp=str.substr(0,pos-1);
								CString red = temp.c_str();
								m_page4.OnSetLuckNumber(str156,red,blue);
							}
							m_page4.OnErrorMessage("");
						}
						else
						{
							m_page4.SetNull();
							m_page4.OnErrorMessage("not send lotto key or over height");
						}
	
					}
				}  
				LeaveCriticalSection(&g_cs);
				break;
			}
		case 4:
			{
				Json::Reader reader; 
				Json::Value value;
				if(reader.parse(m_recivestr,value))
				{  
					if (!value.isNull())
					{
						Json::Value obj = value["result"];
					  string str = obj.toStyledString();
					  m_page5.SetResult(str.c_str());
					}
				}  
				break;
			}
		default:break;
	}
}
LRESULT CDsValueDlg::OnSendMessage(WPARAM wParam, LPARAM lParam)
{
	m_sendCommand = m_page2.m_commandstr;
	ConnetSever();
	OnSend();
	 return 0;
}
void CDsValueDlg::ConnetSever()
{

	EnterCriticalSection(&g_cs);
	if (!AfxSocketInit())
	{
		MessageBox("WindowSocket initial failed!", "Receive", MB_ICONSTOP);
	}
	if (is_connect)
	{
		return;
	}
	int err =0;
	do 
	{
		try
		{
			m_connectsocket.m_hSocket=INVALID_SOCKET;

			UpdateData(true);
			if(m_connectsocket.Create())
			{
				err = m_connectsocket.Connect(_T("127.0.0.1"),8667);
				if (err != SOCKET_ERROR)
				{
					break;
					is_connect = true;
				}
				Sleep(10);
			}
			else
			{
				 AfxMessageBox("SOCKET ERROR");
				 return;
			}
		}
		catch (CException* e)
		{
			CString message = "";
			char buffer[1024] = {0};
			e->GetErrorMessage(buffer,1024);
			AfxMessageBox(buffer);
		}
	}while (true);
	LeaveCriticalSection(&g_cs);

}

LRESULT CDsValueDlg::OnSendBetMessage(WPARAM wParam, LPARAM lParam)
{
	m_sendCommand = m_page3.m_commandstr;
	ConnetSever();
	OnSend();
	return 0;
}
LRESULT CDsValueDlg::OnSendQueryLuckNumMessage(WPARAM wParam, LPARAM lParam)
{
	m_sendCommand = m_page4.m_commandstr;
	ConnetSever();
	OnSend();
	return 0;
}
bool isdigit(string pstr)
{
	CString temp = pstr.c_str();temp.Replace(' ','0');
	pstr = temp.GetString();
	if(pstr != "")
	{
		string numstr(pstr);
		if(	string::npos == numstr.find_first_not_of("0123456789"))
		{
			return true;
		}
	}
	return false;
}
void CDsValueDlg::StartSeverProcess()
{
	STARTUPINFO si; 
	memset(&si, 0, sizeof(STARTUPINFO));  
	si.cb = sizeof(STARTUPINFO);  
	si.dwFlags = STARTF_USESHOWWINDOW;  
	si.wShowWindow =SW_HIDE; //SW_SHOW;  

	char  exepath[MAX_PATH];
	CString  strdir,tmpdir; 
	memset(exepath,0,MAX_PATH); 
	GetModuleFileName(NULL,exepath,MAX_PATH); 
	tmpdir=exepath; 
	strdir=tmpdir.Left(tmpdir.ReverseFind('\\'));
	ProductHttpHead(strdir);
	CString str = "dspayd.exe -datadir=";
	str.AppendFormat("%s",strdir); //\\dspay

	if(!CreateProcess(NULL,(LPSTR)str.GetString(),NULL,NULL,FALSE,0,NULL,NULL,&si,&sever_pi))   
	{  
		AfxMessageBox("sever error!");
		exit(1);  
	}  
}
void CDsValueDlg::CloseProcess(string exename)
{
	HANDLE SnapShot,ProcessHandle;  
	SHFILEINFO shSmall;  
	PROCESSENTRY32 ProcessInfo;   
	int count  = 0;
	while(1)  
	{  
		SnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);  
		if(SnapShot!=NULL)   
		{  
			ProcessInfo.dwSize=sizeof(ProcessInfo);
			BOOL Status=Process32First(SnapShot,&ProcessInfo);  
			while(Status)  
			{    
				SHGetFileInfo(ProcessInfo.szExeFile,0,&shSmall,  
					sizeof(shSmall),SHGFI_ICON|SHGFI_SMALLICON);  
				strlwr(ProcessInfo.szExeFile);  
				for(int i=0;i<3;i++)  
					if(!strcmp(strlwr((LPSTR)exename.c_str()),ProcessInfo.szExeFile))   
					{  

						ProcessHandle=OpenProcess(PROCESS_ALL_ACCESS,FALSE,ProcessInfo.th32ProcessID);  
						TerminateProcess(ProcessHandle,0);  
						return;  
					}  
					Status=Process32Next(SnapShot,&ProcessInfo);  
			}  
			break;
		}  

		Sleep(1000);  
	}  

}
void CDsValueDlg::OnBnClickedButton1()
{
	CString str = "";
	int i = 1;
	str.Format("{\"%s\":\"%s\",\"%s\":","method","setgenerate","params");
	str.AppendFormat("[%s],\"id\":1}\n","true");
	m_sendCommand = str;
	ConnetSever();
	OnSend();
	m_isming = true;
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
}

void CDsValueDlg::OnBnClickedButton2()
{
	CString str = "";
	int i = 1;
	str.Format("{\"%s\":\"%s\",\"%s\":","method","setgenerate","params");
	str.AppendFormat("[%s],\"id\":1}\n","false");
	m_sendCommand = str;
	ConnetSever();
	OnSend();
	m_isming = true;
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	
}

CString rand_str(const int len)
{
	CString str = "";
	int i;
	for(i=0;i<len;++i)
	{
		char Temp = 'A'+rand()%26;
		str.AppendChar(Temp);
	}
	return str;
}
void CDsValueDlg::ProductHttpHead(CString configdir)
{
	CString configpath = "";
	configpath.AppendFormat("%s",configdir);
	configpath.AppendFormat("\\%s","dspay.conf");
	BOOL userflag = false;
	BOOL passFlag = false;
	CString strTemp = "";
	CString user = "";
	if (PathFileExists(configpath))
	{
		fstream mfile;
		mfile.open(configpath,ios::in);
		string linestr = "";
		while(!mfile.eof())
		{
			getline(mfile,linestr);
			strTemp=linestr.c_str() ;
			int upos = strTemp.Find("rpcuser");
			int passpos = strTemp.Find("rpcpassword");
			if (passpos>=0)
			{
				passpos = strTemp.Find("=",passpos);
				rpcpassword= strTemp.Mid(passpos+1);
				userflag = TRUE;
			}
			if (upos >=0)
			{
				upos = strTemp.Find("=",upos);
				rpcuser= strTemp.Mid(upos+1);
				user = strTemp.Mid(upos+1);
				passFlag = TRUE;
			}


		}
	}

	static const int LEN_NAME = 8;
	if (!userflag)
	{
		srand(time(NULL));
		//char name[LEN_NAME+2] = {0};
		//rand_str(LEN_NAME);
		CString name = rand_str(LEN_NAME+1);
		strTemp.AppendFormat("%s%s\r\n","rpcuser=",name);
		rpcuser = name.GetString();
	}
	if (!passFlag)
	{
		srand(time(NULL)+100);
		//char name[LEN_NAME+1] = {0};
		//rand_str(name,LEN_NAME);
		CString rpcpass= rand_str(LEN_NAME+1);
		strTemp.AppendFormat("%s%s\r\n","rpcpassword=",rpcpass);
		rpcpassword = rpcpass.GetString();
	}
	if (!userflag||!passFlag )
	{
		CFile mFile;
		mFile.Open(configpath,CFile::modeCreate|CFile::modeWrite);

		mFile.Write((LPSTR)strTemp.GetString(),strTemp.GetLength());
		mFile.Close();
	}

	CString UserPass = "";
	if (rpcuser!= "" && rpcpassword!="")
	{

		UserPass = rpcuser.c_str();
		UserPass.TrimLeft();
		UserPass.TrimRight();
		CString temp = rpcpassword.c_str();
		temp.TrimLeft();
		temp.TrimRight();
		UserPass.AppendFormat(":%s",temp);
		string strUserPass64 = EncodeBase64(UserPass.GetString());

		m_sendPreHeadstr += "POST / HTTP/1.1\r\n";
		m_sendPreHeadstr +=	"User-Agent: bitcoin-json-rpc/v0.9.1.0-g026a939-beta\r\n";
		m_sendPreHeadstr +=	"Host: 127.0.0.1\r\n";
		m_sendPreHeadstr +="Content-Type: application/json\r\n";
		m_sendendHeadstr +="Connection: close\r\n";
		m_sendendHeadstr +="Accept: application/json\r\n";
		m_sendendHeadstr +="Authorization: Basic ";//ZHNwYXk6YWRtaW4=\r\n\r\n";
		m_sendendHeadstr +=strUserPass64+"\r\n\r\n";
	}
	else
	{
		AfxMessageBox(_T("Invald config error"));
	}


}
string CDsValueDlg::EncodeBase64(const unsigned char* pch, size_t len) {
	static const char *pbase64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	string strRet = "";
	strRet.reserve((len + 2) / 3 * 4);

	int mode = 0, left = 0;
	const unsigned char *pchEnd = pch + len;

	while (pch < pchEnd) {
		int enc = *(pch++);
		switch (mode) {
		case 0: // we have no bits
			strRet += pbase64[enc >> 2];
			left = (enc & 3) << 4;
			mode = 1;
			break;

		case 1: // we have two bits
			strRet += pbase64[left | (enc >> 4)];
			left = (enc & 15) << 2;
			mode = 2;
			break;

		case 2: // we have four bits
			strRet += pbase64[left | (enc >> 6)];
			strRet += pbase64[enc & 63];
			mode = 0;
			break;
		}
	}

	if (mode) {
		strRet += pbase64[left];
		strRet += '=';
		if (mode == 1)
			strRet += '=';
	}

	return strRet;
}
string CDsValueDlg::EncodeBase64(const string& str) {
	return EncodeBase64((const unsigned char*) str.c_str(), str.size());
}

void CDsValueDlg::ParseJsonToList(CString strValue)
{
	Json::Reader reader; 
	Json::Value value;
	if(reader.parse(strValue.GetString(),value))
	{
		Json::Value obj = value["result"];
		strValue = obj.toStyledString().c_str();
	}
	int pos = strValue.Find(",");
	CString strTemp = "";
	m_edit.GetWindowText(strTemp);
	while(pos >=0)
	{
		CString addstr = strValue.Left(pos+1);
		strValue = strValue.Mid(pos+1);
		pos = strValue.Find(",");
		strTemp.AppendFormat("%s\r\n",addstr);
		//m_list.InsertString(-1, addstr);
		//m_list.SetTopIndex(m_list.GetCount() - 1);

	}
	strTemp.AppendFormat("%s\r\n",strValue);
	m_edit.SetWindowText(strTemp);
	//m_list.InsertString(-1, strValue);
	//m_list.SetTopIndex(m_list.GetCount() - 1);
	//Close();
}

BOOL CDsValueDlg::PreTranslateMessage(MSG* pMsg)
{
	if(WM_KEYDOWN == pMsg->message)
	{
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_MESSAGE);
		ASSERT(pEdit);
		if(pMsg->hwnd == pEdit->GetSafeHwnd() && VK_RETURN == pMsg->wParam)
		{
			//AfxMessageBox(_T("OK"));
			CString mesg = "";
			((CEdit*)GetDlgItem(IDC_MESSAGE))->GetWindowText(mesg);
			if (mesg != "")
			{
				SendRPCCommand();
				
			}
			return TRUE;	
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
void  CDsValueDlg::SendRPCCommand()
{
	CString rpcCommand = "";
	m_rpc.GetWindowText(rpcCommand);
	Json::Value root;
	Json::Value arrayObj;  
	Json::Value item;

	int pos = rpcCommand.Find(" ");
	CString method ="";
	CString param ="";
	if (pos >=0)
	{
		method = rpcCommand.Left(pos);
		rpcCommand = rpcCommand.Mid(pos + 1);

	}
	else if (!rpcCommand.IsEmpty())
	{
		root["method"] = rpcCommand.GetString();
		root["params"]=arrayObj;
	}
	if (method != "")
	{
		root["method"] = method.GetString();
		pos = rpcCommand.Find(" ");
		while(pos >=0)
		{
			param = rpcCommand.Left(pos);
			rpcCommand = rpcCommand.Mid(pos + 1);
			if (param.GetLength()<10)
			{
				root["params"].append(atoi(param));
			}
			else
			{
				root["params"].append(param.GetString());
			}
				pos = rpcCommand.Find(" ");
		}
		if (rpcCommand.GetLength()<10)
		{
			root["params"].append(atoi(rpcCommand));
		}
		else
		{
			root["params"].append(rpcCommand.GetString());
		}
	}
// 	root["method"] = "getpeerinfo";
// 	root["params"]=arrayObj;
// 	root["id"] = 1;
	m_sendCommand = root.toStyledString();

	//m_sendCommand = "{\"method\":\"getinfo\",\"params\":[],\"id\":1}\n";;
	ConnetSever();
	OnSend();
	m_noTab = true;
}
void CDsValueDlg::OnBnClickedClear()
{
		//m_list.ResetContent();
		m_edit.SetWindowText("");
}

void CDsValueDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case 1:
		{
			m_sendCommand = "{\"method\":\"getbalance\",\"params\":[],\"id\":1}\n";
			ConnetSever();
			OnSend();
			m_Timer = true;
			break;
		}
	default: break;
	}

	CDialog::OnTimer(nIDEvent);
}

void CDsValueDlg::OnBnClickedButton3()
{
	SendRPCCommand();
}

LRESULT CDsValueDlg::OnGetWalletAddressMessage(WPARAM wParam, LPARAM lParam)
{
	m_sendCommand = "{\"method\":\"getaddressesbyaccount\",\"params\":[\"\"],\"id\":1}\n";
	ConnetSever();
	OnSend();
	return 0;
}
LRESULT CDsValueDlg::OnGetAddressRewardMessage(WPARAM wParam, LPARAM lParam)
{
	m_sendCommand = m_page5.m_commandstr;
	ConnetSever();
	OnSend();
	return 0;
}