#ifndef _MDICLIENT_H_
#define _MDICLIENT_H_

class CMdiClient : public CWnd
{
	DECLARE_DYNCREATE(CMdiClient)

// Attributes
private:
	// The bitmap
	CBitmap*	m_pBmp;
	// The back color
	COLORREF	m_nBackColor;

public:
	// The constructor
	CMdiClient();
	// Set the bitmap
	BOOL SetBitmap(UINT nID);
	// Set the back color
	COLORREF SetBackColor(COLORREF nBackColor);
	// The destructor
	virtual ~CMdiClient();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMdiClient)
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMdiClient)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif // #ifndef _MDICLIENT_H_
