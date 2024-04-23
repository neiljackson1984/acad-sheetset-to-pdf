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
// dbmain.h
//
// DESCRIPTION: Main Exported Database Library Definitions

#ifndef AD_DBMAIN_H
#define AD_DBMAIN_H

#include <stddef.h>
#include "adesk.h"
#include "gepnt2d.h"
#include "gepnt3d.h"
#include "AcHeapOpers.h"
#include "rxobject.h"
#include "rxdlinkr.h"
#include "rxiter.h"
#include "rxditer.h"
#include "rxsrvice.h"
#include "dbboiler.h"   // ACDB_DECLARE_MEMBERS()
#include "dbptrar.h"
#include "dbcolor.h"
#include "dbidar.h"
#include "drawable.h"
#include "dbsecurity.h"
#include "AcString.h"
#include "dbObject.h"
#include "acutAcString.h"
#include "AcCmColor.h"

class AcCmEntityColor;
class AcDbBlockBegin;
class AcDbBlockEnd;
class AcDbDatabase;
class AcDbDatabaseIterator;
class AcDbDatabaseReactor;
class AcDbEntity;
class AcDbEntityReactor;
class AcDbImpDatabase;
class AcDbImpObject;
class AcDbObjectReactor;
class AcDbSpaceIterator;
class AcDbSystemInternals;
class AcDbXObject;
class AcDbBlockReference;
class AcDbSymbolTable;
class AcDbBlockTable;
class AcDbBlockTableRecord;    // (Used in AcDbExtents)
class AcDbLayerTable;
class AcDbTextStyleTable;
class AcDbLinetypeTable;
class AcDbAbstractViewTable;
class AcDbViewTable;
class AcDbUCSTable;
class AcDbViewportTable;
class AcDbRegAppTable;
class AcDbDimStyleTable;
class AcDbDimStyleTableRecord;
class AcDbIdMapping;
class AcDbDictionary;
class AcDbDictionaryWithDefault;
class AcDbMline;
class AcDbMlineStyle;
class AcDbCurve;
class AcDbEllipse;
class AcDbSpline;
class AcDbRegion;
class AcDb3dSolid;
class AcDbBody;
class AcDbDate;
class AcDbExtents;
class AcDbAuditInfo;
class AcDbUndoController;
class AcDbTransactionManager;
class AcDbSpatialFilter;
class AcDbLayerFilter;
class AcGeMatrix2d;
class AcGeVector3d;
class AcGsNode;
class AcGsModel;
class AcGiContext;
class AcDbObjectIdGraph;
class AcDbLayerStateManager;
class AcDwgFileHandle;
class AcDbTableStyle;
class AcFdFieldValue;
class AcDbField;
class AcDbSectionManager;
class AcDbDataLinkManager;
class AcGiMapper;
class AcDbAnnotationScale;
class IAcReadStream;
class IAcWriteStream;

enum class code_page_id : int;          // see codepgid.h

namespace Atil 
{
    class Image; // for Atil::Image
}

#include "acdb.h"
#include "dbhandle.h"
#include "dbfiler.h"
#include "ads_db.h"
#include "gept3dar.h"
#include "dbintar.h"
#include "dbsubeid.h"
#include "dbaudita.h"
#include "acgidefs.h"
#include "acarray.h"
#pragma pack(push, 8)

class AcLocale;

// For getClassID without pulling in wtypes.h
//
struct _GUID;
typedef struct _GUID CLSID;

class AcDbGripData;
typedef AcArray<AcDbGripData*, AcArrayMemCopyReallocator<AcDbGripData*> > AcDbGripDataPtrArray;
typedef AcArray<AcDbFullSubentPath,
        AcArrayObjectCopyReallocator<AcDbFullSubentPath> > AcDbFullSubentPathArray;

extern const AcDbFullSubentPath kNullSubent;

// Global Variables: API exports as functions.
//

// DXF Code --> Data Type mapping function
//
AcDb::DwgDataType acdbGroupCodeToType(AcDb::DxfCode pCode);
// If acdbGroupCodeToType(pField->restype) == kDwgText or kDwgBChunk, then free the string
// or buffer, and set the rstring or buf pointer to null.  Does not free the resbuf itself.
void              acdbFreeResBufContents(resbuf* pField);

// Returns null id if arg is not a persistent reactor
ACDBCORE2D_PORT AcDbObjectId  acdbPersistentReactorObjectId(const void *pSomething);
inline bool acdbIsPersistentReactor(const void *pSomething)
{
    return ! ::acdbPersistentReactorObjectId(pSomething).isNull();
}

ACDB_PORT bool   acdbDisplayPreviewFromDwg(const ACHAR *pszDwgfilename,
                                 void* pPreviewWnd,
                                 const Adesk::UInt32* pBgColor = nullptr);

bool acdbIsCustomObject(const AcDbObjectId& id);

//
// Special case overload for AcDbEntity type.
// Avoids the overhead of desc() and isKindOf()
//
ACDBCORE2D_PORT Acad::ErrorStatus acdbOpenObject(AcDbEntity *& pEnt,
                        AcDbObjectId id, AcDb::OpenMode mode = AcDb::kForRead, bool openErased = false);

// To be deprecated. Please use acdbOpenObject() instead
inline Acad::ErrorStatus
acdbOpenAcDbEntity(AcDbEntity*& pEnt, AcDbObjectId id, AcDb::OpenMode mode,
                   bool openErasedEntity = false)
{
    return ::acdbOpenObject(pEnt, id, mode, openErasedEntity);
}

Acad::ErrorStatus acdbResurrectMeNow(const AcDbObjectId& id);
 
// Translate between AcDbObjectName and ads_name, for use
// with ADS library functions.
//
Acad::ErrorStatus acdbGetAdsName(ads_name&  objName, AcDbObjectId objId);
Acad::ErrorStatus acdbGetObjectId(AcDbObjectId& objId,
                                         const ads_name objName);

Acad::ErrorStatus acdbValKey(const ads_name lname);

//  Mark an object as referenced, so it doesn't get automatically
//  purged after initial regen.
//
Acad::ErrorStatus acdbSetReferenced(AcDbObjectId objId);

/// <summary>
// Get the array of currently active Databases
/// </summary>
/// <returns> Reference to a const AcArray of AcDbDatabase pointers.</returns>
/// <remarks> Can be used to validate a db pointer, but for more reliable checking,
///           please see static AcDbDatabase::runtimeId() and isValidPtr() methods
/// </remarks>
///

ACDBCORE2D_PORT const AcArray<AcDbDatabase *> & acdbActiveDatabaseArray();

class AcDbViewTableRecord;
class AcDbViewport;
class AcDbObjectContextManager;

// Load an mline style file by name.
Acad::ErrorStatus acdbLoadMlineStyleFile(
                const ACHAR *sname, const ACHAR *fname);

// Load a linetype file by ltype name, and file name.  ltname may be wild.
Acad::ErrorStatus acdbLoadLineTypeFile(const ACHAR *ltname,
                                       const ACHAR *fname,
                                       AcDbDatabase *pDb);

//  Allocate memory from, and release it to, the AcDbObject
//  memory pool.  Any memory which will be freed by deleting an
//  AcDbObject should be allocated from this pool.   
//
void* acdbAlloc(size_t);
void* acdbRealloc(void *, size_t);
void  acdbFree(void*);

//Explicit init/term functions for AcDb.
//On Windows dynamic libraries have a 2 phase init that acdb has grown
//to rely on:
//1. Global constructors are called.
//2. DllMain is called.
//On the Mac there's no DllMain so clients must call these functions
//to properly init/term acdb. Most clients won't have to explicity call
//these functions because we implicity call acdbInitialize when 
//acdbSetHostApplicationServices and acdbValidateSetup are called.
//Multiple calls to these functions are OK. Calls after the first are
//ignored.
ACDB_PORT void acdbInitialize();
ACDB_PORT void acdbTerminate();

// ObjectDBX Host Apps must call this startup code after fulfilling
// all relevant contracts, eg registering a HostAppService object

/// <summary>
/// This call controls which language resources RealDWG will attempt to load and use.
/// </summary>
/// <param name="loc">input locale value</param>
/// <returns>Returns Acad::eOk if successful.</returns>
ACDBCORE2D_PORT Acad::ErrorStatus acdbValidateSetup(const AcLocale& loc);

// ObjectDBX Host Apps must call this shutdown code before exiting
//
Acad::ErrorStatus acdbCleanUp();

const ACHAR* acdbOriginalXrefFullPathFor(const AcDbDatabase*);

//  sets the default graphics context for an application.
//  return value is the previous default graphics context (may be nullptr).
AcGiContext * acdbSetDefaultAcGiContext(AcGiContext *);

//  DXF
Acad::ErrorStatus 
acdbGetThumbnailBitmapFromDxfFile(const ACHAR* filename, void*& pBitmap);

