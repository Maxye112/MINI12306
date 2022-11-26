#pragma once
#include "pch.h"

class CCustomDrawCombox :public CComboBox
{
	DECLARE_DYNAMIC(CCustomDrawCombox)
	afx_msg void OnPaint();
public:
	CCustomDrawCombox();
	virtual ~CCustomDrawCombox();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
private:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
private:
	virtual void PreSubclassWindow();
	afx_msg void OnEditUpdate();
	BOOL m_bAutoComplete;
protected:
	DECLARE_MESSAGE_MAP()
	void OnNcPaint(CDC* pDC);
};


