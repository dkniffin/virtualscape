#pragma once

#include "Maths\Matrix4x4.h"
#include "Object3D.h"
#include "shared/pbuffer.h"

#include "HeroscapeEditor3DView.h"
#include "GameDoc.h"

// Vue CGame3DView

class CGame3DView : public CHeroscapeEditor3DView
{
	DECLARE_DYNCREATE(CGame3DView)


//**********
// The enums
//**********
protected:

//************
// The members
//************
protected:

//************
// The methods
//************
public:
	// The constructor
	CGame3DView();
	// the destructor
	virtual ~CGame3DView();
	// Initialise some parameters
	void	InitParams();
	// Compute a random next position
	void	ComputeRandomNextPosition();
	// Get the document
	inline	CGameDoc* CGame3DView::GetDocument() const { return (CGameDoc*) CView::GetDocument(); }
	// Enter in the free game mode
	void	EnterFreeGameMode();
	// Enter in the select position mode
	void	EnterInSelectPositionMode( bool NeedTwoCase );
	// Enter in select figure mode
	void	EnterInSelectFigureMode();

protected:
	DECLARE_MESSAGE_MAP()


public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


