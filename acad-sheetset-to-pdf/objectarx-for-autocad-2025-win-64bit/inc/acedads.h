//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2024 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#ifndef _acedads_h
#define _acedads_h 1

#ifdef __cplusplus
#include "adesk.h"
#endif

#include "adsdef.h"
#include "AcCoreDefs.h"
#include "acbasedefs.h"
#include "acmem.h"
#include "AdAChar.h"

#define AcEdAds_Deprecated_ACHAR_Funcs
#ifdef __cplusplus
#include "acadstrc.h"           // Acad::ErrorStatus
#include "AcString.h"
#ifdef AcEdAds_Deprecated_ACHAR_Funcs
#include "acutAcString.h"       // acutCopyAdsResultStr()
#endif
#endif

#pragma pack (push, 8)
// AdInt32 is obsolete and will be removed in the future
// Please use Adesk::Int32, int32_t or int instead
#ifdef AdInt32
#undef AdInt32
#endif
#ifdef __cplusplus
#define AdInt32 Adesk::Int32
#else
#define AdInt32 long
#endif

// LINKAGE: The following functions are exported with both extern "C" and C++ linkage.
// The extern "C" linkage allows use by legacy C modules (*.c as opposed to *.cpp).
// New modules should be written in C++, as we may some day drop support for C.
//

/* External function definitions accessible from applications */

const ACHAR *  acedGetAppName ();
int            acedUpdate(int vport, ads_point p1, ads_point p2);

#if defined(_WINDEF_) || defined(_ADESK_MAC_)
/* AutoCAD graphics window handle */
#if (defined(_ADESK_CROSS_PLATFORM_) && defined(ACCORE_FABRIC) && !defined(CRX_API)) || !defined(_ADESK_CROSS_PLATFORM_)
ACCORE_PORT HWND           adsw_acadMainWnd();
#ifndef adsw_hwndAcad
#define adsw_hwndAcad adsw_acadMainWnd()
#endif

/* MFC "Document View" window handle */
ACCORE_PORT HWND adsw_acadDocWnd();
#endif
#endif  // _WINDOWS_


#define acedCommand MustSwitchTo_acedCommandC_or_acedCommandS - - !
#define acedCmd MustSwitchTo_acedCmdC_or_acedCmdS - - !

/* Register an ADS function handler */
int            acedRegFunc (int (*fhdl) (void), int fcode);

/* Check for a console break */
int            acedUsrBrk (void);


/* Define an external subroutine in AutoLISP */
int     acedDefun   (const ACHAR *pszName, int nFuncNum);
int     acedDefunEx (const ACHAR *pszGlobalName,
                     const ACHAR *pszLocalName, int nFuncNum);

/* Define help for that external subroutine */
int            acedSetFunHelp (const ACHAR* pszFunctionName, 
                               const ACHAR* pszHelpfile,
                               const ACHAR* pszTopic, int iCmd);

/* Undefine an external subroutine in AutoLISP */
int            acedUndef (const ACHAR *sname, int nFuncNum);

// Utilities for external subroutine interface
int            acedGetFunCode (void);
struct resbuf *acedGetArgs (void);

/* Return the specified type as a result of external subroutine */
int            acedRetList (const struct resbuf *rbuf);
int            acedRetVal (const struct resbuf *rbuf);
int            acedRetPoint (const ads_point pt);
int            acedRetStr (const ACHAR *s);
int            acedRetName (const ads_name aname, int type);
int            acedRetInt (int ival);
int            acedRetReal (double rval);
int            acedRetT (void);
int            acedRetNil (void);
int            acedRetVoid (void);

/* AutoCAD Entity access routines */

int            acedEntSel (const ACHAR *str, ads_name entres,
                             ads_point ptres);
#ifdef __cplusplus
class AcSelectionPreview;
ACCORE_PORT int acedEntSel (const ACHAR *str, ads_name entres,
                             ads_point ptres, AcSelectionPreview *pSelectionPreview);
