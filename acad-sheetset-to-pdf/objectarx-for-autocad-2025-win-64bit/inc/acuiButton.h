//
//  Copyright 2024 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//      arxsdk/acuiButton.h
//
// DESCRIPTION:
//
//   Declarations for various button classes
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "acui_port.h"
#include "aduiButton.h"

/////////////////////////////////////////////////////////////////////////////
// Owner-draw Button

class ACUI_PORT CAcUiOwnerDrawButton : public CAdUiOwnerDrawButton {
    DECLARE_DYNAMIC(CAcUiOwnerDrawButton)

public:
                CAcUiOwnerDrawButton ();
                ~CAcUiOwnerDrawButton ();

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiOwnerDrawButton)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiOwnerDrawButton)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// Bitmap Button

class ACUI_PORT CAcUiBitmapButton : public CAdUiBitmapButton {
    DECLARE_DYNAMIC(CAcUiBitmapButton)

public:
                CAcUiBitmapButton ();
                ~CAcUiBitmapButton ();

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiBitmapButton)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiBitmapButton)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// Static-Style Bitmap Button

class ACUI_PORT CAcUiBitmapStatic : public CAdUiBitmapStatic {
    DECLARE_DYNAMIC(CAcUiBitmapStatic)

public:
                CAcUiBitmapStatic ();
                ~CAcUiBitmapStatic ();

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiBitmapStatic)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiBitmapStatic)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// Drag&Drop Site

class ACUI_PORT CAcUiDropSite : public CAdUiDropSite {
    DECLARE_DYNAMIC(CAcUiDropSite)

public:
                CAcUiDropSite ();
                ~CAcUiDropSite ();

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiDropSite)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiDropSite)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// "Pick-a-point" Button

class ACUI_PORT CAcUiPickButton : public CAdUiBitmapButton {
    DECLARE_DYNAMIC(CAcUiPickButton)

public:
                CAcUiPickButton ();
                ~CAcUiPickButton ();

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiPickButton)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiPickButton)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// "Make-A-Selection" Button

class ACUI_PORT CAcUiSelectButton : public CAcUiPickButton {
    DECLARE_DYNAMIC(CAcUiSelectButton)

public:
                CAcUiSelectButton ();
                ~CAcUiSelectButton ();

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiSelectButton)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiSelectButton)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/// <summary>
/// This class is used to create a bitmap button that uses quick select icon as default icon.
/// </summary>
class ACUI_PORT CAcUiQuickSelectButton : public CAdUiBitmapButton {
    DECLARE_DYNAMIC(CAcUiQuickSelectButton)

public:
                CAcUiQuickSelectButton ();
                ~CAcUiQuickSelectButton ();

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiQuickSelectButton)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiQuickSelectButton)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// Tool-Style Button

class ACUI_PORT CAcUiToolButton : public CAdUiToolButton {
    DECLARE_DYNAMIC(CAcUiToolButton)

public:
                CAcUiToolButton ();
                ~CAcUiToolButton ();

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiToolButton)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiToolButton)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

//////////////////////////////////////////////////////////////////////////////
