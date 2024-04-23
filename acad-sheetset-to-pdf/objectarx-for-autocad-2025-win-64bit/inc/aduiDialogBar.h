//
//  Copyright 2024 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//      arx/aduiDialogBar.h
//

#pragma once

#include "adui_port.h"
#pragma pack (push, 8)
#ifndef _ADESK_MAC_

class CAdUiTextTip;

//////////////////////////////////////////////////////////////////////////////
// Dialog Bar
//
// Essentialy a straight port of CAdUiBaseDialog, except for the constructor.
//
// Note: This class is now obsolete and is slated for removal.
#pragma warning(push)
#pragma warning(disable : 4275) // exported class derives from non-exported class
class ADUI_PORT CAdUiDialogBar : public CDialogBar {
    DECLARE_DYNAMIC(CAdUiDialogBar);

public:
                CAdUiDialogBar ();
                ~CAdUiDialogBar ();

// AdUi message handlers
protected:
virtual ADUI_REPLY DoAdUiMessage (
                    ADUI_NOTIFY notifyCode, UINT controlId, LPARAM lParam
                );
virtual ADUI_REPLY OnNotifyControlChange (UINT controlId, LPARAM lParam);
virtual ADUI_REPLY OnNotifyControlValid (UINT controlId, BOOL isValid);
virtual ADUI_REPLY OnNotifyGeneric (UINT controlId, LPARAM lParam);
virtual ADUI_REPLY OnNotifyUpdateTip (CWnd *control);

// Misc.
protected:
        BOOL    m_bUseTips;
        CAdUiTextTip *m_pTextTip;
        CToolTipCtrl *m_pToolTip;
        CString m_rootKey;

public:
virtual CWnd    *AppMainWindow ();
virtual HINSTANCE AppResourceInstance ();
virtual LPCTSTR AppRootKey ();
        BOOL    GetUseTips ();
        void    SetUseTips (BOOL useTips);

// ClassWizard-controlled
public:
    //{{AFX_DATA(CAdUiDialogBar)
    enum { IDD = 0 };
    //}}AFX_DATA

    //{{AFX_VIRTUAL(CAdUiDialogBar)
    public:
    BOOL PreTranslateMessage(MSG* pMsg) override;
    protected:
    void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
    void PostNcDestroy() override;
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiDialogBar)
    afx_msg LRESULT OnAdUiMessage (WPARAM wParam, LPARAM lParam);
    afx_msg int OnCreate(LPCREATESTRUCT lpcs);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    //}}AFX_MSG
    afx_msg BOOL OnNotify_ToolTipText(UINT id, NMHDR *pNMHDR, LRESULT *pResult);
    DECLARE_MESSAGE_MAP()
};
#pragma warning(pop)

#endif //_ADESK_MAC_
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)

/////////////////////////////////////////////////////////////////////////////