#endif
int            acedNEntSel (const ACHAR *str, ads_name entres,
                              ads_point ptres, ads_point xformres[4],
                              struct resbuf **refstkres);
int            acedNEntSelP (const ACHAR *str, ads_name entres,
                              ads_point ptres, int pickflag,
                              ads_matrix xformres,
                              struct resbuf **refstkres);
int            acedSSGet (const ACHAR *str, const void *pt1,
                            const void *pt2, const struct resbuf *filter,
                            ads_name ss);
#ifdef __cplusplus
ACCORE_PORT int acedSSGet (const ACHAR *str, const void *pt1,
                           const void *pt2, const struct resbuf *filter,
                           ads_name ss, AcSelectionPreview *pSelectionPreview);
#endif
int            acedSSGetFirst (struct resbuf** gset, struct resbuf** pset);
int            acedSSSetFirst (const ads_name pset, const ads_name unused);
int            acedSSFree (const ads_name sname);
#ifdef __cplusplus
int            acedSSLength (const ads_name sname, Adesk::Int32 *len);
#else
int            acedSSLength (const ads_name sname, long *len);
#endif
int            acedSSAdd (const ads_name ename, const ads_name sname,
                            ads_name result);
int            acedSSDel (const ads_name ename, const ads_name ss);
int            acedSSMemb (const ads_name ename, const ads_name ss);
int            acedSSName (const ads_name ss, int i, ads_name entres);
int            acedSSNameX (struct resbuf **rbpp, const ads_name ss,
                            int i);
int            acedSSNameXEx (struct resbuf **rbpp, const ads_name ss,
                              int i, unsigned int flags);

int            acedSSGetKwordCallbackPtr(struct resbuf* (**pFunc)(const ACHAR*));
int            acedSSSetKwordCallbackPtr(struct resbuf* (*pFunc)(const ACHAR*));
int            acedSSGetOtherCallbackPtr(struct resbuf* (**pFunc)(const ACHAR*));
int            acedSSSetOtherCallbackPtr(struct resbuf* (*pFunc)(const ACHAR*));

int            acedTrans (const ads_point pt, const struct resbuf *from,
                            const struct resbuf *to, int disp,
                            ads_point result);

/* General AutoCAD utility routines */
int            acedSetVar (const ACHAR *sym, const struct resbuf *val);
int            acedInitGet (int val, const ACHAR *kwl);

int            acedGetSym (const ACHAR *sname, struct resbuf **value);
int            acedPutSym (const ACHAR *sname, struct resbuf *value);

int            acedHelp (const ACHAR* szFilename, const ACHAR* szTopic, int iCmd);
int            acedHelpForExternal (const ACHAR *pszFunctionName);

int            acedFNSplit (const ACHAR *pathToSplit,
                            ACHAR *prebuf, size_t nPreBufLen,
                            ACHAR *namebuf, size_t nNameBufLen,
                            ACHAR *extbuf, size_t nExtBufLen);

/*  These values are identical to those for the WinHelp() call in the 
    Microsoft Windows(tm) SDK.  If you are using acedHelp() to call AutoCAD 
    platform-independent Help these are the only values available to you.  
    If you are using acedHelp() to call WinHelp() you can include the Windows 
    header file winuser.h and use the full WinHelp() API.  */
#define HELP_CONTENTS     0x0003L  /* display first topic */
#define HELP_HELPONHELP   0x0004L  /* Display help on using help */
#define HELP_PARTIALKEY   0x0105L  /* Display Search dialog */

struct resbuf  *acedArxLoaded (void);
int            acedArxLoad (const ACHAR *app);
int            acedArxUnload (const ACHAR *app);

int            acedInvoke (const struct resbuf *args,
                             struct resbuf **result);
/* Functions that get system variables */
int            acedGetVar (const ACHAR *sym, struct resbuf *result);

