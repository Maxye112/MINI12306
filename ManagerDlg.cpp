﻿// ManagerDlg.cpp: 实现文件
//

#include "pch.h"
#include "MINI12306.h"
#include "afxdialogex.h"
#include "ManagerDlg.h"
#include "AddFlightDlg.h"

// ManagerDlg 对话框
int ManagerDlg::col = -1;
bool ManagerDlg::method = 0;

IMPLEMENT_DYNAMIC(ManagerDlg, CDialogEx)

ManagerDlg::ManagerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MANAGER_DIALOG, pParent)
{

}

ManagerDlg::~ManagerDlg()
{
}

void ManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, mListCtrl);
	DDX_Control(pDX, IDC_COMBO1, mCityList);
	DDX_Control(pDX, IDC_BUTTON1, addf);
	DDX_Control(pDX, IDC_BUTTON2, delf);
	DDX_Control(pDX, IDC_BUTTON3, addc);
	DDX_Control(pDX, IDC_BUTTON4, delc);
}


BEGIN_MESSAGE_MAP(ManagerDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &ManagerDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &ManagerDlg::OnBnClickedButton4)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &ManagerDlg::OnColumnclickList1)
	ON_BN_CLICKED(IDC_BUTTON1, &ManagerDlg::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON2, &ManagerDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// ManagerDlg 消息处理程序

BOOL ManagerDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();
	CString strBmpPath = _T(".\\res\\Main.png");
	CImage img;
	img.Load(strBmpPath);
	CBitmap bmpTmp;
	bmpTmp.Attach(img.Detach());
	m_bkBrush.CreatePatternBrush(&bmpTmp);
	CFont* pFont = new CFont;
	//LOGFONT lf;
	if (pFont)
	{
		pFont->CreateFont(30, 0, 0, 0, 100,
			FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_SWISS, "Arial");
		//GetDlgItem(IDC_EDIT_TEL)->SetFont(pFont);
		//GetDlgItem(IDC_EDIT_PASSWORD)->SetFont(pFont);
	}
	ShowWindow(SW_NORMAL);
	CenterWindow();
	extern CityManager CM;
	int size = CM.CL.size();
	for (int i = 0; i < size; ++i) 
	{
		City New = CM.CL[i];
		mCityList.AddString(New.c_str());
	}
	extern FlightManager FM;
	mListCtrl.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_GRIDLINES);
	mListCtrl.InsertColumn(0, _T("航班号"), LVCFMT_CENTER, 60, 0);
	mListCtrl.InsertColumn(1, _T("出发地"), LVCFMT_CENTER, 80, 0);
	mListCtrl.InsertColumn(2, _T("目的地"), LVCFMT_CENTER, 80, 0);
	mListCtrl.InsertColumn(3, _T("日期"), LVCFMT_CENTER, 80, 0);
	mListCtrl.InsertColumn(4, _T("起飞时间"), LVCFMT_CENTER, 60, 0);
	mListCtrl.InsertColumn(5, _T("到达时间"), LVCFMT_CENTER, 60, 0);
	mListCtrl.InsertColumn(6, _T("一等舱票额"), LVCFMT_CENTER, 80, 0);
	mListCtrl.InsertColumn(7, _T("二等舱票额"), LVCFMT_CENTER, 80, 0);
	size = FM.FQ.size();
	for (int i = 0; i < size; ++i) 
	{
		FlightInfo New = FM.FQ[i];
		CString t0 = New.GetNum();
		CString t1 = New.GetOrigin();
		CString t2 = New.GetDestination();
		CString t3 = New.GetDate();
		CString t4 = New.GetStartTime();
		CString t5 = New.GetArriveTime();
		Seats t = New.GetFirst();
		CString t6, t7, t8;
		t7.Format("%d", t.cnt);
		t = New.GetSecond();
		t8.Format("%d", t.cnt);
		mListCtrl.InsertItem(i, t0);
		mListCtrl.SetItemText(i, 1, t1);
		mListCtrl.SetItemText(i, 2, t2);
		mListCtrl.SetItemText(i, 3, t3);
		mListCtrl.SetItemText(i, 4, t4);
		mListCtrl.SetItemText(i, 5, t5);
		mListCtrl.SetItemText(i, 6, t7);
		mListCtrl.SetItemText(i, 7, t8);
	}
	delete pFont;
	return TRUE;
}

void ManagerDlg::OnBnClickedButton3()
{
	extern CityManager CM;
	CString CityName;
	GetDlgItemText(IDC_COMBO1, CityName);
	if (CityName == "")
		AfxMessageBox("请输入城市名称");
	else {
		City name = CityName;
		if (!CM.AddCity(name))
			AfxMessageBox("城市已存在，请重新输入！");
		else
		{
			mCityList.ResetContent();
			int size = CM.CL.size();
			for (int i = 0; i < size; ++i) {
				City New = CM.CL[i];
				mCityList.AddString(New.c_str());
			}
			MessageBox("城市添加成功！");
		}
	}
}

