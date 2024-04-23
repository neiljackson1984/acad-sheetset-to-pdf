//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2024 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#ifndef _rxdlinkr_h
#define _rxdlinkr_h 1

class AcRxDLinkerReactor;
class AcRxService;
class AcLocale;

#include "rxobject.h"
#include "AdAChar.h"
#include "AcDbCore2dDefs.h"     // ACDBCORE2D_PORT

#pragma pack (push, 8)

struct AcadApp
{
    enum LoadReasons {
        kOnProxyDetection       = 0x01,
        kOnAutoCADStartup       = 0x02,
        kOnCommandInvocation    = 0x04,
        kOnLoadRequest          = 0x08,
        kLoadDisabled           = 0x10,
        kTransparentlyLoadable  = 0x20,
        kOnIdleLoad             = 0x40,
        ///<summary>For Autodesk internal use.</summary>
        kAutodeskInternal1      = 0x80,
        ///<summary>Demand load based on AcDbRegAppTableRecord names.</summary>
        kOnRegAppDetection      = 0x100,
        ///<summary>Demand load based on names of Named Object Dictionary entries.</summary>
        kOnNodEntryDetection    = 0x200
    };

    enum ErrorStatus {
        eOk             = 0,
        eInvalidKey     = 1,
        eInvalidSubKey  = 2,
        eKeyNotFound    = 3,
        eOutOfMemory    = 4,
        eInvalidValue   = 5,
        eValueNotFound  = 6,
        eKeyExists      = 7,
        eRegAccessDenied= 8,
        eRejected       = 9,
        eUnknownError   = 10
    };
};





class ADESK_NO_VTABLE AcRxDynamicLinker: public AcRxObject
{
public:
    using EntryPointFunc = AcRx::AppRetCode(AcRx::AppMsgCode msg, void* pkt);
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxDynamicLinker, ACDBCORE2D_PORT);

    virtual void*          getSymbolAddress (const ACHAR * serviceName,
                                             const char * symbol) const = 0;
    // Overload it for convenience of callers that want to
    // put ACRX_T() around all literals.
    virtual void*          getSymbolAddress (const ACHAR * serviceName,
                                             const ACHAR * symbol) const = 0;

    virtual bool           initListedModules(const ACHAR * fileName) = 0;

    virtual bool           loadModule       (const ACHAR * fileName, 
                                             bool printit,
                                             bool asCmd=false) = 0;
    virtual bool           loadApp          (const ACHAR  * appName,
                                             AcadApp::LoadReasons al,
                                             bool printit,
                                             bool asCmd=false) = 0;

    virtual AcRxObject*    registerService  (const ACHAR * serviceName,
                                             AcRxService* serviceObj) = 0;

    virtual bool           unloadModule     (const ACHAR * fileName,
                                            bool asCmd=false) = 0;
    virtual bool           unloadApp        (const ACHAR * appName,
                                            bool asCmd=false) = 0;

    virtual void           addReactor       (AcRxDLinkerReactor* newReactor) =0;

    virtual void           removeReactor    (AcRxDLinkerReactor* oldReactor) =0;

    virtual bool           isApplicationLocked(const ACHAR * modulename) const =0;
    virtual bool           lockApplication  (void* appId) const = 0;
    virtual bool           unlockApplication(void* appId) const = 0;

    virtual bool           isAppMDIAware(const ACHAR * modulename) const =0;
    virtual bool           registerAppMDIAware(void* appId) const =0;
    virtual bool           registerAppNotMDIAware(void* appId) const =0;
 
    virtual bool           isAppBusy(const ACHAR * modulename) const =0;
    virtual void           setAppBusy(const ACHAR * modulename, bool bBusyFlag) const =0;

    /// <summary>
    /// This function returns product locale
    /// </summary>
    /// <returns>Return product locale.</returns>
    virtual AcLocale       ProductLocale() const =0;

    /// <summary>
    /// Registers an application for dynamic loading.
    /// </summary>
    /// <param name="entryPoint">Module name for application.  Internal use only. </param>
    /// <param name="entryPoint">Entrypoint function for application.  Internal use only. </param>
    /// <returns>
    /// AcadApp::eOk if success.
    /// AcadApp::eRejected if entry cannot be removed.
    /// AcadApp::eKeyNotFound if entry cannot be found.
    /// </returns>

    virtual AcadApp::ErrorStatus registerApp(AcadApp::LoadReasons alr, const ACHAR  *logicalName, const ACHAR* moduleName = nullptr, EntryPointFunc entryPoint = nullptr) = 0;
    virtual AcadApp::ErrorStatus unregisterApp(const ACHAR  *logicalName) = 0;
};


//  The kernel creates the one and only dynamic linker, at
//
#define acrxDynamicLinker                                               \
AcRxDynamicLinker::cast(acrxSysRegistry()->at(ACRX_DYNAMIC_LINKER))

class ADESK_NO_VTABLE AcRxDLinkerReactor: public AcRxObject
//
// Class defining notification events from the dynamic linker,
// specifically the loading and unloading of Arx applications.
//
// Recipients of these calls can and should also
// check the registered services, class and objects to find out
// what happened to logical elements of the system, rather
// than be bound to file name.
//
{
  public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxDLinkerReactor, ACDBCORE2D_PORT);
    ACDBCORE2D_PORT virtual ~AcRxDLinkerReactor();

    virtual void rxAppWillBeLoaded(const ACHAR  * /*moduleName*/) {}
    virtual void rxAppLoaded(const ACHAR  * /*moduleName*/) {}
    virtual void rxAppLoadAborted(const ACHAR  * /*moduleName*/) {}

    virtual void rxAppWillBeUnloaded(const ACHAR  * /*moduleName*/) {}
    virtual void rxAppUnloaded(const ACHAR  * /*moduleName*/) {}
    virtual void rxAppUnloadAborted(const ACHAR  * /*moduleName*/) {}
};


#pragma pack (pop)
#endif
