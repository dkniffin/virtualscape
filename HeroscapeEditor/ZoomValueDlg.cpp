// ZoomValueDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HeroscapeEditor.h"
#include "ZoomValueDlg.h"


// CZoomValueDlg dialog

IMPLEMENT_DYNAMIC(CZoomValueDlg, CDialog)

CZoomValueDlg::CZoomValueDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZoomValueDlg::IDD, pParent)
	, m_ZoomValue(0)
{

}

CZoomValueDlg::~CZoomValueDlg()
{
}

void CZoomValueDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ZOOM_VALUE, m_ZoomValue);
	DDV_MinMaxDouble(pDX, m_ZoomValue, 0.2, 1000);
}


BEGIN_MESSAGE_MAP(CZoomValueDlg, CDialog)
END_MESSAGE_MAP()


// CZoomValueDlg message handlers
