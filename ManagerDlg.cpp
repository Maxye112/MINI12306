// ManagerDlg.cpp: 实现文件
//

#include "pch.h"
#include "MINI12306.h"
#include "afxdialogex.h"
#include "ManagerDlg.h"


// ManagerDlg 对话框

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
}


BEGIN_MESSAGE_MAP(ManagerDlg, CDialogEx)
END_MESSAGE_MAP()


// ManagerDlg 消息处理程序
