// CbookedDlg.cpp: 实现文件
//

#include "pch.h"
#include "MINI12306.h"
#include "afxdialogex.h"
#include "CbookedDlg.h"
#include "CEnsureInfoDlg.h"
// CbookedDlg 对话框

IMPLEMENT_DYNAMIC(CbookedDlg, CDialogEx)

BOOL CbookedDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ShowWindow(SW_NORMAL);
	CenterWindow();
	m_ListCtrl.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_GRIDLINES);
	m_ListCtrl.InsertColumn(0, _T("航班号"), LVCFMT_CENTER, 60, 0);
	m_ListCtrl.InsertColumn(1, _T("出发地"), LVCFMT_CENTER, 80, 0);
	m_ListCtrl.InsertColumn(2, _T("目的地"), LVCFMT_CENTER, 80, 0);
	m_ListCtrl.InsertColumn(3, _T("日期"), LVCFMT_CENTER, 80, 0);
	m_ListCtrl.InsertColumn(4, _T("起飞时间"), LVCFMT_CENTER, 60, 0);
	m_ListCtrl.InsertColumn(5, _T("到达时间"), LVCFMT_CENTER, 60, 0);
	m_ListCtrl.InsertColumn(6, _T("坐席类型"), LVCFMT_CENTER, 60, 0);
	m_ListCtrl.InsertColumn(7, _T("票价"), LVCFMT_CENTER, 60, 0);
	m_ListCtrl.InsertColumn(8, _T("运营状态"), LVCFMT_CENTER, 60, 0);
	extern User CurrentUser;
	extern FlightManager FM;
	size_t size = CurrentUser.BookedList.size();
	bool cancel = false;
	for (size_t i = 0; i < size; ++i) {
		FlightInfo tmp = CurrentUser.BookedList[i];
		FlightInfo t = FM.FindFlight(tmp);
		CString t0 = tmp.GetNum();
		CString t1 = tmp.GetOrigin();
		CString t2 = tmp.GetDestination();
		CString t3 = tmp.GetDate();
		CString t4 = tmp.GetStartTime();
		CString t5 = tmp.GetArriveTime();
		int sta = t.GetStatus();
		if (!sta) cancel = true;
		CString t8 = StatusFuc[sta];
		m_ListCtrl.InsertItem(i, t0);
		m_ListCtrl.SetItemText(i, 1, t1);
		m_ListCtrl.SetItemText(i, 2, t2);
		m_ListCtrl.SetItemText(i, 3, t3);
		m_ListCtrl.SetItemText(i, 4, t4);
		m_ListCtrl.SetItemText(i, 5, t5);
		m_ListCtrl.SetItemText(i, 8, t8);
		int cnt1 = tmp.GetFirst().cnt;
		int cnt2 = tmp.GetSecond().cnt;
		int price;
		if (cnt1 == 0)
		{
			m_ListCtrl.SetItemText(i, 6, _T("二等座"));
			price = tmp.GetSecond().price;
		}
		else
		{
			m_ListCtrl.SetItemText(i, 6, _T("一等座"));
			price = tmp.GetFirst().price;
		}
		CString tp;
		tp.Format("%d", price);
		m_ListCtrl.SetItemText(i, 7, tp);
	}
	if (cancel)
		AfxMessageBox("您有航班被取消！请及时退票！");
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
CbookedDlg::CbookedDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BOOKED_DIALOG, pParent)
{

}

CbookedDlg::~CbookedDlg()
{
}
void CbookedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CbookedDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CbookedDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CbookedDlg 消息处理程序


void CbookedDlg::OnBnClickedButton1()
{
	extern User CurrentUser;
	FlightInfo HaveBooked;
	extern UsersManager UM;
	extern FlightManager FM;
	UpdateData(TRUE);
	int ID = m_ListCtrl.GetSelectionMark();
	if (ID == -1)
		AfxMessageBox(_T("请选择需要变更的航班！"));
	else {
		CEnsureInfoDlg New;
		HaveBooked = CurrentUser.BookedList[ID];
		int cnt1 = HaveBooked.GetFirst().cnt, cnt2 = HaveBooked.GetSecond().cnt;
		New.mCNT = "1";
		New.mFlightArT = HaveBooked.GetArriveTime();
		New.mFlightDep = HaveBooked.GetOrigin();
		New.mFlightInfo = HaveBooked.GetNum();
		New.mFlightType = HaveBooked.GetFirst().cnt ? "一等座" : "二等座";
		int price = cnt1 ? HaveBooked.GetFirst().price : HaveBooked.GetSecond().price;
		New.mFlightArr = HaveBooked.GetDestination();
		New.mFlightSt = HaveBooked.GetStartTime();
		New.mTotal.Format("%d", price);
		const char* Yuan= "元";
		New.mTotal = New.mTotal + Yuan;
 		INT_PTR nRes = New.DoModal();
		if (nRes == IDOK)
		{
			FlightInfo tmp = FM.FindFlight(HaveBooked);
			int Cnt1 = tmp.GetFirst().cnt, Cnt2 = tmp.GetSecond().cnt;
			if (cnt1 == 0)
				tmp.SetSecondInfo(Cnt2 + 1);
			else
				tmp.SetFirstInfo(Cnt1 + 1);
			CurrentUser.Recharge(price);
			vector<FlightInfo>::iterator it = CurrentUser.BookedList.begin() + ID;
			CurrentUser.BookedList.erase(it);
			UM.EditUser(CurrentUser);
			FM.EditFlight(HaveBooked.GetNum(), HaveBooked.GetDate(), tmp);
			MessageBox(_T("退票成功！"));
			CDialogEx::OnOK();
		}
	}
}
