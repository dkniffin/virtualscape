// GameChatView.cpp : implementation file
//

#include "StdAfx.h"

#include "GameChatView.h"
#include "HeroscapeEditor.h"
#include "SocketMessageId.h"

IMPLEMENT_DYNCREATE(CGameChatView, CFormView)

// The constructor
//
CGameChatView::CGameChatView()
:
// Call the base class
CFormView(CGameChatView::IDD)
{
	//{{AFX_DATA_INIT(CGameChatView)
	//}}AFX_DATA_INIT
}

// The destructor
//
CGameChatView::~CGameChatView()
{
}

// Exchange data between control and members
//
void CGameChatView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfoView)
	//}}AFX_DATA_MAP
}

// The window messaging
//
BEGIN_MESSAGE_MAP(CGameChatView, CFormView)
	//{{AFX_MSG_MAP(CGameChatView)
	//}}AFX_MSG_MAP
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CGameChatView::OnBnClickedButtonSend)
END_MESSAGE_MAP()

// Create the window
//
void CGameChatView::Create(CWnd* Parent)
{
	CFormView::Create( NULL, NULL, WS_CHILD|WS_VISIBLE, CRect(0,16,2000,2000), Parent, 3028, NULL );
}

// Destroy the non client area
//
void CGameChatView::PostNcDestroy() 
{
	// Do nothing
}

// Init the view at first time
//
void CGameChatView::OnInitialUpdate() 
{
	// Call the base class
	CFormView::OnInitialUpdate();

	GetDlgItem(IDC_EDIT_MESSAGE)->SetFocus();

	m_IsInit = true;
}

// Create the controls when the view is created
//
int CGameChatView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

// When the view is resize then resize the controls
//
void CGameChatView::OnSize(UINT nType, int cx, int cy)
{
	// Call the base class
	CFormView::OnSize(nType, cx, cy);

	// Now resize the message text
	CWnd* pWnd = GetDlgItem(IDC_EDIT_MESSAGE);
	if( pWnd!=NULL )
		if( ::IsWindow(pWnd->m_hWnd) )
			pWnd->SetWindowPos( NULL, 10, cy-25, cx-110, 20, SWP_NOZORDER );

	// Now resize the button
	pWnd = GetDlgItem(IDC_BUTTON_SEND);
	if( pWnd!=NULL )
		if( ::IsWindow(pWnd->m_hWnd) )
			pWnd->SetWindowPos( NULL, cx-85, cy-25, 0, 0, SWP_NOSIZE|SWP_NOZORDER );

	// Now resize the message list
	pWnd = GetDlgItem(IDC_RICHEDIT_MESSAGE);
	if( pWnd!=NULL )
		if( ::IsWindow(pWnd->m_hWnd) )
		{
			pWnd->SetWindowPos( NULL, 5, 5, cx-15, cy-42, SWP_NOMOVE|SWP_NOZORDER );

			CDC* pDC = GetDC();
			((CRichEditCtrl*) pWnd)->SetTargetDevice( pDC->m_hDC, ::MulDiv(cx-42-15, 1440, pDC->GetDeviceCaps(LOGPIXELSX)) );
			ReleaseDC( pDC );
		}
}

// When the window move
//
void CGameChatView::OnMove(int x, int y)
{
	// Call the base class
	CFormView::OnMove(x, y);

	RedrawWindow();
}

// Add a message receive from other players
//
void CGameChatView::AddMessage( bool IsMine, CString From, CString Message )
{
	CString Str;
	if( !From.IsEmpty() )
		Str.Format( _T("\n%s > %s"), From, Message );
	else
		Str.Format( _T("\n%s"), Message );

	CRichEditCtrl* pRECtrl = (CRichEditCtrl*) GetDlgItem(IDC_RICHEDIT_MESSAGE);

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
		cf.crTextColor = RGB(0,128,0);
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
		cf.crTextColor = RGB(0,0,0);
		cf.dwEffects &= ~CFE_AUTOCOLOR;
		pRECtrl->SetSelectionCharFormat( cf );
	}
	pRECtrl->SetSel( pRECtrl->GetTextLengthEx(GTL_DEFAULT|GTL_PRECISE|GTL_NUMCHARS,CP_ACP ), pRECtrl->GetTextLengthEx(GTL_DEFAULT|GTL_PRECISE|GTL_NUMCHARS,CP_ACP )+1 );
	pRECtrl->LineScroll( pRECtrl->GetLineCount()-pRECtrl->GetFirstVisibleLine()-7 );
}

// Reset the message list
//
void CGameChatView::ResetMessage()
{
	CRichEditCtrl* pRECtrl = (CRichEditCtrl*) GetDlgItem(IDC_RICHEDIT_MESSAGE);

	pRECtrl->SetSel( 0, -1 );
	pRECtrl->ReplaceSel( _T("") );
	pRECtrl->RedrawWindow();
}

// The user wand send a message to everybody
//
void CGameChatView::OnBnClickedButtonSend()
{
	CString Message;
	GetDlgItem(IDC_EDIT_MESSAGE)->GetWindowTextW(Message);

	theApp.m_pGameDoc->m_ToServerSocket.CreateBuffer();
	theApp.m_pGameDoc->m_ToServerSocket.WriteType( theApp.m_pGameDoc->m_PlayerIndex );
	theApp.m_pGameDoc->m_ToServerSocket.WriteType( ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(theApp.m_pGameDoc->m_PlayerIndex))->GetName() );
	theApp.m_pGameDoc->m_ToServerSocket.WriteType( Message );
	theApp.m_pGameDoc->m_ToServerSocket.SendMessage( SMI_TOSERVER_MESSAGE_TO_EVERYONE );

	GetDlgItem(IDC_EDIT_MESSAGE)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT_MESSAGE)->SetFocus();
}
