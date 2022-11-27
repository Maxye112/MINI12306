// EditInfoDlg.cpp: 实现文件
//

#include "pch.h"
#include "MINI12306.h"
#include "afxdialogex.h"
#include "EditInfoDlg.h"
#include <string>

// EditInfoDlg 对话框

IMPLEMENT_DYNAMIC(EditInfoDlg, CDialogEx)

EditInfoDlg::EditInfoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EDITINFO_DIALOG, pParent)
	, mName(_T(""))
	, mID(_T(""))
	, mCurrentTel(_T("")){}

EditInfoDlg::~EditInfoDlg(){}

void EditInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mName);
	DDX_Text(pDX, IDC_EDIT2, mID);
	DDX_Text(pDX, IDC_EDIT5, mCurrentTel);
}


BEGIN_MESSAGE_MAP(EditInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &EditInfoDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &EditInfoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &EditInfoDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDOK, &EditInfoDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// EditInfoDlg 消息处理程序
BOOL EditInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	extern User CurrentUser;
	mName = CurrentUser.GetName();
	mID = CurrentUser.GetID();
	std::string c = CurrentUser.GetTel();
	c[3] = c[4] = c[5] = c[6] = '*';
	mCurrentTel = c.c_str();
	SetDlgItemText(IDC_EDIT1, mName);
	SetDlgItemText(IDC_EDIT2, mID);
	SetDlgItemText(IDC_EDIT5, mCurrentTel);
	ShowWindow(SW_NORMAL);
	CenterWindow();
	UpdateData(TRUE);
	return TRUE;
}

void EditInfoDlg::OnBnClickedButton3()
{
	extern User CurrentUser;
	extern UsersManager UM;
	CString NewName, NewID, FullTel; 
	GetDlgItemText(IDC_EDIT1, NewName);
	GetDlgItemText(IDC_EDIT2, NewID);
	GetDlgItemText(IDC_EDIT10, FullTel);
	if (FullTel == "")
		AfxMessageBox("请输入手机号！");
	else
		if (FullTel == CurrentUser.GetTel())
		{
			char* nname = NewName.GetBuffer(NewName.GetLength());
			char* nid = NewID.GetBuffer(NewID.GetLength());
			CurrentUser.SetName(nname);
			CurrentUser.SetID(nid);
			UM.EditUser(CurrentUser);
			MessageBox("姓名和身份证号修改成功！");
		}
		else
			AfxMessageBox("手机号输入有误！");
}


void EditInfoDlg::OnBnClickedButton1()
{
	extern User CurrentUser;
	extern UsersManager UM;
	CString FullTel, NewPw, APw, CPw;
	GetDlgItemText(IDC_EDIT10, FullTel);
	GetDlgItemText(IDC_EDIT3, CPw);
	GetDlgItemText(IDC_EDIT4, NewPw);
	GetDlgItemText(IDC_EDIT6, APw);
	if (FullTel == "" || NewPw == "" || APw == "" || CPw == "")
		AfxMessageBox("请输入手机号、原先密码、新密码！");
	else
		if (FullTel != CurrentUser.GetTel())
			AfxMessageBox("手机号输入有误！");
		else
			if (NewPw != APw)
				AfxMessageBox("两次输入密码不一致！");
			else
				if (CPw != CurrentUser.GetPassword())
					AfxMessageBox("原密码输入错误！");
				else {
					char* npw = NewPw.GetBuffer(NewPw.GetLength());
					CurrentUser.SetPassword(npw);
					UM.EditUser(CurrentUser);
					MessageBox("密码修改成功！");
				}
}


void EditInfoDlg::OnBnClickedButton4()
{
	extern User CurrentUser;
	extern UsersManager UM;
	CString NewTel, FullTel;
	GetDlgItemText(IDC_EDIT10, FullTel);
	GetDlgItemText(IDC_EDIT11, NewTel);
	if (FullTel == "" || NewTel == "")
		AfxMessageBox("请输入原先手机号和新手机号！");
	else
		if (FullTel != CurrentUser.GetTel() || FullTel.GetLength() != 11 || NewTel.GetLength() != 11)
			AfxMessageBox("手机号输入有误！");
		else {
			char* ntel = NewTel.GetBuffer(NewTel.GetLength());
			CurrentUser.SetTelNum(ntel);
			UM.EditUser(CurrentUser);
			MessageBox("手机号修改成功！");
		}
}


void EditInfoDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}
