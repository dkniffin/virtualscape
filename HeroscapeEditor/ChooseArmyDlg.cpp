// ChooseArmyDlg.cpp : fichier d'implémentation
//

#include "StdAfx.h"

#include "ChooseArmyDlg.h"
#include "HeroscapeEditor.h"
#include "ListCtrlArmy.h"

IMPLEMENT_DYNAMIC(CChooseArmyDlg, CDialog)

// The constructor
//
CChooseArmyDlg::CChooseArmyDlg(CWnd* pParent /*=NULL*/)
:
// Call the base class
CDialog(CChooseArmyDlg::IDD, pParent)
{
}

// The destructor
//
CChooseArmyDlg::~CChooseArmyDlg()
{
}

// Synchronize members and control
//
void CChooseArmyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

// The windows message managing
//
BEGIN_MESSAGE_MAP(CChooseArmyDlg, CDialog)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// Set the max point for choose army
//
void CChooseArmyDlg::SetPoint( int Point )
{
	m_Point = Point;
}

// The dialog bos is initialize
//
BOOL CChooseArmyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString Str,Str2;
	Str.LoadStringW(IDS_POINTFORARMY);

	Str2.Format( Str, m_Point );

	GetDlgItem(IDC_POINTFORARMY)->SetWindowTextW(Str2);

	return TRUE;
}

// The dialog is created
//
int CChooseArmyDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pListViewArmy = new CListCtrlArmy;
    if (!m_pListViewArmy->Create(NULL,_T(""),WS_CHILD|WS_VISIBLE|WS_HSCROLL,CRect(0,20,1000,1000),this, 30011))
        return -1;

	m_pListViewArmy->SetArmyList( m_pArmyList );

	return 0;
}

// Size of the window change so resize child control
//
void CChooseArmyDlg::OnSize(UINT nType, int cx, int cy)
{
	// Call the base class
	CDialog::OnSize(nType, cx, cy);

	CRect rc;
    GetClientRect(rc);
	m_pListViewArmy->SetWindowPos( NULL, 10, 10, cx-20, cy-50, SWP_NOZORDER|SWP_NOACTIVATE );
}

// Save the selection
//
void CChooseArmyDlg::OnOK()
{
	m_SelectedIndex = m_pListViewArmy->m_SelectedIndex;

	// Call the base class
	CDialog::OnOK();
}

// Set the ArmyList
//
void CChooseArmyDlg::SetArmyList( CPtrArray* pArmyList )
{
	m_pArmyList = pArmyList;
}