class AcDbDatabase: public AcRxObject, public AcHeapOperators
//
// A class whose instances represent an  entire DWG file,
// aka database itself.
//
{
public:
    ACRX_DECLARE_MEMBERS(AcDbDatabase);

    // constructor & destructor
    ACDBCORE2D_PORT AcDbDatabase(bool buildDefaultDrawing = true,
                 bool noDocument = false);
    ACDBCORE2D_PORT ~AcDbDatabase();

    /// <summary>Get the unique runtime identifier from this database instance.</summary>
    ACDBCORE2D_PORT int64_t runtimeId() const;

    /// <summary>Get the unique runtime identifier for the given database instance.</summary>
    /// <param name="pDb"> Input pointer to an AcDbDatabase  </param>
    /// <returns> Returns a runtime id which is > 0 on success.
    ///           Else returns an id <= 0 indicating invalid input db ptr.
    /// </returns>
    /// <remarks> Can be used to validate an AcDbDatabase pointer.
    ///           A db address may get re-used if the db is deleted and a new one is created
    ///           at the same location in memory, but they will have different runtime ids.
    /// </remarks>
    ///
    ACDBCORE2D_PORT static int64_t dbIdFromPtr(const AcDbDatabase *pDb);
                    static inline bool isValidPtr(const AcDbDatabase *pDb)
                    {
                        return dbIdFromPtr(pDb) > 0;
                    }

    /// <summary> Get the database pointer from a db runtime id </summary>
    /// <param name="nId"> Input runtime db id, should be > 0 </param>
    /// <returns> The address of the database referred to by the id, if valid.
    ///           Otherwise returns nullptr, indicating no such database
    /// </returns>
    /// <remarks> Useful when caching database references.
    ///           Db ids are only valid for the current process.
    /// </remarks>
    ///
    ACDBCORE2D_PORT static AcDbDatabase * dbPtrFromId(int64_t nId);

    /// <summary>
    /// Find out if this Database is in the process of being destroyed
    /// </summary>
    /// <returns> true if this Database's destructor has been called, false otherwise </returns>
    ///
    ACDBCORE2D_PORT bool isBeingDestroyed() const;

    /// <summary>
    /// Adds a currently non-resident AcDbObject to this database.
    /// </summary>
    /// <param name="id"> Receives the object's new id on success, else null </param>
    /// <param name="pObj"> Pointer to an object which is not yet database resident</param>
    /// <returns> eOk on success, otherwise an error code </returns>
    /// <remarks> Does not set the object's owner, and does not close the object
    ///           Fails with eWrongObjectType if *pObj derives from AcDbEntity
    /// </remarks>
    ///
    ACDBCORE2D_PORT Acad::ErrorStatus addAcDbObject(AcDbObjectId& id, AcDbObject* pObj);

    // For Autodesk internal use only
    ACDBCORE2D_PORT Acad::ErrorStatus addAcDbObject(AcDbObject* pObj);

    static Acad::ErrorStatus markObjectNonPersistent(AcDbObjectId id, bool value);
    static bool isObjectNonPersistent(AcDbObjectId id);
    // Symbol Tables

    Acad::ErrorStatus getBlockTable     (AcDbSymbolTable*& pTable,
                                         AcDb::OpenMode    mode = AcDb::kForRead);
    Acad::ErrorStatus getLayerTable     (AcDbSymbolTable*& pTable,
                                         AcDb::OpenMode    mode = AcDb::kForRead);
    Acad::ErrorStatus getTextStyleTable (AcDbSymbolTable*& pTable,
                                         AcDb::OpenMode    mode = AcDb::kForRead);
    Acad::ErrorStatus getLinetypeTable  (AcDbSymbolTable*& pTable,
                                         AcDb::OpenMode    mode = AcDb::kForRead);
    Acad::ErrorStatus getViewTable      (AcDbSymbolTable*& pTable,
                                         AcDb::OpenMode    mode = AcDb::kForRead);
    Acad::ErrorStatus getUCSTable       (AcDbSymbolTable*& pTable,
                                         AcDb::OpenMode    mode = AcDb::kForRead);
    Acad::ErrorStatus getViewportTable  (AcDbSymbolTable*& pTable,
                                         AcDb::OpenMode    mode = AcDb::kForRead);
    Acad::ErrorStatus getRegAppTable    (AcDbSymbolTable*& pTable,
                                         AcDb::OpenMode    mode = AcDb::kForRead);
    Acad::ErrorStatus getDimStyleTable  (AcDbSymbolTable*& pTable,
                                         AcDb::OpenMode    mode = AcDb::kForRead);

    ACDBCORE2D_PORT
    Acad::ErrorStatus getSymbolTable    (AcDbBlockTable*&     pTable,
                                         AcDb::OpenMode       mode = AcDb::kForRead);
    Acad::ErrorStatus getSymbolTable    (AcDbLayerTable*&     pTable,
                                         AcDb::OpenMode       mode = AcDb::kForRead);
    Acad::ErrorStatus getSymbolTable    (AcDbTextStyleTable*& pTable,
                                         AcDb::OpenMode       mode = AcDb::kForRead);
    Acad::ErrorStatus getSymbolTable    (AcDbLinetypeTable*&  pTable,
                                         AcDb::OpenMode       mode = AcDb::kForRead);
    Acad::ErrorStatus getSymbolTable    (AcDbViewTable*&      pTable,
                                         AcDb::OpenMode       mode = AcDb::kForRead);
    Acad::ErrorStatus getSymbolTable    (AcDbUCSTable*&       pTable,
                                         AcDb::OpenMode       mode = AcDb::kForRead);
    Acad::ErrorStatus getSymbolTable    (AcDbViewportTable*&  pTable,
                                         AcDb::OpenMode       mode = AcDb::kForRead);
    Acad::ErrorStatus getSymbolTable    (AcDbRegAppTable*&    pTable,
                                         AcDb::OpenMode       mode = AcDb::kForRead);
    Acad::ErrorStatus getSymbolTable    (AcDbDimStyleTable*&  pTable,
                                         AcDb::OpenMode       mode = AcDb::kForRead);

    Acad::ErrorStatus getGroupDictionary   (AcDbDictionary*& pDict,
                                            AcDb::OpenMode mode = AcDb::kForRead);
    Acad::ErrorStatus getMLStyleDictionary (AcDbDictionary*& pDict,
                                            AcDb::OpenMode mode = AcDb::kForRead);
    Acad::ErrorStatus getLayoutDictionary  (AcDbDictionary*& pDict,
                                            AcDb::OpenMode mode = AcDb::kForRead);
    Acad::ErrorStatus getPlotStyleNameDictionary(
                                            AcDbDictionaryWithDefault*& pDict,
                                            AcDb::OpenMode mode = AcDb::kForRead);
    Acad::ErrorStatus getMaterialDictionary(AcDbDictionary*& pDict,
                                            AcDb::OpenMode mode = AcDb::kForRead);
    Acad::ErrorStatus getVisualStyleDictionary(AcDbDictionary*& pDict,
                                            AcDb::OpenMode mode = AcDb::kForRead);
    Acad::ErrorStatus getColorDictionary   (AcDbDictionary*& pDict,
                                            AcDb::OpenMode mode = AcDb::kForRead);
    Acad::ErrorStatus getScaleListDictionary(AcDbDictionary*& pDict,
                                             AcDb::OpenMode mode = AcDb::kForRead);
    Acad::ErrorStatus getNamedObjectsDictionary(
                                            AcDbDictionary*& pDict,
                                            AcDb::OpenMode mode = AcDb::kForRead);

    Acad::ErrorStatus getBlockTable     (AcDbBlockTable*& pTable,
                                         AcDb::OpenMode    mode = AcDb::kForRead);
    Acad::ErrorStatus getLayerTable     (AcDbLayerTable*& pTable,
                                         AcDb::OpenMode    mode = AcDb::kForRead);
    Acad::ErrorStatus getTextStyleTable (AcDbTextStyleTable*& pTable,
                                         AcDb::OpenMode    mode = AcDb::kForRead);
    Acad::ErrorStatus getLinetypeTable  (AcDbLinetypeTable*& pTable,
                                         AcDb::OpenMode    mode = AcDb::kForRead);
    Acad::ErrorStatus getViewTable      (AcDbViewTable*& pTable,
                                         AcDb::OpenMode    mode = AcDb::kForRead);
    Acad::ErrorStatus getUCSTable       (AcDbUCSTable*& pTable,
                                         AcDb::OpenMode    mode = AcDb::kForRead);
    Acad::ErrorStatus getViewportTable  (AcDbViewportTable*& pTable,
                                         AcDb::OpenMode    mode = AcDb::kForRead);
    Acad::ErrorStatus getRegAppTable    (AcDbRegAppTable*& pTable,
                                         AcDb::OpenMode    mode = AcDb::kForRead);
    Acad::ErrorStatus getDimStyleTable  (AcDbDimStyleTable*& pTable,
                                         AcDb::OpenMode    mode = AcDb::kForRead);
    Acad::ErrorStatus getPlotSettingsDictionary(AcDbDictionary*& pTable,
                                         AcDb::OpenMode    mode = AcDb::kForRead);
    AcDbObjectId      getSectionManager (void) const;
    Acad::ErrorStatus getSectionManager (AcDbSectionManager*& pMgr, 
                                         AcDb::OpenMode mode = AcDb::kForRead) const;
    AcDbObjectId    dataLinkDictionaryId(void) const;
    Acad::ErrorStatus getDataLinkDictionary(AcDbDictionary*& pDict, 
                                            AcDb::OpenMode mode = AcDb::kForRead);
    AcDbDataLinkManager*getDataLinkManager(void) const;
    Acad::ErrorStatus updateDataLink    (AcDb::UpdateDirection nDir, 
                                         AcDb::UpdateOption nOption);

    ACDBCORE2D_PORT AcDbObjectId  blockTableId() const;
    ACDBCORE2D_PORT AcDbObjectId  layerTableId() const;
    ACDBCORE2D_PORT AcDbObjectId  textStyleTableId() const;
    ACDBCORE2D_PORT AcDbObjectId  linetypeTableId() const;
    ACDBCORE2D_PORT AcDbObjectId  viewTableId() const;
    ACDBCORE2D_PORT AcDbObjectId  UCSTableId() const;
    ACDBCORE2D_PORT AcDbObjectId  viewportTableId() const;
    ACDBCORE2D_PORT AcDbObjectId  regAppTableId() const;
    ACDBCORE2D_PORT AcDbObjectId  dimStyleTableId() const;
    ACDBCORE2D_PORT AcDbObjectId  mLStyleDictionaryId() const;
    ACDBCORE2D_PORT AcDbObjectId  groupDictionaryId() const;
    ACDBCORE2D_PORT AcDbObjectId  layoutDictionaryId() const;
    ACDBCORE2D_PORT AcDbObjectId  plotStyleNameDictionaryId() const;
    ACDBCORE2D_PORT AcDbObjectId  materialDictionaryId() const;
    ACDBCORE2D_PORT AcDbObjectId  visualStyleDictionaryId() const;
    ACDBCORE2D_PORT AcDbObjectId  colorDictionaryId() const;
    ACDBCORE2D_PORT AcDbObjectId  scaleListDictionaryId() const;
    ACDBCORE2D_PORT AcDbObjectId  namedObjectsDictionaryId() const;
    ACDBCORE2D_PORT AcDbObjectId  plotSettingsDictionaryId() const;

    // Template helper method for getting symtab ids
    template <class TableType> AcDbObjectId getSymbolTableId() const;

    AcDbObjectId layerZero() const;
    AcDbObjectId continuousLinetype() const;
    AcDbObjectId byLayerLinetype() const;
    AcDbObjectId byBlockLinetype() const;

    AcDbObjectId globalMaterial() const;
    AcDbObjectId byLayerMaterial() const;
    AcDbObjectId byBlockMaterial() const;

    AcDbObjectId paperSpaceVportId() const;
    AcDbObjectId currentSpaceId() const;

    Acad::ErrorStatus reclaimMemoryFromErasedObjects(const AcDbObjectIdArray& erasedObjects);

    // Traverse the db and remove non-purgeable ids from the array
    Acad::ErrorStatus purge(AcDbObjectIdArray& ids);
    Acad::ErrorStatus purge(AcDbObjectIdGraph& idGraph);
    Acad::ErrorStatus countHardReferences(const AcDbObjectIdArray& ids,
                                          Adesk::UInt32* pCount);

    // Exchange (handle, xrefId) or name for AcDbObjectId 
    //
    ACDBCORE2D_PORT
    Acad::ErrorStatus getAcDbObjectId(AcDbObjectId& retId,
                                      bool createIfNotFound,
                                      const AcDbHandle& objHandle,
                                      Adesk::UInt32 xRefId = 0);
    // Class Dxf Name for this database.
    //
    const ACHAR* classDxfName(const AcRxClass* pClass);

    bool hasClass(const AcRxClass* pClass) const;

    // Filing Operations
    //
    enum OpenMode {
        kForReadAndReadShare =    1,    // Read Access. Allow other readers but not
                                        // other writers. (_SH_DENYWR)
        kForReadAndWriteNoShare = 2,    // Read+Write Access. Disallow other readers and
                                        // other writers. (_SH_DENYRW)
        kForReadAndAllShare =     3,    // Read Access. Allow other readers and writers.
                                        // Closes dwg file after open. (_SH_DENYNO)
                                        // Internally calls closeInput(true)
        kTryForReadShare =        4     // 2-step: first try kForReadAndReadShare, and
                                        // if that fails, then try kForReadAndAllShare 
    };

    // Note that the old overload of this method which took an int _SH_DENYxxx
    // arg is removed. You have to call this method using the OpenMode arg
    // to specify the access and sharing. See above OpenMode comments for
    // the mapping from _SH_DENYxxx to kXXXShare enum vals.
    ACDBCORE2D_PORT Acad::ErrorStatus readDwgFile(const ACHAR* fileName,
                                  OpenMode shmode = kForReadAndReadShare,
                                  bool bAllowCPConversion = false,
                                  const wchar_t* wszPassword = nullptr);

    // Currently for internal use only
    ACDBCORE2D_PORT Acad::ErrorStatus readDwgFile(AcDwgFileHandle *pDwgFile,
                                  bool bAllowCPConversion = false,
                                  const wchar_t* wszPassword = nullptr);

    /// <summary>
    /// Returns true if this database was read in from a dwg file on disk
    /// and there were read errors, but they were not significant enough to
    /// cause readDwgFile() to return an error.
    /// NOTE: closeInput() should be called before using this function to
    ///       be sure that all objects in the drawing have been read in.
    /// </summary>
    //
    ACDBCORE2D_PORT bool needsRecovery() const;

    ACDBCORE2D_PORT void setFullSaveRequired();

    inline Acad::ErrorStatus saveAs(const ACHAR* fileName,
                             const SecurityParams* pSecParams = 0)
    {
        return saveAs(fileName, true, AcDb::kDHL_CURRENT, pSecParams);
    }

    ACDBCORE2D_PORT Acad::ErrorStatus saveAs(const ACHAR* fileName,
                             const bool bBakAndRename,
                             const AcDb::AcDbDwgVersion dwgVer = AcDb::kDHL_CURRENT,
                             const SecurityParams* pSecParams = 0);
    ACDBCORE2D_PORT Acad::ErrorStatus saveAs(AcDwgFileHandle * pOutputFiler,
                             const SecurityParams* pSecParams = 0,
                             bool crashing = false);
    Acad::ErrorStatus save();
    Acad::ErrorStatus dxfIn(const ACHAR* dxfFilename,
                            const ACHAR* logFilename=nullptr);
    Acad::ErrorStatus dxfIn(IAcReadStream* pInputStream,
                            const ACHAR* logFilename=nullptr);

    ACDBCORE2D_PORT
    Acad::ErrorStatus dxfOut(const ACHAR* fileName,
                             int precision = 16,
                             AcDb::AcDbDwgVersion dwgVer = AcDb::kDHL_CURRENT,
                             bool saveThumbnailImage = false);

    /// <summary>
    /// Saves this drawing to a dxf file, allowing caller to specify a code page.
    /// </summary>
    /// <param name="fileName"> Name of the dxf file to save to. </param>
    /// <param name="precision"> Number of bits of accuracy. </param>
    /// <param name="dwgVer"> Dxf format version to create, R12 through current. </param>
    /// <param name="nFlags"> Flag bits. Currently only bit value 0x01 is used, for
    ///             enabling thumbnail preview in the dxf file </param>
    /// <param name="nCodePage"> Code page to use for pre-2007 dxf formats </param>
    /// <returns> Acad::eOk if dxf file is successfully created, else an error status </returns>
    /// <remarks> Dxf files format versions >= 2007 use utf-8 char encoding.
    ///           Older file format versions < 2007 use ansi code page char encoding.
    ///           See codepgid.h for code_page_id value constants.</remarks>
    ///
    ACDBCORE2D_PORT
    Acad::ErrorStatus dxfOutEx(const ACHAR* fileName,
                               int precision = 16,
                               AcDb::AcDbDwgVersion dwgVer = AcDb::kDHL_CURRENT,
                               int nFlags = 0,
                               code_page_id nCodePage = static_cast<code_page_id>(0));

    /// <summary>
    /// If a drawing file is associated with this AcDbDatabase, then this function forces
    /// an immediate read of all necessary information from the file into the AcDbDatabase
    /// object and disconnects the file from the AcDbDatabase.
    /// 
    /// If bCloseFile is true, the drawing file will be closed when it has been fully
    /// read into, and disconnected from, the AcDbDatabase.  If bCloseFile is false,
    /// then the drawing file will still be disconnected from the AcDbDatabase, but
    /// the drawing file will remain open until the host application session ends.
    /// Passing true for this argument is recommended.
    /// 
    /// This function will only execute once per AcDbDatabase, so multiple calls will
    /// have no effect after the first call.
    /// 
    /// WARNING:  This function should only be called on AcDbDatabases that your
    ///           application has created and read in from a dwg file using
    ///           AcDbDatabase::readDwgFile().
    ///
    /// This method is mainly for internal use and does not normally need to be called.
    /// AcDbObjects are automatically brought into memory as needed by acdbOpenObject() etc.
    ///
    /// </summary>
    /// <param name="bCloseFile">Input bool indicating whether to close the drawing file</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus closeInput(bool bCloseFile);

    int approxNumObjects() const;
    Adesk::Int32 numberOfSaves() const;
    const ACHAR * originalFileName() const;
    AcDb::AcDbDwgVersion lastSavedAsVersion() const;
    AcDb::AcDbDwgVersion originalFileVersion() const;
    AcDb::AcDbDwgVersion originalFileSavedByVersion() const;
    AcDb::MaintenanceReleaseVersion lastSavedAsMaintenanceVersion() const;
    AcDb::MaintenanceReleaseVersion originalFileMaintenanceVersion() const;
    AcDb::MaintenanceReleaseVersion originalFileSavedByMaintenanceVersion() const;

    AcDwgFileHandle * inputFiler() const;
#ifdef _ADESK_MAC_
    AcDwgFileHandle * outputFiler() const;
#endif

    Acad::ErrorStatus wblock(AcDbDatabase*& pOutputDb,
                             const AcDbObjectIdArray& outObjIds,
                             const AcGePoint3d& basePoint);

    Acad::ErrorStatus wblock(AcDbDatabase* pOutputDb,  // pre-existing (template) db
                             const AcDbObjectIdArray& outObjIds,
                             const AcGePoint3d& basePoint,
                             AcDb::DuplicateRecordCloning drc);  // kDrcIgnore

    Acad::ErrorStatus wblock(AcDbDatabase*& pOutputDb, AcDbObjectId blockId);
    Acad::ErrorStatus wblock(AcDbDatabase*& pOutputDb);

    // This will force the current WBLOCK* operation to result in
    // a database copy.  Only use this method if your application
    // does some special handling during WBLOCK* notifications and
    // you can only do that correctly if the WBLOCK* results in a
    // database copy.  Needless to say, a database copy will slow
    // down WBLOCK* and increase memory requirements.
    //
    void              forceWblockDatabaseCopy();

    // If preserveSourceDatabase is true, the contents of pDb will not
    // be changed.  If it is false, objects from pDb could be physically
    // moved into the database on which insert() is called.  The latter
    // is much faster.  But pDb will be left in a state where it depends
    // on "this" database (the one on which insert() was called) for vital
    // data.  So pDb should be deleted before "this" database is deleted.
    //
    Acad::ErrorStatus insert(AcDbObjectId& blockId, const ACHAR* pBlockName,
        AcDbDatabase* pDb,
        bool preserveSourceDatabase = true);

    Acad::ErrorStatus insert(const AcGeMatrix3d& xform, AcDbDatabase* pDb,
        bool preserveSourceDatabase = true);

    Acad::ErrorStatus insert(AcDbObjectId& blockId, 
        const ACHAR* pSourceBlockName,
        const ACHAR* pDestinationBlockName,
        AcDbDatabase* pDb,
        bool preserveSourceDatabase = true);

    ACDBCORE2D_PORT Acad::ErrorStatus deepCloneObjects(const AcDbObjectIdArray& objectIds,
        const AcDbObjectId& owner, AcDbIdMapping& idMap,
        bool deferXlation = false);
       
    ACDBCORE2D_PORT Acad::ErrorStatus wblockCloneObjects(const AcDbObjectIdArray& objectIds,
        const AcDbObjectId& owner, AcDbIdMapping& idMap,
        AcDb::DuplicateRecordCloning drc,
        bool deferXlation = false);

    void              abortDeepClone(AcDbIdMapping& idMap);

    // Can return eInvalidInput, eObjectToBeDeleted, eDuplicateKey or eOk
    ACDBCORE2D_PORT Acad::ErrorStatus addReactor(AcDbDatabaseReactor* pReactor) const;

    // Can return eInvalidInput, eKeyNotFound or eOk
    ACDBCORE2D_PORT Acad::ErrorStatus removeReactor(AcDbDatabaseReactor* pReactor) const;

    /// <summary> Register an app name (for use by xdata) </summary>
    /// <param name="pszAppName"> The app name to register </param>
    /// <returns> eOk if app name is successfully registered in this database,
    ///           otherwise an error code </returns>
    /// <remarks> Rejects names with vertical bars and other invalid chars.
    ///           Returns eOk if the name is already registered </remarks>
    ///
    ACDBCORE2D_PORT Acad::ErrorStatus registerApp(const wchar_t *pszAppName);

    /// <summary> Check for a registered app name </summary>
    /// <param name="pszAppName"> The name to check for </param>
    /// <returns> True if the app name is registered in this database, else false </returns>
    ///
    ACDBCORE2D_PORT bool isAppRegistered(const wchar_t *pszAppName) const;

    Acad::ErrorStatus auditXData(AcDbAuditInfo* pInfo);

    AcDbUndoController* undoController() const;
    void              disableUndoRecording(bool disable);
    bool              undoRecording() const ;

    AcDbTransactionManager* transactionManager() const;

    AcDb::MaintenanceReleaseVersion maintenanceReleaseVersion() const
    {
        return AcDb::kMReleaseCurrent;
    }

    Acad::ErrorStatus restoreOriginalXrefSymbols();
    Acad::ErrorStatus restoreForwardingXrefSymbols();

    AcDbObjectId      xrefBlockId() const;

    // Access to ThumbnailImage (preview)
    // These functions take a windows BITMAPINFO*
    //
    /// <summary>
    /// This function provides BITMAP thumbnail of database as return value
    /// </summary>
    /// <returns> This will return BITMAP thumbnail in void* buffer for database </returns>
    ///
    void*             thumbnailBitmap() const;

    /// <summary>
    /// This function sets BITMAP thumbnail into database
    /// </summary>
    /// <param name="pBmp"> A pointer of Bitmap thumbnail to be set into database </param>
    /// <returns> This will return Acad::eOk if thumbnail is successfully set. It returns error status otherwise </returns>
    ///
    Acad::ErrorStatus setThumbnailBitmap(void* pBmp);

    /// <summary>
    /// This function provides Atil::Image thumbnail of database as output
    /// </summary>
    /// <param name="pPreviewImage"> A reference to the pointer of Atil::Image thumbnail </param>
    /// <returns> This will return Acad::eOk if thumbnail is successfully retrieved. It returns error status otherwise </returns>
    /// <remarks> Internal use only </remarks>
    ///
    Acad::ErrorStatus thumbnailImage(Atil::Image*& pPreviewImage) const;

    /// <summary>
    /// This functions sets Atil::Image thumbnail into database
    /// </summary>
    /// <param name="pPreviewImage"> A pointer of Atil::Image thumbnail to be set into database </param>
    /// <returns> This will return Acad::eOk if thumbnail is successfully set. It returns error status otherwise </returns>
    /// <remarks> Internal use only </remarks>
    ///
    Acad::ErrorStatus setThumbnailImage(const Atil::Image *pPreviewImage);

    bool              retainOriginalThumbnailBitmap() const;
    void              setRetainOriginalThumbnailBitmap(bool retain);

    // methods to set and retrieve security-related information
    bool                  setSecurityParams(const SecurityParams* pSecParams,
                                            bool bSetDbMod = true);
    const SecurityParams* cloneSecurityParams();
    static void           disposeSecurityParams(const SecurityParams* pSecParams);

    // Header variables exposed via DXF and/or SETVAR
    //
    bool dimaso() const;
    Acad::ErrorStatus setDimaso(bool aso);

    bool dimsho() const;
    Acad::ErrorStatus setDimsho(bool sho);

    bool plinegen() const;
    Acad::ErrorStatus setPlinegen(bool gen);

    bool orthomode() const;
    Acad::ErrorStatus setOrthomode(bool mode);

    bool regenmode() const;
    Acad::ErrorStatus setRegenmode(bool mode);

    bool fillmode() const;
    Acad::ErrorStatus setFillmode(bool mode);

    bool qtextmode() const;
    Acad::ErrorStatus setQtextmode(bool mode);

    bool psltscale() const;
    Acad::ErrorStatus setPsltscale(bool scale);

    bool limcheck() const;
    Acad::ErrorStatus setLimcheck(bool check);

    bool blipmode() const;
    Acad::ErrorStatus setBlipmode(bool mode);

    Adesk::Int16 saveproxygraphics() const;
    Acad::ErrorStatus setSaveproxygraphics(Adesk::Int16 saveimg);

    Adesk::Int16 delUsedObj() const;
    Acad::ErrorStatus setDelUsedObj(Adesk::Int16 deleteObj);

    ACDBCORE2D_PORT
    bool dispSilh() const;
    Acad::ErrorStatus setDispSilh(bool silh);

    bool plineEllipse() const;
    Acad::ErrorStatus setPlineEllipse(bool pline);

    bool usrtimer() const;
    Acad::ErrorStatus setUsrtimer(bool timer);

    bool skpoly() const;
    Acad::ErrorStatus setSkpoly(bool asPoly);

    bool angdir() const;
    Acad::ErrorStatus setAngdir(bool dir);

    ACDBCORE2D_PORT
    bool splframe() const;
    Acad::ErrorStatus setSplframe(bool disp);

    Adesk::UInt8 xclipFrame() const;
    Acad::ErrorStatus setXclipFrame(Adesk::UInt8 disp);

    bool attreq() const;
    Acad::ErrorStatus setAttreq(bool req);

    bool attdia() const;
    Acad::ErrorStatus setAttdia(bool dia);

    bool mirrtext() const;
    Acad::ErrorStatus setMirrtext(bool mirror);

    bool worldview() const;
    Acad::ErrorStatus setWorldview(bool view);

    ACDBCORE2D_PORT
    bool tilemode() const;
    Acad::ErrorStatus setTilemode(bool mode);

    bool plimcheck() const;
    Acad::ErrorStatus setPlimcheck(bool check);

    bool visretain() const;
    Acad::ErrorStatus setVisretain(bool retain);

    Adesk::Int16 dragmode() const;
    Acad::ErrorStatus setDragmode(Adesk::Int16 mode);

    Adesk::Int16 treedepth() const;
    Acad::ErrorStatus setTreedepth(Adesk::Int16 depth);

    Adesk::Int16 lunits() const;
    Acad::ErrorStatus setLunits(Adesk::Int16 lunits);

    Adesk::Int16 luprec() const;
    Acad::ErrorStatus setLuprec(Adesk::Int16 prec);

    Adesk::Int16 aunits() const;
    Acad::ErrorStatus setAunits(Adesk::Int16 aunits);

    Adesk::Int16 auprec() const;
    Acad::ErrorStatus setAuprec(Adesk::Int16 auprec);

    Adesk::Int16 attmode() const;
    Acad::ErrorStatus setAttmode(Adesk::Int16 mode);

    Adesk::Int16 coords() const;
    Acad::ErrorStatus setCoords(Adesk::Int16 coords);

    Adesk::Int16 pdmode() const;
    Acad::ErrorStatus setPdmode(Adesk::Int16 mode);

    Adesk::Int16 pickstyle() const;
    Acad::ErrorStatus setPickstyle(Adesk::Int16 style);

    Adesk::Int16 useri1() const;
    Acad::ErrorStatus setUseri1(Adesk::Int16 val);

    Adesk::Int16 useri2() const;
    Acad::ErrorStatus setUseri2(Adesk::Int16 val);

    Adesk::Int16 useri3() const;
    Acad::ErrorStatus setUseri3(Adesk::Int16 val);

    Adesk::Int16 useri4() const;
    Acad::ErrorStatus setUseri4(Adesk::Int16 val);

    Adesk::Int16 useri5() const;
    Acad::ErrorStatus setUseri5(Adesk::Int16 val);

    Adesk::Int16 splinesegs() const;
    Acad::ErrorStatus setSplinesegs(Adesk::Int16 segs);

    Adesk::Int16 surfu() const;
    Acad::ErrorStatus setSurfu(Adesk::Int16 u);

    Adesk::Int16 surfv() const;
    Acad::ErrorStatus setSurfv(Adesk::Int16 v);

    Adesk::Int16 surftype() const;
    Acad::ErrorStatus setSurftype(Adesk::Int16 type);

    Adesk::Int16 surftab1() const;
    Acad::ErrorStatus setSurftab1(Adesk::Int16 tab1);

    Adesk::Int16 surftab2() const;
    Acad::ErrorStatus setSurftab2(Adesk::Int16 tab2);

    Adesk::Int16 splinetype() const;
    Acad::ErrorStatus setSplinetype(Adesk::Int16 type);

    Adesk::Int16 shadedge() const;
    Acad::ErrorStatus setShadedge(Adesk::Int16 mode);

    Adesk::Int16 shadedif() const;
    Acad::ErrorStatus setShadedif(Adesk::Int16 dif);

    AcDb::MeasurementValue measurement() const;
    Acad::ErrorStatus setMeasurement(AcDb::MeasurementValue type);

    Adesk::Int16 unitmode() const;
    Acad::ErrorStatus setUnitmode(Adesk::Int16 mode);

    Adesk::Int16 maxactvp() const;
    Acad::ErrorStatus setMaxactvp(Adesk::Int16 max);

    ACDBCORE2D_PORT
    Adesk::Int16 isolines() const;
    Acad::ErrorStatus setIsolines(Adesk::Int16 isolines);
    
    Adesk::UInt8 dwfframe() const;
    Acad::ErrorStatus setDwfframe(Adesk::UInt8);
    
    Adesk::UInt8 dgnframe() const;
    Acad::ErrorStatus setDgnframe(Adesk::UInt8);
    
    Adesk::Int8 pdfframe() const;
    Acad::ErrorStatus setPdfframe(Adesk::Int8 val);

    double ltscale() const;
    Acad::ErrorStatus setLtscale(double scale);

    double textsize() const;
    Acad::ErrorStatus setTextsize(double size);

    double tracewid() const;
    Acad::ErrorStatus setTracewid(double width);

    double sketchinc() const;
    Acad::ErrorStatus setSketchinc(double inc);

    double filletrad() const;
    Acad::ErrorStatus setFilletrad(double radius);

    double thickness() const;
    Acad::ErrorStatus setThickness(double thickness);

    AcDb::LineWeight  celweight() const;
    Acad::ErrorStatus setCelweight(AcDb::LineWeight weight);

    static bool       isValidLineWeight(int weight);
    static AcDb::LineWeight getNearestLineWeight(int weight);

    AcDb::EndCaps endCaps() const;
    Acad::ErrorStatus setEndCaps(AcDb::EndCaps type);

    AcDb::JoinStyle joinStyle() const;
    Acad::ErrorStatus setJoinStyle(AcDb::JoinStyle style);

    bool lineWeightDisplay() const;
    Acad::ErrorStatus setLineWeightDisplay(bool display);

    bool xrefEditEnabled() const;
    Acad::ErrorStatus setXrefEditEnabled(bool enable);

    bool oleStartUp() const;
    Acad::ErrorStatus setOleStartUp(bool val);

    double angbase() const;
    Acad::ErrorStatus setAngbase(double angle);

    double pdsize() const;
    Acad::ErrorStatus setPdsize(double size);

    double plinewid() const;
    Acad::ErrorStatus setPlinewid(double width);

    double userr1() const;
    Acad::ErrorStatus setUserr1(double val);

    double userr2() const;
    Acad::ErrorStatus setUserr2(double val);

    double userr3() const;
    Acad::ErrorStatus setUserr3(double val);

    double userr4() const;
    Acad::ErrorStatus setUserr4(double val);

    double userr5() const;
    Acad::ErrorStatus setUserr5(double val);

    double chamfera() const;
    Acad::ErrorStatus setChamfera(double val);

    double chamferb() const;
    Acad::ErrorStatus setChamferb(double val);

    double chamferc() const;
    Acad::ErrorStatus setChamferc(double val);

    double chamferd() const;
    Acad::ErrorStatus setChamferd(double val);

    ACDBCORE2D_PORT
    double facetres() const;
    ACDBCORE2D_PORT
    Acad::ErrorStatus setFacetres(double facetres);

    // 3DDWF
    double get3dDwfPrec() const;
    Acad::ErrorStatus set3dDwfPrec(double DwfPrec);

    ACDBCORE2D_PORT Acad::ErrorStatus getMenu(AcString & sMenuName) const;
#define AcDbDatabase_Deprecated_ACHAR_Methods
#ifdef AcDbDatabase_Deprecated_ACHAR_Methods
    Acad::ErrorStatus getMenu(ACHAR*& pOutput) const;   // deprecated
#endif

    bool hpInherit() const;
    Acad::ErrorStatus setHpInherit(const bool inherit);

    AcGePoint2d hpOrigin() const;
    Acad::ErrorStatus setHpOrigin(const AcGePoint2d& origin);

    const AcDbDate tdcreate() const;     // returns a local time
    const AcDbDate tdupdate() const;

    const AcDbDate tducreate() const;    // returns a universal time
    const AcDbDate tduupdate() const;

    const AcDbDate tdindwg() const;      // returns a time delta
    const AcDbDate tdusrtimer() const;

    Acad::ErrorStatus resetTimes();

    AcCmColor cecolor() const;
    Acad::ErrorStatus setCecolor(const AcCmColor& color);

    AcCmTransparency cetransparency() const;
    Acad::ErrorStatus setCetransparency(const AcCmTransparency& transparency);

    AcDbHandle handseed() const;
    Acad::ErrorStatus setHandseed(const AcDbHandle& handle);

    AcDbObjectId clayer() const;
    ACDBCORE2D_PORT
    Acad::ErrorStatus setClayer(AcDbObjectId objId);

    AcDb::PlotStyleNameType getCePlotStyleNameId(AcDbObjectId& id) const;
    Acad::ErrorStatus       setCePlotStyleName(AcDb::PlotStyleNameType,
                            AcDbObjectId newId = AcDbObjectId::kNull);
    
    AcDbObjectId textstyle() const;
    Acad::ErrorStatus setTextstyle(AcDbObjectId objId);

    AcDbObjectId celtype() const;
    Acad::ErrorStatus setCeltype(AcDbObjectId objId);

    AcDbObjectId cmaterial() const;
    Acad::ErrorStatus setCmaterial(AcDbObjectId objId);

    AcDbObjectId dimstyle() const;
    Acad::ErrorStatus setDimstyle(AcDbObjectId styleId);

    Acad::ErrorStatus getDimstyleData(AcDbDimStyleTableRecord*& pRec) const;
    Acad::ErrorStatus getDimstyleChildData(const AcRxClass *pDimClass,
                                           AcDbDimStyleTableRecord*& pRec,
                                           AcDbObjectId &style) const;
    AcDbObjectId getDimstyleChildId(const AcRxClass *pDimClass,
                                    AcDbObjectId &parentStyle) const;

    AcDbObjectId getDimstyleParentId(AcDbObjectId &childStyle) const;
                                           
    Acad::ErrorStatus setDimstyleData(AcDbDimStyleTableRecord* pRec);
    Acad::ErrorStatus setDimstyleData(AcDbObjectId id);

    AcDbObjectId cmlstyleID() const;
    Acad::ErrorStatus setCmlstyleID(AcDbObjectId objId);

    Adesk::Int16 cmljust() const;
    Acad::ErrorStatus setCmljust(Adesk::Int16 just);

    double cmlscale() const;
    Acad::ErrorStatus setCmlscale(double scale);

    double celtscale() const;
    Acad::ErrorStatus setCeltscale(double scale);

    // Paper space variable access

    AcGePoint3d pinsbase() const;
    Acad::ErrorStatus setPinsbase(const AcGePoint3d& base);

    AcGePoint3d pextmin() const;

    AcGePoint3d pextmax() const;

    Acad::ErrorStatus setPextmin(const AcGePoint3d& min);
    Acad::ErrorStatus setPextmax(const AcGePoint3d& max);

    AcGePoint2d plimmin() const;
    Acad::ErrorStatus setPlimmin(const AcGePoint2d& min);

    AcGePoint2d plimmax() const;
    Acad::ErrorStatus setPlimmax(const AcGePoint2d& max);

    double pelevation() const;
    Acad::ErrorStatus setPelevation(double elev);

    AcGePoint3d pucsorg() const;

    ACDBCORE2D_PORT
    AcGeVector3d pucsxdir() const;

    ACDBCORE2D_PORT
    AcGeVector3d pucsydir() const;

    ACDBCORE2D_PORT Acad::ErrorStatus setPucs(const AcGePoint3d& ucsOrigin,
                                        const AcGeVector3d& ucsXDir,
                                        const AcGeVector3d& ucsYDir);

    AcDbObjectId pucsname() const;

    ACDBCORE2D_PORT Acad::ErrorStatus setPucsname(const AcDbObjectId& ucsRecId);

    AcDbObjectId pucsBase() const;
    Acad::ErrorStatus setPucsBase(const AcDbObjectId &ucsid);

    AcGePoint3d worldPucsBaseOrigin(AcDb::OrthographicView orthoView) const;
    Acad::ErrorStatus setWorldPucsBaseOrigin(const AcGePoint3d& origin,
                                             AcDb::OrthographicView orthoView);

    bool isPucsOrthographic(AcDb::OrthographicView& orthoView) const;

    double cameraHeight() const;
    Acad::ErrorStatus setCameraHeight(const double cameraHeight);

    double lensLength() const;
    Acad::ErrorStatus setLensLength(const double lensLength);

    bool cameraDisplay() const;
    Acad::ErrorStatus setCameraDisplay(const bool cameraDisplay);

    double stepsPerSec() const;
    Acad::ErrorStatus setStepsPerSec(double stepsPerSec);

    double stepSize() const;
    Acad::ErrorStatus setStepSize(double stepSize);

    bool realWorldScale() const;
    Acad::ErrorStatus setRealWorldScale(const bool realWorldScale);
    // Model space variable access

    AcGePoint3d insbase() const;
    Acad::ErrorStatus setInsbase(const AcGePoint3d& base);

    AcGePoint3d extmin() const;

    AcGePoint3d extmax() const;

    Acad::ErrorStatus updateExt(bool doBestFit = false);

    Acad::ErrorStatus setExtmin(const AcGePoint3d& min);
    Acad::ErrorStatus setExtmax(const AcGePoint3d& max);

    AcGePoint2d limmin() const;
    Acad::ErrorStatus setLimmin(const AcGePoint2d& min);

    AcGePoint2d limmax() const;
    Acad::ErrorStatus setLimmax(const AcGePoint2d& max);

    double elevation() const;
    Acad::ErrorStatus setElevation(double elev);

    AcGePoint3d ucsorg() const;

    ACDBCORE2D_PORT
    AcGeVector3d ucsxdir() const;

    ACDBCORE2D_PORT
    AcGeVector3d ucsydir() const;

    ACDBCORE2D_PORT Acad::ErrorStatus setUcs(const AcGePoint3d& ucsOrigin,
                                       const AcGeVector3d& ucsXDir,
                                       const AcGeVector3d& ucsYDir);
    
    AcDbObjectId ucsname() const;

    ACDBCORE2D_PORT Acad::ErrorStatus setUcsname(const AcDbObjectId& ucsRecId);

    AcDbObjectId ucsBase() const;
    Acad::ErrorStatus setUcsBase(AcDbObjectId ucsid);

    AcGePoint3d worldUcsBaseOrigin(AcDb::OrthographicView orthoView) const;
    Acad::ErrorStatus setWorldUcsBaseOrigin(const AcGePoint3d& origin,
                                            AcDb::OrthographicView orthoView);

    bool isUcsOrthographic(AcDb::OrthographicView& orthoView) const;

/// <summary>
/// This function returns the EMR drawing setting.  0 is not EMR drawing; 1 is EMR drawing.
/// The EMR flag gets set when a drawing is  saved in a EMR (Student Version) product. 
/// </summary>
    bool isEMR() const;

    // Dimension variable api:
    //
    #undef DBDIMVAR_H                   // force the file to get read again
    #include "dbdimvar.h"

    // DEPRECATED METHODS!
    // These are supported but will be removed in future releases:
    //
#define AcDbDDimVars_Deprecated_ACHAR_Methods
#ifdef AcDbDDimVars_Deprecated_ACHAR_Methods
    Acad::ErrorStatus getDimpost(ACHAR*& pOutput) const;
    Acad::ErrorStatus getDimapost(ACHAR*& pOutput) const;
#endif
    ACDBCORE2D_PORT Acad::ErrorStatus getDimblk(AcString & sOutput) const;
#ifdef AcDbDDimVars_Deprecated_ACHAR_Methods
    Acad::ErrorStatus getDimblk(ACHAR*& pOutput) const;
#endif
    ACDBCORE2D_PORT Acad::ErrorStatus getDimblk1(AcString & sOutput) const;
#ifdef AcDbDDimVars_Deprecated_ACHAR_Methods
    Acad::ErrorStatus getDimblk1(ACHAR*& pOutput) const;
#endif
    ACDBCORE2D_PORT Acad::ErrorStatus getDimblk2(AcString & sOutput) const;
#ifdef AcDbDDimVars_Deprecated_ACHAR_Methods
    Acad::ErrorStatus getDimblk2(ACHAR*& pOutput) const;
#endif

    int dimfit() const;
    int dimunit() const;

    Acad::ErrorStatus setDimfit(int fit);
    Acad::ErrorStatus setDimunit(int unit);
    //
    // end DEPRECATED METHODS!


    Acad::ErrorStatus getDimRecentStyleList(AcDbObjectIdArray& objIds) const;

    Acad::ErrorStatus loadLineTypeFile(const ACHAR *ltn, const ACHAR *filename);

    ACDBCORE2D_PORT Acad::ErrorStatus getProjectName(AcString & sProjectName) const;
#ifdef AcDbDatabase_Deprecated_ACHAR_Methods
    Acad::ErrorStatus getProjectName(ACHAR*& pOutput) const;    // deprecated
#endif
    Acad::ErrorStatus setProjectName(const ACHAR*);
    ACDBCORE2D_PORT Acad::ErrorStatus getHyperlinkBase(AcString & sHyperlinkBase) const;
#ifdef AcDbDatabase_Deprecated_ACHAR_Methods
    Acad::ErrorStatus getHyperlinkBase(ACHAR*& pOutput) const;  // deprecated
#endif
    Acad::ErrorStatus setHyperlinkBase(const ACHAR*);
    ACDBCORE2D_PORT Acad::ErrorStatus getStyleSheet(AcString & sStyleSheet) const;
#ifdef AcDbDatabase_Deprecated_ACHAR_Methods
    Acad::ErrorStatus getStyleSheet(ACHAR*& pOutput) const;     // deprecated
#endif
    Acad::ErrorStatus setStyleSheet(const ACHAR*);
    Acad::ErrorStatus getFilename(const ACHAR* & pOutput) const;

    bool              isPartiallyOpened() const;
    Acad::ErrorStatus applyPartialOpenFilters(
        const AcDbSpatialFilter* pSpatialFilter,
        const AcDbLayerFilter* pLayerFilter);
    // This will abort the current partial open operation and
    // continue in a full open of the database.
    //
    void              disablePartialOpen();

    ACDBCORE2D_PORT Acad::ErrorStatus getFingerprintGuid(AcString & guidString) const;
#ifdef AcDbDatabase_Deprecated_ACHAR_Methods
    Acad::ErrorStatus getFingerprintGuid(ACHAR*& guidString) const;     // deprecated
#endif
    Acad::ErrorStatus setFingerprintGuid(const ACHAR *pNewGuid);

    ACDBCORE2D_PORT Acad::ErrorStatus getVersionGuid(AcString & guidString) const;
#ifdef AcDbDatabase_Deprecated_ACHAR_Methods
    Acad::ErrorStatus getVersionGuid(ACHAR*& guidString) const;         // deprecated
#endif
    Acad::ErrorStatus setVersionGuid(const ACHAR *pNewGuid);


    // New text sysvars
    //
    int tstackalign() const;
    Acad::ErrorStatus setTStackAlign(int val);

    int tstacksize() const;
    Acad::ErrorStatus setTStackSize(int val);

    AcDb::UnitsValue insunits() const;
    Acad::ErrorStatus setInsunits(const AcDb::UnitsValue units);


    // Plot Style Legacy
    bool           plotStyleMode() const;

    // Default paperspace viewport scale
    double viewportScaleDefault() const;
    Acad::ErrorStatus setViewportScaleDefault(double newDefaultVPScale);

    // dwg watermark
    bool           dwgFileWasSavedByAutodeskSoftware() const;

    // Layer state manager API
    AcDbLayerStateManager *getLayerStateManager() const;

    // Object context manager API
    AcDbObjectContextManager* objectContextManager() const;

    // When entity traversals are sorted (AcDb::kSortEnts*).
    Adesk::UInt8        sortEnts() const;
    Acad::ErrorStatus   setSortEnts(Adesk::UInt8 sortEnts);

    Adesk::UInt8        drawOrderCtl() const;
    Acad::ErrorStatus   setDrawOrderCtl(Adesk::UInt8 val);
    
    Adesk::UInt8        dimAssoc() const;
    Acad::ErrorStatus setDimAssoc(Adesk::UInt8 val);

    Adesk::UInt8 hideText() const;
    Acad::ErrorStatus setHideText(Adesk::UInt8 val);

    Adesk::UInt8  haloGap() const;
    Acad::ErrorStatus setHaloGap(Adesk::UInt8 val);

    Adesk::UInt16 obscuredColor() const;
    Acad::ErrorStatus setObscuredColor(Adesk::UInt16 val);

    Adesk::UInt8 obscuredLineType() const;
    Acad::ErrorStatus setObscuredLineType(Adesk::UInt8 val);

    Adesk::UInt8  intersectDisplay() const;
    Acad::ErrorStatus setIntersectDisplay(Adesk::UInt8 val);

    Adesk::UInt16 intersectColor() const;
    Acad::ErrorStatus setIntersectColor(Adesk::UInt16 val);

    // For the ACAD_TABLESTYLE dictionary
    Acad::ErrorStatus getTableStyleDictionary(AcDbDictionary*& pDict,
                                              AcDb::OpenMode mode = AcDb::kForRead);
    AcDbObjectId  tableStyleDictionaryId() const;

    // The following functions are similar to setDimstyle/dimstyle
    //
    AcDbObjectId tablestyle() const;
    Acad::ErrorStatus setTablestyle(AcDbObjectId objId);

    // For the ACAD_MLEADERSTYLE dictionary
    Acad::ErrorStatus getMLeaderStyleDictionary(AcDbDictionary*& pDict,
                                              AcDb::OpenMode mode = AcDb::kForRead);
    AcDbObjectId  mleaderStyleDictionaryId() const;

    // The following functions are similar to setDimstyle/dimstyle
    //
    AcDbObjectId mleaderstyle() const;
    Acad::ErrorStatus setMLeaderstyle(AcDbObjectId objId);

    // For the ACAD_DETAILVIEWSTYLE dictionary
    ACDBCORE2D_PORT Acad::ErrorStatus getDetailViewStyleDictionary(AcDbDictionary*& pDict,
                                                             AcDb::OpenMode mode = AcDb::kForRead);
    ACDBCORE2D_PORT AcDbObjectId detailViewStyleDictionaryId() const;
    ACDBCORE2D_PORT AcDbObjectId detailViewStyle() const;
    //Do not change format of setDetailViewStyle function! 
    //We need to preserve format which SymbolTableInfo struct defines for AcDiObservableCollection datatype (AcDiImpManager object)
    ACDBCORE2D_PORT Acad::ErrorStatus setDetailViewStyle(AcDbObjectId objId);

    // For the ACAD_SECTIONVIEWSTYLE dictionary
    ACDBCORE2D_PORT Acad::ErrorStatus getSectionViewStyleDictionary(AcDbDictionary*& pDict,
                                                              AcDb::OpenMode mode = AcDb::kForRead);
    ACDBCORE2D_PORT AcDbObjectId sectionViewStyleDictionaryId() const;
    ACDBCORE2D_PORT AcDbObjectId sectionViewStyle() const;
    //Do not change format of setSectionViewStyle function! 
    //We need to preserve format which SymbolTableInfo struct defines for AcDiObservableCollection datatype (AcDiImpManager object)
    ACDBCORE2D_PORT Acad::ErrorStatus setSectionViewStyle(AcDbObjectId objId);

    Acad::ErrorStatus evaluateFields(int nContext,
                                     const ACHAR* pszPropName= nullptr,
                                     AcDbDatabase* pDb      = nullptr,
                                     int* pNumFound         = nullptr,
                                     int* pNumEvaluated     = nullptr);

    // Get all AcDbViewports in all AcDbLayouts in the database
    Acad::ErrorStatus getViewportArray(AcDbObjectIdArray& vportIds,
                                       bool bGetPaperspaceVports = true) const;

    // Get names of all visual styles in the database (visual styles for
    // internal use only are excluded)
    Acad::ErrorStatus getVisualStyleList(AcArray<const ACHAR*> & vstyleList);

    Adesk::UInt8  solidHist() const;  // 0 (default) or 1
    Acad::ErrorStatus setSolidHist(Adesk::UInt8 val);

    Adesk::UInt8  showHist() const;   // 0, 1(default) or 2
    Acad::ErrorStatus setShowHist(Adesk::UInt8 val);

    double psolWidth() const;
    Acad::ErrorStatus setPsolWidth(double width);
    double psolHeight() const;
    Acad::ErrorStatus setPsolHeight(double height);

    Adesk::UInt16 loftParam() const;
    Acad::ErrorStatus setLoftParam(Adesk::UInt16 flags);
    Adesk::UInt8 loftNormals() const;
    Acad::ErrorStatus setLoftNormals(Adesk::UInt8 value);
    double loftAng1() const;
    Acad::ErrorStatus setLoftAng1(double ang1);
    double loftAng2() const;
    Acad::ErrorStatus setLoftAng2(double ang2);
    double loftMag1() const;
    Acad::ErrorStatus setLoftMag1(double mag1);
    double loftMag2() const;
    Acad::ErrorStatus setLoftMag2(double mag2);

    // Lat and long are in decimal degrees, not radians!
    double latitude() const;
    Acad::ErrorStatus setLatitude(double lat);
    double longitude() const;
    Acad::ErrorStatus setLongitude(double lng);
    double northDirection() const;
    Acad::ErrorStatus setNorthDirection(double northdir);
    AcDb::TimeZone timeZone() const;
    Acad::ErrorStatus setTimeZone(AcDb::TimeZone tz);
    // Offsets measured in hours difference from UTC
    Acad::ErrorStatus getTimeZoneInfo(AcDb::TimeZone tz, double& offset, AcString& desc) const;
    Acad::ErrorStatus setTimeZoneAsUtcOffset(double offset);
    bool geoMarkerVisibility() const;
    Acad::ErrorStatus setGeoMarkerVisibility(bool value);
    ACDBCORE2D_PORT AcString geoCoordinateSystemId() const;

    Adesk::UInt8 lightGlyphDisplay() const;  // 0 or 1(default)
    Acad::ErrorStatus setLightGlyphDisplay(Adesk::UInt8 val);
    Adesk::UInt8 tileModeLightSynch() const;  // 0 or 1(default)
    Acad::ErrorStatus setTileModeLightSynch(Adesk::UInt8 val);

    AcCmColor interfereColor() const;
    Acad::ErrorStatus setInterfereColor(const AcCmColor& color);

    AcDbObjectId interfereObjVisStyle() const;
    Acad::ErrorStatus setInterfereObjVisStyle(AcDbObjectId id);

    AcDbObjectId interfereVpVisStyle() const;
    Acad::ErrorStatus setInterfereVpVisStyle(AcDbObjectId id);

    AcDbObjectId dragVisStyle() const;
    Acad::ErrorStatus setDragVisStyle(AcDbObjectId id);

    Adesk::UInt8 cshadow() const;
    Acad::ErrorStatus setCshadow(Adesk::UInt8 val);

    double shadowPlaneLocation() const;
    Acad::ErrorStatus setShadowPlaneLocation(double val);

    AcDbAnnotationScale* cannoscale() const;
    Acad::ErrorStatus setCannoscale(AcDbAnnotationScale*);

    bool annoAllVisible() const;
    Acad::ErrorStatus setAnnoAllVisible(bool allvis);

    bool annotativeDwg() const;
    Acad::ErrorStatus setAnnotativeDwg(bool anno);

    bool msltscale() const;
    Acad::ErrorStatus setMsltscale(bool val);

    Adesk::UInt8 lightingUnits() const;
    Acad::ErrorStatus setLightingUnits(Adesk::UInt8 val);

    bool lightsInBlocks() const;
    Acad::ErrorStatus setLightsInBlocks(bool val);

    Adesk::Int16 dxeVal() const;
    Acad::ErrorStatus setDxeVal(Adesk::Int16 val);

    double mleaderscale() const;
    Acad::ErrorStatus setMLeaderscale(double scale);

    Adesk::Int16 cDynDisplayMode() const;
    Acad::ErrorStatus setCDynDisplayMode(Adesk::Int16 val);

    Adesk::Int16 previewType() const;
    Acad::ErrorStatus setPreviewType(Adesk::Int16 val);

    Adesk::UInt8 indexctl() const;
    Acad::ErrorStatus setIndexctl(Adesk::UInt8 val);

    Adesk::UInt8 layerEval() const;
    Acad::ErrorStatus setLayerEval(Adesk::UInt8 val);

    Adesk::Int16 layerNotify() const;
    Acad::ErrorStatus setLayerNotify(Adesk::Int16 val);

    double msOleScale() const;
    Acad::ErrorStatus setMsOleScale(double val);

    Adesk::UInt8 updateThumbnail() const;
    Acad::ErrorStatus setUpdateThumbnail(Adesk::UInt8 val);

    enum EraseMask {
        kZeroLengthCurve = 0x01,  //zero length curves (AcDbCurve derived objects)
        kEmptyText       = 0x02,  //empty TEXT/MTEXT objects (which contain only spaces, tabs, enters and/or new lines)
        kAllEmptyObj     = 0xFFFFFFFF
    };
    Adesk::UInt32 eraseEmptyObjects(const Adesk::UInt32 flags);
    Adesk::UInt32 countEmptyObjects(const Adesk::UInt32 flags);

private:
    friend class AcDbSystemInternals;
    AcDbImpDatabase* mpImpDb = nullptr;
    // No copy construction or assignment
    AcDbDatabase (const AcDbDatabase & ) = delete;
    AcDbDatabase & operator = (const AcDbDatabase & ) = delete;
};


