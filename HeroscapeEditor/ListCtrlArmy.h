#pragma once

#include "GameDoc.h"

// CListCtrlArmy view

class CListCtrlArmy : public CScrollView
{
	DECLARE_DYNCREATE(CListCtrlArmy)

//************
// The members
//************
protected:
	// The current game document
	CPtrArray*	m_pArmyList;
	// The memory bitmap (for double buffering)
	CBitmap*	m_pBitmapMemory;

public:
	// The current selected army
	int			m_SelectedIndex;

//************
// The methods
//************
public:
	// The constructor
	CListCtrlArmy();
	// The destructor
	virtual ~CListCtrlArmy();
	// We need to draw yourself the control
	virtual void OnDraw(CDC* pDC);
	// Compute the scroll size
	void	ComputeScrollSize();
	// Set the army list
	void	SetArmyList( CPtrArray* pArmyList );

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