#ifdef AcEdAds_Deprecated_ACHAR_Funcs
// Search for a file using acad's support path
// Returns RTNORM if success, else RTERROR
int acedFindFile (const ACHAR *fname, ACHAR *result, size_t nBufLen);
// Search for a file in the TRUSTED PATHS folders
int acedFindTrustedFile (const ACHAR *fname, ACHAR *result, size_t nBufLen);

/* Functions that get/set environment variables */
int            acedGetEnv (const ACHAR *sym, ACHAR  *var, size_t nBufLen);
#endif
int            acedSetEnv (const ACHAR *sym, const ACHAR *val);

// Functions that get/set configurations  variables
// Deprecated: The .cfg file and the acedGet/SetCfg() API functions will be removed in
// a future release.  Please relocate cfg file settings to the registry or elsewhere
//
int            acedSetCfg (const ACHAR *sym, const ACHAR *val);
#ifdef AcEdAds_Deprecated_ACHAR_Funcs
int            acedGetCfg (const ACHAR *sym, ACHAR  *var, size_t len);

/* Functions that get a string */
int            acedGetString (int cronly, const ACHAR *prompt,
                               ACHAR *result, size_t bufsize);
#endif

/* Functions that pass AutoCAD a single string  */
int            acedMenuCmd (const ACHAR *str);
int            acedPrompt (const ACHAR *str);
int            acedAlert (const ACHAR *str);

/* Functions used to get user input  */
int            acedGetAngle (const ads_point pt, const ACHAR *prompt, double *result);
int            acedGetCorner (const ads_point pt, const ACHAR *prompt, ads_point result);
int            acedGetDist (const ads_point pt, const ACHAR *prompt, double *result);
int            acedGetOrient (const ads_point pt, const ACHAR *prompt, double *result);
int            acedGetPoint (const ads_point pt, const ACHAR *prompt, ads_point result);
// This overload only returns 16-bit int vals, between -32k and 32k
// Deprecated.  Please use one of the other acedGetInt() overloads below instead
int            acedGetInt (const ACHAR *prompt, int *result);
#ifdef AcEdAds_Deprecated_ACHAR_Funcs
int            acedGetKword (const ACHAR *prompt, ACHAR *result, size_t nBufLen);
int            acedGetInput (ACHAR *str, size_t nBufLen);
#endif
int            acedGetReal (const ACHAR *prompt, double *result);
int            acedVports (struct resbuf **vlist);

/* Functions for screen flipping */
int            acedTextScr (void);
int            acedGraphScr (void);
int            acedTextPage (void);

/* Graphics related functions */
int            acedRedraw (const ads_name ent, int mode);
int            acedOsnap (const ads_point pt, const ACHAR *mode,
                            ads_point result);
int            acedGrRead (int track, int *type, struct resbuf *result);
int            acedGrText (int box, const ACHAR *text, int hl);
int            acedGrDraw (const ads_point from, const ads_point to,
                             int color, int hl);
int            acedGrVecs (const struct resbuf *vlist, ads_matrix mat);
int            acedXformSS (const ads_name ssname,
                              ads_matrix genmat);
int            acedDragGen (const ads_name ss, const ACHAR *pmt, int cursor,
                              int (*scnf) (ads_point pt, ads_matrix mt),
                              ads_point p);
int            acedSetView (const struct resbuf *view, int vport);


/* Functions that put up standard dialogs for user input */
int            acedGetFileD (const ACHAR *title, const ACHAR *defawlt,
                               const ACHAR *ext, int flags,
                               struct resbuf *result);
int            acedGetFileNavDialog (const ACHAR *title, const ACHAR *defawlt,
                             const ACHAR *ext, const ACHAR *dlgname, int flags,
                             struct resbuf **result);

int            acedTextBox (const struct resbuf *args,
                              ads_point pt1, ads_point pt2);

