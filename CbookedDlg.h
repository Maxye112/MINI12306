#pragma once
#include "afxdialogex.h"


// CbookedDlg 对话框

class CbookedDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CbookedDlg)

public:
	CbookedDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CbookedDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BOOKED_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;
};
