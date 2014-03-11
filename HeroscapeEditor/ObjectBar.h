#ifndef _OBJECTBAR_H_
#define _OBJECTBAR_H_

#include "sizecbar.h"
#include "ObjectView.h"

class CObjectBar : public CSizingControlBar
{
//************
// The members
//************

protected:
	// The icon
	CStatic				m_wndIcon;
	// The text
	CStatic				m_wndText;
	// The font for the m_wndText
    CFont				m_font;
	// The bitmap for the window symbol
	CBitmap				m_bmp;

public:
	// The info form view
	CObjectView			m_ObjectFV;

//************
// The methods
//************
public:
	// The constructor
	CObjectBar();
	// The destructor
    virtual ~CObjectBar();
	// Set the current document
	void	SetCurrentDoc( void* pDoc );
	// Redraw the object control
	void	RedrawObjectCtrl();

// Attributes
public:

// Overridables
    virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CObjectBar)
	//}}AFX_VIRTUAL

// Implementation
public:

    // Generated message map functions
protected:
    //{{AFX_MSG(CObjectBar)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMove(int x, int y);
    afx_msg void OnSize(UINT nType, int cx, int cy);
};

#endif // #ifndef _OBJECTBAR_H_
