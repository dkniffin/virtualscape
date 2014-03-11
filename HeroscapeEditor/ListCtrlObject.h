#pragma once

#include "Tile.h"

// CListCtrlObject view

class CListCtrlObject : public CScrollView
{
	DECLARE_DYNCREATE(CListCtrlObject)

//************
// The defines
//************
#define	MODE_NULL	0
#define	MODE_DRAG	1

//************
// The members
//************
protected:
	// The object list
	CPtrArray	m_ObjectList;
	// The current mode
	int			m_Mode;
	// The current tile
	CTile*		m_pCurrentTile;
	// The current tile position
	POINT		m_CurrentTilePosition;
	// The difference between mouse pos and tile pos
	double		m_DiffPosTileMouseX;
	double		m_DiffPosTileMouseY;
	// The memory bitmap (for double buffering)
	CBitmap*	m_pBitmapMemory;
	// The current doc
	void*		m_pDoc;

public:
	// The last used tile type
	int			m_LastUsedTileType;
	// The last start area color
	COLORREF	m_LastStartAreaColor;
	// The last personal tile color
	COLORREF	m_LastPersonalTileColor;
	// The last personal tile texture
	CString		m_LastPersonalTileTexture;
	// The last personal tile texture side
	CString		m_LastPersonalTileTextureSide;
	// The last personal tile char
	CString		m_LastPersonalTileChar;
	// The last personal tile name
	CString		m_LastPersonalTileName;
	// The last personal tile nbtile
	int			m_LastPersonalNbTile;
	// For Figure
	CString		m_LastFigureFile;
	CString		m_LastFigureName;
	int			m_LastFigureNbTile;

//************
// The methods
//************
public:
	// The constructor
	CListCtrlObject();
	// The destructor
	virtual ~CListCtrlObject();
	// Add an object to the list
	void	AddObject( CTile* pTile );
	// Remove all the objects in this tab list
	void	RemoveAllObjects();
	// Compute the scroll size
	void	ComputeScrollSize();
	// Set the current document
	void	SetCurrentDoc( void* pDoc );

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


