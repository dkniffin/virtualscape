// ChildFrm.h : interface de la classe CChildFrame
//
#pragma once

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)

public:
	// The constructor
	CChildFrame();
	// The destructor
	virtual ~CChildFrame();
	// Before to create the window
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	// When this window get the focus
	afx_msg void OnSetFocus(CWnd* pOldWnd);

protected:
	// generate by VC++
	DECLARE_MESSAGE_MAP()

};
