#ifndef _INFOLISTBAR_H_
#define _INFOLISTBAR_H_

#include "MyListCtrl.h"
#include "SizeCBar.h"

class CInfoListBar : public CSizingControlBar
{
//************
// The members
//************

protected:
	// The Tree view
    CMyListCtrl	m_wndMyListCtrl;
	// The associate image list
	CImageList	m_ImgLayerList;
	// The icon
	CStatic		m_wndIcon;
	// The text
	CStatic		m_wndText;
	// The font for the m_wndText
    CFont		m_font;
	// The bitmap for the window symbol
	CBitmap		m_bmp;
	// The mode drag and drop or not
	bool		m_b_ModeDrag;
	// The image list for icons
	CImageList	m_ImageList;

//************
// The methods
//************

public:
	// The constructor
	CInfoListBar();
	// The destructor
    virtual				~CInfoListBar();
	// Get the list control
	CListCtrl*			GetListCtrl();
	// Get the current selected object (or NULL)
	int					GetSelectedObjectID();

protected:
	// When the user right clic on the list
	void		OnListRightClick();
	// When the user left clic on the list
	void		OnListLeftClick();
	// The selection has changed
	void		OnSelChanged( NMLISTVIEW* pnmlv );
	// The user clic on an item
	void		OnKeyDown( int iItem );
	// When the user double clic on the list
	void		OnListDblClick();

// Attributes
public:

// Overridables
    virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CInfoListBar)
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:

    // Generated message map functions
protected:
    //{{AFX_MSG(CInfoListBar)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#endif // #ifndef _INFOLISTBAR_H_
