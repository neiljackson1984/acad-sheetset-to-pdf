//
//  Copyright 2024 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//      arxsdk/aduiEdit.h
//

#pragma once

#include "adui_port.h"

#pragma pack (push, 8)

#ifndef _ADESK_MAC_

class CAdUiDrawTipText;

////////////////////////////////////////////////////////////////////////////
// CAdUiEdit window
#pragma warning(push)
#pragma warning(disable : 4275)
class ADUI_PORT CAdUiEdit : public CEdit {
    DECLARE_DYNAMIC(CAdUiEdit)

public:
                CAdUiEdit ();
                ~CAdUiEdit ();

// Misc.
protected:
        CPoint  m_lastMousePoint;
        CRect   m_tipRect;

public:
virtual void    GetContentExtent (LPCTSTR text, int& width, int& height);
        void    GetTextExtent (LPCTSTR text, int& width, int& height);

// Validation style
public:
        DWORD   m_styleMask;            // style bits (application-defined)

virtual void    SetStyleMask (DWORD);   // define behavior
        DWORD   GetStyleMask ();        // fetch the style
        BOOL    IsStyleMaskSet (DWORD); // verify styles

// AdUi message handlers
protected:
        CWnd    *m_aduiParent;

virtual ADUI_REPLY DoAdUiMessage (
                    ADUI_NOTIFY notifyCode, UINT controlId, LPARAM lParam
                );
virtual void    OnDrawTip (CDC& dc);
virtual BOOL    OnDrawTipText (CAdUiDrawTipText& dtt);
virtual ADUI_REPLY OnGetTipSupport (CPoint& p);
virtual BOOL    OnGetTipRect (CRect& r);
virtual BOOL    OnGetTipText (CString& text);
virtual BOOL    OnHitTipRect (CPoint& p);
public:
        CWnd    *GetAdUiParent ();
        void    SetAdUiParent (CWnd *w);

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAdUiEdit)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiEdit)
    afx_msg LRESULT OnAdUiMessage (WPARAM wParam, LPARAM lParam);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

class    CAdUiSearchBoxEditor;
class    CAdUiSearchBoxSearchButton;
class    CAdUiSearchBoxClearButton;

////////////////////////////////////////////////////////////////////////////
// CAdUiSearchBox window
class ADUI_PORT CAdUiSearchBox : public CAdUiEdit{
    DECLARE_DYNAMIC(CAdUiSearchBox)

public:
                CAdUiSearchBox ();
                ~CAdUiSearchBox ();
virtual BOOL    Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
        void    PreSubclassWindow() override;
        void    SetDefaultText(LPCTSTR pszText);
        void    SetNotification(LPCTSTR pszText);
        void    ClearEditor();
        bool    IsEditEmpty();

        void    SetButtonBackgroundColorForThemeChange(COLORREF color, bool bThemeIsDark); // INTERNAL USE ONLY

public: //Override methods
virtual void    EditChanged();
virtual void    ClearButtonClicked();
virtual void    SearchButtonClicked();

protected:
    LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam) override;
    //{{AFX_MSG(CAdUiComboBox)
    BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) override;
    afx_msg void OnClearButton();
    afx_msg void OnSearchButton();
    afx_msg void SetEditFocus();
    afx_msg void KillEditFocus();
    afx_msg void OnEditChange();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
private:
    BOOL    CreateControls();
    BOOL    DestroyControls();
    void    UpdateSearchBox();
    void    UpdateButton();
    void    GetControlRect(CRect &editRect, CRect &buttonRect);

private:
    bool                    m_bIsControlsCreated;
    CAdUiSearchBoxEditor*    m_pEditor;
    CAdUiSearchBoxSearchButton*      m_pBtnSearch;
    CAdUiSearchBoxClearButton*   m_pBtnClear;

    CString                 m_strNotification;
    CString                 m_strDefaultText;
};
#pragma warning(pop)

#endif //_ADESK_MAC_
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)

/////////////////////////////////////////////////////////////////////////////
