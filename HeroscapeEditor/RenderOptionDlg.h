#pragma once
#include "afxcmn.h"


// CRenderOptionDlg dialog

class CRenderOptionDlg : public CDialog
{
	DECLARE_DYNAMIC(CRenderOptionDlg)

public:
	CRenderOptionDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRenderOptionDlg();

// Dialog Data
	enum { IDD = IDD_RENDER_VIDEO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	UINT m_ImageCount;
	UINT m_FirstFrame;
	UINT m_LastFrame;
	CString m_FileName;
	CSpinButtonCtrl m_SpinFrameNumber;
	CSpinButtonCtrl m_SpinFirstFrame;
	CSpinButtonCtrl m_SpinLastFrame;
	virtual BOOL OnInitDialog();
	BOOL m_HighQuality;
	afx_msg void OnBnClickedButtonRenderFile();
};
