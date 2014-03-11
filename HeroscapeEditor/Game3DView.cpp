// Game3DView.cpp : fichier d'implémentation
//

#include "StdAfx.h"

#include "GL/gl.h" 
#include "GL/glext.h"
#include "GL/glu.h" 
#include "glh/glh_extensions.h"
#include "glh/glh_obs.h"
#include <Math.h>
#include "shared/pbuffer.h"

#include "FigureObject.h"
#include "Game3DView.h"
#include "HeroscapeEditor.h"
#include "MainFrm.h"
#include "Maths/Color.h"
#include "PersonalTexture.h"
#include "StaticGraphicalLib.h"

// CGame3DView

IMPLEMENT_DYNCREATE(CGame3DView, CHeroscapeEditor3DView)

BEGIN_MESSAGE_MAP(CGame3DView, CHeroscapeEditor3DView)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// The constructor
//
CGame3DView::CGame3DView()
{
}

// The destructor
//
CGame3DView::~CGame3DView()
{
}

// Initialise some parameters
//
void CGame3DView::InitParams()
{
	CGameDoc* pDoc = (CGameDoc*) GetDocument();

	UpdateData1();
	UpdateData2();

	OnCameraGoHome();

	ComputeRandomNextPosition();
}

// Compute a random next position
//
void CGame3DView::ComputeRandomNextPosition()
{
}

// Enter in the free game mode
//
void CGame3DView::EnterFreeGameMode()
{
	m_Mode = MODE3D_NULL; // We can move as we want
}

// Enter in the select position mode
//
void CGame3DView::EnterInSelectPositionMode( bool NeedTwoCase )
{
	m_Mode = MODE3D_SELECT_POSITION;
	m_DisplayPositionTwoCase = NeedTwoCase;
	m_DisplayPositionRotation = 0;
}

// Enter in remove figure mode
//
void CGame3DView::EnterInSelectFigureMode()
{
	m_Mode = MODE3D_SELECT_FIGURE;
}

// The user use mouse wheel
//
BOOL CGame3DView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if( m_Mode==MODE3D_SELECT_POSITION )
	{
		if( zDelta<0 )
		{
			if( ++m_DisplayPositionRotation>5 )
				m_DisplayPositionRotation=0;
		}
		else
		{
			if( --m_DisplayPositionRotation<0 )
				m_DisplayPositionRotation=5;
		}
		m_IsModified = true;
		RedrawWindow();
	}

	// Call the base class
	return CHeroscapeEditor3DView::OnMouseWheel(nFlags, zDelta, pt);
}

// When the user release the left mouse button
//
void CGame3DView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// Call the base class
	CHeroscapeEditor3DView::OnLButtonUp(nFlags, point);

	// if we are in select position mode then return the selected position
	if( m_Mode==MODE3D_SELECT_POSITION && !m_MouseMoveUntilLButtonDown )
	{
		m_Mode=MODE3D_NULL;
		if( m_DisplayPositionX>=0 )
			GetDocument()->SetCurrentSelectedPosition( m_DisplayPositionX, m_DisplayPositionY, m_DisplayPositionZ+1, m_DisplayPositionRotation );
		else
		{
			GetDocument()->ResetAllFigure();
			GetDocument()->m_pCurrentFigureTile->m_CreationTime = -1;
			ComputeShadow();
			m_IsModified = true;
			RedrawWindow();
		}
	}
	// If we are in select figure mode then return the selected figure
	else if( m_Mode==MODE3D_SELECT_FIGURE && !m_MouseMoveUntilLButtonDown )
	{
		m_Mode=MODE3D_NULL;
		GetDocument()->SetCurrentSelectedFigure( m_pSelectedFigure );
	}
}
