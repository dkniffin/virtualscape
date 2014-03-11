#pragma once

#include "GameDoc.h"

// CListCtrlPlayer view

class CListCtrlPlayer : public CScrollView
{
	DECLARE_DYNCREATE(CListCtrlPlayer)

//************
// The members
//************
protected:
	// The current game document
	CGameDoc*	m_pGameDoc;
	// The memory bitmap (for double buffering)
	CBitmap*	m_pBitmapMemory;

//************
// The methods
//************
public:
	// The constructor
	CListCtrlPlayer();
	// The destructor
	virtual ~CListCtrlPlayer();
	// We need to draw yourself the control
	virtual void OnDraw(CDC* pDC);
	// Compute the scroll size
	void	ComputeScrollSize();
	// Set the current game document
	void	SetCurrentGameDoc( CGameDoc* pGameDoc );

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};


