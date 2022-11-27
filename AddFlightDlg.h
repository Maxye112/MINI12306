#pragma once
#include "afxdialogex.h"
class AddFlightDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddFlightDlg)

public:
	AddFlightDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AddFlightDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CCustomDrawCombox Ori;
	CCustomDrawCombox Dest;
	afx_msg void OnBnClickedOk();
	CDateTimeCtrl m_DTCtrl;
	afx_msg void OnBnClickedRadio1();
	int nIndex, p;
	CButton Add;
	CButton Edit;
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedRadio3();
};
