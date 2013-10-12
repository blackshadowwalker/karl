; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWindowPlayDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WindowPlay.h"

ClassCount=3
Class1=CWindowPlayApp
Class2=CWindowPlayDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_WINDOWPLAY_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDR_MENU1

[CLS:CWindowPlayApp]
Type=0
HeaderFile=WindowPlay.h
ImplementationFile=WindowPlay.cpp
Filter=N

[CLS:CWindowPlayDlg]
Type=0
HeaderFile=WindowPlayDlg.h
ImplementationFile=WindowPlayDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_OPEN

[CLS:CAboutDlg]
Type=0
HeaderFile=WindowPlayDlg.h
ImplementationFile=WindowPlayDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_WINDOWPLAY_DIALOG]
Type=1
Class=CWindowPlayDlg
ControlCount=1
Control1=IDC_OCX1,{6BF52A52-394A-11D3-B153-00C04F79FAA6},1342242816

[MNU:IDR_MENU1]
Type=1
Class=CWindowPlayDlg
Command1=IDC_OPEN
CommandCount=1

