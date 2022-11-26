
// MINI12306Dlg.h: 头文件
//

#pragma once


// CMINI12306Dlg 对话框
class CMINI12306Dlg : public CDialogEx
{
// 构造
public:
	CMINI12306Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MINI12306_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	// 用户的类型
	//CComboBox CType;

	afx_msg void OnBnClickedButtonregi();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	CBrush m_bkBrush;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	CEdit MTel;
	CEdit MPW;
	CCustomDrawBtn Reset;
	CCustomDrawBtn Register;
	CCustomDrawBtn Login;
	CCustomDrawGroupBox R1, R2;
};
