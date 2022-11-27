// CFindFlightDlg.cpp: 实现文件
//

#include "pch.h"
#include "MINI12306.h"
#include "afxdialogex.h"
#include "CFindFlightDlg.h"
#include "CEnsureInfoDlg.h"

// CFindFlightDlg 对话框

IMPLEMENT_DYNAMIC(CFindFlightDlg, CDialogEx)

CFindFlightDlg::CFindFlightDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_QUERY_DIALOG, pParent){nIndex = -1;}

CFindFlightDlg::~CFindFlightDlg(){}

void CFindFlightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	//DDX_Control(pDX, IDC_RADIO1, F);
}

BOOL CFindFlightDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ShowWindow(SW_NORMAL);
	CenterWindow();

	// TODO: 在此添加额外的初始化代码
	CCustomDrawListCtrl* pListCtrl = (CCustomDrawListCtrl*)GetDlgItem(IDC_LIST1);
	pListCtrl->SetRowHeight(20);
	pListCtrl->SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_GRIDLINES);
	pListCtrl->InsertColumn(0, _T("航班号"), LVCFMT_CENTER, 60, 0);
	pListCtrl->InsertColumn(1, _T("出发地"), LVCFMT_CENTER, 80, 0);
	pListCtrl->InsertColumn(2, _T("目的地"), LVCFMT_CENTER, 80, 0);
	pListCtrl->InsertColumn(3, _T("日期"), LVCFMT_CENTER, 80, 0);
	pListCtrl->InsertColumn(4, _T("起飞时间"), LVCFMT_CENTER, 60, 0);
	pListCtrl->InsertColumn(5, _T("到达时间"), LVCFMT_CENTER, 60, 0);
	pListCtrl->InsertColumn(6, _T("一等舱票额"), LVCFMT_CENTER, 80, 0);
	pListCtrl->InsertColumn(7, _T("二等舱票额"), LVCFMT_CENTER, 80, 0);
	extern FlightManager FM;
	int size = (int)List.size();
	for (int i = 0; i < size; ++i) {
		FlightInfo tmp = List[i];
		CString t0 = tmp.GetNum();
		CString t1 = tmp.GetOrigin();
		CString t2 = tmp.GetDestination();
		CString t3 = tmp.GetDate();
		CString t4 = tmp.GetStartTime();
		CString t5 = tmp.GetArriveTime();
		Seats t = tmp.GetFirst();
		CString t6, t7, t8;
		t7.Format("%d", t.cnt);
		t = tmp.GetSecond();
		t8.Format("%d", t.cnt);
		pListCtrl->InsertItem(i, t0);
		pListCtrl->SetItemText(i, 1, t1);
		pListCtrl->SetItemText(i, 2, t2);
		pListCtrl->SetItemText(i, 3, t3);
		pListCtrl->SetItemText(i, 4, t4);
		pListCtrl->SetItemText(i, 5, t5);
		pListCtrl->SetItemText(i, 6, t7);
		pListCtrl->SetItemText(i, 7, t8);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

BEGIN_MESSAGE_MAP(CFindFlightDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &CFindFlightDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDOK, &CFindFlightDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO2, &CFindFlightDlg::OnBnClickedRadio2)
END_MESSAGE_MAP()


// CFindFlightDlg 消息处理程序


void CFindFlightDlg::OnBnClickedRadio1() { nIndex = 1; }


void CFindFlightDlg::OnBnClickedOk()
{
	extern User CurrentUser;
	extern UsersManager UM;
	extern FlightManager FM;
	UpdateData(TRUE);
	int t = m_ListCtrl.GetSelectionMark();
	if (t == -1)
		AfxMessageBox(_T("请选择一个航班！"));
	else
	{
		FlightInfo tmp = List[t];
		CString T, CNT, tot;
		int Cnt, SinglePrice;
		INT_PTR nRES;
		if (nIndex == -1)
			AfxMessageBox(_T("请选择坐席类型！"));
		else
		{
			bool OK = true;
			if (nIndex == 0) {
				SinglePrice = tmp.GetSecond().price;
				T = "二等座";
				Cnt = tmp.GetSecond().cnt;
				if (Cnt < 1)
					nRES = AfxMessageBox(_T("无票额，请重新选择")), OK = false;
				else
					tmp.SetSecondInfo(Cnt - 1);
			}
			else
			{
				SinglePrice = tmp.GetFirst().price;
				T = "一等座";
				Cnt = tmp.GetFirst().cnt;
				if (Cnt < 1)
					nRES = AfxMessageBox(_T("无票额，请重新选择")), OK = false;
				else
					tmp.SetFirstInfo(Cnt - 1);
			}
			if (OK){
				CNT.Format("%d", 1);
				tot.Format("%d", SinglePrice);
				CEnsureInfoDlg Ensure;
				Ensure.mFlightInfo = tmp.GetNum();
				Ensure.mFlightDep = tmp.GetOrigin();
				Ensure.mFlightArr = tmp.GetDestination();
				Ensure.mFlightSt = tmp.GetStartTime();
				Ensure.mFlightArT = tmp.GetArriveTime();
				Ensure.mFlightType = T;
				char yuan[] = "元", zhang[] = "张";
				Ensure.mCNT = CNT + zhang;
				CString Yuan = yuan;
				Ensure.mTotal = tot;
				Ensure.tot = SinglePrice;
				nRES = Ensure.DoModal();
				if (nRES == IDOK)
				{
					FM.EditFlight(tmp.GetNum(), tmp.GetDate(), tmp);
					FlightInfo HaveBooked = tmp;
					if (nIndex == 0)
					{
						HaveBooked.SetSecondInfo(1);
						HaveBooked.SetFirstInfo(0);
					}
					else
					{
						HaveBooked.SetFirstInfo(1);
						HaveBooked.SetSecondInfo(0);
					}
					CurrentUser.book(SinglePrice);
					CurrentUser.BookedList.push_back(HaveBooked);
					UM.EditUser(CurrentUser);
					MessageBox(_T("购买成功！"));
					CDialogEx::OnOK();
				}
			}
		}
	}
}


void CFindFlightDlg::OnBnClickedRadio2() { nIndex = 0; }
