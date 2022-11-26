#pragma once
#include "afxdialogex.h"

// CPassenger 对话框

class CPassenger : public CDialogEx
{
	DECLARE_DYNAMIC(CPassenger)

public:
	CPassenger(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPassenger();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PASS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	// 用户名
	CString m_UserName;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	CDateTimeCtrl m_DTCtrl;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton7();
	CCustomDrawCombox  mOri;
	CCustomDrawCombox  mDest;
	CCustomDrawCombox  mNum;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBrush m_bkBrush;
	CCustomDrawEdit UserName;
	CCustomDrawBtn Book;
	CCustomDrawBtn Recharge;
	CCustomDrawBtn FindByNum;
	CCustomDrawBtn Booked;
	CCustomDrawBtn EditInfo;
	CCustomDrawBtn Exit;
};
