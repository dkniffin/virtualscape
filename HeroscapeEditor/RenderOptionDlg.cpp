// RenderOptionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HeroscapeEditor.h"
#include "RenderOptionDlg.h"


// CRenderOptionDlg dialog

IMPLEMENT_DYNAMIC(CRenderOptionDlg, CDialog)

CRenderOptionDlg::CRenderOptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRenderOptionDlg::IDD, pParent)
	, m_ImageCount(0)
	, m_FirstFrame(0)
	, m_LastFrame(0)
	, m_FileName(_T(""))
	, m_HighQuality(FALSE)
{

}

CRenderOptionDlg::~CRenderOptionDlg()
{
}

void CRenderOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RENDER_IMAGENUMBER, m_ImageCount);
	DDV_MinMaxUInt(pDX, m_ImageCount, 1, 99999999);
	DDX_Text(pDX, IDC_RENDER_FIRSTIMAGE, m_FirstFrame);
	DDV_MinMaxUInt(pDX, m_FirstFrame, 1, 99999999);
	DDX_Text(pDX, IDC_RENDER_LASTIMAGE, m_LastFrame);
	DDV_MinMaxUInt(pDX, m_LastFrame, 1, 99999999);
	DDX_Text(pDX, IDC_RENDER_FILE, m_FileName);
	DDX_Control(pDX, IDC_RENDER_SPINNUMBERIMAGE, m_SpinFrameNumber);
	DDX_Control(pDX, IDC_RENDER_SPIN_FIRSTIMAGE, m_SpinFirstFrame);
	DDX_Control(pDX, IDC_RENDER_SPIN_LASTIMAGE, m_SpinLastFrame);
	DDX_Check(pDX, IDC_RENDER_HIGHQUALITY, m_HighQuality);
}


BEGIN_MESSAGE_MAP(CRenderOptionDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RENDER_FILE, &CRenderOptionDlg::OnBnClickedButtonRenderFile)
END_MESSAGE_MAP()


// CRenderOptionDlg message handlers

BOOL CRenderOptionDlg::OnInitDialog()
{
	// Call the base class
	CDialog::OnInitDialog();

	m_SpinFrameNumber.SetRange32(1,99999999);
	m_SpinFirstFrame.SetRange32(1,99999999);
	m_SpinLastFrame.SetRange32(1,99999999);

	return TRUE;
}

// The user want choose the filename to save
//
void CRenderOptionDlg::OnBnClickedButtonRenderFile()
{
	UpdateData( TRUE );

	CFileDialog fd( FALSE, NULL, 0, 4|2 | OFN_NOTESTFILECREATE | OFN_PATHMUSTEXIST, _T("Bitmap (*.bmp)|*.bmp||") );

	if( fd.DoModal()==IDOK )
	{
		m_FileName = fd.GetPathName();

		UpdateData( FALSE );
	}
}
