#if !defined(AFX_LANECONFIG_H__42A38FF5_70DC_4A31_A902_83B7915F9512__INCLUDED_)
#define AFX_LANECONFIG_H__42A38FF5_70DC_4A31_A902_83B7915F9512__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LaneConfig.h : header file
//

#include "ConfigType.h"

/////////////////////////////////////////////////////////////////////////////
// LaneConfig dialog
enum tagDrawType{ DrawRegion, Line};
typedef enum tagDrawType DrawType;

class LaneConfig : public CDialog
{
// Construction
public:

	CPoint M2CConvertPt(CPoint cpt);	// convert image point to screen point
	CPoint C2MConvertPt(CPoint cpt);	// convert screen point to image point

	LaneConfig(CWnd* pParent = NULL);   // standard constructor
	Tel_LaneConfig tempLaneConfig;
	Image *img;
	Image *pConfigImage;
	bool startDraw ;
protected:
	bool modified;
	int ptSum;
	DrawType drawtype;
	void UpdateShow();

	static bool inited;
	CDC* m_dc;
	CComboBox m_number;
	CComboBox m_ID;
	CComboBox m_configtype;
	CStatic m_src;

//	CPoint rectPoint[4]; //车道的四个点
//	Tel_Point tempPoint[4];

	CPoint pt[4][4];//Region points
	CPoint lpt[4][2];// Line points
	int ptNum;		// Region第几个区域
	int ptNum_i;	// Region第ptNum个区域中的第ptNum_i个点
	int lptNum;		// Line第几个区域
	int lptNum_i;	// Line第ptNum个区域中的第ptNum_i个点

	int iDraw_Point[4];

	int iPointIndex;

	void ShowPic();
	void DrawImage();
//	int JudgPoints(CPoint point,CRect r);


// Dialog Data
	//{{AFX_DATA(LaneConfig)
	enum { IDD = IDD_LANE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LaneConfig)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(LaneConfig)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnStartDraw();
	afx_msg void OnSave();
	afx_msg void OnForgo();
	afx_msg void OnReturn();
	afx_msg void OnSelchangeConfigtype();
	afx_msg void OnSetfocusConfigtype();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetfocusNum();
	afx_msg void OnSelchangeNum();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDeleteRgn();
	// 更新界面的区域或线
	long UpdateDraws(void);
	CString m_info;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LANECONFIG_H__42A38FF5_70DC_4A31_A902_83B7915F9512__INCLUDED_)
