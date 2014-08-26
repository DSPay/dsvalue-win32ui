// Page3.cpp : 实现文件
//

#include "stdafx.h"
#include "DsValue.h"
#include "Page3.h"
#include "DsValueDlg.h"
#include <algorithm>
#include <vector>
#include <assert.h>
#include<time.h>
#define random(x) (rand()%x)
// CPage3 对话框

IMPLEMENT_DYNAMIC(CPage3, CDialog)

CPage3::CPage3(CWnd* pParent /*=NULL*/)
	: CDialog(CPage3::IDD, pParent)
{
	is_Getaddress = false;
	 nCurrentTime = 0;
	 nPCurrentTime = 0;
}

CPage3::~CPage3()
{

}

void CPage3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_preNumber);
	DDX_Control(pDX, IDC_EDIT4, m_ret);
	DDX_Control(pDX, IDC_EDIT5, m_number2);
	DDX_Control(pDX, IDC_ADDRESS, m_address);
	DDX_Control(pDX, IDC_ACOUNT, m_sendmoney);
	DDX_Control(pDX, IDC_COMBO2, m_betc);
	DDX_Control(pDX, IDC_COMBO3, m_blue);
	DDX_Control(pDX, IDC_PEERBET, m_amoutbet);
	DDX_Control(pDX, IDC_Total, m_staticTotalBet);
}


BEGIN_MESSAGE_MAP(CPage3, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CPage3::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CPage3::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CPage3::OnCbnSelchangeSelectNum)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CPage3::OnCbnSelchangeBlue)
	ON_BN_CLICKED(IDC_GETADDRESS, &CPage3::OnBnClickedGetaddress)
	ON_EN_CHANGE(IDC_ACOUNT, &CPage3::OnEnChangeAcount)
	ON_EN_CHANGE(IDC_PEERBET, &CPage3::OnEnChangePeerbet)
	ON_EN_CHANGE(IDC_EDIT2, &CPage3::OnEnChangeComputeTotalBet)
	ON_EN_CHANGE(IDC_EDIT5, &CPage3::OnEnChangeMulitCountBet)
END_MESSAGE_MAP()


// CPage3 消息处理程序
typedef long long  int64_t;
static int64_t factorial(int64_t n) {
	if (n <= 1)
		return 1;
	else
		return n * factorial(n - 1);
}

