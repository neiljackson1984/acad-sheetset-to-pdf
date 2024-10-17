#!pwsh
. { #initialize
    import-module neil-utility1
    set-alias  TlbImp "C:\Program Files (x86)\Microsoft SDKs\Windows\v10.0A\bin\NETFX 4.8.1 Tools\x64\TlbImp.exe"


    .{
        $pathOfTranscriptFile = (Join-Path $env:temp "$(get-date -format yyyyMMdd_HHmmss).transcript")
        @{
            Path = $pathOfTranscriptFile
            IncludeInvocationHeader=$True
        } | % { Start-Transcript @_ }
        ##code $pathOfTranscriptFile
    }

}; return


<#  2024-10-15-1537

see (https://forums.autodesk.com/t5/net/referencing-acsmcomponents-dll-error/td-p/11846171)



exploring the possibility of parsing sheetset files ourselves rather than relying on the AcSmComponents com library.

see (https://github.com/triroakenshield/AcSmSheetSetMgr)



#>



$progID = "AcSmComponents.AcSmSheetSetMgr.25"
$progID = "AutoCAD.Application"
$progID = "AutoCAD.Application.25"

gi "registry::HKEY_LOCAL_MACHINE\SOFTWARE\Classes\$progID"
$clsid = (gi "registry::HKEY_CLASSES_ROOT\$progID\CLSID").GetValue("")
gi "registry::HKEY_LOCAL_MACHINE\SOFTWARE\Classes\CLSID\$($clsid))"

gi (join-path "registry::HKEY_CLASSES_ROOT\CLSID" $clsid) 
gci (join-path "registry::HKEY_CLASSES_ROOT\CLSID" $clsid) 
gi (join-path "registry::HKEY_CLASSES_ROOT\CLSID" $clsid) | % {$_.GetValue("")}
gp (join-path "registry::HKEY_CLASSES_ROOT\CLSID" $clsid)
gci (join-path "registry::HKEY_CLASSES_ROOT\CLSID" $clsid) | fl
gi (join-path "registry::HKEY_CLASSES_ROOT\CLSID" "$($clsid)/TypeLib")| % {$_.GetValue("")}



gci "registry::HKEY_CLASSES_ROOT\AcSmComponents*" |% {$_.Name} | sort
gi "registry::HKEY_CLASSES_ROOT\*axdb*" |% {$_.Name} | sort
gi "registry::HKEY_CLASSES_ROOT\AutoCAD.Application" |% {$_.Name} | sort
(join-path "registry::HKEY_CLASSES_ROOT\CLSID" $((gi "registry::HKEY_CLASSES_ROOT\ObjectDBX.AxDbDocument.25\CLSID").GetValue("")) "TypeLib") |%  {(gi $_).GetValue("")} 
(join-path "registry::HKEY_CLASSES_ROOT\CLSID" $((gi "registry::HKEY_CLASSES_ROOT\AutoCAD.Application\CLSID").GetValue("")) "TypeLib") |%  {(gi $_).GetValue("")} 
gp (join-path "registry::HKEY_CLASSES_ROOT\CLSID" $((gi "registry::HKEY_CLASSES_ROOT\ObjectDBX.AxDbDocument.25\CLSID").GetValue("")))
gci (join-path "registry::HKEY_CLASSES_ROOT\CLSID" $((gi "registry::HKEY_CLASSES_ROOT\ObjectDBX.AxDbDocument.25\CLSID").GetValue("")))
(join-path "registry::HKEY_CLASSES_ROOT\CLSID" $((gi "registry::HKEY_CLASSES_ROOT\ObjectDBX.AxDbDocument.25\CLSID").GetValue("")) "InProcServer32")|%  {(gi $_).GetValue("")} 

findFileInProgramFiles  AcSmComponents.dll

##$sheetSetMgr = New-Object -ComObject "AcSmComponents.AcSmSheetSetMgr"
$sheetSetMgr  = New-Object -ComObject "AcSmComponents.AcSmSheetSetMgr.25"
$doc  = New-Object -ComObject "ObjectDBX.AxDbDocument.25"
$sheetdb = $sheetSetMgr.OpenDatabase("C:\work\2020-08-13_219004_shaffer\main_sheetset.dst",$false)
Add-Type -LiteralPath "C:\work\acad-sheetset-to-pdf\acad-sheetset-to-pdf\objectarx-for-autocad-2025-win-64bit\inc-x64\acsmcomponents25.tlb"
powershell
$sheetSetMgr | get-member

get-command -all tlbimp
findfileinprogramfiles tlbimp.exe

gci -file -recurse -force $env:localappdata -filter "tlbimp.exe"
$psversiontable | fl *
[Environment]::Version |% {$_.ToString()}

#%%
pwsh -c {
    set-alias  TlbImp "C:\Program Files (x86)\Microsoft SDKs\Windows\v10.0A\bin\NETFX 4.8.1 Tools\x64\TlbImp.exe"
    $typesByTlbFileName = @{}
    foreach($pathOfTlbFile  in @(
        "C:\work\acad-sheetset-to-pdf\acad-sheetset-to-pdf\objectarx-for-autocad-2025-win-64bit\inc-x64\acsmcomponents25.tlb"
        "C:\work\acad-sheetset-to-pdf\acad-sheetset-to-pdf\objectarx-for-autocad-2025-win-64bit\inc-x64\axdb25enu.tlb"
    )){
        $pathOfAssemblyFile = $(join-path $env:temp "$(new-guid).dll")
        TlbImp $pathOfTlbFile /out:$pathOfAssemblyFile /namespace:Autodesk.AutoCAD.Interop
        ## gi $pathOfAssemblyFile
        $typesByTlbFileName[(split-path -leaf $pathOfTlbFile)] = @(
            Add-Type -PassThru -LiteralPath $pathOfAssemblyFile
        )
    }

    $acSmSheetSetMgrClass = [Autodesk.AutoCAD.Interop.AcSmSheetSetMgrClass]::new()


    $sheetdb = $acSmSheetSetMgrClass.OpenDatabase("C:\work\2020-08-13_219004_shaffer\main_sheetset.dst",$false)
}
#%%


$typesByTlbFileName.Values
$typesByTlbFileName.Values
$typesByTlbFileName['acsmcomponents25.tlb'] |? {$_.Name -eq "AcSmSheetSetMGr"} |% {$_.FullName}

TlbImp /?

findFileInProgramFiles "AcSmComponents*"
findFileInProgramFiles "AXDBLib*"
findFileInProgramFiles "AXDB*"

$x = Add-Type -PassThru -LiteralPath "C:\Program Files\Autodesk\AutoCAD 2025\AcSmComponents.Interop.dll"
Add-Type -LiteralPath "C:\Program Files\Autodesk\AutoCAD 2025\axdb.dll"

[Autodesk.AutoCAD.Interop.AcSmSheetSetMgr]

$acSmSheetSetMgr | get-member

#%%
.{
    @{
        recurse=$true 
        file=$true
        Path = @(
            (split-path -parent  (get-command acad).Path ) 
            (join-path $env:programfiles "Common Files/Autodesk Shared")
            "C:\work\acad-sheetset-to-pdf\acad-sheetset-to-pdf\objectarx-for-autocad-2025-win-64bit"
        )
        include = @(
            ## "AcDbMgd.dll"
            ## "AcMgd.dll"
            ## "AcCoreMgd.dll"
            ## "Autodesk.AutoCAD.Interop.Common.dll"
            ## "Autodesk.AutoCAD.Interop.dll"
            ##"*AXDBLib*"
            "*AXDB*"
            "*acax*"
            "*acpal*"
        )
    } | % {gci @_} |
    select -expand fullname 
}
#%%

gci -recurse -file (split-path -parent  (get-command acad).Path ),"C:\work\acad-sheetset-to-pdf\acad-sheetset-to-pdf\objectarx-for-autocad-2025-win-64bit" -filter "*interop*" |% {$_.fullname}

#%%
.{
    $typesFromAcSmComponentsInteropAssembly = @(Add-Type -PassThru -LiteralPath "C:\Program Files\Autodesk\AutoCAD 2025\AcSmComponents.Interop.dll")
    $typesFromAutocadInteropAssembly        = @(Add-Type -PassThru -LiteralPath "C:\Program Files\Autodesk\AutoCAD 2025\Autodesk.AutoCAD.Interop.dll")
    $typesFromAcDbMgdAssembly        = @(Add-Type -PassThru -LiteralPath "C:\Program Files\Autodesk\AutoCAD 2025\acdbmgd.dll")
    $typesFromAcCoreMgdAssembly        = @(Add-Type -PassThru -LiteralPath "C:\Program Files\Autodesk\AutoCAD 2025\accoremgd.dll")


}
#%%



$typesFromAcSmComponentsInteropAssembly.Count
$typesFromAutocadInteropAssembly.Count
$typesFromAcDbMgdAssembly.Count
$typesFromAcSmComponentsInteropAssembly |? {$_.Name -eq "AcSmSheetSetMgr"}  |% {$_.FullName}

$typesFromAcDbMgdAssembly |% {$_.FullName} | sort

[Autodesk.AutoCAD.Interop.AcSmSheetSetMgr] | fl *
$sheetSetMgr = [Autodesk.AutoCAD.Interop.AcSmSheetSetMgr]::new()
[Autodesk.AutoCAD.Interop.AcSmSheetSetMgr] | get-member
[Autodesk.AutoCAD.Interop.AcSmSheetSetMgr].DeclaredConstructors
[Autodesk.AutoCAD.Interop.AcSmSheetSetMgr].DeclaredMembers

$typesFromAutocadInteropAssembly |%  {$_.FullName} | sort
$typesFromAcSmComponentsInteropAssembly |%  {$_.FullName} | sort

[Autodesk.AutoCAD.Interop.AcSmSheetSetMgrClass].DeclaredMembers
[Autodesk.AutoCAD.Interop.AcSmSheetSetMgrClass].DeclaredConstructors

$acSmSheetSetMgrClass = [Autodesk.AutoCAD.Interop.AcSmSheetSetMgrClass]::new()

$acSmSheetSetMgrClass.GetType()
$acSmSheetSetMgrClass.GetType().FullName
$acSmSheetSetMgrClass | get-member
$sheetdb = $acSmSheetSetMgrClass.OpenDatabase("C:\work\2020-08-13_219004_shaffer\main_sheetset.dst",$false)


gci -file -force -recurse "C:\work\acad-sheetset-to-pdf\acad-sheetset-to-pdf\objectarx-for-autocad-2025-win-64bit"  -filter "*axdb*" |% {$_.FullNAme}
gci -file -force -recurse "C:\Program Files\Autodesk\AutoCAD 2025"  -filter "*Ac*Mgd*" |% {$_.FullNAme}

Get-WmiObject Win32_Thread -Filter "ProcessHandle = $($PID)" | Select-Object ProcessHandle, ThreadId, ApartmentState

get-command *autocad*
code --goto (getcommandpath getAutocadComObject)


[TQ84.COM]::getActiveObject('AutoCAD.Application.25')  

taskkill /t /f  /im acad.exe

gci "registry::"
gci "registry::HKEY_LOCAL_MACHINE"
gci "registry::HKEY_LOCAL_MACHINE\SYSTEM"
gci "registry::HKEY_LOCAL_MACHINE\SOFTWARE\Classes"

get-command -all dotnet


get-autocadComObject

$acSmSheetSetMgr = [TQ84.COM]::getActiveObject('AcSmComponents.AcSmSheetSetMgr') 
$acSmSheetSetMgr = [TQ84.COM]::getActiveObject('AcSmComponents.AcSmSheetSetMgr.25') 




#%%
&{  # load several useful AutoCAD assemblies (dll files) into memory,
    
    $typesByAssemblyFilename  = @{}
    $pathsOfAssemblyFiles = @(
        gci -recurse -file (split-path (get-command acad).Path -parent) -include @(
            "AcDbMgd.dll"
            "AcMgd.dll"
            "AcCoreMgd.dll"
            "Autodesk.AutoCAD.Interop.Common.dll"
            "Autodesk.AutoCAD.Interop.dll"
            "AcSmComponents.Interop.dll"
        ) | 
        select -expand fullname
    )
    
    ##$pathsOfAssemblyFiles | % { [System.Reflection.Assembly]::LoadFrom($_) }  | out-null

    Add-Type -LiteralPath $pathsOfAssemblyFiles

    foreach($pathOfAssemblyFile in $pathsOfAssemblyFiles){
        ## [System.Reflection.Assembly]::LoadFrom($pathOfAssemblyFile) 
       ##  $typesByAssemblyFilename[(split-path -leaf $pathOfAssemblyFile)]  = @(Add-Type -PassThru -LiteralPath $pathOfAssemblyFile)
    }


    $pathsOfAssemblyFilesGeneratedByTlbImp = @()
    if($true){
        set-alias  TlbImp "C:\Program Files (x86)\Microsoft SDKs\Windows\v10.0A\bin\NETFX 4.8.1 Tools\x64\TlbImp.exe"
        $typesByTlbFileName = @{}
        foreach($pathOfTlbFile  in @(
            "C:\work\acad-sheetset-to-pdf\acad-sheetset-to-pdf\objectarx-for-autocad-2025-win-64bit\inc-x64\acsmcomponents25.tlb"
            "C:\work\acad-sheetset-to-pdf\acad-sheetset-to-pdf\objectarx-for-autocad-2025-win-64bit\inc-x64\axdb25enu.tlb"
            "C:\work\acad-sheetset-to-pdf\acad-sheetset-to-pdf\objectarx-for-autocad-2025-win-64bit\inc-x64\acax25ENU.tlb"
        )){
            $pathOfDirectoryForTlbImpOutput = (join-path $env:temp "$(new-guid)")
            New-Item -itemtype Directory -force  -Path $pathOfDirectoryForTlbImpOutput | out-null
            push-location  $pathOfDirectoryForTlbImpOutput
            
            ## $pathOfAssemblyFile = $(join-path $env:temp "$(new-guid).dll")
            TlbImp @(
                $pathOfTlbFile 
                "/machine:x64"
                ##"/out:$($pathOfAssemblyFile)" 
                ##"/namespace:Autodesk.AutoCAD.Interop"
            )
            ## gi $pathOfAssemblyFile
            $pathOfAssemblyFile = gci . | select -first 1
            $pathsOfAssemblyFilesGeneratedByTlbImp  += $pathOfAssemblyFile
            write-host "pathOfAssemblyFile: $pathOfAssemblyFile"
            $typesByTlbFileName[(split-path -leaf $pathOfTlbFile)] = @(
                Add-Type -PassThru -LiteralPath $pathOfAssemblyFile
            )
            pop-location
        }
    
    }
}
#%%
[Autodesk.AutoCAD.Interop.AcSmDatabase] $acSmDatabase = ([Autodesk.AutoCAD.Interop.AcSmDatabase] ([Autodesk.AutoCAD.Interop.AcSmDatabaseClass]::new()) )
$x =  [Autodesk.AutoCAD.Interop.AcSmDatabaseClass]::new()
$acSmDatabase.GetType()

## $acSmSheetSetMgr =  [ACSMCOMPONENTS25Lib.AcSmSheetSetMgrClass]::new()
## $acSmDatabase.LockDb($acSmSheetSetMgr )

$acSmDatabase.LockDb($x)
$acSmDatabase.LoadFromFile("C:\work\2020-08-13_219004_shaffer\main_sheetset.dst")

$acSmDatabase.GetDbVersion()
$acSmDatabase.GetLockStatus()
#%%
[System.Runtime.Loader.AssemblyLoadContext]::Default.Assemblies | get-member
[AppDomain]::CurrentDomain.GetType().FullName
[System.Runtime.Loader.AssemblyLoadContext]::Default.GetType().FullName

[AppDomain]::CurrentDomain.GetAssemblies() |% {$_.ExportedTypes} 
[AppDomain]::CurrentDomain.GetAssemblies() |? {(split-path -leaf $_.Location) -eq  "AcSmComponents.Interop.dll"} 
[AppDomain]::CurrentDomain.GetAssemblies() |? {(split-path -leaf $_.Location) -eq  "AcSmComponents.Interop.dll"} |% {$_.ExportedTypes} |% {$_.FullName} | sort
[AppDomain]::CurrentDomain.GetAssemblies() |? {(split-path -leaf $_.Location) -eq  "Autodesk.AutoCAD.Interop.dll"} |% {$_.ExportedTypes} |% {$_.FullName} | sort
[AppDomain]::CurrentDomain.GetAssemblies() |? {(split-path -leaf $_.Location) -eq  "AcMgd.dll"} |% {$_.ExportedTypes} |% {$_.FullName} | sort
[AppDomain]::CurrentDomain.GetAssemblies() |% {$_.ExportedTypes} |? {$_.FullName -match "ApplicationServices"} |% {$_.FullName} | sort
[AppDomain]::CurrentDomain.GetAssemblies() |? {(split-path -leaf $_.Location) -eq  "AcMgd.dll"} |% {$_.ExportedTypes} |? {$_.FullName -match "ApplicationServices"} |% {$_.FullName} | sort

[AppDomain]::CurrentDomain.GetAssemblies()[-2] | fl *

[AppDomain]::CurrentDomain.GetAssemblies() |% {$_.ExportedTypes} |? {$_.FullName -match "sheetset"} |%  {$_.FullName}

<# see  (https://help.autodesk.com/view/OARX/2024/CHS/?guid=GUID-BFFF308E-CC10-4C56-A81E-C15FB300EB70) #>

[Autodesk.AutoCAD.ApplicationServices.Application] | fl *

[Autodesk.AutoCAD.ApplicationServices.Core.Application].DeclaredMEmbers  | select -expand Name | sort
[Autodesk.AutoCAD.ApplicationServices.Application].DeclaredMEmbers  | select -expand Name | sort
[Autodesk.AutoCAD.ApplicationServices.Application].DeclaredMEmbers  | ? {$_.Name -eq 'get_AcadApplication'}
[Autodesk.AutoCAD.ApplicationServices.Application].DeclaredMEmbers  | ? {$_.Name -eq 'Initialize'}
[Autodesk.AutoCAD.ApplicationServices.Application].DeclaredMEmbers |? {$_.ISStatic}  | select -expand Name | sort
[Autodesk.AutoCAD.ApplicationServices.Application].DeclaredMEmbers |? {$_.IsPublic} |? {$_.ISStatic}  | select -expand Name | sort
[Autodesk.AutoCAD.ApplicationServices.Core.Application].DeclaredMEmbers |? {$_.IsPublic} |? {$_.ISStatic}  | select -expand Name | sort
[Autodesk.AutoCAD.ApplicationServices.Core.Application].DeclaredMethods |? {$_.IsPublic} |? {$_.ISStatic}  | select -expand Name | sort
[Autodesk.AutoCAD.ApplicationServices.Core.Application].DeclaredMEmbers |? {$_.ISStatic}  | select -expand Name | sort

$x = [Autodesk.AutoCAD.ApplicationServices.Core.Application]::new()
[Autodesk.AutoCAD.ApplicationServices.Core.Application].DeclaredConstructors|  fl *
[Autodesk.AutoCAD.ApplicationServices.Core.Application].DeclaredConstructors| get-member

[Autodesk.AutoCAD.ApplicationServices.Core.Application].DeclaredConstructors[1].GetParameters()

[Autodesk.AutoCAD.ApplicationServices.Application].GetMethod('get_AcadApplication').GetParameters()

[Autodesk.AutoCAD.ApplicationServices.Core.Application]::get_Version()

[Autodesk.AutoCAD.ApplicationServices.Core.Application] | get-member
[Autodesk.AutoCAD.ApplicationServices.Application]::Initialize()

[Autodesk.AutoCAD.ApplicationServices.Core.Application].GetMEthod("Invoke")
[Autodesk.AutoCAD.ApplicationServices.Core.Application]::get_DocumentManager()
[Autodesk.AutoCAD.ApplicationServices.Application]::AcadApplication


$acSmSheetSetMgr =  [ACSMCOMPONENTS25Lib.AcSmSheetSetMgr]::new()
$acSmSheetSetMgr = NEw-Object ACSMCOMPONENTS25Lib.AcSmSheetSetMgrClass
$acSmSheetSetMgr.GetType().FullName

TlbImp /?

$sheetdb = $acSmSheetSetMgr.OpenDatabase("C:\work\2020-08-13_219004_shaffer\main_sheetset.dst",$false)

<# copied  from https://github.com/triroakenshield/AcSmSheetSetMgr/blob/fcb337ef714ef56617005503c0a923d3da6564ba/AcSmDatabase.cs#L86 #>

$encode = [byte[]] @(
    0x8C, 0x8F, 0x8E, 0x89, 0x88, 0x8B, 0x8A, 0x85, 0x84, 0x87, 0x86, 0x81, 0x80, 0x83, 0x82, 0x8D,
    0xBC, 0xBF, 0xBE, 0xB9, 0xB8, 0xBB, 0xBA, 0xB5, 0xB4, 0xB7, 0xB6, 0xB1, 0xB0, 0xB3, 0xB2, 0xAD,
    0xAC, 0xAF, 0xAE, 0xA9, 0xA8, 0xAB, 0xAA, 0xA5, 0xA4, 0xA7, 0xA6, 0xA1, 0xA0, 0xA3, 0xA2, 0xDD,
    0xDC, 0xDF, 0xDE, 0xD9, 0xD8, 0xDB, 0xDA, 0xD5, 0xD4, 0xD7, 0xD6, 0xD1, 0xD0, 0xD3, 0xD2, 0xCD,
    0xCC, 0xCF, 0xCE, 0xC9, 0xC8, 0xCB, 0xCA, 0xC5, 0xC4, 0xC7, 0xC6, 0xC1, 0xC0, 0xC3, 0xC2, 0xFD,
    0xFC, 0xFF, 0xFE, 0xF9, 0xF8, 0xFB, 0xFA, 0xF5, 0xF4, 0xF7, 0xF6, 0xF1, 0xF0, 0xF3, 0xF2, 0xED,
    0xEC, 0xEF, 0xEE, 0xE9, 0xE8, 0xEB, 0xEA, 0xE5, 0xE4, 0xE7, 0xE6, 0xE1, 0xE0, 0xE3, 0xE2, 0x1D,
    0x1C, 0x1F, 0x1E, 0x19, 0x18, 0x1B, 0x1A, 0x15, 0x14, 0x17, 0x16, 0x11, 0x10, 0x13, 0x12, 0xD,
    0xC,  0xF,  0xE,  0x9,  0x8,  0xB,  0xA,  0x5,  0x4,  0x7,  0x6,  0x1,  0x0,  0x3,  0x2,  0x3D,
    0x3C, 0x3F, 0x3E, 0x39, 0x38, 0x3B, 0x3A, 0x35, 0x34, 0x37, 0x36, 0x31, 0x30, 0x33, 0x32, 0x2D,
    0x2C, 0x2F, 0x2E, 0x29, 0x28, 0x2B, 0x2A, 0x25, 0x24, 0x27, 0x26, 0x21, 0x20, 0x23, 0x22, 0x5D,
    0x5C, 0x5F, 0x5E, 0x59, 0x58, 0x5B, 0x5A, 0x55, 0x54, 0x57, 0x56, 0x51, 0x50, 0x53, 0x52, 0x4D,
    0x4C, 0x4F, 0x4E, 0x49, 0x48, 0x4B, 0x4A, 0x45, 0x44, 0x47, 0x46, 0x41, 0x40, 0x43, 0x42, 0x7D,
    0x7C, 0x7F, 0x7E, 0x79, 0x78, 0x7B, 0x7A, 0x75, 0x74, 0x77, 0x76, 0x71, 0x70, 0x73, 0x72, 0x6D,
    0x6C, 0x6F, 0x6E, 0x69, 0x68, 0x6B, 0x6A, 0x65, 0x64, 0x67, 0x66, 0x61, 0x60, 0x63, 0x62, 0x9D,
    0x9C, 0x9F, 0x9E, 0x99, 0x98, 0x9B, 0x9A, 0x95, 0x94, 0x97, 0x96, 0x91, 0x90, 0x93, 0x92, 0xFF 
)

$types = @(Add-Type -passthru -path "C:\Users\Admin\AppData\Local\Temp\4bcc81de-04a5-4527-80e0-1c6cc5f09cd0\AcSmSheetSetMgr\bin\Debug\AcSmSheetSetMgr.dll")

$types | % {$_.FullName}

$acSmDatabase = [AcSmSheetSetMgr.AcSmDatabase]::LoadDst("C:\work\2020-08-13_219004_shaffer\main_sheetset.dst")

$acSmDatabase | get-member
$acSmDatabase.GetAllSheetTitle()
$xmlDocument = $acSmDatabase | get-member


$pathOfDstFile = "C:\work\2020-08-13_219004_shaffer\main_sheetset.dst"
$acSmDatabase = [AcSmSheetSetMgr.AcSmDatabase]::LoadDst($pathOfDstFile)
$x = (join-path $env:temp "$(new-guid).xml");$acSmDatabase.SaveXML($x);code $x
$acSmSheetSet = $acSmDatabase.FindChild("AcSmSheetSet")
$acSmFileReferenceOfDwgFileContainingThePageSetup = $acSmSheetSet.FindChild("AcSmFileReference", "AltPageSetups")
$relativePathOfDwgFileContainingThePageSetup = $acSmFileReferenceOfDwgFileContainingThePageSetup.FindChild("AcSmProp","Relative_FileName").Value
$pathOfDwgFileContainingThePageSetup = [IO.Path]::GetFullPath([IO.Path]::Join($pathOfDstFile, "..", $relativePathOfDwgFileContainingThePageSetup))
$sheets = $acSmSheetSet.FindAllChild("AcSmSheet")
#%%
foreach($sheet in $sheets){
    $acSmAcDbLayoutReference = $sheet.FindChild("AcSmAcDbLayoutReference")
    $pathOfDwgFileContainingTheLayout = [IO.Path]::GetFullPath(
        [IO.Path]::Join(
            $pathOfDstFile,
            "..", 
            $acSmAcDbLayoutReference.FindChild("AcSmProp","Relative_FileName").Value
        )
    )

    write-host "==============="
    @(
        {$sheet.ID}
        {$sheet.GetProperty('Title').Value}
        {$sheet.GetProperty('Number').Value}
        {$acSmAcDbLayoutReference.FindChild("AcSmProp","Relative_FileName").Value}
        {$pathOfDwgFileContainingTheLayout}
        {$acSmAcDbLayoutReference.FindChild("AcSmProp","Name").Value}
    ) |% {write-host "$($_): $(& $_)"}

}

#%%
$sheets[0] | fl *
$sheets[0].GetProperty("Number").Value
gi ([IO.Path]::Join($pathOfDstFile, "..")) |% {$_.FullName}

($sheetSet.FindChild("AcSmFileReference", "AltPageSetups"))

$sheetSet.GetType()

<# see https://www.cadtutor.net/forum/topic/54734-disadvantage-of-sheetsets/ #>

gci -file  -force (split-path -parent  (get-command acad).Path ) -filter "*.dll" |% {$_.Name}  | sort

nuget search AcSmSheetSetMgr

cd "C:\work\acad-sheetset-to-pdf"
git status
braid add --help
braid add "https://github.com/triroakenshield/AcSmSheetSetMgr" "acad-sheetset-to-pdf/AcSmSheetSetMgr"