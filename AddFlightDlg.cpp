// AddFlightDlg.cpp: 实现文件
//

#include "pch.h"
#include "MINI12306.h"
#include "afxdialogex.h"
#include "AddFlightDlg.h"


// AddFlightDlg 对话框

IMPLEMENT_DYNAMIC(AddFlightDlg, CDialogEx)

AddFlightDlg::AddFlightDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_DIALOG, pParent)
{
	nIndex = -1;
	p = 0;
}

AddFlightDlg::~AddFlightDlg()
{
}

void AddFlightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, Ori);
	DDX_Control(pDX, IDC_COMBO2, Dest);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_DTCtrl);
	DDX_Control(pDX, IDOK, Add);
	DDX_Control(pDX, IDOK2, Edit);
}


BEGIN_MESSAGE_MAP(AddFlightDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddFlightDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO1, &AddFlightDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &AddFlightDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDOK2, &AddFlightDlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDC_RADIO3, &AddFlightDlg::OnBnClickedRadio3)
END_MESSAGE_MAP()


// AddFlightDlg 消息处理程序


BOOL AddFlightDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	extern CityManager CM;
	int size = CM.CL.size();
	for (int i = 0; i < size; ++i) 
	{
		CityInfo NewCity = CM.CL[i];
		Ori.AddString(NewCity.City.c_str());
		Dest.AddString(NewCity.City.c_str());
	}
	if (p == 0)
		Edit.EnableWindow(0);
	else 
	{
		Add.EnableWindow(0);
		extern FlightInfo CurrentFlight;
		SetDlgItemText(IDC_COMBO1, CurrentFlight.GetOrigin());
		SetDlgItemText(IDC_COMBO2, CurrentFlight.GetDestination());
		SetDlgItemText(IDC_EDIT4, CurrentFlight.GetNum());
		SetDlgItemInt(IDC_EDIT12, CurrentFlight.GetFirst().price);
		SetDlgItemInt(IDC_EDIT8, CurrentFlight.GetFirst().cnt);
		SetDlgItemInt(IDC_EDIT9, CurrentFlight.GetSecond().cnt);
		SetDlgItemInt(IDC_EDIT13, CurrentFlight.GetSecond().price);
		SetDlgItemText(IDC_EDIT6, CurrentFlight.GetStartTime());
		SetDlgItemText(IDC_EDIT7, CurrentFlight.GetArriveTime());
	}
	return TRUE;  // return TRUE unless you set the focus to a control
}


void AddFlightDlg::OnBnClickedOk()
{
	CString O, D, No, Fc, Fp, Sc, Sp, Day, Year, Month, Date, ST, AT;
	GetDlgItemText(IDC_COMBO1, O);
	GetDlgItemText(IDC_COMBO2, D);
	GetDlgItemText(IDC_EDIT4, No);
	GetDlgItemText(IDC_EDIT12, Fp);
	GetDlgItemText(IDC_EDIT8, Fc);
	GetDlgItemText(IDC_EDIT9, Sc);
	GetDlgItemText(IDC_EDIT13, Sp);
	GetDlgItemText(IDC_EDIT6, ST);
	GetDlgItemText(IDC_EDIT7, AT);
	if (O == "" || D == "" || No == "" || Fp == "" || Fc == "" || Sc == "" || Sp == "" || ST == "" || AT == "" || nIndex == -1)
		AfxMessageBox("请完整填写信息！");
	else
	{
		COleDateTime m_Date;
		m_DTCtrl.GetTime(m_Date);
		int year = m_Date.GetYear();
		int month = m_Date.GetMonth();
		int day = m_Date.GetDay();
		Year.Format("%d", year);
		Month.Format("%d", month);
		Day.Format("%d", day);
		Date = Year + "/" + Month + "/" + Day;
		char* ori = O.GetBuffer(O.GetLength());
		char* dest = D.GetBuffer(D.GetLength());
		char* no = No.GetBuffer(No.GetLength());
		char* date = Date.GetBuffer(Date.GetLength());
		char* st = ST.GetBuffer(ST.GetLength());
		char* at = AT.GetBuffer(AT.GetLength());
		FlightInfo NewFlight(no, date);
		NewFlight.SetFirstInfo(atoi(Fc), atoi(Fp));
		NewFlight.SetSecondInfo(atoi(Sc), atoi(Sp));
		NewFlight.SetTime(st, at);
		NewFlight.SetOrigin(ori);
		NewFlight.SetDestination(dest);
		NewFlight.SetStatus(nIndex);
		extern FlightManager FM;
		extern CityManager CM;
		if (FM.AddFlight(NewFlight))
		{
			CM.EditCity(ori, 0);
			CM.EditCity(dest, 0);
			MessageBox("航班添加成功！");
			CDialogEx::OnOK();
		}
		else
			AfxMessageBox("航班已存在！");
	}
}


void AddFlightDlg::OnBnClickedRadio1() { nIndex = 1; }
void AddFlightDlg::OnBnClickedRadio2() { nIndex = 0; }
void AddFlightDlg::OnBnClickedRadio3() { nIndex = 2; }

void AddFlightDlg::OnBnClickedOk2()
{
	CString O, D, No, Fc, Fp, Sc, Sp, Day, Year, Month, Date, ST, AT;
	GetDlgItemText(IDC_COMBO1, O);
	GetDlgItemText(IDC_COMBO2, D);
	GetDlgItemText(IDC_EDIT4, No);
	GetDlgItemText(IDC_EDIT12, Fp);
	GetDlgItemText(IDC_EDIT8, Fc);
	GetDlgItemText(IDC_EDIT9, Sc);
	GetDlgItemText(IDC_EDIT13, Sp);
	GetDlgItemText(IDC_EDIT6, ST);
	GetDlgItemText(IDC_EDIT7, AT);
	if (O == "" || D == "" || No == "" || Fp == "" || Fc == "" || Sc == "" || Sp == "" || ST == "" || AT == "" || nIndex == -1)
		AfxMessageBox("请完整填写信息！");
	else
	{
		COleDateTime m_Date;
		m_DTCtrl.GetTime(m_Date);
		int year = m_Date.GetYear();
		int month = m_Date.GetMonth();
		int day = m_Date.GetDay();
		Year.Format("%d", year);
		Month.Format("%d", month);
		Day.Format("%d", day);
		Date = Year + "/" + Month + "/" + Day;
		char* ori = O.GetBuffer(O.GetLength());
		char* dest = D.GetBuffer(D.GetLength());
		char* no = No.GetBuffer(No.GetLength());
		char* date = Date.GetBuffer(Date.GetLength());
		char* st = ST.GetBuffer(ST.GetLength());
		char* at = AT.GetBuffer(AT.GetLength());
		FlightInfo NewFlight(no, date);
		NewFlight.SetFirstInfo(atoi(Fc), atoi(Fp));
		NewFlight.SetSecondInfo(atoi(Sc), atoi(Sp));
		NewFlight.SetTime(st, at);
		NewFlight.SetOrigin(ori);
		NewFlight.SetDestination(dest);
		NewFlight.SetStatus(nIndex);
		extern FlightManager FM;
		extern CityManager CM;
		if (FM.EditFlight(no, date, NewFlight))
		{
			MessageBox("航班信息修改成功！");
			CDialogEx::OnOK();
		}
		else
			AfxMessageBox("航班不存在！修改失败！");
	}
}



