// ProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HeroscapeEditor.h"
#include "ProgressDlg.h"


// CProgressDlg dialog

IMPLEMENT_DYNAMIC(CProgressDlg, CDialog)

// The constructor
//
CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
:
// The base class
CDialog(CProgressDlg::IDD, pParent)
{
	Create( CProgressDlg::IDD, pParent );
}

// The destructor
//
CProgressDlg::~CProgressDlg()
{
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_BAR, m_ProgressBar);
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
END_MESSAGE_MAP()


// CProgressDlg message handlers
