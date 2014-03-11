// GameActionView.cpp : implementation file
//

#include "StdAfx.h"

#include "GameActionView.h"
#include "GameDoc.h"
#include "HeroscapeEditor.h"
#include "SocketMessageId.h"

IMPLEMENT_DYNCREATE(CGameActionView, CFormView)

// The constructor
//
CGameActionView::CGameActionView()
:
// Call the base class
CFormView(CGameActionView::IDD)
{
	//{{AFX_DATA_INIT(CGameActionView)
	//}}AFX_DATA_INIT
}

// The destructor
//
CGameActionView::~CGameActionView()
{
}

// Exchange data between control and members
//
void CGameActionView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGameActionView)
	//}}AFX_DATA_MAP
}

// The window messaging
//
BEGIN_MESSAGE_MAP(CGameActionView, CFormView)
	//{{AFX_MSG_MAP(CGameActionView)
	//}}AFX_MSG_MAP
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOVE()
END_MESSAGE_MAP()

// Create the window
//
void CGameActionView::Create(CWnd* Parent)
{
	CFormView::Create( NULL, NULL, WS_CHILD|WS_VISIBLE, CRect(0,16,2000,2000), Parent, 3029, NULL );
}

// Destroy the non client area
//
void CGameActionView::PostNcDestroy() 
{
	// Do nothing
}

// Init the view at first time
//
void CGameActionView::OnInitialUpdate() 
{
	// Call the base class
	CFormView::OnInitialUpdate();

	m_IsInit = true;
}

// Create the controls when the view is created
//
int CGameActionView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

// When the view is resize then resize the controls
//
void CGameActionView::OnSize(UINT nType, int cx, int cy)
{
	// Call the base class
	CFormView::OnSize(nType, cx, cy);

	// Now resize the action list
	CWnd* pWnd = GetDlgItem(IDC_RICHEDIT_ACTION);
	if( pWnd!=NULL )
		if( ::IsWindow(pWnd->m_hWnd) )
		{
			pWnd->SetWindowPos( NULL, 5, 5, cx-15, cy-15, SWP_NOMOVE|SWP_NOZORDER );

			CDC* pDC = GetDC();
			((CRichEditCtrl*) pWnd)->SetTargetDevice( pDC->m_hDC, ::MulDiv(cx-42-15, 1440, pDC->GetDeviceCaps(LOGPIXELSX)) );
			ReleaseDC( pDC );
		}
}

// When the window move
//
void CGameActionView::OnMove(int x, int y)
{
	// Call the base class
	CFormView::OnMove(x, y);

	RedrawWindow();
}

// Close the last action in the display list
//
void CGameActionView::CloseLastAction()
{
	CString Str;

	Str.LoadStringW(IDS_ACTIONDONE);

	CRichEditCtrl* pRECtrl = (CRichEditCtrl*) GetDlgItem(IDC_RICHEDIT_ACTION);

	// Set text to the richedit control
	long Last = pRECtrl->GetTextLengthEx(GTL_DEFAULT|GTL_PRECISE|GTL_NUMCHARS,CP_ACP );
	pRECtrl->SetSel( Last, Last );
	pRECtrl->ReplaceSel( Str );
	pRECtrl->SetSel( pRECtrl->GetTextLengthEx(GTL_DEFAULT|GTL_PRECISE|GTL_NUMCHARS,CP_ACP ), pRECtrl->GetTextLengthEx(GTL_DEFAULT|GTL_PRECISE|GTL_NUMCHARS,CP_ACP )+1 );
}

// Add an action done by us or an other player
//
void CGameActionView::AddAction( bool IsMine, CString PlayerName, int ActionType )
{
	CString Str;
	CString ActionText;
	switch( ActionType )
	{
	case CGameDoc::TA_CHOOSE_ARMY:
		ActionText.LoadStringW(IDS_ACTION_CHOOSE_ARMY);
		break;
	case CGameDoc::TA_FREEGAME:
		ActionText.LoadStringW(IDS_FREEGAME);
		break;
	default:
		ActionText.LoadStringW(IDS_ACTION_UNKNOWN);
		break;
	}

	AddString( IsMine, PlayerName, ActionText );
}

// Add a string
//
void CGameActionView::AddString( bool IsMine, CString PlayerName, CString Text )
{
	CString Str;

	Str.Format( _T("\n%s > %s ... "), PlayerName, Text );

	CRichEditCtrl* pRECtrl = (CRichEditCtrl*) GetDlgItem(IDC_RICHEDIT_ACTION);

	// Set text to the richedit control
	long Last = pRECtrl->GetTextLengthEx(GTL_DEFAULT|GTL_PRECISE|GTL_NUMCHARS,CP_ACP );
	pRECtrl->SetSel( Last, Last+1 );
	pRECtrl->ReplaceSel( Str );
	pRECtrl->SetSel( Last, pRECtrl->GetTextLengthEx(GTL_DEFAULT|GTL_PRECISE|GTL_NUMCHARS,CP_ACP ) );
	if( IsMine )
	{
		CHARFORMAT2 cf;

		cf.cbSize = sizeof(CHARFORMAT2);
		cf.dwMask = CFM_COLOR;
		pRECtrl->GetSelectionCharFormat( cf );

		cf.cbSize = sizeof(CHARFORMAT2);
		cf.dwMask = CFM_COLOR;
		cf.crTextColor = RGB(128,0,0);
		cf.dwEffects &= ~CFE_AUTOCOLOR;
		pRECtrl->SetSelectionCharFormat( cf );
	}
	else
	{
		CHARFORMAT2 cf;

		cf.cbSize = sizeof(CHARFORMAT2);
		cf.dwMask = CFM_COLOR;
		pRECtrl->GetSelectionCharFormat( cf );

		cf.cbSize = sizeof(CHARFORMAT2);
		cf.dwMask = CFM_COLOR;
		cf.crTextColor = RGB(0,0,128);
		cf.dwEffects &= ~CFE_AUTOCOLOR;
		pRECtrl->SetSelectionCharFormat( cf );
	}
	pRECtrl->SetSel( pRECtrl->GetTextLengthEx(GTL_DEFAULT|GTL_PRECISE|GTL_NUMCHARS,CP_ACP ), pRECtrl->GetTextLengthEx(GTL_DEFAULT|GTL_PRECISE|GTL_NUMCHARS,CP_ACP )+1 );
	pRECtrl->LineScroll( pRECtrl->GetLineCount()-pRECtrl->GetFirstVisibleLine()-8 );
	pRECtrl->RedrawWindow();
}

// Reset all the actions
//
void CGameActionView::ResetAction()
{
	CRichEditCtrl* pRECtrl = (CRichEditCtrl*) GetDlgItem(IDC_RICHEDIT_ACTION);

	pRECtrl->SetSel( 0, -1 );
	pRECtrl->ReplaceSel( _T("") );
	pRECtrl->RedrawWindow();
}