static int MselectN(int m, int n) {

	assert(m >= 0 && n >= 0);
	if(n == 0) return 1;
	if(m < n) return 0;
	if (m < 1 || m == n)
		return 1;
	return factorial(m) / (factorial(m - n) * factorial(n));
}
void CPage3::OnBnClickedButton1()
{
	int CurrentSel = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	CString address = "";
	CString SelectNumber = "";
	CString red  ="";
	CString blue ="";
	CString money = "";
	int nSendmoney =0;
	CString str = "";
	int i = 1;
	switch(CurrentSel)
	{
		case 0:
			{
				m_address.GetWindowText(address);
				if (address.IsEmpty())
				{
				//	AfxMessageBox("reward address can't empty");
					m_address.SetFocus();
					return;
				}
				m_preNumber.GetWindowText(SelectNumber);
				if ((SelectNumber.IsEmpty()|| SelectNumber.GetLength()<12)&&!isdigit(SelectNumber.GetString()) )
				{
				//	AfxMessageBox("select number can't empty or select number error");
					m_preNumber.SetFocus();
					return;
				}
				m_sendmoney.GetWindowText(money);
				if (money.IsEmpty()&& !isdigit(money.GetString()))
				{
					//AfxMessageBox("money can't empty or number");
					m_sendmoney.SetFocus();
					return;
				}
				nSendmoney = atof(money)*100;
				str.Format("{\"%s\":\"%s\",\"%s\":","method","sendlottobet","params");		
				str.AppendFormat("[\"\",%d,0,\"%s\",\"%s\"],\"id\":%d}\n",nSendmoney,HextoStr(SelectNumber),address,i);
				break;
			}
		case 1:
			{
				m_address.GetWindowText(address);
				if (address.IsEmpty())
				{
					//AfxMessageBox("reward address can't empty");
					m_address.SetFocus();
					return;
				}
				m_preNumber.GetWindowText(red);
				if ((red.IsEmpty()|| red.GetLength()<10)&&!isdigit(red.GetString()) )
				{
					//AfxMessageBox("select red number can't empty or select number error");
					m_preNumber.SetFocus();
					return;
				}
				m_number2.GetWindowText(blue);
				if ((blue.IsEmpty()|| blue.GetLength()<2)&&!isdigit(blue.GetString()) )
				{
					//AfxMessageBox("select number can't empty or select number error");
					m_number2.SetFocus();
					return;
				}
				m_sendmoney.GetWindowText(money);
				if (money.IsEmpty()&& !isdigit(money.GetString()))
				{
					//AfxMessageBox("money can't empty or number");
					m_sendmoney.SetFocus();
					return;
				}
				nSendmoney = atof(money)*100;
				str.Format("{\"%s\":\"%s\",\"%s\":","method","sendlottobet","params");
				str.AppendFormat("[\"\",%d,1,\"%sff%s\",\"%s\"],\"id\":%d}\n",nSendmoney,HextoStr(red),HextoStr(blue),address,i);
				break;
			}
		default: break;
	}

	m_commandstr = str;
	CWnd* m_pMainWnd = AfxGetApp()->m_pMainWnd;
	m_pMainWnd->SendMessage(WM_MY_SendBet,0,0);
}

void CPage3::OnCbnSelchangeCombo1()
{
	int CurrentSel = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	switch(CurrentSel)
	{
		case 0:
			{
				((CStatic*)GetDlgItem(IDC_Select))->SetWindowText("Select 15_6:");
				m_preNumber.SetWindowText("for example 1 2 3 4 5 6");
				((CStatic*)GetDlgItem(IDC_AFTER))->SetWindowText("");
				((CStatic*)GetDlgItem(IDC_AFTER))->ShowWindow(false);
				((CStatic*)GetDlgItem(IDC_EDIT5))->ShowWindow(false);
				((CComboBox*)GetDlgItem(IDC_COMBO3))->ShowWindow(false);
				m_betc.ResetContent();
				m_betc.InsertString(0,"6");m_betc.InsertString(1,"7");m_betc.InsertString(2,"8");
				m_betc.InsertString(3,"9");m_betc.InsertString(4,"10");m_betc.InsertString(5,"11");
				m_betc.InsertString(6,"12");m_betc.InsertString(7,"13");m_betc.InsertString(8,"14");
				m_betc.InsertString(9,"15");
				break;
			}
		case 1:
			{
				((CStatic*)GetDlgItem(IDC_Select))->SetWindowText("Select 20_5:");
				m_preNumber.SetWindowText("for example 1 2 3 4 5");
				((CStatic*)GetDlgItem(IDC_AFTER))->SetWindowText("Select 10_2:");
				((CStatic*)GetDlgItem(IDC_AFTER))->ShowWindow(TRUE);
				((CStatic*)GetDlgItem(IDC_EDIT5))->ShowWindow(TRUE);
				((CComboBox*)GetDlgItem(IDC_COMBO3))->ShowWindow(TRUE);
				m_number2.SetWindowText("for example 1 2 3");
				m_betc.ResetContent();
				m_betc.InsertString(0,"5");
				m_betc.InsertString(1,"6");m_betc.InsertString(2,"7");m_betc.InsertString(3,"8");
				m_betc.InsertString(4,"9");m_betc.InsertString(5,"10");m_betc.InsertString(6,"11");
				m_betc.InsertString(7,"12");m_betc.InsertString(8,"13");m_betc.InsertString(9,"14");
				m_betc.InsertString(10,"15");m_betc.InsertString(11,"16");m_betc.InsertString(12,"17");
				m_betc.InsertString(13,"18");m_betc.InsertString(14,"19");m_betc.InsertString(15,"20");
				
				m_blue.ResetContent();
				m_blue.InsertString(0,"2");
				m_blue.InsertString(1,"3");m_blue.InsertString(2,"4");m_blue.InsertString(3,"5");
				m_blue.InsertString(4,"6");m_blue.InsertString(5,"7");m_blue.InsertString(6,"8");
				m_blue.InsertString(7,"9");m_blue.InsertString(8,"10");

				break;
			}
		default: break;
	}
}
#define BEGIN(a)            ((char*)&(a))
#define END(a)              ((char*)&((&(a))[1]))
CString CPage3::getvchSelect(int selectsize,int totalsize) {
	int randch;
	CString ret = "";
	int count = 0;
	vector<int> nvTemp;
	if (selectsize > totalsize)
	{
		return "";
	}
	 srand((int)time(0));
	while (selectsize > 0) {
		int seed = totalsize+1;
		randch = random(seed);
		CString str;str.AppendFormat("%02d",randch);
		if (ret.Find(str)<0 && randch >0)
		{
			ret.AppendFormat("%02d ",randch);
			nvTemp.push_back(randch);
			selectsize--;
		}
	}
	sort(nvTemp.begin(),nvTemp.end());
	ret = "";
	vector<int>::iterator it  = nvTemp.begin();
	for (;it != nvTemp.end();it++)
	{
		ret.AppendFormat("%02d ",*it);
	}
	return ret;
}

