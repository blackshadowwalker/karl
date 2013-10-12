
// ITSconfigToolKDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ITSconfigToolK.h"
#include "ITSconfigToolKDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CITSconfigToolKDlg 对话框
CITSconfigToolKDlg::CITSconfigToolKDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CITSconfigToolKDlg::IDD, pParent)
{
	img = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CITSconfigToolKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CITSconfigToolKDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CITSconfigToolKDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CITSconfigToolKDlg 消息处理程序

BOOL CITSconfigToolKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	configDlg.DoModal();
	exit(0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CITSconfigToolKDlg::OnPaint()
{
	
}

HCURSOR CITSconfigToolKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CITSconfigToolKDlg::OnBnClickedOk()
{
	
}
