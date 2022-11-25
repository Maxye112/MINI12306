#pragma once
#include "afxdialogex.h"


// CResetDialog1 对话框

class CResetDialog1 : public CDialogEx
{
	DECLARE_DYNAMIC(CResetDialog1)

public:
	CResetDialog1(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CResetDialog1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESET_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString mTel;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRadio1();
	int Typ;
	afx_msg void OnBnClickedRadio2();
};
