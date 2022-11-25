// CPassenger.cpp: 实现文件
//

#include "pch.h"
#include "MINI12306.h"
#include "afxdialogex.h"
#include "CPassenger.h"
#include "CFindFlightDlg.h"
#include "CbookedDlg.h"
#include "CRechargeDlg.h"

// CPassenger 对话框

IMPLEMENT_DYNAMIC(CPassenger, CDialogEx)
BOOL CPassenger::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ShowWindow(SW_NORMAL);
	CenterWindow();
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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
}


BEGIN_MESSAGE_MAP(CPassenger, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CPassenger::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CPassenger::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON5, &CPassenger::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CPassenger::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CPassenger::OnBnClickedButton3)
END_MESSAGE_MAP()


// CPassenger 消息处理程序


void CPassenger::OnBnClickedButton2()//退出登陆的程序
{
	CDialogEx::OnOK();
}


void CPassenger::OnBnClickedButton1()
{
	CString Ori, Dest, Year, Month, Day, Date;
	GetDlgItemText(IDC_EDIT2, Ori);
	GetDlgItemText(IDC_EDIT5, Dest);
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
	//MessageBox(Date);
	// TODO: 在此添加控件通知处理程序代码
}


void CPassenger::OnBnClickedButton5()
{
	//extern User CurrentUser;
	//extern UsersManager UM;
	CRechargeDlg New;
	New.m_Money.Format("%d", CurrentUser.GetMoney());
	New.m_UserName = CurrentUser.GetName();
	INT_PTR nRes = New.DoModal();
	if (nRes == IDOK)
	
		MessageBox(_T("充值成功！"));
	
	
	// TODO: 在此添加控件通知处理程序代码
}


void CPassenger::OnBnClickedButton4()
{
	//查阅用户订单
	CbookedDlg New;
	New.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}


void CPassenger::OnBnClickedButton3()
{
	extern User CurrentUser;

	//修改用户信息
	// TODO: 在此添加控件通知处理程序代码
}
