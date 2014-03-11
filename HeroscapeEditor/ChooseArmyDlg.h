#pragma once

#include "ListCtrlArmy.h"
#include "Resource.h"

// Boîte de dialogue CChooseArmyDlg

class CChooseArmyDlg : public CDialog
{
	DECLARE_DYNAMIC(CChooseArmyDlg)
//************
// The members
//************
public:
	// The point for choose army
	int				m_Point;
	// The list with army
	CListCtrlArmy*	m_pListViewArmy;
	// The army list
	CPtrArray*		m_pArmyList;
	// The current selection
	int				m_SelectedIndex;

//************
// The methods
//************
public:
	// The constructor
	CChooseArmyDlg(CWnd* pParent = NULL);
	// The destructor
	virtual ~CChooseArmyDlg();
	// Set the max point for choose army
	void	SetPoint( int Point );
	// Set the ArmyList
	void	SetArmyList( CPtrArray* pArmyList );

// Données de boîte de dialogue
	enum { IDD = IDD_CHOOSE_ARMY };

protected:
	// Synchronize members and control
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	virtual void OnOK();
};
