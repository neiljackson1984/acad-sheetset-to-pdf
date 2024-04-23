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
#pragma once
#pragma pack (push, 8)

#ifndef ACSYNERGY_PORT
#define ACSYNERGY_PORT
#endif

class AcDbImpViewBorder;

class ACSYNERGY_PORT AcDbViewBorder : public AcDbEntity
{
    friend class AcDbAssocViewRepActionBody;
    friend class AcDbImpViewBorder;
    friend class AcDbImpViewSymbol;
public:
    ACRX_DECLARE_MEMBERS(AcDbViewBorder);

	/// <summary>
	/// Default constructor. 
	/// </summary>
	///
	/// <remarks>
	/// For internal use only.
	/// </remarks>
	///
    AcDbViewBorder();

	/// <summary>
	/// Destructor.
	/// </summary>
	///
    ~AcDbViewBorder();

    enum ViewStyleType 
    {
        kFromBase               = 0,
        kWireframeVisibleEdges  = 1,
        kWireframeHiddenEdges   = 2,
        kShadedVisibleEdges     = 3,
        kShadedHiddenEdges      = 4
    };

    enum SourceType
    {
        kSourceNotDefined   = 0,
        kInventorSource     = 1,
        kFusionSource       = 2,
        kModelSpaceSource   = 3
    };

    AcGePoint3d                 insertionPoint() const;
    double                      height() const;
    double                      width() const;
    AcDbViewBorder::SourceType  sourceType() const;
    AcString                    inventorFileReference() const;
    bool                        isFirstAngleProjection() const;
    double                      rotationAngle() const;
    AcDbViewBorder::ViewStyleType viewStyleType() const;
    double                      scale() const;
    Adesk::UInt32               shadedDPI() const;

    AcDbObjectId                viewportId() const;

    // AcGiDrawable protocols
    Adesk::Boolean      subWorldDraw(AcGiWorldDraw* pWd) override;

    // AcDbObject protocols
    Acad::ErrorStatus   subErase(Adesk::Boolean erasing) override;
    Acad::ErrorStatus   subDeepClone(AcDbObject* pOwnerObject, AcDbObject*& pClonedObject, 
                            AcDbIdMapping& idMap, Adesk::Boolean isPrimary = true) const override;
    Acad::ErrorStatus   subWblockClone(AcRxObject* pOwnerObject, AcDbObject*& pClonedObject, 
                            AcDbIdMapping& idMap, Adesk::Boolean isPrimary = true) const override;

    Acad::ErrorStatus   dwgOutFields(AcDbDwgFiler* pFiler) const override;
    Acad::ErrorStatus   dwgInFields(AcDbDwgFiler* pFiler) override;
    Acad::ErrorStatus   dxfOutFields(AcDbDxfFiler* pFiler) const override;
    Acad::ErrorStatus   dxfInFields(AcDbDxfFiler* pFiler) override;
    Acad::ErrorStatus   audit(AcDbAuditInfo* pAuditInfo) override;

    Acad::ErrorStatus   subGetStretchPoints(AcGePoint3dArray& stretchPoints) const override;
    Acad::ErrorStatus   subMoveStretchPointsAt(const AcDbIntArray & indices, 
                                               const AcGeVector3d& offset) override;


    // AcDbEntity protocols
    Acad::ErrorStatus   subGetGripPoints(AcDbGripDataPtrArray& grips, 
                                         const double curViewUnitSize, 
                                         const int gripSize, 
                                         const AcGeVector3d& curViewDir, 
                                         const int bitflags) const override;
    Acad::ErrorStatus   subGetGripPoints(AcGePoint3dArray& gripPoints, 
                                         AcDbIntArray & osnapModes, 
                                         AcDbIntArray & geomIds) const override;
    Acad::ErrorStatus   subMoveGripPointsAt(const AcDbVoidPtrArray& gripAppData,
                                         const AcGeVector3d& offset, 
                                         const int bitflags) override;
    Acad::ErrorStatus   subMoveGripPointsAt(const AcDbIntArray & indices, 
                                            const AcGeVector3d& offset) override;
    void                subGripStatus(const AcDb::GripStat status) override;

    Acad::ErrorStatus   subGetOsnapPoints(AcDb::OsnapMode osnapMode, 
                                          Adesk::GsMarker gsSelectionMark, 
                                          const AcGePoint3d& pickPoint, 
                                          const AcGePoint3d& lastPoint, 
                                          const AcGeMatrix3d& viewXform, 
                                          AcGePoint3dArray& snapPoints, 
                                          AcDbIntArray & geomIds) const override;

    Acad::ErrorStatus   subGetOsnapPoints(AcDb::OsnapMode osnapMode, 
                                          Adesk::GsMarker gsSelectionMark, 
                                          const AcGePoint3d& pickPoint, 
                                          const AcGePoint3d& lastPoint, 
                                          const AcGeMatrix3d& viewXform, 
                                          AcGePoint3dArray& snapPoints, 
                                          AcDbIntArray & geomIds, 
                                          const AcGeMatrix3d& insertionMat) const override;

    Acad::ErrorStatus   subIntersectWith(const AcDbEntity* pEnt, 
                                         AcDb::Intersect intType, 
                                         const AcGePlane& projPlane, 
                                         AcGePoint3dArray& points, 
                                         Adesk::GsMarker thisGsMarker = 0, 
                                         Adesk::GsMarker otherGsMarker = 0) const override;

