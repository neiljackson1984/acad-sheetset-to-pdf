//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2024 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "acbasedefs.h"
#include "rxobject.h"
#include "AdAChar.h"

#pragma pack (push, 8)

class AcRxMemberCollection;
class AcRxAttributeCollection;
class AcRxSet;
class AcRxImpClass;
class AcRxMemberCollectionBuilder;
typedef void (*AcRxMemberCollectionConstructorPtr)(AcRxMemberCollectionBuilder&, void*);

class AcRxClass: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxClass, ACBASE_PORT);

    ACBASE_PORT AcRxObject* addX(AcRxClass*, AcRxObject*);
    // Deprecated: The getX() method will be removed in a future
    // release.  Please use queryX() instead.
    ACBASE_PORT AcRxObject* getX(const AcRxClass*);
    ACBASE_PORT AcRxObject* delX(AcRxClass*);
    // Deprecated, use const version instead
    ACBASE_PORT AcRxObject* queryX(const AcRxClass*);
    /// <summary>
    ///This method searches for a protocol extension object associated with this object.
    /// </summary>
    ///
    /// <param name="protocolClass">
    /// Input pointer to AcRxClass object of the protocol extension class being searched for 
    /// </param>
    ACBASE_PORT AcRxObject* queryX(const AcRxClass*) const;

    ACBASE_PORT AcRxObject* create();
    ACBASE_PORT const ACHAR* appName() const;
    ACBASE_PORT const ACHAR* dxfName() const;
    ACBASE_PORT const ACHAR* name() const;
    ACBASE_PORT void        getClassVersion(int& dwgVer,
                            int& maintVer) const;
    ACBASE_PORT int         proxyFlags() const;

    bool isDerivedFrom(const AcRxClass*) const;

    /// <summary>
    /// Static method for checking if first (left) class arg is derived from second (right) one
    /// </summary>
    /// <param name="pDerived"> Ptr to class to test for derivation from pBase </param>
    /// <param name="pBase"> Ptr to class to test for being in pDerived's parenthood chain </param>
    /// <returns> True if both class pointers are non-null and pDerived is derived from
    ///           (i.e. in the sub-tree of children of) pBase.  Otherwise false. </returns>
    /// <remarks> Both classes should be already registered with the class system.
    ///           All RxClasses are in the derived from AcRxObject::desc()
    /// </remarks>
    ///
    static ACBASE_PORT bool isDerivedFrom(const AcRxClass *pDerived, const AcRxClass* pBase);

    ACBASE_PORT AcRxClass*     myParent() const;
    ACBASE_PORT AcRx::Ordering comparedTo(const AcRxObject*) const override;

    ACBASE_PORT AppNameChangeFuncPtr appNameCallbackPtr() const;

    ACBASE_PORT const AcRxSet* descendants() const;
    ACBASE_PORT AcRxMemberCollection* members() const;
    ACBASE_PORT const AcRxAttributeCollection& attributes() const;
    ACBASE_PORT AcRxAttributeCollection& attributes();
protected:
    AcRxClass(const ACHAR* name, const ACHAR* parent,
              AcRxMemberCollectionConstructorPtr memberConstruct, void* userData);
    ~AcRxClass();
private:
    // Private unimplemented overload of AcRxObject::isKindOf(), to cause compile errors
    // on incorrect usage such as this: pClass->isKindOf(pOtherClass).
    // What you really want to use is: pClass->isDerivedFrom(pOtherClass)
    //
    void isKindOf(void *);
    AcRxClass();        // default ctor for internal use only
    friend class AcRxImpClass;
    AcRxImpClass* m_pImp;
    AcRxClass(const AcRxClass &) = delete;      // no copying
    AcRxClass operator = (const AcRxClass &) = delete;

public:
    static void* operator new(size_t size);
    static void* operator new[](size_t size);
    static void operator delete(void* p);
    static void operator delete[](void* p);
};

ACBASE_PORT AcRxClass* newAcRxClass(
    const ACHAR* className,
    const ACHAR* parentClassName,
    int         proxyFlags = 0,
    AcRxObject* (*pseudoConstructor)() = NULL,
    const ACHAR* dxfName = NULL,
    const ACHAR* appName = NULL);

ACBASE_PORT AcRxClass* newAcRxClass(
    const ACHAR* className,
    const ACHAR* parentClassName,
    int         dwgVer,
    int         maintVer,
    int         proxyFlags = 0,
    AcRxObject* (*pseudoConstructor)() = NULL,
    const ACHAR* dxfName = NULL,
    const ACHAR* appName = NULL,
    AppNameChangeFuncPtr func = NULL);

ACBASE_PORT AcRxClass* newAcRxClass(
    const ACHAR* className,
    const ACHAR* parentClassName,
    int         dwgVer,
    int         maintVer,
    int         proxyFlags ,
    AcRxObject* (*pseudoConstructor)() ,
    const ACHAR* dxfName ,
    const ACHAR* appName ,
    AppNameChangeFuncPtr func,
    AcRxMemberCollectionConstructorPtr makeMembers,
    void* userData = NULL);

ACBASE_PORT void acrxBuildClassHierarchy();

// Destruction:  DELETE AcDbObject-derived CLASSES DURING APPLICATION UNLOAD ONLY !!!

ADESK_DEPRECATE_FOR_INTERNAL_USE ACBASE_PORT void deleteAcRxClass(AcRxClass* pClassObj);

template <class RXClass>
void deleteAcRxClass()
{
    ADESK_SUPPRESS_DEPRECATED
    deleteAcRxClass(RXClass::gpDesc);
    ADESK_SUPPRESS_DEPRECATED
    RXClass::gpDesc = nullptr;
}

inline bool AcRxClass::isDerivedFrom(const AcRxClass* pOtherClass) const
{
    return AcRxClass::isDerivedFrom(this, pOtherClass);
}

inline bool AcRxObject::isKindOf(const AcRxClass* pOtherClass) const
{
    return AcRxClass::isDerivedFrom(this->isA(), pOtherClass);
}

typedef void(*RxInitFuncPtr)();
#ifndef _DEBUG
AcRxClass* acrxQueueClassForInitialization(AcRxClass** pgpDesc, RxInitFuncPtr rxInit);
#else
AcRxClass* acrxQueueClassForInitialization(AcRxClass** pgpDesc, RxInitFuncPtr rxInit, const wchar_t* className);
#endif
#pragma pack (pop)

