// TilePerso1Dlg.cpp : implementation file
//

#include "StdAfx.h"

#include <io.h>

#include "GlobalIHM.h"
#include "HeroscapeEditor.h"
#include "TilePerso1Dlg.h"


// CTilePerso1Dlg dialog

IMPLEMENT_DYNAMIC(CTilePerso1Dlg, CDialog)

CTilePerso1Dlg::CTilePerso1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTilePerso1Dlg::IDD, pParent)
	, m_Name(_T(""))
	, m_NbDispo(0)
	, m_Character(_T(""))
{

}

CTilePerso1Dlg::~CTilePerso1Dlg()
{
}

void CTilePerso1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TILETYPENAME, m_Name);
	DDX_Control(pDX, IDC_COMBO_TILEPERSONBHEX, m_cb_NbHex);
	DDX_Text(pDX, IDC_EDIT_TILEPERSONBDISPO, m_NbDispo);
	DDX_Control(pDX, IDC_SP_TILEPERSONBDISPO, m_sp_NbDispo);
	DDX_Text(pDX, IDC_EDIT_TILEPERSOCAR, m_Character);
	DDX_Control(pDX, IDC_COMBO_TILEPERSOTEXTURE, m_cb_Texture);
	DDX_Control(pDX, IDC_COMBO_TILEPERSOTEXTURESIDE, m_cb_TextureSide);
}


BEGIN_MESSAGE_MAP(CTilePerso1Dlg, CDialog)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_BT_COLOR2D, &CTilePerso1Dlg::OnBnClickedBtColor2d)
END_MESSAGE_MAP()


// CTilePerso1Dlg message handlers

BOOL CTilePerso1Dlg::OnInitDialog()
{
	// Call the base class
	CDialog::OnInitDialog();

	m_cb_NbHex.AddString( _T("1") );
	m_cb_NbHex.AddString( _T("2") );
	m_cb_NbHex.AddString( _T("3") );
	m_cb_NbHex.AddString( _T("7") );
	m_cb_NbHex.AddString( _T("24") );

	CString Str;
	Str.Format( _T("%i"), m_NbHex );
	m_cb_NbHex.SelectString( -1, Str );

	m_sp_NbDispo.SetRange( 0, 999 );

	// Add all texture files find in the personal directory
	_finddata_t fd;
	CString Path = theApp.m_CurrentDir+_T("\\Images\\Personal\\*.bmp");

	char* pStr = theApp.GetAsciiString( Path );
	long Handle = (long) _findfirst( pStr, &fd );
	long Ret = Handle;
	while( Ret!=-1 )
	{
		CString Str(fd.name);
		m_cb_Texture.AddString( Str );
		m_cb_TextureSide.AddString( Str );
		Ret = _findnext( Handle, &fd );
	}
	free( pStr );

	// Select texture
	m_cb_Texture.SetCurSel(0);
	m_cb_Texture.SelectString( -1, m_Texture );
	m_cb_TextureSide.SetCurSel(0);
	m_cb_TextureSide.SelectString( -1, m_TextureSide );

	return TRUE;
}

// Draw color button
//
void CTilePerso1Dlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle( lpDrawItemStruct->hDC );

	if( nIDCtl==IDC_BT_COLOR2D )
	{
		CGlobalIHM::DrawColorButton( lpDrawItemStruct, m_Color2D );
	}

	// Call the base class
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

// The user want change the tile color
//
void CTilePerso1Dlg::OnBnClickedBtColor2d()
{
	CColorDialog cdlg( m_Color2D, CC_FULLOPEN, this );
	if( cdlg.DoModal()==IDOK )
	{
		m_Color2D = cdlg.GetColor();
		Invalidate();
	}
}

// The user validate the choice
//
void CTilePerso1Dlg::OnOK()
{
	// Call the base class
	CDialog::OnOK();

	m_cb_Texture.GetLBText( m_cb_Texture.GetCurSel(), m_Texture );
	m_cb_TextureSide.GetLBText( m_cb_TextureSide.GetCurSel(), m_TextureSide );
	CString Str;
	m_cb_NbHex.GetLBText( m_cb_NbHex.GetCurSel(), Str );
	m_NbHex = _wtoi( Str );
}