void CPage3::OnCbnSelchangeSelectNum()
{
		UpdateData();
		int CurrentSel = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
		CString temp="";
		((CComboBox*)GetDlgItem(IDC_COMBO2))->GetWindowText(temp);
		int count =0;
		if (temp !="")
		{
			count =	atoi(temp);
		}
		m_staticTotalBet.SetWindowText("");
		count = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel(); 
		switch(CurrentSel)
		{
		case 0:
			{
				CString str = getvchSelect((count+6),15);
				m_preNumber.SetWindowText(str);
				int betC = MselectN((count+6),6);
				str = "";str.AppendFormat("%d",betC);
				m_staticTotalBet.SetWindowText(str);
				UpdateData(false);
				break;
			}
		case 1:
			{
				CString str = getvchSelect((count+5),20);
				m_preNumber.SetWindowText(str);

				CString blue = "";
				m_number2.GetWindowText(blue);
				if (isdigit(blue.GetString()))
				{
					blue =  HextoStr(blue);
					int blueCount = blue.GetLength()/2;
					int betC = MselectN((blueCount),2)*MselectN((count+5),5);;
					str = "";str.AppendFormat("%d",betC);
					m_staticTotalBet.SetWindowText(str);
				}
				UpdateData(false);
				break;
			}
		default:break;
		}
}

