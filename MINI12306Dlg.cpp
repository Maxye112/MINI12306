
// MINI12306Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MINI12306.h"
#include "MINI12306Dlg.h"
#include "CRegister.h"
#include "CPassenger.h"
#include "CResetDialog1.h"
#include "afxdialogex.h"
#include "ManagerDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
int Typ = -1;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX){}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()
// CMINI12306Dlg 对话框
CMINI12306Dlg::CMINI12306Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MINI12306_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMINI12306Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TEL, MTel);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, MPW);
	DDX_Control(pDX, IDC_BUTTON2, Reset);
	DDX_Control(pDX, IDC_BUTTONRegi, Register);
	DDX_Control(pDX, IDOK, Login);
	DDX_Control(pDX, IDC_RADIO1, R1);
	DDX_Control(pDX, IDC_RADIO2, R2);
}

BEGIN_MESSAGE_MAP(CMINI12306Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMINI12306Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTONRegi, &CMINI12306Dlg::OnBnClickedButtonregi)
	ON_BN_CLICKED(IDC_BUTTON2, &CMINI12306Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_RADIO1, &CMINI12306Dlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMINI12306Dlg::OnBnClickedRadio2)
	ON_WM_CTLCOLOR()
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// CMINI12306Dlg 消息处理程序

BOOL CMINI12306Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ShowWindow(SW_NORMAL);
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	MoveWindow(0, 0, 640, 480);
	CenterWindow();
	CString strBmpPath = _T(".\\res\\LoginUI.png");
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
		GetDlgItem(IDC_EDIT_TEL)->SetFont(pFont);
		GetDlgItem(IDC_EDIT_PASSWORD)->SetFont(pFont);
	}
	//delete pFont;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


HBRUSH CMINI12306Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd == this)
		hbr = m_bkBrush;
	return hbr;
}


void CMINI12306Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
		CDialogEx::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMINI12306Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
		CDialogEx::OnPaint();
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMINI12306Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMINI12306Dlg::OnBnClickedOk()
{
	extern UsersManager UM;
	CString ITEL, IPW; 
	GetDlgItemText(IDC_EDIT_TEL, ITEL);
	GetDlgItemText(IDC_EDIT_PASSWORD, IPW);
	char* Tel = ITEL.GetBuffer(ITEL.GetLength());
	char* Pw = IPW.GetBuffer(IPW.GetLength());
	if (ITEL == "" || IPW == "" || Typ == -1 )
		AfxMessageBox(_T("请完整填写信息！"), MB_OK | MB_ICONERROR, 0);
	else
	{
		if (ITEL.GetLength() != 11)
			AfxMessageBox(_T("请检查手机号的输入！"));
		else{
			if (!UM.ValidateUser(Tel, Pw, Typ))
				AfxMessageBox(_T("请检查用户是否注册，或者检查手机号和密码和用户类型！"), MB_OK | MB_ICONERROR, 0);
			else
				if (Typ == 0)
				{
					//用户端
					CPassenger PasDlg;
					extern User CurrentUser;
					UM.FindUserByTel(Tel, CurrentUser);
					PasDlg.m_UserName = CurrentUser.GetName();
					MessageBox(_T("登录成功！"));
					GetDlgItem(IDC_EDIT_TEL)->SetWindowTextA("");
					GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowTextA("");
					ShowWindow(SW_HIDE);
					INT_PTR New = PasDlg.DoModal();
					if (IDOK == New)
					{
						ShowWindow(SW_NORMAL);
						CenterWindow();
					}
					else CDialogEx::OnOK();
				}
				else
				{
					//管理端
					ManagerDlg NewWin;
					MessageBox(_T("登录成功！"));
					extern User CurrentUser;
					UM.FindUserByTel(Tel, CurrentUser);
					GetDlgItem(IDC_EDIT_TEL)->SetWindowTextA("");
					GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowTextA("");
					ShowWindow(SW_HIDE);
					INT_PTR New = NewWin.DoModal();
					if (IDOK == New)
					{
						ShowWindow(SW_NORMAL);
						CenterWindow();
					}
					else CDialogEx::OnOK();
				}
		}
	}
}


void CMINI12306Dlg::OnBnClickedButtonregi()
{
	CRegister RegDlg;
	RegDlg.DoModal();
}


void CMINI12306Dlg::OnBnClickedButton2()
{
	CResetDialog1 New;
	GetDlgItemText(IDC_EDIT_TEL, New.mTel);
	New.DoModal();
}

void CMINI12306Dlg::OnBnClickedRadio1(){Typ = 0;}
void CMINI12306Dlg::OnBnClickedRadio2(){Typ = 1;}

LRESULT CMINI12306Dlg::OnNcHitTest(CPoint point)
{
	LRESULT ret = CDialogEx::OnNcHitTest(point);
	return (ret == HTCLIENT) ? HTCAPTION : ret;
}
