// CbookedDlg.cpp: 实现文件
//

#include "pch.h"
#include "MINI12306.h"
#include "afxdialogex.h"
#include "CbookedDlg.h"


// CbookedDlg 对话框

IMPLEMENT_DYNAMIC(CbookedDlg, CDialogEx)

BOOL CbookedDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ShowWindow(SW_NORMAL);
	CenterWindow();
	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST1);
	pListCtrl->SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_GRIDLINES);
	pListCtrl->InsertColumn(0, _T("航班号"), LVCFMT_CENTER, 60, 0);
	pListCtrl->InsertColumn(1, _T("出发地"), LVCFMT_CENTER, 80, 0);
	pListCtrl->InsertColumn(2, _T("目的地"), LVCFMT_CENTER, 80, 0);
	pListCtrl->InsertColumn(3, _T("日期"), LVCFMT_CENTER, 80, 0);
	pListCtrl->InsertColumn(4, _T("起飞时间"), LVCFMT_CENTER, 60, 0);
	pListCtrl->InsertColumn(5, _T("到达时间"), LVCFMT_CENTER, 60, 0);
	extern User CurrentUser;
	size_t size = CurrentUser.BookedList.size();
	for (size_t i = 0; i < size; ++i) {
		FlightInfo tmp = CurrentUser.BookedList[i];
		CString t0 = tmp.GetNum();
		CString t1 = tmp.GetOrigin();
		CString t2 = tmp.GetDestination();
		CString t3 = tmp.GetDate();
		CString t4 = tmp.GetStartTime();
		CString t5 = tmp.GetArriveTime();
		pListCtrl->InsertItem(i, t0);
		pListCtrl->SetItemText(i, 1, t1);
		pListCtrl->SetItemText(i, 2, t2);
		pListCtrl->SetItemText(i, 3, t3);
		pListCtrl->SetItemText(i, 4, t4);
		pListCtrl->SetItemText(i, 5, t5);
	}
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
END_MESSAGE_MAP()


// CbookedDlg 消息处理程序