#ifdef AcDbDDimVars_Deprecated_ACHAR_Methods
inline Acad::ErrorStatus AcDbDatabase::getDimpost(ACHAR*& pOutput) const
{
    return ::acutNewString(this->dimpost(), pOutput);
}
inline Acad::ErrorStatus AcDbDatabase::getDimapost(ACHAR*& pOutput) const
{
    return ::acutNewString(this->dimapost(), pOutput);
}
inline Acad::ErrorStatus AcDbDatabase::getDimblk(ACHAR*& pOutput) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbDatabase::getDimblk, pOutput); 
}
inline Acad::ErrorStatus AcDbDatabase::getDimblk1(ACHAR*& pOutput) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbDatabase::getDimblk1, pOutput); 
}
inline Acad::ErrorStatus AcDbDatabase::getDimblk2(ACHAR*& pOutput) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbDatabase::getDimblk2, pOutput); 
}
#endif

#ifdef AcDbDatabase_Deprecated_ACHAR_Methods
inline Acad::ErrorStatus AcDbDatabase::getMenu(ACHAR*& pOutput) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbDatabase::getMenu, pOutput); 
}
inline Acad::ErrorStatus AcDbDatabase::getProjectName(ACHAR*& pOutput) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbDatabase::getProjectName, pOutput); 
}
inline Acad::ErrorStatus AcDbDatabase::getHyperlinkBase(ACHAR*& pOutput) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbDatabase::getHyperlinkBase, pOutput); 
}
inline Acad::ErrorStatus AcDbDatabase::getStyleSheet(ACHAR*& pOutput) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbDatabase::getStyleSheet, pOutput); 
}
inline Acad::ErrorStatus AcDbDatabase::getFingerprintGuid(ACHAR*& pOutput) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbDatabase::getFingerprintGuid, pOutput); 
}
inline Acad::ErrorStatus AcDbDatabase::getVersionGuid(ACHAR*& pOutput) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbDatabase::getVersionGuid, pOutput); 
}
#endif

