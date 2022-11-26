#pragma once
#include "pch.h"
#include "afxdialogex.h"


// EditInfoDlg 对话框

class EditInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(EditInfoDlg)

public:
	EditInfoDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~EditInfoDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDITINFO_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString mName;
	CString mID;
	CString mCurrentTel;

	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedOk();
};
