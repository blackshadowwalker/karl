#pragma once
#include "afxwin.h"

#include "ITSdefine.h"

// CConfigDlg 对话框

class CConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConfigDlg)
private:
	char	bgPicPath[256];
	long	rectId;
	bool	bLButtonDown;

	bool	bStartDrawSnapLine;
	bool	bStartDrawLaneLine;
	bool	bEditCaseRect;
	bool	bModefyLane;
	bool	bSetCaseRect;
	
	bool	bSetSnapLines;
	bool	bSetLaneLines;
	char	tempstr[512];
	CString	tempcstr;
	
	Line	tempLine;
	Lane	tempLane;
	
	Lane		m_lane[MAX_LANE];
	VdRegion	vdRegion;
	SnapLine	m_snapLine;
	int			retNum;

	int		pointPtr;
	CDC		*m_dc;

	bool	lButtonDown;
	int		selectedPoint ;//the index of point at one selected line; value:1,2 
	int		selectedCasePointIndex;
public:
	Image	*img;
	int		readConfig();
	bool	saveConfig();
	void	setBackgroundImage(char *path);
	const char*	getBackgroundImage() { return  bgPicPath;}
	void	ReDrawCaseRect();

public:
	CConfigDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CConfigDlg();

// 对话框数据
	enum { IDD = IDD_CONFIG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void PreInitDialog();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedTest();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	CComboBox m_screenMode;
	CComboBox m_LightGroupNumber;
	CComboBox m_snapLines;
	CComboBox m_lightId;
	CComboBox m_laneId;

	long setImage(char* filepath, bool bSHow = true);

	afx_msg void OnBnClickedBtAddSnapLine();
	CStatic m_imageFrame;
	
	afx_msg void OnBnClickedBtSave();
	
	afx_msg void OnBnClickedBtSetLine();
	afx_msg void OnCbnSelchangeLightNum();
	afx_msg void OnBnClickedBtSetLaneProp();
	afx_msg void OnBnClickedBtLaneAdd();
	afx_msg void OnBnClickedBtLaneModefy();
	afx_msg void OnBnClickedBtLaneDelete();
	afx_msg void OnBnClickedBtLaneCancel();
	afx_msg void OnCbnSelchangeLaneId();
	afx_msg void OnBnClickedBtSetCaseRect();
	afx_msg void OnBnClickedVdRegionEdit();
	CButton bEditRectCon;
	CButton *m_groupBoxLaneType;
	CButton *m_groupBoxEventType;
	CButton *m_groupOperaLane;
	CButton *m_groupOperaLine;
	void	LaneVisible(bool bShow);
	void	LineVisible(bool bShow);
	void	VdRegionVisible(bool bShow);
	
	afx_msg void OnCbnSelchangeSnapLines();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CComboBox m_lane_line;
	CStatic m_status;
};
