// GridViewTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GridViewTest.h"
#include "GridViewTestDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridViewTestDlg dialog

CGridViewTestDlg::CGridViewTestDlg(CWnd* pParent /*=NULL*/)
: CDialog(CGridViewTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGridViewTestDlg)
	m_nFixCols = 1;
	m_nFixRows = 1;
	m_nCols = 8;
	m_nRows = 20;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGridViewTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGridViewTestDlg)
	DDX_Control(pDX, IDC_GRID, m_Grid);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGridViewTestDlg, CDialog)
//{{AFX_MSG_MAP(CGridViewTestDlg)
ON_WM_SYSCOMMAND()
ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridViewTestDlg message handlers

BOOL CGridViewTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	InitGridView();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGridViewTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	
	CDialog::OnSysCommand(nID, lParam);
	
}

HCURSOR CGridViewTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

bool CGridViewTestDlg::InitGridView()
{
	m_RowSpin.SetRange(0,999);
	m_FixRowSpin.SetRange(0,999);
	m_FixColSpin.SetRange(0,999);
	m_ColSpin.SetRange(0,999);
	
	m_ImageList.Create(MAKEINTRESOURCE(IDB_IMAGES), 16, 1, RGB(255,255,255));
	m_Grid.SetImageList(&m_ImageList);
	
	m_Grid.EnableDragAndDrop(TRUE);
	m_Grid.GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));
	
	m_Grid.SetVirtualMode(false);
    m_Grid.SetEditable(true);
	m_Grid.SetHeaderSort(true);
	
	m_Grid.SetAutoSizeStyle();
	
	FilleDatasToGridView();    // Sets the grid mode, fills the grid
	
	m_Grid.SetFixedColumnSelection(TRUE);
    m_Grid.SetFixedRowSelection(TRUE);
	m_Grid.EnableColumnHide();
	
	return true;
}

void CGridViewTestDlg::FilleDatasToGridView() 
{
    UpdateData();
	
	m_nFixCols = 1;
	m_nFixRows = 1;
	m_nCols = 6;
	m_nRows = 16;
	
	m_Grid.DeleteAllItems();
	TRY {
		m_Grid.SetRowCount(m_nRows);
		m_Grid.SetColumnCount(m_nCols);
		m_Grid.SetFixedRowCount(m_nFixRows);
		m_Grid.SetFixedColumnCount(m_nFixCols);
	}
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		return;
	}
	END_CATCH
	
		
		for (int row = 0; row < m_Grid.GetRowCount(); row++)
        {
			for (int col = 0; col < m_Grid.GetColumnCount(); col++)
			{ 
                CString str;
				
				GV_ITEM Item;
				
				Item.mask = GVIF_TEXT;
				Item.row = row;
				Item.col = col;
				
				if (row < m_nFixRows)
                    str.Format(_T("Column %d"),col);
                else if (col < m_nFixCols) 
                    str.Format(_T("Row %d"), row);
                else 
					str.Format(_T("%d"),row*col);
                Item.strText = str;
				
				if (rand() % 10 == 1)
				{
                    COLORREF clr = RGB(rand()%128 + 128, rand()%128 + 128, rand()%128 + 128);
                    Item.crBkClr = clr;             // or - m_Grid.SetItemBkColour(row, col, clr);
                    Item.crFgClr = RGB(255,0,0);    // or - m_Grid.SetItemFgColour(row, col, RGB(255,0,0));				    
                    Item.mask    |= (GVIF_BKCLR|GVIF_FGCLR);
				}
				
				if (col < m_Grid.GetFixedColumnCount())
                {
                    Item.iImage = rand()%m_ImageList.GetImageCount();
                    Item.mask  |= (GVIF_IMAGE);
                }
				
				m_Grid.SetItem(&Item);
			}
        }
		
#if !defined(_WIN32_WCE) || (_WIN32_WCE < 211)
		m_Grid.AutoSize();
#endif
		
		UpdateData(FALSE);
}

