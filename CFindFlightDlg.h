#pragma once
#include "afxdialogex.h"


// CFindFlightDlg 对话框

class CFindFlightDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFindFlightDlg)

public:
	CFindFlightDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFindFlightDlg();
	CString Ori, Dest, Date;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QUERY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedOk();
	CListCtrl m_ListCtrl;
	int nIndex;
	afx_msg void OnBnClickedRadio2();
};
