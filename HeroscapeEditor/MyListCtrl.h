#ifndef _MYLISTCTRL_H_
#define _MYLISTCTRL_H_

class CMyListCtrl : public CListCtrl
{
//*************
// The members
//*************
protected:
	// To know it this is a special list or not
	bool		m_IsSpecialList;
	// The array with more data
	CPtrArray	m_ArrayDatas;

public:
	// The active view
	CView*		m_pView;

//*************
// The methods
//*************
public:
	// The constructor
	CMyListCtrl();
	// Set if this is a special list or not
	void SetSpecialList( bool IsSpecialList );
	// Draw the item
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	// Delete all the item datas
	void DeleteAllDatas();
	// Add informations
	void AddInformationDatas( void* pDatas );

//******************
// Generate by VC++
//******************

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListCtrl)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif // #ifndef _MYLISTCTRL_H_