void ManagerDlg::OnBnClickedButton4()
{
	extern CityManager CM;
	CString CityName;
	GetDlgItemText(IDC_COMBO1, CityName);
	if (CityName == "")
		AfxMessageBox("请输入城市名称！");
	else {
		City name = CityName;
		if (!CM.DelCity(name))
			AfxMessageBox("城市不存在！");
		else {
			mCityList.ResetContent();
			int size = CM.CL.size();
			for (int i = 0; i < size; ++i) {
				City New = CM.CL[i];
				mCityList.AddString(New.c_str());
			}
			MessageBox("城市删除成功！");
		}
	}
}


int CALLBACK ManagerDlg::MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	int row1 = (int)lParam1;
	int row2 = (int)lParam2;
	CListCtrl* lc = (CListCtrl*)lParamSort;
	CString lp1 = lc->GetItemText(row1, col);
	CString lp2 = lc->GetItemText(row2, col);
	if (col == 7 || col == 8)
		if (method)
			return atoi(lp1) - atoi(lp2);
		else
			return atoi(lp2) - atoi(lp1);
	else
	{
		if (method)
			return lp1.CompareNoCase(lp2);
		else
			return lp2.CompareNoCase(lp1);
	}
	return 0;

}


void ManagerDlg::OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	col = pNMLV->iSubItem;
	int cnt = mListCtrl.GetItemCount();
	for (int i = 0; i < cnt; i++)
		mListCtrl.SetItemData(i, i); 
	mListCtrl.SortItems(MyCompareProc, (DWORD_PTR)&mListCtrl);
	method = !method;
	*pResult = 0;
}


void ManagerDlg::OnBnClickedButton1()
{
	AddFlightDlg NewWin;
	INT_PTR nRes = NewWin.DoModal();
	extern FlightManager FM;
	if (nRes == IDOK)
	{
		mListCtrl.DeleteAllItems();
		int size = FM.FQ.size();
		for (int i = 0; i < size; ++i)
		{
			FlightInfo New = FM.FQ[i];
			CString t0 = New.GetNum();
			CString t1 = New.GetOrigin();
			CString t2 = New.GetDestination();
			CString t3 = New.GetDate();
			CString t4 = New.GetStartTime();
			CString t5 = New.GetArriveTime();
			Seats t = New.GetFirst();
			CString t6, t7, t8;
			t7.Format("%d", t.cnt);
			t = New.GetSecond();
			t8.Format("%d", t.cnt);
			mListCtrl.InsertItem(i, t0);
			mListCtrl.SetItemText(i, 1, t1);
			mListCtrl.SetItemText(i, 2, t2);
			mListCtrl.SetItemText(i, 3, t3);
			mListCtrl.SetItemText(i, 4, t4);
			mListCtrl.SetItemText(i, 5, t5);
			mListCtrl.SetItemText(i, 6, t7);
			mListCtrl.SetItemText(i, 7, t8);
		}
	}

	// TODO: 在此添加控件通知处理程序代码
}


HBRUSH ManagerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd == this)
		hbr = m_bkBrush;
	return hbr;
}


void ManagerDlg::OnBnClickedButton2()
{
	int ID = mListCtrl.GetSelectionMark();
	if (ID == -1)
		AfxMessageBox("请选择航班！");
	else {
		extern FlightManager FM;
		FlightInfo tmp = FM.FQ[ID];
		FM.DelFlight(tmp.GetNum(), tmp.GetDate());
		mListCtrl.DeleteAllItems();
		int size = FM.FQ.size();
		for (int i = 0; i < size; ++i)
		{
			FlightInfo New = FM.FQ[i];
			CString t0 = New.GetNum();
			CString t1 = New.GetOrigin();
			CString t2 = New.GetDestination();
			CString t3 = New.GetDate();
			CString t4 = New.GetStartTime();
			CString t5 = New.GetArriveTime();
			Seats t = New.GetFirst();
			CString t6, t7, t8;
			t7.Format("%d", t.cnt);
			t = New.GetSecond();
			t8.Format("%d", t.cnt);
			mListCtrl.InsertItem(i, t0);
			mListCtrl.SetItemText(i, 1, t1);
			mListCtrl.SetItemText(i, 2, t2);
			mListCtrl.SetItemText(i, 3, t3);
			mListCtrl.SetItemText(i, 4, t4);
			mListCtrl.SetItemText(i, 5, t5);
			mListCtrl.SetItemText(i, 6, t7);
			mListCtrl.SetItemText(i, 7, t8);
		}
		MessageBox("航班删除成功！");
	}
}
