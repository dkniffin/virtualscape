#pragma once


// CZoomValueDlg dialog

class CZoomValueDlg : public CDialog
{
	DECLARE_DYNAMIC(CZoomValueDlg)

public:
	CZoomValueDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CZoomValueDlg();

// Dialog Data
	enum { IDD = IDD_GET_ZOOM_VALUE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double m_ZoomValue;
};
