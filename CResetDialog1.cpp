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
{Typ = -1;}

CResetDialog1::~CResetDialog1(){}

void CResetDialog1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mTel);
}
BEGIN_MESSAGE_MAP(CResetDialog1, CDialogEx)
	ON_BN_CLICKED(IDOK, &CResetDialog1::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO1, &CResetDialog1::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CResetDialog1::OnBnClickedRadio2)
END_MESSAGE_MAP()
// CResetDialog1 消息处理程序
void CResetDialog1::OnBnClickedOk()
{
	extern UsersManager UM;
	extern User CurrentUser;
	CString ID, Name, PW, NPW, Tel;
	GetDlgItemText(IDC_EDIT3, ID);
	GetDlgItemText(IDC_EDIT4, Name);
	GetDlgItemText(IDC_EDIT2, PW);
	GetDlgItemText(IDC_EDIT5, NPW);
	GetDlgItemText(IDC_EDIT1, Tel);
	if (ID == "" || Name == "" || PW == "" || NPW == "" || Tel == "" || Typ == -1)
		AfxMessageBox(_T("请完整填写信息！"), MB_OK | MB_ICONERROR, 0);
	else 
		if (PW != NPW)
		{
			GetDlgItem(IDC_EDIT2)->SetWindowTextA("");
			GetDlgItem(IDC_EDIT5)->SetWindowTextA("");
			AfxMessageBox(_T("两次输入密码不一致！请重新输入！"), MB_OK | MB_ICONERROR, 0);
		}
		else {
			if (Tel.GetLength() != 11)
				AfxMessageBox(_T("请检查手机号的输入！"));
			else
			{
				char* tel = Tel.GetBuffer(Tel.GetLength());
				if (UM.FindUserByTel(tel, CurrentUser))
				{
					char* StdTel = CurrentUser.GetTel();
					char* StdName = CurrentUser.GetName();
					char* StdID = CurrentUser.GetID();
					int StdIndex = CurrentUser.GetUserType();
					if (!strcmp(StdName, Name) && !strcmp(StdID, ID))
					{
						CurrentUser.SetPassword(PW.GetBuffer(PW.GetLength()));
						UM.EditUser(CurrentUser);
						MessageBox(_T("用户密码重置成功！"));
						CDialogEx::OnOK();
					}
					else
						AfxMessageBox(_T("请检查输入是否有误！"), MB_OK | MB_ICONERROR, 0);
				}
				else
					AfxMessageBox(_T("该用户未注册！请检查输入是否有误！"), MB_OK | MB_ICONERROR, 0);
			}
		}

}


void CResetDialog1::OnBnClickedRadio1(){Typ = 0;}
void CResetDialog1::OnBnClickedRadio2(){Typ = 1;}
