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
#ifndef _IDRELVER_H
#define _IDRELVER_H
#include "id.h"

//
// This file uses the following convention to distinguish macros that
// files including this file can use (for external use) and macros that
// only this file should use (for internal use).
//
// Macros for internal use have two underscores
// Macros for external use start with ACADV_ (one underscore).
//

#define VALUE2STR(x) #x
#define ID2STR(a) ID2STR__1(a)
#define ID2STR__1(a) VALUE2STR(a)

//
// Calculate the numbers for the FILEVERSION resources.
//
// The four parts of the file version resources,
// each of which evaluates to an integer constant.
//      ACADV_{RCFILEVER1, RCFILEVER2, RCFILEVER3, RCFILEVER4}.
//
// We keep the FILEVERSION and PRODUCTVERSION numbers the same.
// So these are also used for setting the ProductVersion in rc files.
#define ACADV_RCFILEVER1 ACADV_RELMAJOR
#define ACADV_RCFILEVER2 ACADV_RELMINOR

#define ACADV_RCFILEVER1_CORRECTION (6 + ACADV_RCFILEVER1)

//
// Build ACADV_VERNAME
//
// Create the string form of the release numbers, e.g.,
// "16.0" or "16.1".
//
#if defined(_MSC_VER) || defined(UNICODE)
// This definition is used when included by source files
#define ACADV_VERNAME ACRX_T(ID2STR(ACADV_RELMAJOR)) ACRX_T(".") \
                      ACRX_T(ID2STR(ACADV_RELMINOR))
#else // !_MSC_VER
// This definition is used when included by resource files
#define ACADV_VERNAME ID2STR(ACADV_RELMAJOR) "." \
                      ID2STR(ACADV_RELMINOR)
#endif // !_MSC_VER

// And finally, a copyright string for general use.
//
#define ACAD_COPYRIGHT    "Copyright 2024 Autodesk, Inc.  All rights reserved."
#define ACAD_COPYRIGHT_YEAR   "2024"

// Type library version for AutoCAD Type Library
// (axdb<ver><lang>.tlb)
//
#define ACAD_TLBVERSION_MAJOR   1
#define ACAD_TLBVERSION_MINOR   0
#define ACAD_TLBVERSION         ACAD_TLBVERSION_MAJOR.ACAD_TLBVERSION_MINOR

// String form of the type library version (ex. "1.0")
#ifdef _MSC_VER
// This definition is used when included by source files
#define ACAD_TLBVERSIONSTR      ACRX_T(ID2STR(ACAD_TLBVERSION_MAJOR)) ACRX_T(".") \
                                ACRX_T(ID2STR(ACAD_TLBVERSION_MINOR))
#else // !_MSC_VER
// This definition is used when included by resource files
#define ACAD_TLBVERSIONSTR      ID2STR(ACAD_TLBVERSION_MAJOR) "." \
                                ID2STR(ACAD_TLBVERSION_MINOR)
#endif// !_MSC_VER

// Type library version for AutoCAD/ObjectDBX Common Type Library
// (acax<ver><lang>.tlb)
//
#define ACDB_TLBVERSION_MAJOR   1
#define ACDB_TLBVERSION_MINOR   0
#define ACDB_TLBVERSION         ACDB_TLBVERSION_MAJOR.ACDB_TLBVERSION_MINOR

// String form of the type library version (ex. "1.0")
#ifdef _MSC_VER
// This definition is used when included by source files
#define ACDB_TLBVERSIONSTR      ACRX_T(ID2STR(ACDB_TLBVERSION_MAJOR)) ACRX_T(".") \
                                ACRX_T(ID2STR(ACDB_TLBVERSION_MINOR))
#else // !_MSC_VER
// This definition is used when included by resource files
#define ACDB_TLBVERSIONSTR      ID2STR(ACDB_TLBVERSION_MAJOR) "." \
                                ID2STR(ACDB_TLBVERSION_MINOR)
#endif// !_MSC_VER
#endif
