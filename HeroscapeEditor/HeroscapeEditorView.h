// HeroscapeEditorView.h : interface de la classe CHeroscapeEditorView
//


#pragma once

#include "HeroscapeEditorDoc.h"

class CHeroscapeEditorView : public CScrollView
{
//************
// The defines
//************
#define	MODE_NULL			0
#define	MODE_DRAG			1
#define	MODE_ADD_ON_MOVE	2
#define	MODE_SELECT_ON_MOVE	3

#define	BOARD_MAX_TILE_X	100
#define	BOARD_MAX_TILE_Y	100
#define	TILE_ORIGINAL_SIZE	12

#define PS_DEFAULT			1
#define PS_NUM				2

//************
// The members
//************
protected:
	// The zoom level
	double m_ZoomLevel;
	// The tile size
	int			m_TileStepX2;
	int			m_TileStepX3;
	int			m_TileStepY2;
	int			m_TileStepY3;
	int			m_TileStepY4;
	// The memory bitmap (to redraw more quickly)
	CBitmap*	m_pBitmapMemory;
	// The memory bitmap2 (to redraw more quickly)
	CBitmap*	m_pBitmapMemory2;
	// The memory bitmap under current level (to redraw more quickly)
	CBitmap*	m_pBitmapMemoryUnderCurrentLevel;
	// The current z level
	int			m_CurrentZLevel;
	// The difference between mouse pos and tile pos
	POINT		m_LastLButtonDownPos;
	POINT		m_SelectedTileOffset;
	// The mode
	int			m_Mode;
	int			m_ScrollPosX;
	int			m_ScrollPosY;
	// Is it on Onion skin mode
	bool		m_OnionSkinMode;
	// To move correctly with key
	int			m_LastMoveVertical;
	// The printing mode
	int			m_PrintState;

public:
	// Does we must display number or not
	bool		m_DisplayNumber;

//************
// The methods
//************
protected:
	// The constructor
	CHeroscapeEditorView();
	// The destructor
	virtual ~CHeroscapeEditorView();
	// Recompute the scroll size
	void	RecomputeScrollSize();
	// Zoom in
	void	ZoomIn( CPoint Point );
	// Zoom out
	void	ZoomOut( CPoint Point );

public:
	// Inform the view that a tile is currently moving
	void	InformTileMoving( CTile* pTile, POINT Point, double DiffPosTileMouseX, double DiffPosTileMouseY );
	// Inform the view that a tile is launching
	bool	InformTileLaunch( CTile* pTile, POINT Point, double DiffPosTileMouseX, double DiffPosTileMouseY );
	// Get the tile position for a pixel
	void	GetTilePosition( POINT Point, int& PosX, int& PosY );
	// Center on a point
	void	CenterOnPoint( double XCenter, double YCenter );
	// Center on a position and blink
	void	CenterOnPosAndBlink( int x, int y, int z );
	// The view need to be update only for current level or above
	void	OnUpdateFromCurrentLevel(CView* pSender, LPARAM lHint, CObject* pHint);

	DECLARE_DYNCREATE(CHeroscapeEditorView)

// Attributs
public:
	CHeroscapeEditorDoc* GetDocument() const;

// Opérations
public:

// Substitutions
public:
	virtual void OnDraw(CDC* pDC);  // substitué pour dessiner cette vue
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Fonctions générées de la table des messages
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
public:
	afx_msg void OnZoomin();
public:
	afx_msg void OnZoomout();
public:
	afx_msg void OnZoomValue();
public:
	afx_msg void OnFullview();
public:
	afx_msg void OnLevelup();
public:
	afx_msg void OnLeveldown();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
public:
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
public:
	afx_msg void OnUpdateLeveldown(CCmdUI *pCmdUI);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
public:
	afx_msg void OnEditRotateLeft();
public:
	afx_msg void OnEditRotateRight();
public:
	afx_msg void OnUpdateEditRotateLeft(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateEditRotateRight(CCmdUI *pCmdUI);
public:
	afx_msg void OnEditRemove();
public:
	afx_msg void OnUpdateEditRemove(CCmdUI *pCmdUI);
public:
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
protected:
//	virtual void OnActivateFrame(UINT nState, CFrameWnd* pDeactivateFrame);
public:
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
public:
	afx_msg void OnSelectAll();
public:
	afx_msg void OnSelectNothing();
public:
	afx_msg void OnSelectInverse();
public:
	afx_msg void OnSelectLevelup();
public:
	afx_msg void OnSelectLeveldown();
public:
	afx_msg void OnUpdateOutilsReverse(CCmdUI *pCmdUI);
public:
	afx_msg void OnOutilsReverse();
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
public:
	afx_msg void OnSelectLevel();
public:
	afx_msg void OnUpdateSelectLevelup(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateSelectLeveldown(CCmdUI *pCmdUI);
public:
	afx_msg void OnOutilsNumber();
public:
	afx_msg void OnUpdateOutilsNumber(CCmdUI *pCmdUI);
	afx_msg void OnFichierApercunum();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnFilePrint();
	afx_msg void OnFichierImprimernum();
	afx_msg void OnOutilsRemovelevel();
	afx_msg void OnOutilsInsertlevel();
	afx_msg void OnOutilsGoLevel();
	afx_msg void OnSelectSameTileSameLevel();
};

inline CHeroscapeEditorDoc* CHeroscapeEditorView::GetDocument() const { return reinterpret_cast<CHeroscapeEditorDoc*>(m_pDocument); }

