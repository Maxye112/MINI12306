// CRechargeDlg.cpp: 实现文件
//

#include "pch.h"
#include "MINI12306.h"
#include "afxdialogex.h"
#include "CRechargeDlg.h"


// CRechargeDlg 对话框

IMPLEMENT_DYNAMIC(CRechargeDlg, CDialogEx)

CRechargeDlg::CRechargeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RECHARGE_DIALOG, pParent)
	, m_UserName(_T(""))
	, m_Money(_T(""))
	, Addi(_T(""))
{

}

CRechargeDlg::~CRechargeDlg()
{
}

void CRechargeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_UserName);
	DDX_Text(pDX, IDC_EDIT2, m_Money);
	DDX_Text(pDX, IDC_EDIT3, Addi);
}


BEGIN_MESSAGE_MAP(CRechargeDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRechargeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CRechargeDlg 消息处理程序


void CRechargeDlg::OnBnClickedOk()
{
	extern User CurrentUser;
	extern UsersManager UM;
	GetDlgItemText(IDC_EDIT3, Addi);
	if (Addi == "")
	{
		AfxMessageBox("请重新输入！");
		CDialogEx::OnCancel();
	}
	else
	{
		int add = atoi(Addi);
		CurrentUser.Recharge(add);
		UM.EditUser(CurrentUser);
		CDialogEx::OnOK();
	}
}