void CPage3::OnCbnSelchangeBlue()
{
		UpdateData(TRUE);
		m_staticTotalBet.SetWindowText("");
		int CurrentSel = ((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCurSel();
		int count = CurrentSel+ 2; 
		CString str = getvchSelect(count,10);
		m_number2.SetWindowText(str);

		CString SelectNumber = "";
		m_preNumber.GetWindowText(SelectNumber);
		if (isdigit(SelectNumber.GetString()))
		{
			SelectNumber =  HextoStr(SelectNumber);
			int redCount = SelectNumber.GetLength()/2;
			int betC = MselectN((count),2)*MselectN(redCount,5);
			str = "";str.AppendFormat("%d",betC);
			m_staticTotalBet.SetWindowText(str);
		}

		UpdateData(false);
}

void CPage3::OnBnClickedGetaddress()
{
	is_Getaddress = true;
	CWnd* m_pMainWnd = AfxGetApp()->m_pMainWnd;
	m_pMainWnd->SendMessage(WM_MY_GetAddress,0,0);

}
bool CPage3::isGetaddress()
{
	return is_Getaddress;
}
void CPage3::SetAddressFlag()
{
		is_Getaddress = false;
}
CString CPage3::HextoStr(CString str)
{
	CString ret = "";
	int pos = str.Find( " ");
	while(pos >=0)
	{
		CString temp = str.Left(pos);
		temp.Trim();
		int number = atoi(temp);
		ret.AppendFormat("%02x",number);
		str = str.Mid(pos+1);
		str.TrimLeft(" ");
		pos = str.Find(" ");

	}
	if (str != "")
	{
		str.TrimLeft(" ");
		int number = atoi(str);
		ret.AppendFormat("%02x",str);

	}
return ret;

}

void CPage3::ComputeAmountPeerBet(CString nSelectNumber,CString blue,double value)
{
	int CurrentSel = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	switch(CurrentSel)
	{
	case 0:
		{
			int numCount = nSelectNumber.GetLength()/2;
			if (numCount >=6)
			{
				double peerbet = value/(double)MselectN(numCount,6);
				CString nTemp = "";
				nTemp.AppendFormat("%.8f",peerbet);
				CString pre = "";
				m_amoutbet.GetWindowText(pre);
				if(pre != nTemp)
				m_amoutbet.SetWindowText(nTemp);
			}
			break;
		}
	case 1:
		{
			int redCount = nSelectNumber.GetLength()/2;
			int blueCount = blue.GetLength()/2;
			if (redCount >=5&& blueCount>=2)
			{
				double peerbet = value/(double)(MselectN(redCount,5)*MselectN(blueCount,2));
				CString nTemp = "";
				nTemp.AppendFormat("%8f",peerbet);
				//m_amoutbet.SetWindowText("");
				CString pre = "";
				m_amoutbet.GetWindowText(pre);
				if(pre != nTemp)
				m_amoutbet.SetWindowText(nTemp);
			}

			break;
		}
	default:break;
	}
}
void CPage3::ComputeAmountBet(CString nSelectNumber,CString blue,double value)
{
	int CurrentSel = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	switch(CurrentSel)
	{
	case 0:
		{
			int numCount = nSelectNumber.GetLength()/2;
			if (numCount >=6)
			{
				double peerbet = value*(double)MselectN(numCount,6);
				CString nTemp = "";
				nTemp.AppendFormat("%.8f",peerbet);
				//m_sendmoney.SetWindowText("");
				CString pre = "";
				m_sendmoney.GetWindowText(pre);
				if(pre != nTemp)
				m_sendmoney.SetWindowText(nTemp);
			}
			break;
		}
	case 1:
		{
			int redCount = nSelectNumber.GetLength()/2;
			int blueCount = blue.GetLength()/2;
			if (redCount >=5&& blueCount>=2)
			{
				double peerbet = value*(double)(MselectN(redCount,5)*MselectN(blueCount,2));
				CString nTemp = "";
				nTemp.AppendFormat("%8f",peerbet);
				//m_sendmoney.SetWindowText("");
				CString pre = "";
				m_sendmoney.GetWindowText(pre);
					if(pre != nTemp)
				m_sendmoney.SetWindowText(nTemp);
			}

			break;
		}
	default:break;
	}
}

double CPage3::ComputeAmuont(CString nSelectNumber,CString blue,double value)
{
	int CurrentSel = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	switch(CurrentSel)
	{
	case 0:
		{
			int numCount = nSelectNumber.GetLength()/2;
			if (numCount >=6)
			{
				double peerbet = value*(double)MselectN(numCount,6);
				return peerbet;
			}
			break;
		}
	case 1:
		{
			int redCount = nSelectNumber.GetLength()/2;
			int blueCount = blue.GetLength()/2;
			if (redCount >=5&& blueCount>=2)
			{
				double peerbet = value*(double)(MselectN(redCount,5)*MselectN(blueCount,2));
				return peerbet;
			}

			break;
		}
	default:break;
	}
	return 0.0;
}
void CPage3::Clear()
{
	UpdateData();
	m_preNumber.SetWindowText("");
	m_ret.SetWindowText("");
	m_number2.SetWindowText("");
	m_commandstr = "";
	m_address.SetWindowText("");
	m_sendmoney.SetWindowText("");
	m_amoutbet.SetWindowText("");
	m_staticTotalBet.SetWindowText("");
	m_betc.SetCurSel(-1);
	m_blue.SetCurSel(-1);
	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
	m_betc.InsertString(0,"6");m_betc.InsertString(1,"7");m_betc.InsertString(2,"8");
	m_betc.InsertString(3,"9");m_betc.InsertString(4,"10");m_betc.InsertString(5,"11");
	m_betc.InsertString(6,"12");m_betc.InsertString(7,"13");m_betc.InsertString(8,"14");
	m_betc.InsertString(9,"15");
	((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
	CString str = getvchSelect(6,15);
	m_preNumber.SetWindowText(str);
	UpdateData(false);
}

void CPage3::OnEnChangeAcount()
{
	CString SelectNumber ="";
	CString money = "";
	CString red = "";
	CString blue = "";
	int CurrentSel = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	if ((GetTickCount() - nPCurrentTime) < 1000)
	{
		return;
	}
	nCurrentTime=GetTickCount();
	switch(CurrentSel)
	{
	case 0:
		{
			m_preNumber.GetWindowText(SelectNumber);
			if ((SelectNumber.IsEmpty()|| SelectNumber.GetLength()<12)&&!isdigit(SelectNumber.GetString()) )
			{
				//AfxMessageBox("select number can't empty or select number error");
				m_preNumber.SetFocus();
				return;
			}
			m_sendmoney.GetWindowText(money);
			if (money.IsEmpty()&& !isdigit(money.GetString()))
			{
				//AfxMessageBox("money can't empty or number");
				return;
				m_sendmoney.SetFocus();
			}

			ComputeAmountPeerBet(HextoStr(SelectNumber),"",atof(money));
			break;
		}
	case 1:
		{
			m_preNumber.GetWindowText(red);
			if ((red.IsEmpty()|| red.GetLength()<10)&&!isdigit(red.GetString()) )
			{
				//AfxMessageBox("select red number can't empty or select number error");
				return;
				m_preNumber.SetFocus();
			}
			m_number2.GetWindowText(blue);
			if ((blue.IsEmpty()|| blue.GetLength()<2)&&!isdigit(blue.GetString()) )
			{
				//AfxMessageBox("select number can't empty or select number error");
				return;
				m_number2.SetFocus();
			}
			m_sendmoney.GetWindowText(money);
			if (money.IsEmpty()&& !isdigit(money.GetString()))
			{
				//AfxMessageBox("money can't empty or number");
				return;
				m_sendmoney.SetFocus();
			}
			ComputeAmountPeerBet(HextoStr(red),HextoStr(blue),atof(money));
			break;
		}
	default: break;
	}
}

void CPage3::OnEnChangePeerbet()
{
	CString SelectNumber ="";
	CString money = "";
	CString red = "";
	CString blue = "";
	if ((GetTickCount() - nCurrentTime) < 1000)
	{
		return;
	}
	nPCurrentTime=GetTickCount();
	int CurrentSel = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	switch(CurrentSel)
	{
	case 0:
		{
			m_preNumber.GetWindowText(SelectNumber);
			if ((SelectNumber.IsEmpty()|| SelectNumber.GetLength()<12)&&!isdigit(SelectNumber.GetString()) )
			{
				//AfxMessageBox("select number can't empty or select number error");
				return;
				m_preNumber.SetFocus();
			}
			if (!isdigit(SelectNumber.GetString()))
			{
				return;
			}
			m_amoutbet.GetWindowText(money);
			if (money.IsEmpty()&& !isdigit(money.GetString()))
			{
				//AfxMessageBox("money can't empty or number");
				return;
				m_sendmoney.SetFocus();
			}

			ComputeAmountBet(HextoStr(SelectNumber),"",atof(money));
			break;
		}
	case 1:
		{
			m_preNumber.GetWindowText(red);
			if ((red.IsEmpty()|| red.GetLength()<10) )
			{
				//AfxMessageBox("select red number can't empty or select number error");
				return;
				m_preNumber.SetFocus();
			}
			if (!isdigit(red.GetString()))
			{
				return;
			}
			m_number2.GetWindowText(blue);
			if ((blue.IsEmpty()|| blue.GetLength()<2)&&!isdigit(blue.GetString()) )
			{
				//AfxMessageBox("select number can't empty or select number error");
				return;
				m_number2.SetFocus();
			}
			if (!isdigit(blue.GetString()))
			{
				return;
			}
			m_amoutbet.GetWindowText(money);
			if (money.IsEmpty()&& !isdigit(money.GetString()))
			{
				//AfxMessageBox("money can't empty or number");
				return;
				m_sendmoney.SetFocus();
			}
			ComputeAmountBet(HextoStr(red),HextoStr(blue),atof(money));
			break;
		}
	default: break;
	}
}

void CPage3::OnEnChangeComputeTotalBet()
{
	int CurrentSel = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	m_staticTotalBet.SetWindowText("");

	switch(CurrentSel)
	{
	case 0:
		{
			UpdateData(TRUE);
			CString SelectNumber = "";
			m_preNumber.GetWindowText(SelectNumber);
			if (!isdigit(SelectNumber.GetString()))
			{
				return;
			}
			SelectNumber =  HextoStr(SelectNumber);
			int numCount = SelectNumber.GetLength()/2;
			if (numCount >=6)
			{
				int countbet = MselectN(numCount,6);
				CString nTemp = "";nTemp.AppendFormat("%d",countbet);
				m_staticTotalBet.SetWindowText(nTemp);
				UpdateData(FALSE);
			}
			break;
		}
	case 1:
		{
			UpdateData(TRUE);
			CString red = "";
			CString blue = "";
			m_preNumber.GetWindowText(red);
			m_number2.GetWindowText(blue);
			if (!isdigit(red.GetString()) ||!isdigit(blue.GetString())  )
			{
				return;
			}
			red =  HextoStr(red);
			blue =  HextoStr(blue);
			int redCount = red.GetLength()/2;
			int blueCount = blue.GetLength()/2;
			if (redCount >=5&& blueCount>=2)
			{
				int countbet = MselectN(redCount,5)*MselectN(blueCount,2);
				CString nTemp = "";nTemp.AppendFormat("%d",countbet);
				m_staticTotalBet.SetWindowText(nTemp);
				UpdateData(FALSE);
			}
			break;
		}
	default:break;
	}
}

void CPage3::OnEnChangeMulitCountBet()
{
	int CurrentSel = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	m_staticTotalBet.SetWindowText("");
	switch(CurrentSel)
	{
	case 1:
		{
			UpdateData(TRUE);
			CString SelectNumber = "";
			m_preNumber.GetWindowText(SelectNumber);
			if (!isdigit(SelectNumber.GetString()))
			{
				return;
			}
			SelectNumber =  HextoStr(SelectNumber);
			int redCount = SelectNumber.GetLength()/2;
			CString blueNumber = "";
			m_number2.GetWindowText(blueNumber);
			blueNumber =  HextoStr(blueNumber);

			int blueCount = blueNumber.GetLength()/2;
			if (redCount >=5&& blueCount>=2)
			{
				int countbet = MselectN(redCount,5)*MselectN(blueCount,2);
				CString nTemp = "";nTemp.AppendFormat("%d",countbet);
				m_staticTotalBet.SetWindowText(nTemp);
				UpdateData(FALSE);
			}
			break;
		}
	default:break;
	}
}
