#ifndef _GAMECHATBAR_H_
#define _GAMECHATBAR_H_

#include "GameChatView.h"
#include "SizeCBar.h"

class CGameChatBar : public CSizingControlBar
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
	CGameChatView		m_GameChatFV;

//************
// The methods
//************
public:
	// The constructor
	CGameChatBar();
	// The destructor
    virtual ~CGameChatBar();
	// When the chat bar is moved
	afx_msg void	OnMove(int x, int y);
	// When the chat bar is resize
    afx_msg void	OnSize(UINT nType, int cx, int cy);
	// Add a message to the list
	void			AddMessage( bool IsMine, CString From, CString Message );
	// Reset the message list
	void			ResetMessage();

// Attributes
public:

// Overridables
    virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CGameChatBar)
	//}}AFX_VIRTUAL

// Implementation
public:

    // Generated message map functions
protected:
    //{{AFX_MSG(CGameChatBar)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
public:
};

#endif // #ifndef _GAMECHATBAR_H_
