; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDialogGraph
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "History.h"
LastPage=0

ClassCount=9
Class1=CHistoryApp
Class2=CHistoryDoc
Class3=CHistoryView
Class4=CMainFrame

ResourceCount=5
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Resource2=IDD_DIALOG3
Class6=CButtons
Class7=CBrowse
Resource3=IDD_DIALOG1
Class8=NoOfWeld
Resource4=IDR_MAINFRAME
Class9=CDialogGraph
Resource5=IDD_DIALOG4

[CLS:CHistoryApp]
Type=0
HeaderFile=History.h
ImplementationFile=History.cpp
Filter=N
LastObject=CHistoryApp

[CLS:CHistoryDoc]
Type=0
HeaderFile=HistoryDoc.h
ImplementationFile=HistoryDoc.cpp
Filter=N
LastObject=CHistoryDoc
BaseClass=CDocument
VirtualFilter=DC

[CLS:CHistoryView]
Type=0
HeaderFile=HistoryView.h
ImplementationFile=HistoryView.cpp
Filter=W
LastObject=CHistoryView
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=History.cpp
ImplementationFile=History.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_OPEN
Command2=ID_FILE_OPEN
Command3=ID_APP_EXIT
Command4=ID_APP_ABOUT
CommandCount=4

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[CLS:CButtons]
Type=0
HeaderFile=Buttons.h
ImplementationFile=Buttons.cpp
BaseClass=CButton
Filter=W
LastObject=CButtons
VirtualFilter=BWC

[DLG:IDD_DIALOG1]
Type=1
Class=CBrowse
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242817
Control3=IDC_BUTTON1,button,1342242817
Control4=IDC_LIST2,listbox,1353778561
Control5=IDC_STATIC_PS,static,1342308864

[CLS:CBrowse]
Type=0
HeaderFile=Browse.h
ImplementationFile=Browse.cpp
BaseClass=CDialog
Filter=D
LastObject=CBrowse
VirtualFilter=dWC

[DLG:IDD_DIALOG3]
Type=1
Class=NoOfWeld
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC_WELD,static,1342308352

[CLS:NoOfWeld]
Type=0
HeaderFile=NoOfWeld.h
ImplementationFile=NoOfWeld.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_APP_ABOUT
VirtualFilter=dWC

[DLG:IDD_DIALOG4]
Type=1
Class=CDialogGraph
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_RADIO1,button,1342177289
Control5=IDC_RADIO2,button,1342177289
Control6=IDC_RADIO3,button,1342177289
Control7=IDC_RADIO4,button,1342177289
Control8=IDC_RADIO5,button,1342177289
Control9=IDC_RADIO6,button,1342177289

[CLS:CDialogGraph]
Type=0
HeaderFile=DialogGraph.h
ImplementationFile=DialogGraph.cpp
BaseClass=CDialog
Filter=D
LastObject=CDialogGraph
VirtualFilter=dWC

