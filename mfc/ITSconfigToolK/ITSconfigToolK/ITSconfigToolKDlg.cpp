
// ITSconfigToolKDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ITSconfigToolK.h"
#include "ITSconfigToolKDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CITSconfigToolKDlg �Ի���
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


// CITSconfigToolKDlg ��Ϣ�������

BOOL CITSconfigToolKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	configDlg.DoModal();
	exit(0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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
