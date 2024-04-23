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
// DESCRIPTION: Exported AcDbLongTransaction classes

#ifndef AD_DBLTRANS_H
#define AD_DBLTRANS_H 1

#include "dbmain.h"
#include "AdAChar.h"

#pragma pack (push, 8)

class AcString;

class AcDbLongTransWorkSetIterator : public AcRxObject
{
public:
    ~AcDbLongTransWorkSetIterator() {};
    ACRX_DECLARE_MEMBERS(AcDbLongTransWorkSetIterator);

    virtual void           start (bool incRemovedObjs = false,
                                  bool incSecondaryObjs = false) = 0; 

    virtual bool           done () = 0;
    virtual void           step () = 0;

    virtual AcDbObjectId   objectId () const = 0;

    virtual bool           curObjectIsErased () const = 0;
    virtual bool           curObjectIsRemoved () const = 0;
    virtual bool           curObjectIsPrimary () const = 0;

};

class AcDbLongTransaction : public AcDbObject
{
public:
    AcDbLongTransaction();
    ~AcDbLongTransaction();
    ACDB_DECLARE_MEMBERS(AcDbLongTransaction);

    enum { kSameDb      = 0,
           kXrefDb      = 1,
           kUnrelatedDb = 2  };

    int                  type () const;
    AcDbObjectId         originBlock() const;
    AcDbObjectId         destinationBlock() const;

    ACDBCORE2D_PORT Acad::ErrorStatus getLongTransactionName(AcString &) const;
#define AcDb_LongTrnsxn_Deprecated_ACHAR_Methods
#ifdef AcDb_LongTrnsxn_Deprecated_ACHAR_Methods
    // With this overload, caller is responsible for freeing the string. To be deprecated
    Acad::ErrorStatus    getLongTransactionName(ACHAR*&) const;
#endif

    Acad::ErrorStatus    addToWorkSet (AcDbObjectId id);
    Acad::ErrorStatus    removeFromWorkSet (AcDbObjectId id);
    Acad::ErrorStatus    syncWorkSet ();

    // The parameter includes both erased and removed objects
    //
    Acad::ErrorStatus    newWorkSetIterator(
                             AcDbLongTransWorkSetIterator*& pNewIter,
                             bool incRemovedObjs = false,
                             bool incSecondaryObjs = false) 
                                 const;

    AcDbObjectId         originObject(AcDbObjectId id) const;

    bool                 workSetHas(AcDbObjectId id, 
                                    bool bIncErased = false) const;

    AcDbIdMapping*       activeIdMap();

    void                 regenWorkSetWithDrawOrder();

    bool                 disallowDrawOrder();
};

#pragma pack (pop)

#ifdef AcDb_LongTrnsxn_Deprecated_ACHAR_Methods
    // With this overload, caller is responsible for freeing the string. To be deprecated
inline Acad::ErrorStatus AcDbLongTransaction::getLongTransactionName(ACHAR*&pName) const
{
    return ::acutGetAcStringConvertToAChar(this,
                    &AcDbLongTransaction::getLongTransactionName, pName);
}

#endif

#endif
