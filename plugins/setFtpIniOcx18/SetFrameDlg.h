#if !defined(AFX_SETFRAMEDLG_H__C2F9DC48_D708_42AF_9591_424CD60166D1__INCLUDED_)
#define AFX_SETFRAMEDLG_H__C2F9DC48_D708_42AF_9591_424CD60166D1__INCLUDED_


#include "TimeConfigDlg.h"	// Added by ClassView
#include "OperationConfig.h"	// Added by ClassView
#include "VehicleCalibration.h"	// Added by ClassView
#include "LightConfig.h"	// Added by ClassView
#include "LaneConfig.h"
#include "SetDlg.h"	// Added by ClassView
#include "UpDownFile.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetFrameDlg.h : header file
//
#include "Progress.h"
/////////////////////////////////////////////////////////////////////////////
// CSetFrameDlg dialog

class CSetFrameDlg : public CDialog
{
// Construction
public:
	CSetFrameDlg(CWnd* pParent = NULL);   // standard constructor

	bool readConfig();
	int m_r, m_g, m_b;
	FTP_THREAD_DATA  ftpData ;
	LRESULT OnTFFtpMessage(WPARAM wParam, LPARAM lParam);

protected:	
	CBrush m_brush;
	CTimeConfigDlg m_timeConfigDlg;
	long size;
	CProgress *m_progress;
	
	CSetDlg m_setDlg;
	bool ReadFileInfo();
	Image *img;
	void ShowPic(Image* img);
	LaneConfig m_LaneConfig;
	LightConfig m_LightConfig;
	OperationConfig m_OperationConfig;
	VehicleCalibration m_VehicleCalibration;
	

// Dialog Data
	//{{AFX_DATA(CSetFrameDlg)
	enum { IDD = IDD_SET_FRAM_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetFrameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation


	// Generated message map functions
	//{{AFX_MSG(CSetFrameDlg)
public:	
	afx_msg void OnVehicle();
	afx_msg void OnLight();
	afx_msg void OnLane();
	afx_msg void OnDoconfig();
	afx_msg void OnUploadIni();
	afx_msg void OnDownLoadIni();
	afx_msg void OnBtSetftp();
	afx_msg void OnTimeConfig();
protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	bool SetFtpInfo(char *Ip, long port, char *userName, char *passWord, char *serverPath, char *localPath, char *cameraName, int fileSum, CString fileLists);
	CString GetFtpInfo(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETFRAMEDLG_H__C2F9DC48_D708_42AF_9591_424CD60166D1__INCLUDED_)
