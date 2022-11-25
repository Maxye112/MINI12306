#pragma once
#include "afxdialogex.h"


// ManagerDlg 对话框

class ManagerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ManagerDlg)

public:
	ManagerDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ManagerDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MANAGER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl mListCtrl;
};
