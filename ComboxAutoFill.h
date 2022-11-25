#if !defined(AFX_ComboCompletion_H__115F422E_5CD5_11D1_ABBA_00A02__INCLUDED_)
#define AFX_ComboCompletion_H__115F422E_5CD5_11D1_ABBA_00A02__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// ComboCompletion.h : header file
//
// Copyright (c) Chris Maunder 1997.
// Please feel free to use and distribute.


/////////////////////////////////////////////////////////////////////////////
// CComboCompletion window

class CComboCompletion : public CComboBox
{
    // Construction
public:
    CComboCompletion();

    // Attributes
public:

    // Operations
public:

    // Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CComboCompletion)
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CComboCompletion();

    BOOL m_bAutoComplete;

    // Generated message map functions
protected:
    //{{AFX_MSG(CComboCompletion)
    afx_msg void OnEditUpdate();
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};
#endif