/*  Function to retrieve or establish AutoCAD's tablet transformation: */
int            acedTablet  (const struct resbuf *args,
                              struct resbuf **result);

/// <summary>
/// Gets the localized or the language independent name of a command.
/// I.e., translates a command name from local to global, or from global to local
/// </summary>
///
/// <param name="cmd">
///  Input string which is the command name to be translated.
///  If the first char is underbar ('_'), then cmd is taken as global (language
///  independent), and the function returns the localized name.
///  Otherwise cmd is take as localized and the global name is returned
/// </param>
///
/// <param name="result">
///  Pointer to an out pointer which receives the address of the buffer containing
///  the translated name.  The caller is responsible for freeing up this buffer.
///  On error, *result will be set to nullptr
/// </param>
///
/// <returns>
///  Returns RTNORM on success, else RTERROR
/// </returns>
///
/// <remarks>
///  This overload returning an allocated buffer is deprecated and may be removed.
///  Please use the AcString-based overload below instead.
///  The AcString-based overload returns an empty string on error.
/// </remarks>
///
#ifdef AcEdAds_Deprecated_ACHAR_Funcs
int            acedGetCName (const ACHAR *cmd, ACHAR **result);
#endif

// Internal use only. 
int           acedEatCommandThroat(void);

// The following are AcDb related, but were not able to be moved over
// to AcDb at this time.  They will be moved in a future release.  7/14/98

int            acdbEntDel (const ads_name ent);
struct resbuf *acdbEntGetX (const ads_name ent, const struct resbuf *args);
struct resbuf *acdbEntGet (const ads_name ent);
int            acdbEntLast (ads_name result);
int            acdbEntNext (const ads_name ent, ads_name result);
int            acdbEntUpd (const ads_name ent);
int            acdbEntMod (const struct resbuf *ent);
int            acdbEntMake (const struct resbuf *ent);
int            acdbEntMakeX (const struct resbuf *entm, ads_name result);

int            acdbRegApp (const ACHAR *appname);
struct resbuf *acdbTblNext (const ACHAR *tblname, int rewind);
struct resbuf *acdbTblSearch (const ACHAR *tblname, const ACHAR *sym,
                              int setnext);
int            acdbNamedObjDict (ads_name result);
struct resbuf *acdbDictSearch (const ads_name dict, const ACHAR* sym, 
                               int setnext);
struct resbuf *acdbDictNext (const ads_name dict, int rewind);
int            acdbDictRename (const ads_name dictname, const ACHAR* oldsym,
                               const ACHAR* newsym);
int            acdbDictRemove (const ads_name dictname, const ACHAR* symname);
int            acdbDictAdd (const ads_name dictname, const ACHAR* symname,
                            const ads_name newobj);

int            acdbTblObjName (const ACHAR *tblname, const ACHAR *sym, 
                               ads_name result);

#ifdef AcEdAds_Deprecated_ACHAR_Funcs
// These 3 charbuf and size-based overloads are deprecated.
// Please use the AcString-based ones below instead
int            acdbAngToS    (double v, int unit, int prec, ACHAR *str, size_t nBufLen);
int            acdbRawAngToS (double v, int unit, int prec, ACHAR *str, size_t nBufLen);
int            acdbRToS    (double val, int unit, int prec, ACHAR *str, size_t nBufLen);
#endif

int            acdbAngToF    (const ACHAR *str, int unit, double *v);
int            acdbRawAngToF (const ACHAR *str, int unit, double *v);
int            acdbDisToF    (const ACHAR *str, int unit, double *v);
int            acdbInters (const ads_point from1, const ads_point to1,
                           const ads_point from2, const ads_point to2,
                           int teston, ads_point result);
int            acdbSNValid (const ACHAR *tbstr, int pipetest);

int            ads_queueexpr(const ACHAR* expr);

#ifdef __cplusplus