//  Backward compatibility.
inline Acad::ErrorStatus acdbSaveAs2004(AcDbDatabase* pDb,
                                        const ACHAR* fileName)
{
    return pDb->saveAs(fileName, false, AcDb::kDHL_1800);
}

inline Acad::ErrorStatus acdbSaveAs2000(AcDbDatabase* pDb,
                                        const ACHAR* fileName)
{
    return pDb->saveAs(fileName, false, AcDb::kDHL_1015);
}

inline Acad::ErrorStatus acdbSaveAsR14(AcDbDatabase* pDb,
                                       const ACHAR* fileName)
{
    return pDb->saveAs(fileName, false, AcDb::kDHL_1014);
}

inline Acad::ErrorStatus acdbDxfOutAs2004(AcDbDatabase* pDb,
                                          const ACHAR* fileName,
                                          const int precision = 16)
{
    return pDb->dxfOut(fileName, precision, AcDb::kDHL_1800);
}

inline Acad::ErrorStatus acdbDxfOutAs2000(AcDbDatabase* pDb,
                                          const ACHAR* fileName,
                                          const int precision = 16)
{
    return pDb->dxfOut(fileName, precision, AcDb::kDHL_1015);
}

inline Acad::ErrorStatus acdbDxfOutAsR12(AcDbDatabase* pDb,
                                         const ACHAR* fileName,
                                         const int precision = 16)
{
    return pDb->dxfOut(fileName, precision, AcDb::kDHL_1009);
}


