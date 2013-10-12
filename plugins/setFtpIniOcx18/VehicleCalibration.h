#if !defined(AFX_VEHICLECALIBRATION_H__E520E0FE_9D77_4551_9C01_C6B27B80BF64__INCLUDED_)
#define AFX_VEHICLECALIBRATION_H__E520E0FE_9D77_4551_9C01_C6B27B80BF64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VehicleCalibration.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VehicleCalibration dialog

class VehicleCalibration : public CDialog
{
	DECLARE_DYNAMIC(VehicleCalibration)
// Construction
public:
	Image *img;
	void ShowPic();
	VehicleCalibration(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(VehicleCalibration)
	enum { IDD = IDD_VEHICLE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VehicleCalibration)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(VehicleCalibration)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VEHICLECALIBRATION_H__E520E0FE_9D77_4551_9C01_C6B27B80BF64__INCLUDED_)
