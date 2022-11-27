// CRegister.cpp: 实现文件
//

#include "pch.h"
#include "MINI12306.h"
#include "afxdialogex.h"
#include "CRegister.h"



// CRegister 对话框

IMPLEMENT_DYNAMIC(CRegister, CDialogEx)

CRegister::CRegister(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REGISTER_DIALOG, pParent){}

CRegister::~CRegister(){}
BOOL CRegister::OnInitDialog()
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
	// TODO: 在此添加额外的初始化代码
	CType.AddString(_T("乘客"));
	CType.AddString(_T("管理员"));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, CType);
}


BEGIN_MESSAGE_MAP(CRegister, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRegister::OnBnClickedOk)
END_MESSAGE_MAP()


// CRegister 消息处理程序


void CRegister::OnBnClickedOk()
{
	extern UsersManager UM;
	CString NAME, ID, PW, APW, TEL;
	int type = CType.GetCurSel();
	GetDlgItemText(IDC_EDIT_TEL, TEL);
	GetDlgItemText(IDC_EDIT_NAME, NAME);
	GetDlgItemText(IDC_EDIT_ID, ID);
	GetDlgItemText(IDC_EDIT_PW, PW);
	GetDlgItemText(IDC_EDIT2, APW);
	if (NAME == "" || ID == "" || PW == "" || APW == "")
		AfxMessageBox(_T("请完整填写信息！"), MB_OK | MB_ICONERROR, 0);
	else {
		if (TEL.GetLength() != 11)
			AfxMessageBox(_T("请检查手机号的输入！"), MB_OK | MB_ICONERROR, 0);
		else{
			char* name = NAME.GetBuffer(NAME.GetLength());
			char* id = ID.GetBuffer(ID.GetLength());
			char* pw = PW.GetBuffer(PW.GetLength());
			char* Apw = APW.GetBuffer(APW.GetLength());
			char* tel = TEL.GetBuffer(TEL.GetLength());
			if (strcmp(pw, Apw) != 0)
				AfxMessageBox(_T("两次输入密码不一致，请重新输入！"), MB_OK | MB_ICONERROR, 0);
			else
			{
				if (UM.AddUser(name, pw, tel, id, type))
				{
					MessageBox(_T("用户注册成功！"));
					CDialogEx::OnOK();
				}
				else
					AfxMessageBox(_T("用户已存在！"), MB_OK | MB_ICONERROR, 0);
			}
		}
	}
}