ACCORE_PORT int acdbAngToS    (double val, AcString &sOut, int unit = -1, int prec = -1);
ACCORE_PORT int acdbRawAngToS (double val, AcString &sOut, int unit = -1, int prec = -1);
ACCORE_PORT int acdbRToS      (double val, AcString &sOut, int unit = -1, int prec = -1);
ACCORE_PORT int acedFindFile (const ACHAR *fname, AcString &sResult);
ACCORE_PORT int acedFindTrustedFile (const ACHAR *fname, AcString &sResult);
ACCORE_PORT int acedGetCName (const ACHAR *cmd, AcString &sOut);
ACCORE_PORT int acedGetEnv (const ACHAR *sym, AcString &sResult);
ACCORE_PORT int acedGetCfg (const ACHAR *sym, AcString &sResult);
ACCORE_PORT int acedGetString (int cronly, const ACHAR *prompt, AcString &sResult);
ACCORE_PORT int acedGetInt (const ACHAR *prompt, int &nResult);         // returns 32-bit int
ACCORE_PORT int acedGetInt (const ACHAR *prompt, int &nResult, int nMin, int nMax);
ACCORE_PORT int acedGetKword (const ACHAR *prompt, AcString & sResult);
ACCORE_PORT int acedGetInput (AcString &sOut);

// Deprecated, restricts return val to MinShort..MaxShort
//
inline int acedGetInt (const ACHAR *prompt, int *result)
{
    ACCORE_PORT int acedGetShort(const wchar_t *, int *);
    return acedGetShort(prompt, result);
}

#ifdef AcEdAds_Deprecated_ACHAR_Funcs
Acad::ErrorStatus acutNewString(const ACHAR* pInput, ACHAR*& pOutput);

// Following inlines are all deprecated.  Please use AcString-based overloads instead
// Except for the acedGetFullXXX() funcs, they are also all exported (on Windows),
// with both MSVC name mangling and extern "C" signatures
//

inline int acedGetString (int cronly, const ACHAR *prompt, ACHAR *result, size_t bufsize)
{
    AcString sOut;
    const int nAdsRet = ::acedGetString(cronly, prompt, sOut);
    return ::acutCopyAdsResultStr(nAdsRet, sOut.constPtr(), result, bufsize);
}

inline int acedGetInput (ACHAR *str, size_t nBufLen)
{
    AcString sOut;
    const int nAdsRet = ::acedGetInput(sOut);
    return ::acutCopyAdsResultStr(nAdsRet, sOut.constPtr(), str, nBufLen);
}

inline int acedGetFullInput(ACHAR *&pStr)
{
    AcString sOut;
    const int nRet = ::acedGetInput(sOut);
    ::acutNewString(sOut.constPtr(), pStr);     // (old string is not freed)
    return nRet;
}

inline int acedGetKword (const ACHAR *prompt, ACHAR *result, size_t nBufLen)
{
    AcString sOut;
    const int nAdsRet = ::acedGetKword(prompt, sOut);
    return ::acutCopyAdsResultStr(nAdsRet, sOut.constPtr(), result, nBufLen);
}

// use AcString-based acedGetKword() instead
inline int acedGetFullKword(const ACHAR * pString, ACHAR *&pStr)
{
    AcString sOut;
    const int nRet = ::acedGetKword(pString, sOut);
    ::acutNewString(sOut.constPtr(), pStr);     // (old string is not freed)
    return nRet;
}

// use AcString-based acedGetString() instead
inline int acedGetFullString(int cronly, const ACHAR *pString, ACHAR *&pResult)
{
    AcString sResult;
    const int nRet = ::acedGetString(cronly, pString, sResult);
    ::acutNewString(sResult.constPtr(), pResult);       // (old string is not freed)
    return nRet;
}

inline int acedFindFile (const ACHAR *fname, ACHAR *result, size_t nBufLen)
{
    AcString sOut;
    const int nAdsRet = ::acedFindFile (fname, sOut);
    return ::acutCopyAdsResultStr(nAdsRet, sOut.constPtr(), result, nBufLen);
}

