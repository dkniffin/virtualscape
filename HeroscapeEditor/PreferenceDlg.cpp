// PreferenceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GlobalIHM.h"
#include "HeroscapeEditor.h"
#include "PreferenceDlg.h"


// CPreferenceDlg dialog

IMPLEMENT_DYNAMIC(CPreferenceDlg, CDialog)

// The constructor
//
CPreferenceDlg::CPreferenceDlg(CWnd* pParent /*=NULL*/)
:
// Call the base class
CDialog(CPreferenceDlg::IDD, pParent)
, m_ShadowContrast(0)
, m_ShadowQuality(0)
, m_PhotoQuality(0)
, m_IsDepthField(FALSE)
, m_DepthField_Aperture(0)
, m_DepthField_Distance(0)
, m_DepthField_Quality(0)
, m_DisplayTable(FALSE)
, m_Luminosity(0)
, m_i_TextureType(0)
, m_MoveSolidscape(FALSE)
, m_i_AnaglyphiqueMode(0)
{

}

// The destructor
//
CPreferenceDlg::~CPreferenceDlg()
{
}

// Synchronize control and members
//
void CPreferenceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_SHADOW_QUALITY, m_SL_ShadowQuality);
	DDX_Control(pDX, IDC_SLIDER_SHADOW_CONTRAST, m_SL_ShadowContrast);
	DDX_Slider(pDX, IDC_SLIDER_SHADOW_CONTRAST, m_ShadowContrast);
	DDX_Slider(pDX, IDC_SLIDER_SHADOW_QUALITY, m_ShadowQuality);
	DDX_Control(pDX, IDC_SLIDER_PHOTO_QUALITY, m_SL_PhotoQuality);
	DDX_Slider(pDX, IDC_SLIDER_PHOTO_QUALITY, m_PhotoQuality);
	DDX_Check(pDX, IDC_CHECK_DEPTH_FIELD, m_IsDepthField);
	DDX_Text(pDX, IDC_ED_DEPTHFIELD_APERTURE, m_DepthField_Aperture);
	DDX_Text(pDX, IDC_ED_DEPTHFIELD_DISTANCE, m_DepthField_Distance);
	DDX_Slider(pDX, IDC_SLIDER_PHOTO_DEPTH_FIELD_QUALITY, m_DepthField_Quality);
	DDX_Control(pDX, IDC_SLIDER_PHOTO_DEPTH_FIELD_QUALITY, m_SL_DepthField_Quality);
	DDX_Control(pDX, IDC_SP_DEPTHFIELD_APERTURE, m_Sp_DepthField_Aperture);
	DDX_Control(pDX, IDC_SP_DEPTHFIELD_DISTANCE, m_Sp_DepthField_Distance);
	DDX_Check(pDX, IDC_CHECK_DISPLAY_TABLE, m_DisplayTable);
	DDX_Control(pDX, IDC_SLIDER_PHOTO_LUMINOSITY, m_SL_Luminosity);
	DDX_Slider(pDX, IDC_SLIDER_PHOTO_LUMINOSITY, m_Luminosity);
	DDX_Control(pDX, IDC_COMBO_TEXTURE_TYPE, m_cb_TextureType);
	DDX_CBIndex(pDX, IDC_COMBO_TEXTURE_TYPE, m_i_TextureType);
	DDX_Control(pDX, IDC_COMBO_UNIT, m_cb_Unit);
	DDX_Check(pDX, IDC_CHECK_MOVE_SOLIDSCAPE, m_MoveSolidscape);
	DDX_Control(pDX, IDC_COMBO_ANAGLYPHIQUE_MODE, m_cb_AnaglyphiqueMode);
	DDX_CBIndex(pDX, IDC_COMBO_ANAGLYPHIQUE_MODE, m_i_AnaglyphiqueMode);
}


BEGIN_MESSAGE_MAP(CPreferenceDlg, CDialog)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_BT_BACKGROUNDCOLOR2D, &CPreferenceDlg::OnBnClickedBtBackgroundcolor2d)
	ON_BN_CLICKED(IDC_BT_BACKGROUNDCOLOR3D, &CPreferenceDlg::OnBnClickedBtBackgroundcolor3d)
	ON_CBN_SELCHANGE(IDC_COMBO_UNIT, &CPreferenceDlg::OnCbnSelchangeComboUnit)
	ON_BN_CLICKED(IDC_BT_TOPOGRAPHICCOLORHIGH, &CPreferenceDlg::OnBnClickedBtTopographiccolorhigh)
	ON_BN_CLICKED(IDC_BT_TOPOGRAPHICCOLORLOW, &CPreferenceDlg::OnBnClickedBtTopographiccolorlow)