class AcDbObjectIterator: public AcRxObject, public AcHeapOperators
{
public:
    ACRX_DECLARE_MEMBERS(AcDbObjectIterator);
    ~AcDbObjectIterator();

    ACDBCORE2D_PORT
    bool           done() const;
    ACDBCORE2D_PORT
    void           step(bool backwards = false, bool skipDeleted = true);
    void           setPosition(AcDbEntity*  pEnt);
    void           setPosition(AcDbObjectId  pObj);
    ACDBCORE2D_PORT
    void           start(bool atEnd = false);
    ACDBCORE2D_PORT
    AcDbEntity*    entity();
    ACDBCORE2D_PORT
    AcDbObjectId   objectId();

private:
    friend class AcDbSystemInternals;
    AcDbObjectIterator();
    AcDbSpaceIterator* mpImpIterator = nullptr;
};


class ADESK_NO_VTABLE AcDbXObject: public AcRxObject
//
// AcRxObject which recognizes filer protocol,
// and has a ACRX_DXF_CLASS_OBJ_BODY
//
{
public:
    ACRX_DECLARE_MEMBERS(AcDbXObject);

    virtual Acad::ErrorStatus audit(AcDbAuditInfo* pAuditInfo);

    Acad::ErrorStatus dwgIn(AcDbDwgFiler* pFiler);
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
    Acad::ErrorStatus dwgOut(AcDbDwgFiler* pFiler) const;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;

    Acad::ErrorStatus dxfIn(AcDbDxfFiler* pFiler);
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);
    Acad::ErrorStatus dxfOut(AcDbDxfFiler* pFiler) const;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;

    protected:
    AcDbXObject();
};

class AcCmComplexColor: public  AcDbXObject
{
public:
    ACRX_DECLARE_MEMBERS(AcCmComplexColor); 

    virtual AcCmComplexColor* incReference();
    virtual void              decReference();

    virtual Acad::ErrorStatus getDescription(AcString & desc) const;
#define AcColor_Deprecated_ACHAR_Methods
#ifdef AcColor_Deprecated_ACHAR_Methods
    Acad::ErrorStatus getDescription(ACHAR*& desc) const; // deprecated
#endif
    virtual Acad::ErrorStatus getExplanation(AcString & expl) const;
#ifdef AcColor_Deprecated_ACHAR_Methods
    Acad::ErrorStatus getExplanation(ACHAR*& expl) const; // deprecated
#endif

    virtual AcCmEntityColor::ColorMethod  colorMethod() const;

    virtual bool              isByColor() const;
    virtual bool              isByLayer() const;
    virtual bool              isByBlock() const;
    virtual bool              isByACI()   const;
    virtual bool              isByPen ()  const;
    virtual bool              isForeground()   const;

    virtual Acad::ErrorStatus setRGB  (Adesk::UInt8 red, 
                                       Adesk::UInt8 green, 
                                       Adesk::UInt8 blue);
    virtual Adesk::UInt8      red  () const;
    virtual Adesk::UInt8      green() const;
    virtual Adesk::UInt8      blue () const;

