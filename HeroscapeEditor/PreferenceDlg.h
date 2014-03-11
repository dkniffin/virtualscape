#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CPreferenceDlg dialog

class CPreferenceDlg : public CDialog
{
	DECLARE_DYNAMIC(CPreferenceDlg)
public:
	// The view background color
	COLORREF	m_BackgroundColor2D;
	COLORREF	m_BackgroundColor3D;
	// The topographic view color
	COLORREF	m_TopographicColorLow;
	COLORREF	m_TopographicColorHigh;
	// The unit
	int			m_i_Unit;

public:
	// The constructor
	CPreferenceDlg(CWnd* pParent = NULL);
	// The destructor
	virtual ~CPreferenceDlg();

// Dialog Data
	enum { IDD = IDD_PREFERENCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_SL_ShadowQuality;
public:
	CSliderCtrl m_SL_ShadowContrast;
public:
	virtual BOOL OnInitDialog();
public:
	int m_ShadowContrast;
public:
	int m_ShadowQuality;
public:
	CSliderCtrl m_SL_PhotoQuality;
public:
	int m_PhotoQuality;
public:
	BOOL m_IsDepthField;
public:
	int m_DepthField_Aperture;
public:
	int m_DepthField_Distance;
public:
	int m_DepthField_Quality;
public:
	CSliderCtrl m_SL_DepthField_Quality;
public:
	CSpinButtonCtrl m_Sp_DepthField_Aperture;
public:
	CSpinButtonCtrl m_Sp_DepthField_Distance;
public:
	BOOL m_DisplayTable;
public:
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
public:
	afx_msg void OnBnClickedBtBackgroundcolor2d();
public:
	afx_msg void OnBnClickedBtBackgroundcolor3d();
public:
	CSliderCtrl m_SL_Luminosity;
public:
	int m_Luminosity;
public:
	CComboBox m_cb_TextureType;
public:
	int m_i_TextureType;
public:
	CComboBox m_cb_Unit;
public:
	afx_msg void OnCbnSelchangeComboUnit();
	BOOL m_MoveSolidscape;
	afx_msg void OnBnClickedBtTopographiccolorhigh();
	afx_msg void OnBnClickedBtTopographiccolorlow();
	CComboBox m_cb_AnaglyphiqueMode;
	int m_i_AnaglyphiqueMode;
};
