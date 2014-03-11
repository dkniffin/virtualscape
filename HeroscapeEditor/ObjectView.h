#ifndef _OBJECTVIEW_H_
#define _OBJECTVIEW_H_

#include "Resource.h"
#include "afxcmn.h"

#include "ListCtrlObject.h"

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CObjectView : public CFormView
{
//************
// The methods
//************
public:
	// The constructor
	CObjectView();
	// The destructor
	~CObjectView();
	// Create the window
	void	Create(CWnd* Parent);
	// Set the current document
	void	SetCurrentDoc( void* pDoc );
	// Redraw the object control
	void	RedrawObjectCtrl();
	// Init the window
	void	Init();

//******************
// Generated by VC++
//******************

protected:
	DECLARE_DYNCREATE(CObjectView)

// Form Data
public:
	//{{AFX_DATA(CInfoView)
	enum { IDD = IDD_OBJECTVIEW };
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CObjectView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CListCtrlObject* m_pObjectList;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	afx_msg void OnTcnSelchangeTabObjectType(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnMove(int x, int y);
};

#endif // #ifndef _OBJECTVIEW_H_