    // 32-bit RGB value in Win32 RGBQUAD format 0x00rrggbb 
    Acad::ErrorStatus   setRGB(Adesk::UInt32 rgbValue);
    Adesk::UInt32       getRGB() const;
    // 32-bit color value in AutoCAD RGBM format 0xmmrrggbb
    Acad::ErrorStatus   setRGBM(Adesk::UInt32 rgbmValue);
    Adesk::UInt32       getRGBM() const;
    
    virtual Adesk::UInt16     colorIndex() const;
    virtual Acad::ErrorStatus setColorIndex(Adesk::UInt16 colorIndex);
    virtual Adesk::UInt16     penIndex() const;   
    virtual Acad::ErrorStatus setPenIndex (Adesk::UInt16 penIndex);

    // --- AcRxObject protocol
    //
    Acad::ErrorStatus copyFrom(const AcRxObject*) override;
    Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler) override;
    Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const override;
    Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler) override;
    Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const override;
    Acad::ErrorStatus audit(AcDbAuditInfo* pAuditInfo) override;

private:
    Adesk::UInt16 refCount = 0;
    AcCmEntityColor mColor;
#ifdef AcCmColor_DEPRECATED_METHODS
  public:
    [[deprecated("Prefer specific setMethod() calls to this generic call")]] ACDBCORE2D_PORT virtual Acad::ErrorStatus setColorMethod(
        AcCmEntityColor::ColorMethod eColorMethod);
    [[deprecated("Use getRGBM() or getRGB()")]] ACDBCORE2D_PORT virtual Adesk::UInt32     color() const;
    [[deprecated("Use setRGBM() or setRGB()")]] ACDBCORE2D_PORT virtual Acad::ErrorStatus setColor(Adesk::UInt32 color);
    [[deprecated("Use setRGB()")]] ACDBCORE2D_PORT virtual Acad::ErrorStatus              setRed(Adesk::UInt8 red);
    [[deprecated("Use setRGB()")]] ACDBCORE2D_PORT virtual Acad::ErrorStatus              setGreen(Adesk::UInt8 green);
    [[deprecated("Use setRGB()")]] ACDBCORE2D_PORT virtual Acad::ErrorStatus              setBlue(Adesk::UInt8 blue);
#endif
};

#ifdef AcColor_Deprecated_ACHAR_Methods
inline Acad::ErrorStatus AcCmComplexColor::getDescription(ACHAR*& desc) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcCmComplexColor::getDescription, desc); 
}

inline Acad::ErrorStatus AcCmComplexColor::getExplanation(ACHAR*& expl) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcCmComplexColor::getExplanation, expl); 
}
#endif

class  AcCmHSB   
{

public:
    ACDBCORE2D_PORT AcCmHSB();
    ACDBCORE2D_PORT AcCmHSB(Adesk::UInt16 hue, Adesk::UInt8 saturation, Adesk::UInt8 brightness);
    ACDBCORE2D_PORT AcCmHSB(const AcCmHSB&);
    ACDBCORE2D_PORT AcCmHSB& operator=(const AcCmHSB& inputColor);
    ACDBCORE2D_PORT virtual ~AcCmHSB();

    ACDBCORE2D_PORT bool operator ==(const AcCmHSB& color) const;
    ACDBCORE2D_PORT bool operator !=(const AcCmHSB& color) const;

    ACDBCORE2D_PORT virtual Adesk::UInt32     value() const;

    ACDBCORE2D_PORT virtual Acad::ErrorStatus rgbToHSB(Adesk::UInt8 r, Adesk::UInt8 g, Adesk::UInt8 b);
    ACDBCORE2D_PORT virtual Acad::ErrorStatus hsbToRGB(Adesk::UInt8 *r, Adesk::UInt8 *g, Adesk::UInt8 *b);

    ACDBCORE2D_PORT virtual Acad::ErrorStatus setHSB(Adesk::UInt32 value);
    ACDBCORE2D_PORT virtual Acad::ErrorStatus setHSB  (Adesk::UInt16 hue, 
                               Adesk::UInt8 saturation, 
                               Adesk::UInt8 brightness);
    ACDBCORE2D_PORT virtual Acad::ErrorStatus setHSB(double hue, double saturation, double brightness);
    ACDBCORE2D_PORT virtual Acad::ErrorStatus setHue  (Adesk::UInt16 hue);
    ACDBCORE2D_PORT virtual Acad::ErrorStatus setHue  (double hue);
    ACDBCORE2D_PORT virtual Acad::ErrorStatus setSaturation (Adesk::UInt8 saturation);
    ACDBCORE2D_PORT virtual Acad::ErrorStatus setSaturation (double saturation);
    ACDBCORE2D_PORT virtual Acad::ErrorStatus setBrightness (Adesk::UInt8 brightness);
    ACDBCORE2D_PORT virtual Acad::ErrorStatus setBrightness (double brightness);
    ACDBCORE2D_PORT virtual Adesk::UInt16     hue  () const;
    ACDBCORE2D_PORT virtual Adesk::UInt8      saturation() const;
    ACDBCORE2D_PORT virtual Adesk::UInt8      brightness () const;

private:

    Adesk::UInt32           mHSB = 0;
};


// the following functions convert strings to AcCmColor instances
// Parameters:
//        clr  - reference to an instance of AcCmColor.  This instance
//               will be filled out with the color value corresponding
//             to pInput or pBookName, pColorName
//      pInput - pointer to a string representation of a color.  This
//             can be an ACI color [ByBlock, red, 70] or an RGB color
//             [120,12,36]
//        pBookName - pointer to a string specifying the name of a
//               colorbook
//        pColorName - pointer to a string specifying the name of a
//             color in the colorbook identified by pBookName
//
// Return values:
//        Acad::eOk                    for success
//        Acad::eBadColor                for an invalid string or strings
//      Acad::eInvalidInput            if no colorbooks are present
//      Acad::eNotImplementedYet    if certain dlls are not present
//
Acad::ErrorStatus accmGetColorFromACIName(AcCmColor& clr, const ACHAR *pInput);
Acad::ErrorStatus accmGetColorFromRGBName(AcCmColor& clr, const ACHAR *pInput);
Acad::ErrorStatus ACDBCORE2D_PORT accmGetFromHSBName(AcCmHSB& hsb, const ACHAR *pInput);
Acad::ErrorStatus accmGetColorFromColorBookName(AcCmColor& clr, const ACHAR *pBookName, const ACHAR *pColorName);

// the following function gets localized names for the standard
//  AutoCAD colors: ByBlock, red, yellow, green, ..., ByLayer
void accmGetLocalizedColorNames( const ACHAR* colors[9] );

class AcDbColor: public AcDbObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbColor);

    AcDbColor();
    ~AcDbColor();

    void getColor(AcCmColor& color) const;
    void setColor(const AcCmColor& color);
    const AcCmEntityColor& entityColor(void) const;

    // Saving as previous versions.
    //
    Acad::ErrorStatus   decomposeForSave(
                        AcDb::AcDbDwgVersion ver,
                        AcDbObject*& replaceObj,
                        AcDbObjectId& replaceId,
                        Adesk::Boolean& exchangeXData) override;


    Acad::ErrorStatus   dwgInFields(AcDbDwgFiler* pFiler) override;
    Acad::ErrorStatus   dwgOutFields(AcDbDwgFiler* pFiler) const override;

    Acad::ErrorStatus   dxfInFields(AcDbDxfFiler* pFiler) override;
    Acad::ErrorStatus   dxfOutFields(AcDbDxfFiler* pFiler) const override;
    
private:

    AcCmColor           m_color;    // main storage
    AcCmEntityColor     m_ecol;     // quick reference

protected:
    Acad::ErrorStatus subWblockClone(AcRxObject* pOwnerObject,
                                  AcDbObject*& pClonedObject,
                                  AcDbIdMapping& idMap,
                                  Adesk::Boolean isPrimary
                                  = true) const override;

};


class ADESK_NO_VTABLE AcDbEntity: public AcDbObject
{
public:
    ACDBCORE2D_DECLARE_MEMBERS(AcDbEntity);

    ~AcDbEntity();

    AcDbObjectId                blockId() const;

    AcCmColor                   color() const;
    // setColor()'s pDb arg is used for looking up named colors when entity is non-db-resident
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   setColor(const AcCmColor& color, bool doSubents, AcDbDatabase *pDb);
    // Deprecated method. Calls the above overload. Marked final to prevent overrides
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   setColor(const AcCmColor& color, bool doSubents = true) final;
    Adesk::UInt16               colorIndex() const;
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   setColorIndex(Adesk::UInt16 color,
                                  Adesk::Boolean doSubents = true);
    AcCmEntityColor             entityColor() const;

    AcCmTransparency            transparency() const;
    virtual Acad::ErrorStatus   setTransparency(const AcCmTransparency& trans,
                                  Adesk::Boolean doSubents = true);


    ACDBCORE2D_PORT Acad::ErrorStatus plotStyleName(AcString &sName) const;
    AcString                    plotStyleName(Acad::ErrorStatus *pEs) const;
#define AcDbEnt_Deprecated_ACHAR_Methods
#ifdef AcDbEnt_Deprecated_ACHAR_Methods
    ACHAR*                      plotStyleName() const;  // deprecated
#endif
    AcDb::PlotStyleNameType     getPlotStyleNameId(AcDbObjectId& id) const;
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   setPlotStyleName(const ACHAR* newName,
                                  Adesk::Boolean doSubents = true);
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   setPlotStyleName(AcDb::PlotStyleNameType,
                                AcDbObjectId newId = AcDbObjectId::kNull,
                                Adesk::Boolean doSubents = true);
    
    ACDBCORE2D_PORT Acad::ErrorStatus layer(AcString &sName) const;
    AcString                    layerName(Acad::ErrorStatus *pEs = nullptr) const;
#ifdef AcDbEnt_Deprecated_ACHAR_Methods
    ACHAR*                      layer() const;
#endif
    AcDbObjectId                layerId() const;
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   setLayer(const ACHAR* newVal,
                                  Adesk::Boolean doSubents = true,
                                  bool allowHiddenLayer = false);
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   setLayer(AcDbObjectId newVal,
                                  Adesk::Boolean doSubents = true,
                                  bool allowHiddenLayer = false);

    ACDBCORE2D_PORT Acad::ErrorStatus linetype(AcString &sName) const;
    AcString                    linetypeName(Acad::ErrorStatus *pEs = nullptr) const;
#ifdef AcDbEnt_Deprecated_ACHAR_Methods
    ACHAR*                      linetype() const;       // deprecated
#endif
    AcDbObjectId                linetypeId() const;
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   setLinetype(const ACHAR* newVal,
                                  Adesk::Boolean doSubents = true);
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   setLinetype(AcDbObjectId newVal,
                                  Adesk::Boolean doSubents = true);

    ACDBCORE2D_PORT Acad::ErrorStatus material(AcString &sName) const;
    AcString                    materialName(Acad::ErrorStatus *pEs = nullptr) const;
#ifdef AcDbEnt_Deprecated_ACHAR_Methods
    ACHAR*                      material() const;       // deprecated
#endif
    AcDbObjectId                materialId() const;
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   setMaterial(const ACHAR* newVal, Adesk::Boolean doSubents = true);
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   setMaterial(AcDbObjectId newVal, Adesk::Boolean doSubents = true);

    /// <summary>
    /// Enumerates the visual style types that can be set into an entity.
    /// </summary>
    enum VisualStyleType {

        /// <summary>
        /// Full visual style, defines the overall visual style of the entity.
        /// </summary>
        kFullVisualStyle,

        /// <summary>
        /// Optional face-only visual style which can vary independently of 
        /// the full visual style.
        /// </summary>
        kFaceVisualStyle,

        /// <summary>
        /// Optional edge-only visual style which can vary independently of
        /// the full visual style.
        /// </summary>
        kEdgeVisualStyle
    };

    /// <summary>
    /// Sets visual styles for the entity.  
    /// </summary>
    /// <param name="visualStyleId">
    /// Input AcDbObjectId of the AcDbVisualStyle
    /// </param>    
    /// <param name="vsType">
    /// Input VisualStyleType of the visual style type to set.
    /// </param>    
    /// <param name="doSubents">
    /// Input bool, if true applies this visual style to all sub entities.  
    /// </param>    
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   setVisualStyle  (AcDbObjectId visualStyleId, 
                                                 VisualStyleType vsType = kFullVisualStyle,  
                                                 Adesk::Boolean doSubents = true);

    /// <summary>
    /// Gets the visual styles from the entity.
    /// </summary>
    /// <param name="vsType">
    /// Input VisualStyleType of the visual style type to retrieve.
    /// </param>    
    /// <returns>
    /// AcDbObjectId of the visual style.
    /// </returns>    
    AcDbObjectId                visualStyleId   (VisualStyleType vsType = kFullVisualStyle) const;

    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus getMaterialMapper(AcGiMapper& mapper) const;
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus setMaterialMapper(const AcGiMapper& mapper, Adesk::Boolean doSubents = true);

    double                      linetypeScale() const;
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   setLinetypeScale(double newval,
                                  Adesk::Boolean doSubents = true);

    AcDb::Visibility            visibility() const;
    ACDBCORE2D_PORT virtual Acad::ErrorStatus   setVisibility(AcDb::Visibility newVal,
                                  bool doSubents = true) final;

    AcDb::LineWeight            lineWeight() const;
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   setLineWeight(AcDb::LineWeight newVal,
                                  Adesk::Boolean doSubents = true);

    ACDBCORE2D_PORT
    virtual AcDb::CollisionType collisionType() const;

    ACDBCORE2D_PORT
    virtual bool                castShadows() const;
    ACDBCORE2D_PORT
    virtual void                setCastShadows(bool newVal);
    ACDBCORE2D_PORT
    virtual bool                receiveShadows() const;
    ACDBCORE2D_PORT
    virtual void                setReceiveShadows(bool newVal);

    Acad::ErrorStatus           setPropertiesFrom(const AcDbEntity* pEntity,
                                  Adesk::Boolean doSubents = true);

    virtual Adesk::Boolean      isPlanar() const { return false; }
    virtual Acad::ErrorStatus   getPlane(AcGePlane&, AcDb::Planarity&) const
                                    { return Acad::eNotApplicable; }