inline int acedGetEnv (const ACHAR *sym, ACHAR  *var, size_t nBufLen)
{
    AcString sOut;
    const int nAdsRet = ::acedGetEnv (sym, sOut);
    return ::acutCopyAdsResultStr(nAdsRet, sOut.constPtr(), var, nBufLen);
}

inline int acedGetCfg (const ACHAR *sym, ACHAR  *var, size_t len)
{
    AcString sOut;
    const int nAdsRet = ::acedGetCfg (sym, sOut);
    return ::acutCopyAdsResultStr(nAdsRet, sOut.constPtr(), var, len);
}

inline int acedGetCName(const ACHAR *cmd, ACHAR **result)
{
    // Duplicate some codes from adscodes.h
    const int acedADS_RTNORM = 5100;
    const int acedADS_RTERROR = -5001;
    if (result == nullptr)
        return acedADS_RTERROR;         // invalid input
    AcString sOut;
    const int nRet = ::acedGetCName(cmd, sOut);
    if (nRet == acedADS_RTNORM)
        acutNewString(sOut.constPtr(), *result);        // (old string is not freed)
    else
        *result = nullptr;
    return nRet;
}

inline int acedFindTrustedFile(const ACHAR *fname, ACHAR *result, size_t nBufLen)
{
    AcString sOut;
    const int nAdsRet = ::acedFindTrustedFile(fname, sOut);
    return ::acutCopyAdsResultStr(nAdsRet, sOut.constPtr(), result, nBufLen);
}

inline int acdbRToS (double val, int unit, int prec, ACHAR *str, size_t nBufLen)
{
    AcString sOut;
    const int nAdsRet = ::acdbRToS(val, sOut, unit, prec);
    return ::acutCopyAdsResultStr(nAdsRet, sOut.constPtr(), str, nBufLen);
}

inline int acdbAngToS (double v, int unit, int prec, ACHAR *str, size_t nBufLen)
{
    AcString sOut;
    const int nAdsRet = ::acdbAngToS (v, sOut, unit, prec);
    return ::acutCopyAdsResultStr(nAdsRet, sOut.constPtr(), str, nBufLen);
}

inline int acdbRawAngToS (double v, int unit, int prec, ACHAR *str, size_t nBufLen)
{
    AcString sOut;
    const int nAdsRet = ::acdbRawAngToS (v, sOut, unit, prec);
    return ::acutCopyAdsResultStr(nAdsRet, sOut.constPtr(), str, nBufLen);
}

// C++ templates that allow callers to omit the buffer length argument if they're
// passing in a fixed size character array
//
template<size_t nBufLen> inline int acedGetEnv(const wchar_t *pszName, wchar_t (& buf)[nBufLen])
{
    return ::acedGetEnv(pszName, buf, nBufLen);
}

template<size_t nBufLen> inline int acedGetInput(wchar_t (& buf)[nBufLen])
{
    return ::acedGetInput(buf, nBufLen);
}

template<size_t nBufLen> inline int acedGetString(int cronly, const wchar_t *prompt,
                                wchar_t (& buf)[nBufLen])
{
    return ::acedGetString(cronly, prompt, buf, nBufLen);
}

template<size_t nBufLen> inline int acedFindFile(const wchar_t *pszName, wchar_t (& buf)[nBufLen])
{
    return ::acedFindFile(pszName, buf, nBufLen);
}

template<size_t nBufLen> inline int acedFindTrustedFile(const wchar_t *pszName,
                                                        wchar_t (& buf)[nBufLen])
{
    return ::acedFindTrustedFile(pszName, buf, nBufLen);
}

template<size_t nBufLen> inline int acedGetKword(const wchar_t *pszPrompt, wchar_t (& buf)[nBufLen])
{
    return ::acedGetKword(pszPrompt, buf, nBufLen);
}

