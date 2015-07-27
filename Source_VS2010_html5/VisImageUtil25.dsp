# Microsoft Developer Studio Project File - Name="VisImageUtil25" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=VisImageUtil25 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VisImageUtil25.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VisImageUtil25.mak" CFG="VisImageUtil25 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VisImageUtil25 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VisImageUtil25 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VisImageUtil25 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VisImageUtil25_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VisImageUtil25_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Version.lib /nologo /dll /machine:I386 /nodefaultlib:"libc.lib libcmt.lib msvcrtd.lib libcd.lib libcmtd.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Release\VisImageUtil25.dll ..\TestVB6\VisImageUtil25.dll	copy Release\VisImageUtil25.dll ..\Distribute\VisImageUtil25.dll	copy Release\VisImageUtil25.lib ..\Distribute\VisImageUtil25.lib	copy VisImageUtil25.h ..\Distribute\VisImageUtil25.h	copy VisImageUtil25Struct.h ..\Distribute\VisImageUtil25Struct.h	copy Release\VisImageUtil25.dll ..\TestCSharp\Bin\VisImageUtil25.dll
# End Special Build Tool

!ELSEIF  "$(CFG)" == "VisImageUtil25 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VisImageUtil25_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VisImageUtil25_EXPORTS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Version.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Debug\VisImageUtil25.dll ..\TestVB6\VisImageUtil25.dll	copy Debug\VisImageUtil25.dll ..\TestCSharp\Bin\VisImageUtil25.dll
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "VisImageUtil25 - Win32 Release"
# Name "VisImageUtil25 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CImageUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\VisImageUtil25.cpp
# End Source File
# Begin Source File

SOURCE=.\VisImageUtil25.def
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CImageUtil.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\VisImageUtil25.h
# End Source File
# Begin Source File

SOURCE=.\VisImageUtil25Struct.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\VisImageUtil25.rc
# End Source File
# End Group
# Begin Group "LIB"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LIB\BASE64\base64.c
# End Source File
# Begin Source File

SOURCE=.\LIB\BASE64\base64.h
# End Source File
# Begin Source File

SOURCE=.\LIB\Block.cpp
# End Source File
# Begin Source File

SOURCE=.\LIB\Block.h
# End Source File
# Begin Source File

SOURCE=.\LIB\CDeskew.cpp
# End Source File
# Begin Source File

SOURCE=.\LIB\CDeskew.h
# End Source File
# Begin Source File

SOURCE=.\LIB\CInfoLibDIB.cpp
# End Source File
# Begin Source File

SOURCE=.\LIB\CInfoLibDIB.h
# End Source File
# Begin Source File

SOURCE=.\LIB\CRemoveLine.cpp
# End Source File
# Begin Source File

SOURCE=.\LIB\CRemoveLine.h
# End Source File
# Begin Source File

SOURCE=.\LIB\CViscryptor.cpp
# End Source File
# Begin Source File

SOURCE=.\LIB\CViscryptor.h
# End Source File
# Begin Source File

SOURCE=.\LIB\Debug.cpp
# End Source File
# Begin Source File

SOURCE=.\LIB\Debug.h
# End Source File
# Begin Source File

SOURCE=.\LIB\DLLVersion.cpp
# End Source File
# Begin Source File

SOURCE=.\LIB\DLLVersion.h
# End Source File
# Begin Source File

SOURCE=.\LIB\INFOFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\LIB\INFOFilter.h
# End Source File
# Begin Source File

SOURCE=.\LIB\InfoLib.cpp
# End Source File
# Begin Source File

SOURCE=.\LIB\InfoLib.h
# End Source File
# Begin Source File

SOURCE=.\LIB\INFOLIBBMP.h
# End Source File
# Begin Source File

SOURCE=.\LIB\INFOLIBEXT.h
# End Source File
# Begin Source File

SOURCE=.\LIB\INFOLIBGIF.h
# End Source File
# Begin Source File

SOURCE=.\LIB\INFOLIBIG.h
# End Source File
# Begin Source File

SOURCE=.\LIB\INFOLIBJ2K.h
# End Source File
# Begin Source File

SOURCE=.\LIB\INFOLIBJPEG.h
# End Source File
# Begin Source File

SOURCE=.\LIB\INFOLIBPNG.h
# End Source File
# Begin Source File

SOURCE=.\LIB\INFOLIBTIFF.h
# End Source File
# Begin Source File

SOURCE=.\LIB\Quantize.cpp
# End Source File
# Begin Source File

SOURCE=.\LIB\Quantize.h
# End Source File
# Begin Source File

SOURCE=.\LIB\Resample.h
# End Source File
# Begin Source File

SOURCE=.\LIB\SEED_KISA.cpp
# End Source File
# Begin Source File

SOURCE=.\LIB\SEED_KISA.h
# End Source File
# Begin Source File

SOURCE=.\LIB\TiffAppender.h
# End Source File
# Begin Source File

SOURCE=.\LIB\TiffParser.h
# End Source File
# Begin Source File

SOURCE=.\LIB\Util.cpp
# End Source File
# Begin Source File

SOURCE=.\LIB\Util.h
# End Source File
# Begin Source File

SOURCE=.\LIB\visReadDoc\visReadDoc.h
# End Source File
# Begin Source File

SOURCE=.\LIB\INFOLIBTIFF.lib
# End Source File
# Begin Source File

SOURCE=.\LIB\INFOLIBBMP.lib
# End Source File
# Begin Source File

SOURCE=.\LIB\INFOLIBJ2K.lib
# End Source File
# Begin Source File

SOURCE=.\LIB\INFOLIBJPEG.lib
# End Source File
# Begin Source File

SOURCE=.\LIB\VisTiffTag.lib
# End Source File
# Begin Source File

SOURCE=.\LIB\INFOLIBPNG.lib
# End Source File
# Begin Source File

SOURCE=.\LIB\INFOLIBGIF.lib
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