    ACDBCORE2D_PORT
    virtual void                getEcs(AcGeMatrix3d& retVal) const;

    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus   getGeomExtents(AcDbExtents& extents) const ADESK_SEALED;

    // Subentity acquisition and manipulation
    //
    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus addSubentPaths(
                                  const AcDbFullSubentPathArray& newPaths) ADESK_SEALED;

    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus deleteSubentPaths(
                                  const AcDbFullSubentPathArray& paths) ADESK_SEALED;

    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL   Acad::ErrorStatus getSubentClassId(
                                  const AcDbFullSubentPath& path,
                                  CLSID*                    clsId) const ADESK_SEALED;
 
    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus transformSubentPathsBy(
                                  const AcDbFullSubentPathArray& paths,
                                  const AcGeMatrix3d&            xform) ADESK_SEALED;

    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus getGripPointsAtSubentPath(
                                  const AcDbFullSubentPath&      path,
                                  AcDbGripDataPtrArray&          grips,
                                  const double                   curViewUnitSize,
                                  const int                      gripSize,
                                  const AcGeVector3d&            curViewDir,
                                  const int                      bitflags) const ADESK_SEALED;
    
    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus moveGripPointsAtSubentPaths(
                                  const AcDbFullSubentPathArray& paths,
                                  const AcDbVoidPtrArray&        gripAppData,
                                  const AcGeVector3d&            offset,
                                  const int                      bitflags) ADESK_SEALED;

    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus getSubentPathGeomExtents(
                                  const AcDbFullSubentPath&      path, 
                                  AcDbExtents&                   extents) const ADESK_SEALED;

    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus getSubentPathsAtGsMarker(
                                  AcDb::SubentType       type,
                                  Adesk::GsMarker        gsMark, 
                                  const AcGePoint3d&     pickPoint,
                                  const AcGeMatrix3d&    viewXform, 
                                  int&                   numPaths,
                                  AcDbFullSubentPath*&   subentPaths, 
                                  int                    numInserts = 0,
                                  AcDbObjectId*          entAndInsertStack
                                                           = nullptr) const ADESK_SEALED;

    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus getGsMarkersAtSubentPath(
                               const AcDbFullSubentPath& subPath, 
                               AcArray<Adesk::GsMarker>& gsMarkers) const ADESK_SEALED;

    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus highlight(const AcDbFullSubentPath& subId 
                                        = kNullSubent, const Adesk::Boolean highlightAll 
                        = false) const ADESK_SEALED;
    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus unhighlight(const AcDbFullSubentPath& subId 
                                        = kNullSubent, const Adesk::Boolean highlightAll  
                        = false) const ADESK_SEALED;
    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL AcDbEntity*       subentPtr(const AcDbFullSubentPath& id) const ADESK_SEALED;
 
    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus getOsnapPoints(
                                 AcDb::OsnapMode     osnapMode,
                                 Adesk::GsMarker     gsSelectionMark,
                                 const AcGePoint3d&  pickPoint,
                                 const AcGePoint3d&  lastPoint,
                                 const AcGeMatrix3d& viewXform,
                                 AcGePoint3dArray&   snapPoints,
                                 AcDbIntArray &   geomIds) const ADESK_SEALED;

    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus getOsnapPoints(
                                 AcDb::OsnapMode     osnapMode,
                                 Adesk::GsMarker     gsSelectionMark,
                                 const AcGePoint3d&  pickPoint,
                                 const AcGePoint3d&  lastPoint,
                                 const AcGeMatrix3d& viewXform,
                                 AcGePoint3dArray&   snapPoints,
                                 AcDbIntArray &   geomIds,
                                 const AcGeMatrix3d& insertionMat) const ADESK_SEALED;

    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL bool isContentSnappable() const ADESK_SEALED;

    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus   getGripPoints(
                                   AcGePoint3dArray&  gripPoints,
                                   AcDbIntArray &     osnapModes,
                                   AcDbIntArray &  geomIds) const ADESK_SEALED;

    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus moveGripPointsAt(const AcDbIntArray & indices,
        const AcGeVector3d& offset) ADESK_SEALED;

    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus   getGripPoints(AcDbGripDataPtrArray& grips,
        const double curViewUnitSize, const int gripSize, 
        const AcGeVector3d& curViewDir, const int bitflags) const ADESK_SEALED;

    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus moveGripPointsAt(const AcDbVoidPtrArray& gripAppData,
        const AcGeVector3d& offset, const int bitflags) ADESK_SEALED;
    
    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus getStretchPoints(
        AcGePoint3dArray& stretchPoints) const ADESK_SEALED;

    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus moveStretchPointsAt(const AcDbIntArray & indices,
        const AcGeVector3d& offset) ADESK_SEALED;

    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus intersectWith(const AcDbEntity* pEnt,
                                    AcDb::Intersect intType, 
                                    AcGePoint3dArray& points,
                                    Adesk::GsMarker thisGsMarker = 0, 
                                    Adesk::GsMarker otherGsMarker = 0) const ADESK_SEALED;
 
    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus intersectWith(const AcDbEntity* pEnt,
                                             AcDb::Intersect intType, 
                                             const AcGePlane& projPlane,
                                             AcGePoint3dArray& points, 
                                             Adesk::GsMarker thisGsMarker = 0,
                                             Adesk::GsMarker otherGsMarker = 0) const ADESK_SEALED;

    Acad::ErrorStatus          boundingBoxIntersectWith(
                                             const AcDbEntity*   pEnt,
                                             AcDb::Intersect     intType,
                                             AcGePoint3dArray&   points,
                                             Adesk::GsMarker     thisGsMarker,
                                             Adesk::GsMarker     otherGsMarker) const;

    Acad::ErrorStatus          boundingBoxIntersectWith(
                                             const AcDbEntity*   pEnt,
                                             AcDb::Intersect     intType,
                                             const AcGePlane&    projPlane,
                                             AcGePoint3dArray&   points,
                                             Adesk::GsMarker     thisGsMarker,
                                             Adesk::GsMarker     otherGsMarker) const;

    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL void  list() const ADESK_SEALED;

    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus   transformBy(const AcGeMatrix3d& xform) ADESK_SEALED;
    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus   getTransformedCopy(const AcGeMatrix3d& xform,
                                                   AcDbEntity*& pEnt) const ADESK_SEALED;
    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus   explode(AcDbVoidPtrArray& entitySet) const ADESK_SEALED;

    void                        recordGraphicsModified(
                                    Adesk::Boolean setModified = true);

    Acad::ErrorStatus           draw();
    ACDBCORE2D_PORT
    virtual void                saveAs(AcGiWorldDraw* mode, AcDb::SaveType st);

    ACDBCORE2D_PORT ADESK_SEALED_VIRTUAL Acad::ErrorStatus   getCompoundObjectTransform(AcGeMatrix3d & xMat) const ADESK_SEALED;

    void                        setDatabaseDefaults();
    void                        setDatabaseDefaults(AcDbDatabase* pDb);
    ACDBCORE2D_PORT
    virtual void                subSetDatabaseDefaults(AcDbDatabase* pDb);

    ACDBCORE2D_PORT Acad::ErrorStatus   applyPartialUndo(AcDbDwgFiler* undoFiler,
                                                 AcRxClass*    classObj) override;

    ACDBCORE2D_PORT Acad::ErrorStatus   audit(AcDbAuditInfo* pAuditInfo) override;

    ACDBCORE2D_PORT Acad::ErrorStatus   dwgInFields(AcDbDwgFiler* pFiler) override;
    ACDBCORE2D_PORT Acad::ErrorStatus   dwgOutFields(AcDbDwgFiler* pFiler) const override;

    ACDBCORE2D_PORT Acad::ErrorStatus   dxfInFields(AcDbDxfFiler* pFiler) override;
    ACDBCORE2D_PORT Acad::ErrorStatus   dxfOutFields(AcDbDxfFiler* pFiler) const override;


    ACDBCORE2D_PORT AcGiDrawable*       drawable() override;

    // AcGiDrawable interface
    //
    ACDBCORE2D_PORT bool                bounds(AcDbExtents& bounds) const override;

    ACDBCORE2D_PORT virtual bool        cloneMeForDragging() final;
    ACDBCORE2D_PORT virtual bool        hideMeForDragging() const final;

    virtual void                        dragStatus(const AcDb::DragStat status);
    ACDBCORE2D_PORT virtual void        gripStatus(const AcDb::GripStat status) final;
    ACDBCORE2D_PORT virtual void        subentGripStatus(
                                    const AcDb::GripStat      status,
                                    const AcDbFullSubentPath& subentity) final;

    ACDBCORE2D_PORT virtual Acad::ErrorStatus getGripEntityUCS(const void* pGripAppData, 
        AcGeVector3d& normalVec, AcGePoint3d& origin, AcGeVector3d& xAxis) const final;

protected:
    // Makes AcDbEntity an abstract class.
    AcDbEntity();

    // AcDbPropertiesOverrule related
    Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
    ACDBCORE2D_PORT
    virtual void                subList() const;

    // AcDbOsnapOverrule
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   subGetOsnapPoints(
                                    AcDb::OsnapMode     osnapMode,
                                    Adesk::GsMarker     gsSelectionMark,
                                    const AcGePoint3d&  pickPoint,
                                    const AcGePoint3d&  lastPoint,
                                    const AcGeMatrix3d& viewXform,
                                    AcGePoint3dArray&   snapPoints,
                                    AcDbIntArray &   geomIds) const;
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   subGetOsnapPoints(
                                    AcDb::OsnapMode     osnapMode,
                                    Adesk::GsMarker     gsSelectionMark,
                                    const AcGePoint3d&  pickPoint,
                                    const AcGePoint3d&  lastPoint,
                                    const AcGeMatrix3d& viewXform,
                                    AcGePoint3dArray&   snapPoints,
                                    AcDbIntArray &   geomIds,
                                    const AcGeMatrix3d& insertionMat) const;

    ACDBCORE2D_PORT
    virtual bool                subIsContentSnappable() const;

    // AcDbTransformOverrule
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   subTransformBy(const AcGeMatrix3d& xform);
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   subGetTransformedCopy(const AcGeMatrix3d& xform,
                                                   AcDbEntity*& pEnt) const;
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   subExplode(AcDbVoidPtrArray& entitySet) const;
    ACDBCORE2D_PORT
    virtual Adesk::Boolean      subCloneMeForDragging();
    ACDBCORE2D_PORT
    virtual bool                subHideMeForDragging() const;

    // AcDbGripOverrule
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   subGetGripPoints(
                                    AcGePoint3dArray&  gripPoints,
                                    AcDbIntArray &     osnapModes,
                                    AcDbIntArray &  geomIds) const;

    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   subGetGripPoints(AcDbGripDataPtrArray& grips,
                                    const double curViewUnitSize, const int gripSize, 
                                    const AcGeVector3d& curViewDir, const int bitflags) const;

    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   subMoveGripPointsAt(const AcDbIntArray & indices,
                                    const AcGeVector3d& offset);

    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   subMoveGripPointsAt(const AcDbVoidPtrArray& gripAppData,
                                    const AcGeVector3d& offset, const int bitflags);

    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   subGetStretchPoints(
                                    AcGePoint3dArray& stretchPoints) const;

    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   subMoveStretchPointsAt(const AcDbIntArray & indices,
                                    const AcGeVector3d& offset);

    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   subGetGeomExtents(AcDbExtents& extents) const;

    // AcDbSubentityOverrule related
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus subGetSubentClassId(
                                  const AcDbFullSubentPath& path,
                                  CLSID*                    clsId) const;

    ACDBCORE2D_PORT
    virtual  Acad::ErrorStatus subAddSubentPaths(
                                  const AcDbFullSubentPathArray& newPaths);

    ACDBCORE2D_PORT
    virtual  Acad::ErrorStatus subDeleteSubentPaths(
                                  const AcDbFullSubentPathArray& paths);
 
    ACDBCORE2D_PORT
    virtual  Acad::ErrorStatus subTransformSubentPathsBy(
                                  const AcDbFullSubentPathArray& paths,
                                  const AcGeMatrix3d&            xform);

    ACDBCORE2D_PORT
    virtual  Acad::ErrorStatus subGetGripPointsAtSubentPath(
                                  const AcDbFullSubentPath&      path,
                                  AcDbGripDataPtrArray&          grips,
                                  const double                   curViewUnitSize,
                                  const int                      gripSize,
                                  const AcGeVector3d&            curViewDir,
                                  const int                      bitflags) const;
    
    ACDBCORE2D_PORT
    virtual  Acad::ErrorStatus subMoveGripPointsAtSubentPaths(
                                  const AcDbFullSubentPathArray& paths,
                                  const AcDbVoidPtrArray&        gripAppData,
                                  const AcGeVector3d&            offset,
                                  const int                      bitflags);

    ACDBCORE2D_PORT
    virtual  Acad::ErrorStatus subGetSubentPathGeomExtents(
                                  const AcDbFullSubentPath&      path, 
                                  AcDbExtents&                   extents) const;   

    ACDBCORE2D_PORT
    virtual  Acad::ErrorStatus subGetSubentPathsAtGsMarker(
                                  AcDb::SubentType       type,
                                  Adesk::GsMarker        gsMark, 
                                  const AcGePoint3d&     pickPoint,
                                  const AcGeMatrix3d&    viewXform, 
                                  int&                   numPaths,
                                  AcDbFullSubentPath*&   subentPaths, 
                                  int                    numInserts = 0,
                                  AcDbObjectId*          entAndInsertStack
                                                           = nullptr) const;

    ACDBCORE2D_PORT
    virtual  Acad::ErrorStatus subGetGsMarkersAtSubentPath(
                               const AcDbFullSubentPath& subPath, 
                               AcArray<Adesk::GsMarker>& gsMarkers) const;

    ACDBCORE2D_PORT
    virtual AcDbEntity*        subSubentPtr(const AcDbFullSubentPath& id) const;

    ACDBCORE2D_PORT
    virtual void subGripStatus(const AcDb::GripStat status);
    ACDBCORE2D_PORT
    virtual void               subSubentGripStatus(
                                    const AcDb::GripStat      status,
                                    const AcDbFullSubentPath& subentity);

    // AcDbHighlightOverrule related
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus subHighlight(const AcDbFullSubentPath& subId 
                                        = kNullSubent, const Adesk::Boolean highlightAll 
                                        = false) const;
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus subUnhighlight(const AcDbFullSubentPath& subId 
                                        = kNullSubent, const Adesk::Boolean highlightAll  
                                        = false) const;

