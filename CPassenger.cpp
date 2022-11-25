// CPassenger.cpp: 实现文件
//

#include "pch.h"
#include "MINI12306.h"
#include "afxdialogex.h"
#include "CPassenger.h"
#include "CFindFlightDlg.h"
#include "CbookedDlg.h"
#include "CRechargeDlg.h"
#include "EditInfoDlg.h"
// CPassenger 对话框

IMPLEMENT_DYNAMIC(CPassenger, CDialogEx)
BOOL CPassenger::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ShowWindow(SW_NORMAL);
	CenterWindow();
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	extern CityManager CM;
	int size = CM.CL.size();
	for (int i = 0; i < size; ++i) 
	{
		CString Name= CM.CL[i].c_str();
		mOri.AddString(Name);
		mDest.AddString(Name);
	}
	extern FlightManager FM;
	size = FM.FQ.size();
	COleDateTime m_Date;
	CString Year, Month, Day, Date;
	m_DTCtrl.GetTime(m_Date);
	int year = m_Date.GetYear();
	int month = m_Date.GetMonth();
	int day = m_Date.GetDay();
	Year.Format("%d", year);
	Month.Format("%d", month);
	Day.Format("%d", day);
	Date = Year + "/" + Month + "/" + Day;
	//char* date = Date.GetBuffer(Date.GetLength());
	for (int i = 0; i < size; ++i)
	{
		if (FM.FQ[i].GetDate() != Date) 
			continue;
		CString ID = FM.FQ[i].GetNum();
		mNum.AddString(ID);
	}
	// TODO: 在此添加额外的初始化代码
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

CPassenger::CPassenger(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PASS_DIALOG, pParent)
	, m_UserName(_T(""))
{

}

CPassenger::~CPassenger()
{
}

void CPassenger::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_UserName);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_DTCtrl);
	DDX_Control(pDX, IDC_COMBO1, mOri);
	DDX_Control(pDX, IDC_COMBO2, mDest);
	DDX_Control(pDX, IDC_COMBO3, mNum);
}


BEGIN_MESSAGE_MAP(CPassenger, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CPassenger::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CPassenger::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON5, &CPassenger::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CPassenger::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CPassenger::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON7, &CPassenger::OnBnClickedButton7)
END_MESSAGE_MAP()


// CPassenger 消息处理程序


void CPassenger::OnBnClickedButton2()//退出登陆的程序
{
	CDialogEx::OnOK();
}


void CPassenger::OnBnClickedButton1()
{
	CString Ori, Dest, Year, Month, Day, Date;
	GetDlgItemText(IDC_COMBO1, Ori);
	GetDlgItemText(IDC_COMBO2, Dest);
	if (Ori == "" || Dest == "")
		AfxMessageBox(_T("请输入出发地和目的地！"), MB_OK | MB_ICONERROR, 0);
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
		CFindFlightDlg query;
		query.Ori = Ori, query.Dest = Dest, query.Date = Date;
		query.DoModal();
	}
}


void CPassenger::OnBnClickedButton5()
{
	CRechargeDlg New;
	New.m_Money.Format("%d", CurrentUser.GetMoney());
	New.m_UserName = CurrentUser.GetName();
	INT_PTR nRes = New.DoModal();
	if (nRes == IDOK)
		MessageBox(_T("充值成功！"));
}


void CPassenger::OnBnClickedButton4()
{
	//查阅用户订单
	CbookedDlg New;
	New.DoModal();
}


void CPassenger::OnBnClickedButton3()
{
	EditInfoDlg New;
	extern User CurrentUser;
	New.mName = CurrentUser.GetName();
	New.mID = CurrentUser.GetID();
	std::string c = CurrentUser.GetTel();
	c[3] = c[4] = c[5] = c[6] = '*';
	New.mCurrentTel = c.c_str();
	New.DoModal();
	m_UserName = CurrentUser.GetName();
	SetDlgItemText(IDC_EDIT1,m_UserName);
	//修改用户信息
}


void CPassenger::OnBnClickedButton7()
{
	CString Year, Month, Day, Date;
	COleDateTime m_Date;
	m_DTCtrl.GetTime(m_Date);
	int year = m_Date.GetYear();
	int month = m_Date.GetMonth();
	int day = m_Date.GetDay();
	Year.Format("%d", year);
	Month.Format("%d", month);
	Day.Format("%d", day);
	Date = Year + "/" + Month + "/" + Day;
}
