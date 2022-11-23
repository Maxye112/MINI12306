// CResetDialog1.cpp: 实现文件
//

#include "pch.h"
#include "MINI12306.h"
#include "afxdialogex.h"
#include "CResetDialog1.h"


// CResetDialog1 对话框

IMPLEMENT_DYNAMIC(CResetDialog1, CDialogEx)

CResetDialog1::CResetDialog1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RESET_DIALOG, pParent)
	, mTel(_T(""))
{

}

CResetDialog1::~CResetDialog1()
{
}

void CResetDialog1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mTel);
}


BEGIN_MESSAGE_MAP(CResetDialog1, CDialogEx)
	ON_BN_CLICKED(IDOK, &CResetDialog1::OnBnClickedOk)
END_MESSAGE_MAP()


// CResetDialog1 消息处理程序


void CResetDialog1::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	CString ID, Name, PW, NPW;
	GetDlgItemText(IDC_EDIT3, ID);
	GetDlgItemText(IDC_EDIT4, Name);
	GetDlgItemText(IDC_EDIT2, PW);
	GetDlgItemText(IDC_EDIT5, NPW);
	if (ID == "" || Name == "" || PW == "" || NPW =="")
		AfxMessageBox(_T("请完整填写信息！"), MB_OK | MB_ICONERROR, 0);
	if (PW != NPW)
	{
		GetDlgItem(IDC_EDIT2)->SetWindowTextA("");
		GetDlgItem(IDC_EDIT5)->SetWindowTextA("");
		AfxMessageBox(_T("两次输入密码不一致！请重新输入！"), MB_OK | MB_ICONERROR, 0);
	}

}
