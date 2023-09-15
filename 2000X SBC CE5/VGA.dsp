# Microsoft Developer Studio Project File - Name="VGA" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=VGA - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VGA.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VGA.mak" CFG="VGA - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VGA - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VGA - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VGA - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "VGA - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "VGA - Win32 Release"
# Name "VGA - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Application.cpp
# End Source File
# Begin Source File

SOURCE=.\BottomMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildView.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\CommPort.cpp
# End Source File
# Begin Source File

SOURCE=.\Connection.cpp
# End Source File
# Begin Source File

SOURCE=.\EtherPort.cpp
# End Source File
# Begin Source File

SOURCE=.\HostCommand.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\Queue.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreenKeypad.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreenObject.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreenObjectList.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TcpSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\VfdAdd_Back_Next_Button.cpp
# End Source File
# Begin Source File

SOURCE=.\VfdAlphanumeric.cpp
# End Source File
# Begin Source File

SOURCE=.\VfdChoice.cpp
# End Source File
# Begin Source File

SOURCE=.\VfdDate.cpp
# End Source File
# Begin Source File

SOURCE=.\VfdLargeRadioMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\VfdObject.cpp
# End Source File
# Begin Source File

SOURCE=.\VfdRadioButton.cpp
# End Source File
# Begin Source File

SOURCE=.\VfdRadioLargeButton.cpp
# End Source File
# Begin Source File

SOURCE=.\VfdRadioMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\VfdSubmenu.cpp
# End Source File
# Begin Source File

SOURCE=.\VfdText.cpp
# End Source File
# Begin Source File

SOURCE=.\VfdTime.cpp
# End Source File
# Begin Source File

SOURCE=.\VfdTitle.cpp
# End Source File
# Begin Source File

SOURCE=.\VfdToggle.cpp
# End Source File
# Begin Source File

SOURCE=.\VfdVariable.cpp
# End Source File
# Begin Source File

SOURCE=.\VGA.cpp
# End Source File
# Begin Source File

SOURCE=.\VGA.rc
# End Source File
# Begin Source File

SOURCE=.\VGAExitButton.cpp
# End Source File
# Begin Source File

SOURCE=.\VGANextButton.cpp
# End Source File
# Begin Source File

SOURCE=.\VGAObject.cpp
# End Source File
# Begin Source File

SOURCE=.\VGASave.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Application.h
# End Source File
# Begin Source File

SOURCE=.\BottomMenu.h
# End Source File
# Begin Source File

SOURCE=.\ChildView.h
# End Source File
# Begin Source File

SOURCE=.\ClientSocket.h
# End Source File
# Begin Source File

SOURCE=.\CommPort.h
# End Source File
# Begin Source File

SOURCE=.\Connection.h
# End Source File
# Begin Source File

SOURCE=.\EtherPort.h
# End Source File
# Begin Source File

SOURCE=.\HostCommand.h
# End Source File
# Begin Source File

SOURCE=.\MainFrame.h
# End Source File
# Begin Source File

SOURCE=.\newres.h
# End Source File
# Begin Source File

SOURCE=.\Queue.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ScreenKeypad.h
# End Source File
# Begin Source File

SOURCE=.\ScreenObject.h
# End Source File
# Begin Source File

SOURCE=.\ScreenObjectList.h
# End Source File
# Begin Source File

SOURCE=.\ServerSocket.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TcpSocket.h
# End Source File
# Begin Source File

SOURCE=.\VfdAdd_Back_Next_Button.h
# End Source File
# Begin Source File

SOURCE=.\VfdAlphanumeric.h
# End Source File
# Begin Source File

SOURCE=.\VfdChoice.h
# End Source File
# Begin Source File

SOURCE=.\VfdDate.h
# End Source File
# Begin Source File

SOURCE=.\VfdLargeRadioMenu.h
# End Source File
# Begin Source File

SOURCE=.\VfdObject.h
# End Source File
# Begin Source File

SOURCE=.\VfdRadioButton.h
# End Source File
# Begin Source File

SOURCE=.\VfdRadioLargeButton.h
# End Source File
# Begin Source File

SOURCE=.\VfdRadioMenu.h
# End Source File
# Begin Source File

SOURCE=.\VfdSubmenu.h
# End Source File
# Begin Source File

SOURCE=.\VfdText.h
# End Source File
# Begin Source File

SOURCE=.\VfdTime.h
# End Source File
# Begin Source File

SOURCE=.\VfdTitle.h
# End Source File
# Begin Source File

SOURCE=.\VfdToggle.h
# End Source File
# Begin Source File

SOURCE=.\VfdVariable.h
# End Source File
# Begin Source File

SOURCE=.\VGA.h
# End Source File
# Begin Source File

SOURCE=.\VGAExitButton.h
# End Source File
# Begin Source File

SOURCE=.\VGANextButton.h
# End Source File
# Begin Source File

SOURCE=.\VGAObject.h
# End Source File
# Begin Source File

SOURCE=.\VGASave.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VGA.ico
# End Source File
# Begin Source File

SOURCE=.\res\VGA.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
