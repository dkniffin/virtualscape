// DocumentConfigDlg.cpp : implementation file
//

#include "StdAfx.h"

#include "DocumentConfigDlg.h"
#include "GlobalIHM.h"
#include "HeroscapeEditor.h"

// CDocumentConfigDlg dialog

IMPLEMENT_DYNAMIC(CDocumentConfigDlg, CDialog)

// The constructor
//
CDocumentConfigDlg::CDocumentConfigDlg(CWnd* pParent /*=NULL*/)
:
// Call the base class
CDialog(CDocumentConfigDlg::IDD, pParent)
, m_BattleFieldName(_T(""))
, m_Author(_T(""))
, m_PrintTransparency(0)
, m_PlayerNumber(_T(""))
, m_reScenario(_T(""))
, m_PrintTileNumber(FALSE)
, m_b_PrintStartAreaAsLevel(FALSE)
{
	m_ScenarioWriteBufferPos = 0;
	m_ScenarioBufferPos = 0;
	m_ColorText = RGB(0,0,0);
}

// The destructor
//
CDocumentConfigDlg::~CDocumentConfigDlg()
{
}

// Synchronize data and members
//
void CDocumentConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_BATTLEFIELDNAME, m_BattleFieldName);
	DDX_Text(pDX, IDC_EDIT_AUTHOR, m_Author);
	DDX_Text(pDX, IDC_EDIT_PRINTTRANSPARENCY, m_PrintTransparency);
	DDV_MinMaxUInt(pDX, m_PrintTransparency, 0, 100);
	DDX_Control(pDX, IDC_COMBO_LEVELBYPAGE, m_ComboLevelByPage);
	DDX_Control(pDX, IDC_SP_PRINT_TRANSPARENCY, m_Sp_PrintTransparency);
	DDX_Text(pDX, IDC_EDIT_PLAYER_NUMBER, m_PlayerNumber);
	DDX_Control(pDX, IDC_RICHEDIT_SCENARIO, m_re_Scenario);
	DDX_Text(pDX, IDC_RICHEDIT_SCENARIO, m_reScenario);
	DDX_Check(pDX, IDC_CHECK_PRINT_TILE_NUMBER, m_PrintTileNumber);
	DDX_Check(pDX, IDC_CHECK_PRINT_START_AREA_AS_LEVEL, m_b_PrintStartAreaAsLevel);
}


BEGIN_MESSAGE_MAP(CDocumentConfigDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_BOLD, &CDocumentConfigDlg::OnBnClickedButtonBold)
	ON_BN_CLICKED(IDC_BUTTON_UNDERLINE, &CDocumentConfigDlg::OnBnClickedButtonUnderline)
	ON_BN_CLICKED(IDC_BUTTON_ITALIC, &CDocumentConfigDlg::OnBnClickedButtonItalic)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_BUTTON_TEXTCOLOR, &CDocumentConfigDlg::OnBnClickedButtonTextcolor)
	ON_BN_CLICKED(IDC_BUTTON_BACKCOLOR, &CDocumentConfigDlg::OnBnClickedButtonBackcolor)
	ON_NOTIFY(EN_SELCHANGE, IDC_RICHEDIT_SCENARIO, &CDocumentConfigDlg::OnEnSelchangeRicheditScenario)
END_MESSAGE_MAP()

// The document is initialised
//
BOOL CDocumentConfigDlg::OnInitDialog()
{
	// Call the base class
	CDialog::OnInitDialog();

	m_Sp_PrintTransparency.SetRange(0,100);

	m_ComboLevelByPage.AddString( _T("1") );
	m_ComboLevelByPage.AddString( _T("2") );
	m_ComboLevelByPage.AddString( _T("4") );
	m_ComboLevelByPage.AddString( _T("6") );

	CString Str;
	Str.Format( _T("%i"), m_NbLevelByPage );
	m_ComboLevelByPage.SelectString( -1, Str );

	if( m_PrintingGrid )
		((CButton*) GetDlgItem( IDC_CHECK_PRINTGRID ))->SetCheck( BST_CHECKED );


	CDC* pDC = GetDC();
	m_re_Scenario.SetTargetDevice( pDC->m_hDC, ::MulDiv(525, 1440, pDC->GetDeviceCaps(LOGPIXELSX)) );
	ReleaseDC( pDC );

	// Set text to the richedit control
	EDITSTREAM es;
	es.dwCookie = (DWORD) this;
	es.dwError = 0;
	es.pfnCallback = MyStreamInCallback;
	m_re_Scenario.StreamIn(SF_RTF|SF_UNICODE, es);
	if( !m_Scenario.IsEmpty() )
	{
		m_re_Scenario.SetWindowTextW( m_Scenario );
	}

	m_re_Scenario.SendMessage( EM_SETEVENTMASK, 0, ENM_SELCHANGE );

	return TRUE;
}

void CDocumentConfigDlg::OnOK()
{
	if( (((CButton*) GetDlgItem( IDC_CHECK_PRINTGRID ))->GetCheck()&BST_CHECKED)==BST_CHECKED )
		m_PrintingGrid = TRUE;
	else
		m_PrintingGrid = FALSE;

	CString Str;
	m_ComboLevelByPage.GetLBText( m_ComboLevelByPage.GetCurSel(), Str );
	m_NbLevelByPage = _wtoi( Str );

	// Read the richedit control
	EDITSTREAM es;

	es.dwCookie = (DWORD) this;
	es.dwError = 0;
	es.pfnCallback = MyStreamOutCallback;
	m_ScenarioBufferPos = 0;
	m_re_Scenario.StreamOut(SF_RTF, es);

	// Call the base class
	CDialog::OnOK();
}

