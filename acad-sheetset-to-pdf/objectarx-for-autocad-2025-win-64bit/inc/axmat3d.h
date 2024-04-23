//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2024 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
//
#ifndef __AXMAT3D_H_
#define __AXMAT3D_H_

#include "gemat3d.h"
#pragma pack (push, 8)

#ifndef AXAUTOEXP
#ifdef AXAUTO_DLL
	#define AXAUTOEXP __declspec(dllexport)
#else
	#define AXAUTOEXP __declspec(dllimport)
#endif
#endif

//#pragma warning(disable : 4290) 

class AXAUTOEXP AcAxMatrix3d : public AcGeMatrix3d
{
public:
    // constructors
    AcAxMatrix3d();
    AcAxMatrix3d(const VARIANT* var) noexcept(false);
    AcAxMatrix3d(const VARIANT& var) noexcept(false);
    AcAxMatrix3d(const SAFEARRAY* safeArrayPt) noexcept(false);

    // equal operators
    AcAxMatrix3d& operator=(const VARIANT* var) noexcept(false);
    AcAxMatrix3d& operator=(const VARIANT& var) noexcept(false);
    AcAxMatrix3d& operator=(const SAFEARRAY* safeArrayPt) noexcept(false);

    // utilities
private:
    AcAxMatrix3d& fromSafeArray(const SAFEARRAY* safeArrayPt) noexcept(false);
};

#pragma pack (pop)
#endif

