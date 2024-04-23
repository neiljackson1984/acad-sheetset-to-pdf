/////////////////////////////////////////////////////////////////////////////
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

#pragma once

// The AcFilterablePropertyContext enum identifies whether the framework is
// dealing with creating property filters for the "Quick Properties" feature or
// the "Rollover Tooltips" feature.
typedef
#ifndef __clang__
__declspec(uuid("a0999d56-72b5-4e7c-9c9b-a041c4274c24"))
#endif
enum AcFilterablePropertyContext
{
    acQuickPropertiesContext = 0,
    acTooltipContext = 1
} AcFilterablePropertyContext;