template<size_t nPreBufLen, size_t nNameBufLen, size_t nExtBufLen> inline int
        acedFNSplit(const wchar_t *pathToSplit,
                    wchar_t (& prebuf) [nPreBufLen],
                    wchar_t (& namebuf)[nNameBufLen],
                    wchar_t (& extbuf) [nExtBufLen])
{
    return ::acedFNSplit(pathToSplit, prebuf, nPreBufLen, namebuf, nNameBufLen,
                         extbuf, nExtBufLen);
}

// Template overloads to handle legacy callers who pass only ptr args and no sizes.
// NULL is usually defined as 0, so it will bind to the size_t args.
// If someone passes a different integer value by mistake, we'll forward it to the
// main acedFNSplit and it will return an error because a ptr arg is null and its
// corresponding size arg is not zero

// This first one is invoked by acedFNSplit(path, NULL, namebuf, NULL);
template<size_t nNameBufLen> inline int acedFNSplit(const wchar_t *pathToSplit,
                                size_t nPre,
                                wchar_t (& namebuf)[nNameBufLen],
                                size_t nExt)
{
    return ::acedFNSplit(pathToSplit, nullptr, nPre, namebuf, nNameBufLen, nullptr, nExt);
}

// Invoked by acedFNSplit(path, NULL, NULL, extbuf);
template<size_t nExtBufLen> inline int acedFNSplit(const wchar_t *pathToSplit,
                                size_t nPre,
                                size_t nName,
                                wchar_t (& extbuf)[nExtBufLen])
{
    return ::acedFNSplit(pathToSplit, nullptr, nPre, nullptr, nName, extbuf, nExtBufLen);
}

// Invoked by acedFNSplit(path, NULL, namebuf, extbuf);
template<size_t nNameBufLen, size_t nExtBufLen> inline int acedFNSplit(
                                const wchar_t *pathToSplit,
                                size_t nPre,
                                wchar_t (& namebuf)[nNameBufLen],
                                wchar_t (& extbuf)[nExtBufLen])
{
    return ::acedFNSplit(pathToSplit, nullptr, nPre, namebuf, nNameBufLen, extbuf, nExtBufLen);
}

// Invoked by acedFNSplit(path, prebuf, NULL, NULL);
template<size_t nPreBufLen> inline int acedFNSplit(const wchar_t *pathToSplit,
                                wchar_t (& prebuf)[nPreBufLen],
                                size_t nName,
                                size_t nExt)
{
    return ::acedFNSplit(pathToSplit, prebuf, nPreBufLen, nullptr, nName, nullptr, nExt);
}

template<size_t nBufLen> inline int acdbAngToS(double v, int unit, int prec,
                                               wchar_t (& buf)[nBufLen])
{
    return ::acdbAngToS(v, unit, prec, buf, nBufLen);
}

template<size_t nBufLen> inline int acdbRawAngToS(double v, int unit, int prec,
                                                  wchar_t (& buf)[nBufLen])
{
    return ::acdbRawAngToS(v, unit, prec, buf, nBufLen);
}

template<size_t nBufLen> inline int acdbRToS(double v, int unit, int prec,
                                             wchar_t (& buf)[nBufLen])
{
    return ::acdbRToS(v, unit, prec, buf, nBufLen);
}
// End of ifdef AcEdAds_Deprecated_ACHAR_Funcs
#endif

class AcEdCommandRejector
{
public:
    virtual bool reject(const ACHAR* globalCmdName, const ACHAR* localCmdName) = 0;
};

ACCORE_PORT void acedRegisterCommandRejector(AcEdCommandRejector* pRejector);
ACCORE_PORT void acedUnRegisterCommandRejector(AcEdCommandRejector* pRejector);

#endif  /* __cplusplus */

#pragma pack (pop)

#endif  /* !_acedads_h */
 