    // AcDbVisibilityOverrule related
    ACDBCORE2D_PORT virtual AcDb::Visibility  subVisibility() const;
    ACDBCORE2D_PORT virtual Acad::ErrorStatus subSetVisibility(AcDb::Visibility newVal,
                                        Adesk::Boolean doSubents = true);

    // AcDbGeometryOverrule related
    ACDBCORE2D_PORT
    virtual  Acad::ErrorStatus subIntersectWith(const AcDbEntity* pEnt,
                                        AcDb::Intersect intType, 
                                        AcGePoint3dArray& points,
                                        Adesk::GsMarker thisGsMarker = 0, 
                                        Adesk::GsMarker otherGsMarker = 0) const;
 
    ACDBCORE2D_PORT
    virtual  Acad::ErrorStatus subIntersectWith(const AcDbEntity* pEnt,
                                             AcDb::Intersect intType, 
                                             const AcGePlane& projPlane,
                                             AcGePoint3dArray& points, 
                                             Adesk::GsMarker thisGsMarker = 0,
                                             Adesk::GsMarker otherGsMarker = 0) const;

    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus subGetGripEntityUCS(const void* pGripAppData, 
        AcGeVector3d& normalVec, AcGePoint3d& origin, AcGeVector3d& xAxis) const;

    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus   subGetCompoundObjectTransform(AcGeMatrix3d & xMat) const;

    friend class AcDbPropertiesOverrule;
    friend class AcDbOsnapOverrule;
    friend class AcDbTransformOverrule;
    friend class AcDbGripOverrule;
    friend class AcDbSubentityOverrule;
    friend class AcDbHighlightOverrule;
    friend class AcDbHighlightStateOverrule;
    friend class AcDbVisibilityOverrule;
    friend class AcDbGeometryOverrule;
    friend class AcDbGripEntityOverrule;

public:
    Acad::ErrorStatus  pushHighlight     (const AcDbFullSubentPath& subId,
                                          AcGiHighlightStyle        highlightStyle);
    Acad::ErrorStatus  popHighlight      (const AcDbFullSubentPath& subId);
    AcGiHighlightStyle highlightState    (const AcDbFullSubentPath& subId);

protected:
    // AcDbHighlightStateOverrule related
    ACDBCORE2D_PORT virtual Acad::ErrorStatus  subPushHighlight  (const AcDbFullSubentPath& subId,
                                          AcGiHighlightStyle        highlightStyle);
    ACDBCORE2D_PORT virtual Acad::ErrorStatus  subPopHighlight   (const AcDbFullSubentPath& subId);
    ACDBCORE2D_PORT virtual AcGiHighlightStyle subHighlightState (const AcDbFullSubentPath& subId);

    // No copy construction or assignment (but there is a copyFrom method)
    AcDbEntity (const AcDbEntity & ) = delete;
    AcDbEntity & operator = (const AcDbEntity & ) = delete;
};

// Note: makes sense to put this inline, even though it's
// a virtual, because all derived classes' dtors will call
// this dtor directly.
//
inline AcDbEntity::~AcDbEntity()
{
    // Do Nothing, AcDbObject destructor takes care of imp object.
}

inline AcString AcDbEntity::plotStyleName(Acad::ErrorStatus *pEs) const
{
    AcString sName;
    Acad::ErrorStatus es = this->plotStyleName(sName);
    if (pEs != nullptr)
        *pEs = es;
    return sName;
}

inline AcString AcDbEntity::layerName(Acad::ErrorStatus *pEs) const
{
    AcString sName;
    Acad::ErrorStatus es = this->layer(sName);
    if (pEs != nullptr)
        *pEs = es;
    return sName;
}

inline AcString AcDbEntity::linetypeName(Acad::ErrorStatus *pEs) const
{
    AcString sName;
    Acad::ErrorStatus es = this->linetype(sName);
    if (pEs != nullptr)
        *pEs = es;
    return sName;
}

inline AcString AcDbEntity::materialName(Acad::ErrorStatus *pEs) const
{
    AcString sName;
    Acad::ErrorStatus es = this->material(sName);
    if (pEs != nullptr)
        *pEs = es;
    return sName;
}

#ifdef AcDbEnt_Deprecated_ACHAR_Methods
// These next 4 inlined methods are deprecated and will be removed in a future release.
// Please use the overloads which take AcString & arg instead
//
inline ACHAR * AcDbEntity::plotStyleName() const
{
    AcString sName;
    return ::acutAcStringToAChar(sName, this->plotStyleName(sName));
}

inline ACHAR * AcDbEntity::layer() const
{
    AcString sName;
    return ::acutAcStringToAChar(sName, this->layer(sName));
}

inline ACHAR * AcDbEntity::linetype() const
{
    AcString sName;
    return ::acutAcStringToAChar(sName, this->linetype(sName));
}

inline ACHAR * AcDbEntity::material() const
{
    AcString sName;
    return ::acutAcStringToAChar(sName, this->material(sName));
}
#endif

class ADESK_NO_VTABLE AcDbObjectReactor: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbObjectReactor);
    ACDBCORE2D_PORT virtual ~AcDbObjectReactor();

    virtual void cancelled      (const AcDbObject* ) {}
    virtual void copied         (const AcDbObject* ,
                                 const AcDbObject* /*newObj*/) {}
    virtual void erased         (const AcDbObject* ,
                                 bool /*bErasing*/) {}
    virtual void goodbye        (const AcDbObject* ) {}
    virtual void openedForModify(const AcDbObject* ) {}
    virtual void modified       (const AcDbObject* ) {}
    virtual void subObjModified (const AcDbObject* ,
                                 const AcDbObject* /*subObj*/) {}
    virtual void modifyUndone   (const AcDbObject* ) {}
    virtual void modifiedXData  (const AcDbObject* ) {}
    virtual void unappended     (const AcDbObject* ) {}
    virtual void reappended     (const AcDbObject* ) {}
    virtual void objectClosed   (const AcDbObjectId ) {}

protected:
    ACDBCORE2D_PORT AcDbObjectReactor();
};

class ADESK_NO_VTABLE AcDbEntityReactor: public AcDbObjectReactor
{
public:
    ACRX_DECLARE_MEMBERS(AcDbEntityReactor);
    ACDBCORE2D_PORT ~AcDbEntityReactor();
    virtual void modifiedGraphics(const AcDbEntity* ) {}
    virtual void dragCloneToBeDeleted (const AcDbEntity* /*pOriginalObj*/,
                                       const AcDbEntity* /*pClone*/) {}
protected:
    ACDBCORE2D_PORT AcDbEntityReactor();
};

class ADESK_NO_VTABLE AcDbDatabaseReactor: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbDatabaseReactor);
    ACDBCORE2D_PORT virtual ~AcDbDatabaseReactor();

    virtual void objectAppended       (const AcDbDatabase* , const AcDbObject* ) {}
    virtual void objectUnAppended     (const AcDbDatabase* , const AcDbObject* ) {}
    virtual void objectReAppended     (const AcDbDatabase* , const AcDbObject* ) {}
    virtual void objectOpenedForModify(const AcDbDatabase* , const AcDbObject* ) {}
    virtual void objectModified       (const AcDbDatabase* , const AcDbObject* ) {}
    virtual void objectErased         (const AcDbDatabase* , const AcDbObject* ,
                                       bool /*bErased*/) {}
    virtual void headerSysVarWillChange(const AcDbDatabase* , const ACHAR* /*name*/) {}
    virtual void headerSysVarChanged   (const AcDbDatabase* , const ACHAR* /*name*/,
                                        bool /*bSuccess*/) {}
    virtual void proxyResurrectionCompleted(const AcDbDatabase* ,
                                            const ACHAR* /*appname*/, 
                                            AcDbObjectIdArray& /*objects*/) {}
    virtual void goodbye              (const AcDbDatabase* ) {}
};

class AcDbExtents2d : public AcHeapOperators
{
public:
    ACDBCORE2D_PORT AcDbExtents2d();
    ACDBCORE2D_PORT AcDbExtents2d(const AcDbExtents2d& src);
    ACDBCORE2D_PORT AcDbExtents2d(const AcGePoint2d& min, const AcGePoint2d& max);
 
    AcGePoint2d       minPoint() const { return mMinPoint; }
    AcGePoint2d       maxPoint() const { return mMaxPoint; }
    ACDBCORE2D_PORT Acad::ErrorStatus set(const AcGePoint2d& min, const AcGePoint2d& max);

    ACDBCORE2D_PORT void  addPoint (const AcGePoint2d& pt);
    ACDBCORE2D_PORT void  addExt   (const AcDbExtents2d& src);

    ACDBCORE2D_PORT void  expandBy(const AcGeVector2d& vec);
    ACDBCORE2D_PORT void  transformBy(const AcGeMatrix2d& mat);
    
    ACDBCORE2D_PORT bool operator==(const AcDbExtents2d& other) const;

private:
    AcGePoint2d    mMinPoint;
    AcGePoint2d    mMaxPoint;
};

class AcDbExtents : public AcHeapOperators
{
public:
    ACDBCORE2D_PORT AcDbExtents();
    ACDBCORE2D_PORT AcDbExtents(const AcDbExtents& src);
    ACDBCORE2D_PORT AcDbExtents(const AcGePoint3d& min, const AcGePoint3d& max);
 
    AcGePoint3d       minPoint() const { return mMinPoint; }
    AcGePoint3d       maxPoint() const { return mMaxPoint; }
    ACDBCORE2D_PORT
    Acad::ErrorStatus set(const AcGePoint3d& min, const AcGePoint3d& max);

    ACDBCORE2D_PORT
    void              addPoint (const AcGePoint3d& pt);
    ACDBCORE2D_PORT
    void              addExt   (const AcDbExtents& src);
    Acad::ErrorStatus addBlockExt(AcDbBlockTableRecord* pBTR);

    void              expandBy(const AcGeVector3d& vec);
    void              transformBy(const AcGeMatrix3d& mat);

    bool              operator==(const AcDbExtents& other) const;

private:
    AcGePoint3d    mMinPoint;
    AcGePoint3d    mMaxPoint;
};

template <> inline AcDbObjectId AcDbDatabase::getSymbolTableId<AcDbBlockTable>() const
{
    return this->blockTableId();
}
template <> inline AcDbObjectId AcDbDatabase::getSymbolTableId<AcDbLayerTable>() const
{
    return this->layerTableId();
}
template <> inline AcDbObjectId AcDbDatabase::getSymbolTableId<AcDbTextStyleTable>() const
{
    return this->textStyleTableId();
}
template <> inline AcDbObjectId AcDbDatabase::getSymbolTableId<AcDbLinetypeTable>() const
{
    return this->linetypeTableId();
}
template <> inline AcDbObjectId AcDbDatabase::getSymbolTableId<AcDbViewTable>() const
{
    return this->viewTableId();
}
template <> inline AcDbObjectId AcDbDatabase::getSymbolTableId<AcDbUCSTable>() const
{
    return this->UCSTableId();
}
template <> inline AcDbObjectId AcDbDatabase::getSymbolTableId<AcDbViewportTable>() const
{
    return this->viewportTableId();
}
template <> inline AcDbObjectId AcDbDatabase::getSymbolTableId<AcDbRegAppTable>() const
{
    return this->regAppTableId();
}
template <> inline AcDbObjectId AcDbDatabase::getSymbolTableId<AcDbDimStyleTable>() const
{
    return this->dimStyleTableId();
}

inline Acad::ErrorStatus
AcDbDatabase::getBlockTable(
    AcDbBlockTable*& pTable,
    AcDb::OpenMode mode)
{
    return getSymbolTable(pTable, mode);
}

inline Acad::ErrorStatus
AcDbDatabase::getLayerTable(
    AcDbLayerTable*& pTable,
    AcDb::OpenMode mode)
{
    return getSymbolTable(pTable, mode);
}

inline Acad::ErrorStatus
AcDbDatabase::getTextStyleTable(
    AcDbTextStyleTable*& pTable,
    AcDb::OpenMode mode)
{
    return getSymbolTable(pTable, mode);
}

inline Acad::ErrorStatus
AcDbDatabase::getLinetypeTable(
    AcDbLinetypeTable*& pTable,
    AcDb::OpenMode mode)
{
    return getSymbolTable(pTable, mode);
}

inline Acad::ErrorStatus
AcDbDatabase::getViewTable(
    AcDbViewTable*& pTable,
    AcDb::OpenMode mode)
{
    return getSymbolTable(pTable, mode);
}

inline Acad::ErrorStatus
AcDbDatabase::getUCSTable(
    AcDbUCSTable*& pTable,
    AcDb::OpenMode mode)
{
    return getSymbolTable(pTable, mode);
}

inline Acad::ErrorStatus
AcDbDatabase::getViewportTable(
    AcDbViewportTable*& pTable,
    AcDb::OpenMode mode)
{
    return getSymbolTable(pTable, mode);
}

inline Acad::ErrorStatus
AcDbDatabase::getRegAppTable(
    AcDbRegAppTable*& pTable,
    AcDb::OpenMode mode)
{
    return getSymbolTable(pTable, mode);
}

inline Acad::ErrorStatus
AcDbDatabase::getDimStyleTable(
    AcDbDimStyleTable*& pTable,
    AcDb::OpenMode mode)
{
    return getSymbolTable(pTable, mode);
}

/////////////////////////////////////////////////////////////////////////
// Text Finder API.
#define AC_SRCH_BLOCK         0x01
#define AC_SRCH_DIM_TEXT      0x02
#define AC_SRCH_TEXT          0x04
#define AC_SRCH_LINK_DESC     0x08
#define AC_SRCH_LINK_URL      0x10
#define AC_SRCH_MATCH_CASE    0x20
#define AC_SRCH_WHOLE_WORD    0x40

#define AC_SRCH_DEFAULT       0x1F

bool acdbTextFind(AcDbDatabase* pDatabase,
                  AcDbObjectIdArray& resultSet,
                  const ACHAR* findString,
                  const ACHAR* replaceString = nullptr,
                  Adesk::UInt8 searchOptions = AC_SRCH_DEFAULT,
                  const AcDbObjectIdArray& selSet = AcDbObjectIdArray());


/// <summary>
/// This function returns true if the current thread is the GS tessellation worker thread
/// </summary>
ACDBCORE2D_PORT bool acdbIsGsWorkerThread();

#pragma pack(pop)

#endif
