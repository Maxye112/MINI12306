#pragma once
#include "afxdialogex.h"


// CEnsureInfoDlg 对话框

class CEnsureInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEnsureInfoDlg)

public:
	CEnsureInfoDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CEnsureInfoDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BEFORE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString mFlightInfo;
	CString mFlightDep;
	CString mFlightArr;
	CString mFlightSt;
	CString mFlightArT;
	CString mFlightType;
	CString mCNT;
	CString mTotal;
	int tot;
	afx_msg void OnBnClickedOk();
};
