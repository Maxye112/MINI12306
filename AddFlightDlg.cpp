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
}


BEGIN_MESSAGE_MAP(AddFlightDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddFlightDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// AddFlightDlg 消息处理程序


BOOL AddFlightDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	extern CityManager CM;
	int size = CM.CL.size();
	for (int i = 0; i < size; ++i) 
	{
		City NewCity = CM.CL[i];
		Ori.AddString(NewCity.c_str());
		Dest.AddString(NewCity.c_str());
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
	extern FlightManager FM;
	if (FM.AddFlight(NewFlight))
	{
		MessageBox("航班添加成功！");
		CDialogEx::OnOK();
	}
	else
		AfxMessageBox("航班已存在！");
}
