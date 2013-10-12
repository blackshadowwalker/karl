; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGridViewTestDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "GridViewTest.h"

ClassCount=4
Class1=CGridViewTestApp
Class2=CGridViewTestDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_GRIDVIEWTEST_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=CMyDlg
Resource4=IDD_GRIDVIEW_DLG

[CLS:CGridViewTestApp]
Type=0
HeaderFile=GridViewTest.h
ImplementationFile=GridViewTest.cpp
Filter=N

[CLS:CGridViewTestDlg]
Type=0
HeaderFile=GridViewTestDlg.h
ImplementationFile=GridViewTestDlg.cpp
Filter=D
LastObject=CGridViewTestDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=GridViewTestDlg.h
ImplementationFile=GridViewTestDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_GRIDVIEWTEST_DIALOG]
Type=1
Class=CGridViewTestDlg
ControlCount=1
Control1=IDC_GRID,MFCGridCtrl,1342242816

[DLG:IDD_GRIDVIEW_DLG]
Type=1
Class=CMyDlg
ControlCount=1
Control1=IDC_GRID2,,1342242816

[CLS:CMyDlg]
Type=0
HeaderFile=MyDlg.h
ImplementationFile=MyDlg.cpp
BaseClass=CDialog
Filter=D

