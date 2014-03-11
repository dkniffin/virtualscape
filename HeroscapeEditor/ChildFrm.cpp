// ChildFrm.cpp : implémentation de la classe CChildFrame
//
#include "StdAfx.h"

#include "ChildFrm.h"
#include "HeroscapeEditor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()


// The constructor
//
CChildFrame::CChildFrame()
{
}

// The destructor
//
CChildFrame::~CChildFrame()
{
}

// When the windows is to be create
//
BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO : changez ici la classe ou les styles Window en modifiant CREATESTRUCT cs
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// When this window get the focus
//
void CChildFrame::OnSetFocus(CWnd* pOldWnd)
{
	// Call the base class
	CMDIChildWnd::OnSetFocus(pOldWnd);

	CView* pView = GetActiveView();
	if( pView!=NULL )
		pView->SetFocus();
}
