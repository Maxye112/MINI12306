// CEnsureInfoDlg.cpp: 实现文件
//

#include "pch.h"
#include "MINI12306.h"
#include "afxdialogex.h"
#include "CEnsureInfoDlg.h"


// CEnsureInfoDlg 对话框

IMPLEMENT_DYNAMIC(CEnsureInfoDlg, CDialogEx)

CEnsureInfoDlg::CEnsureInfoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BEFORE_DIALOG, pParent)
	, mFlightInfo(_T(""))
	, mFlightDep(_T(""))
	, mFlightArr(_T(""))
	, mFlightSt(_T(""))
	, mFlightArT(_T(""))
	, mFlightType(_T(""))
	, mCNT(_T(""))
	, mTotal(_T(""))
{

}

CEnsureInfoDlg::~CEnsureInfoDlg()
{
}

void CEnsureInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mFlightInfo);
	DDX_Text(pDX, IDC_EDIT2, mFlightDep);
	DDX_Text(pDX, IDC_EDIT3, mFlightArr);
	DDX_Text(pDX, IDC_EDIT4, mFlightSt);
	DDX_Text(pDX, IDC_EDIT6, mFlightArT);
	DDX_Text(pDX, IDC_EDIT7, mFlightType);
	DDX_Text(pDX, IDC_EDIT8, mCNT);
	DDX_Text(pDX, IDC_EDIT9, mTotal);
}


BEGIN_MESSAGE_MAP(CEnsureInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CEnsureInfoDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CEnsureInfoDlg 消息处理程序


void CEnsureInfoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
