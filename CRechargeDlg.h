#pragma once
#include "afxdialogex.h"


// CRechargeDlg 对话框

class CRechargeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRechargeDlg)

public:
	CRechargeDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRechargeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RECHARGE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_UserName;
	CString m_Money;
	CString Addi;
	afx_msg void OnBnClickedOk();
};