// The user want that the selection are bold or not
//
void CDocumentConfigDlg::OnBnClickedButtonBold()
{
	CHARFORMAT2 cf;

	cf.cbSize = sizeof(CHARFORMAT2);
	cf.dwMask = CFM_BOLD;

	m_re_Scenario.GetSelectionCharFormat( cf );
	cf.dwMask = CFM_BOLD;
	cf.dwEffects ^= CFE_BOLD;
	m_re_Scenario.SetSelectionCharFormat( cf );
}

// The user want that the selection are underline or not
//
void CDocumentConfigDlg::OnBnClickedButtonUnderline()
{
	CHARFORMAT2 cf;

	cf.cbSize = sizeof(CHARFORMAT2);
	cf.dwMask = CFM_UNDERLINE;

	m_re_Scenario.GetSelectionCharFormat( cf );
	cf.dwMask = CFM_UNDERLINE;
	cf.dwEffects ^= CFE_UNDERLINE;
	m_re_Scenario.SetSelectionCharFormat( cf );
}

// Read the data of the richedit text
//
DWORD CALLBACK CDocumentConfigDlg::MyStreamOutCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	CDocumentConfigDlg* pDlg = (CDocumentConfigDlg*) dwCookie;
	memcpy( pDlg->m_ScenarioBuffScenario+pDlg->m_ScenarioBufferPos, pbBuff, cb );
	
	pDlg->m_ScenarioBufferPos += cb;
	*pcb = cb;

	return 0;
}

// Write the data to the richedit text
//
DWORD CALLBACK CDocumentConfigDlg::MyStreamInCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	CDocumentConfigDlg* pDlg = (CDocumentConfigDlg*) dwCookie;
	if( pDlg->m_ScenarioWriteBufferPos+cb>pDlg->m_ScenarioBufferPos )
	{
		memcpy( pbBuff, pDlg->m_ScenarioBuffScenario+pDlg->m_ScenarioWriteBufferPos, pDlg->m_ScenarioBufferPos-pDlg->m_ScenarioWriteBufferPos );
		*pcb = pDlg->m_ScenarioBufferPos-pDlg->m_ScenarioWriteBufferPos;
		pDlg->m_ScenarioWriteBufferPos = pDlg->m_ScenarioBufferPos;
	}
	else
	{
		memcpy( pbBuff, pDlg->m_ScenarioBuffScenario+pDlg->m_ScenarioWriteBufferPos, cb );
		*pcb = cb;
		pDlg->m_ScenarioWriteBufferPos += cb;
	}

	return 0;
}

// The user want that the selection are italic or not
//
void CDocumentConfigDlg::OnBnClickedButtonItalic()
{
	CHARFORMAT2 cf;

	cf.cbSize = sizeof(CHARFORMAT2);
	cf.dwMask = CFM_ITALIC;

	m_re_Scenario.GetSelectionCharFormat( cf );
	cf.dwMask = CFM_ITALIC;
	cf.dwEffects ^= CFE_ITALIC;
	m_re_Scenario.SetSelectionCharFormat( cf );
}

// Draw the color button
//
void CDocumentConfigDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle( lpDrawItemStruct->hDC );

	if( nIDCtl==IDC_BUTTON_TEXTCOLOR )
	{
		CGlobalIHM::DrawColorButton( lpDrawItemStruct, m_ColorText );
	}
	if( nIDCtl==IDC_BUTTON_BACKCOLOR )
	{
		CGlobalIHM::DrawColorButton( lpDrawItemStruct, m_ColorBack );
	}

	// Call the base class
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

// The user want change the color of the selected text
//
void CDocumentConfigDlg::OnBnClickedButtonTextcolor()
{
	CColorDialog cdlg( m_ColorText, CC_FULLOPEN, this );
	if( cdlg.DoModal()==IDOK )
	{
		m_ColorText = cdlg.GetColor();

		CHARFORMAT2 cf;

		cf.cbSize = sizeof(CHARFORMAT2);
		cf.dwMask = CFM_COLOR;

		m_re_Scenario.GetSelectionCharFormat( cf );
		cf.dwMask = CFM_COLOR;
		cf.crTextColor = m_ColorText;
		cf.dwEffects &= ~CFE_AUTOCOLOR;
		m_re_Scenario.SetSelectionCharFormat( cf );
	}
}

// The user want change the color of the selected text background
//
void CDocumentConfigDlg::OnBnClickedButtonBackcolor()
{
	CColorDialog cdlg( m_ColorBack, CC_FULLOPEN, this );
	if( cdlg.DoModal()==IDOK )
	{
		m_ColorBack = cdlg.GetColor();

		CHARFORMAT2 cf;

		cf.cbSize = sizeof(CHARFORMAT2);
		cf.dwMask = CFM_BACKCOLOR;

		m_re_Scenario.GetSelectionCharFormat( cf );
		cf.dwMask = CFM_BACKCOLOR;
		cf.crBackColor = m_ColorBack;
		cf.dwEffects &= ~CFE_AUTOBACKCOLOR;
		m_re_Scenario.SetSelectionCharFormat( cf );
	}
}

void CDocumentConfigDlg::OnEnSelchangeRicheditScenario(NMHDR *pNMHDR, LRESULT *pResult)
{
	SELCHANGE *pSelChange = reinterpret_cast<SELCHANGE *>(pNMHDR);

	CHARFORMAT2 cf;

	cf.cbSize = sizeof(CHARFORMAT2);
	cf.dwMask = CFM_BACKCOLOR | CFM_COLOR;

	m_re_Scenario.GetSelectionCharFormat( cf );

	m_ColorBack = cf.crBackColor;
	m_ColorText = cf.crTextColor;

	Invalidate( false );

	*pResult = 0;
}
