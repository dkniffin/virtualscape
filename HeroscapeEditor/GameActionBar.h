#ifndef _GAMEACTIONBAR_H_
#define _GAMEACTIONBAR_H_

#include "GameActionView.h"
#include "SizeCBar.h"

class CGameActionBar : public CSizingControlBar
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
	CGameActionView		m_GameActionFV;

//************
// The methods
//************
public:
	// The constructor
	CGameActionBar();
	// The destructor
    virtual ~CGameActionBar();
	// When the bar is moved
	afx_msg void	OnMove(int x, int y);
	// When the bar is resize
    afx_msg void	OnSize(UINT nType, int cx, int cy);
	// Reset all the actions
	void			ResetAction();

// Attributes
public:

// Overridables
    virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CGameActionBar)
	//}}AFX_VIRTUAL

// Implementation
public:

    // Generated message map functions
protected:
    //{{AFX_MSG(CGameActionBar)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
public:
};

#endif // #ifndef _GAMEACTIONBAR_H_