    Acad::ErrorStatus   subIntersectWith(const AcDbEntity* pEnt, 
                                         AcDb::Intersect intType, 
                                         AcGePoint3dArray& points, 
                                         Adesk::GsMarker thisGsMarker = 0, 
                                         Adesk::GsMarker otherGsMarker = 0) const override;

    Acad::ErrorStatus   subTransformBy(const AcGeMatrix3d& xform) override;

    Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;

    void                subList() const override;

    Acad::ErrorStatus   subHighlight(const AcDbFullSubentPath& subId = kNullSubent, 
                                     const Adesk::Boolean highlightAll = false) const override;

    Acad::ErrorStatus   subUnhighlight(const AcDbFullSubentPath& subId = kNullSubent, 
                                       const Adesk::Boolean highlightAll = false) const override;

    Acad::ErrorStatus  subGetSubentPathsAtGsMarker(AcDb::SubentType       type,
                                                   Adesk::GsMarker        gsMark, 
                                                   const AcGePoint3d&     pickPoint,
                                                   const AcGeMatrix3d&    viewXform, 
                                                   int&                   numPaths,
                                                   AcDbFullSubentPath*&   subentPaths, 
                                                   int                    numInserts = 0,
                                                   AcDbObjectId*          entAndInsertStack
                                                                           = NULL) const override;

    Acad::ErrorStatus  subGetGsMarkersAtSubentPath(const AcDbFullSubentPath& subPath, 
                                                   AcArray<Adesk::GsMarker>& gsMarkers) const override;

    Acad::ErrorStatus  subGetSubentClassId(const AcDbFullSubentPath& path, CLSID* clsId) const override;

    void                saveAs(AcGiWorldDraw* mode, AcDb::SaveType st) override;

    Acad::ErrorStatus   setLayer(const ACHAR* newVal,
                                 Adesk::Boolean doSubents = true,
                                 bool allowHiddenLayer = false) override;
    Acad::ErrorStatus   setLayer(AcDbObjectId newVal,
                                 Adesk::Boolean doSubents = true,
                                 bool allowHiddenLayer = false) override;
    // Internal use only methods
    Acad::ErrorStatus           setViewportId(const AcDbObjectId& viewportId);
    AcGePoint2d                 centerPoint(bool exludeSketchEnts = true) const;
    AcGePoint3d                 centerPoint3d(bool exludeSketchEnts = true) const;
    Acad::ErrorStatus           getSize(AcGePoint3d& minPt,
                                        AcGePoint3d& maxPt) const;
    Acad::ErrorStatus           setSize(const AcGePoint3d& minPt,
                                        const AcGePoint3d& maxPt);
    void                        setScale(double newScale);
    Acad::ErrorStatus           recalculateBorder();

    void                        setTransientEnts(const AcArray<AcDbEntity*>& traientEnts);
    void                        setDisableUnHighlight(bool bIsDisable);
    bool                        hitTest(const AcGePoint3d& inputPt) const;

    // Internal use only - subentity related methods
    Acad::ErrorStatus getSubentColor(const AcDbSubentId& subentId, AcCmColor& color) const;
    Acad::ErrorStatus setSubentColor(const AcDbSubentId& subentId, const AcCmColor& color);

    Acad::ErrorStatus getSubentLayerId(const AcDbSubentId& subentId, AcDbObjectId& layerId) const;
    Acad::ErrorStatus setSubentLayer(const AcDbSubentId& subentId, AcDbObjectId newVal);

    Acad::ErrorStatus getSubentLinetypeId(const AcDbSubentId& subentId, AcDbObjectId& linetypeId) const;
    Acad::ErrorStatus setSubentLinetype(const AcDbSubentId& subentId, AcDbObjectId newVal);

    Acad::ErrorStatus getSubentLinetypeScale(const AcDbSubentId& subentId, double& linetypeScale) const;
    Acad::ErrorStatus setSubentLinetypeScale(const AcDbSubentId& subentId, double newVal);

    ACHAR*            getSubentPlotStyleName(const AcDbSubentId& subentId) const;
    Acad::ErrorStatus setSubentPlotStyleName(const AcDbSubentId& subentId, const ACHAR* newName);

    Acad::ErrorStatus getSubentLineWeight(const AcDbSubentId& subentId, AcDb::LineWeight& lineweight) const;
    Acad::ErrorStatus setSubentLineWeight(const AcDbSubentId& subentId, AcDb::LineWeight newVal);

    Acad::ErrorStatus getSubentVisibility(const AcDbSubentId& subentId, AcDb::Visibility& visVal) const;
    Acad::ErrorStatus setSubentVisibility(const AcDbSubentId& subentId, AcDb::Visibility newVal);

    Acad::ErrorStatus subentIdToNestedEnts (const AcDbSubentId& subentId, AcDbFullSubentPathArray &nestedEnts) const;


    Acad::ErrorStatus subGetGeomExtents(AcDbExtents& extents) const override;
private:
    AcGeMatrix3d            transientXform() const;

private:
    AcDbImpViewBorder*          mpAcDbImpViewBorder;

    static  double              sViewBoderOffset;
};


#pragma pack (pop)
