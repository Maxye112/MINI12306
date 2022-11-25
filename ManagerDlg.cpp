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
	DDX_Control(pDX, IDC_COMBO1, mCityList);
}


BEGIN_MESSAGE_MAP(ManagerDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &ManagerDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// ManagerDlg 消息处理程序

BOOL ManagerDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();
	ShowWindow(SW_NORMAL);
	CenterWindow();
	extern CityManager CM;
	int size = CM.CL.size();
	for (int i = 0; i < size; ++i) {
		City New = CM.CL[i];
		mCityList.AddString(New.c_str());
	}
	return TRUE;
}

void ManagerDlg::OnBnClickedButton3()
{
	extern CityManager CM;
	CString CityName;
	GetDlgItemText(IDC_COMBO1, CityName);
	if (CityName == "")
		AfxMessageBox("请输入城市名称");
	else {
		City name = CityName;
		if (!CM.AddCity(name))
			AfxMessageBox("城市已存在，请重新输入！");
		else
		{
			mCityList.ResetContent();
			int size = CM.CL.size();
			for (int i = 0; i < size; ++i) {
				City New = CM.CL[i];
				mCityList.AddString(New.c_str());
			}
			MessageBox("城市添加成功！");
		}
	}
}
