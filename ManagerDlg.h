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

private:
	static int col;
	static bool method;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CCustomDrawListCtrl mListCtrl;
	afx_msg void OnBnClickedButton3();
	virtual BOOL OnInitDialog();
	CCustomDrawCombox mCityList;
	afx_msg void OnBnClickedButton4();
	
	static int CALLBACK MyCompareProc(LPARAM, LPARAM, LPARAM);
	afx_msg void OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton1();
	CBrush m_bkBrush;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton2();
	CCustomDrawBtn addf, delf, addc, delc;
};