END_MESSAGE_MAP()


// Fhe dialog is initialise
//
BOOL CPreferenceDlg::OnInitDialog()
{
	// Call the base class
	CDialog::OnInitDialog();

	m_SL_ShadowQuality.SetRange(1,3,TRUE);
	m_SL_ShadowContrast.SetRange(0,30,TRUE);
	m_SL_PhotoQuality.SetRange(5,20,TRUE);
	m_SL_DepthField_Quality.SetRange(3,20,TRUE);
	m_SL_Luminosity.SetRange(0,100,TRUE);

	m_Sp_DepthField_Aperture.SetRange(5,50);
	m_Sp_DepthField_Distance.SetRange(5,500);

	m_SL_ShadowQuality.SetPos( m_ShadowQuality );
	m_SL_ShadowContrast.SetPos( m_ShadowContrast );
	m_SL_PhotoQuality.SetPos( m_PhotoQuality );
	m_SL_DepthField_Quality.SetPos( m_DepthField_Quality );
	m_SL_Luminosity.SetPos( m_Luminosity );
	m_SL_Luminosity.SetTicFreq( 5 );

	CString	Str;
	Str.LoadStringW( IDS_NORMAL );
	m_cb_TextureType.AddString( Str );
	Str.LoadStringW( IDS_SRMALLOY );
	m_cb_TextureType.AddString( Str );

	m_cb_TextureType.SetCurSel( m_i_TextureType );

	Str.LoadStringW( IDS_RED_BLUE );
	m_cb_AnaglyphiqueMode.AddString(Str);
	Str.LoadStringW( IDS_RED_GREEN );
	m_cb_AnaglyphiqueMode.AddString(Str);
	Str.LoadStringW( IDS_RED_CYAN );
	m_cb_AnaglyphiqueMode.AddString(Str);

	m_cb_TextureType.SetCurSel( m_i_AnaglyphiqueMode );

	// Set the current unit
	m_cb_Unit.SetCurSel( m_i_Unit );

	UpdateData( FALSE );

	return TRUE;
}

// Owner draw
//
void CPreferenceDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle( lpDrawItemStruct->hDC );

	if( nIDCtl==IDC_BT_BACKGROUNDCOLOR2D )
	{
		CGlobalIHM::DrawColorButton( lpDrawItemStruct, m_BackgroundColor2D );
	}
	else if( nIDCtl==IDC_BT_BACKGROUNDCOLOR3D )
	{
		CGlobalIHM::DrawColorButton( lpDrawItemStruct, m_BackgroundColor3D );
	}
	else if( nIDCtl==IDC_BT_TOPOGRAPHICCOLORLOW )
	{
		CGlobalIHM::DrawColorButton( lpDrawItemStruct, m_TopographicColorLow );
	}
	else if( nIDCtl==IDC_BT_TOPOGRAPHICCOLORHIGH )
	{
		CGlobalIHM::DrawColorButton( lpDrawItemStruct, m_TopographicColorHigh );
	}

	// Call the base class
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

// When the user want change the 2D background color
//
void CPreferenceDlg::OnBnClickedBtBackgroundcolor2d()
{
	CColorDialog cdlg( m_BackgroundColor2D, CC_FULLOPEN, this );
	if( cdlg.DoModal()==IDOK )
	{
		m_BackgroundColor2D = cdlg.GetColor();
		Invalidate();
	}
}

// When the user want change the 3D background color
//
void CPreferenceDlg::OnBnClickedBtBackgroundcolor3d()
{
	CColorDialog cdlg( m_BackgroundColor3D, CC_FULLOPEN, this );
	if( cdlg.DoModal()==IDOK )
	{
		m_BackgroundColor3D = cdlg.GetColor();
		Invalidate();
	}
}

// When the user change the selection in the combo unit
//
void CPreferenceDlg::OnCbnSelchangeComboUnit()
{
	m_i_Unit = m_cb_Unit.GetCurSel();
}

// When the user want change the topographic high color
//
void CPreferenceDlg::OnBnClickedBtTopographiccolorhigh()
{
	CColorDialog cdlg( m_TopographicColorHigh, CC_FULLOPEN, this );
	if( cdlg.DoModal()==IDOK )
	{
		m_TopographicColorHigh = cdlg.GetColor();
		Invalidate();
	}
}

// When the user want change the topographic low color
//
void CPreferenceDlg::OnBnClickedBtTopographiccolorlow()
{
	CColorDialog cdlg( m_TopographicColorLow, CC_FULLOPEN, this );
	if( cdlg.DoModal()==IDOK )
	{
		m_TopographicColorLow = cdlg.GetColor();
		Invalidate();
	}
}
