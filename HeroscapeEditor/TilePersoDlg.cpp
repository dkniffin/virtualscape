// TilePersoDlg.cpp : implementation file
//

#include "StdAfx.h"

#include "GlobalIHM.h"
#include "HeroscapeEditor.h"
#include "TilePerso.h"
#include "TilePersoDlg.h"
#include "TilePerso1Dlg.h"

// CTilePersoDlg dialog

IMPLEMENT_DYNAMIC(CTilePersoDlg, CDialog)

// The constructor
//
CTilePersoDlg::CTilePersoDlg(CWnd* pParent /*=NULL*/)
:
// Call the base class
CDialog(CTilePersoDlg::IDD, pParent)
{

}

// The destructor
//
CTilePersoDlg::~CTilePersoDlg()
{
}

// Synchronize data between control and members
//
void CTilePersoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TILEPERSO, m_lc_TileList);
}


BEGIN_MESSAGE_MAP(CTilePersoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADDTILEPERSO, &CTilePersoDlg::OnBnClickedButtonAddtileperso)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &CTilePersoDlg::OnBnClickedButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CTilePersoDlg::OnBnClickedButtonModify)
END_MESSAGE_MAP()


// CTilePersoDlg message handlers
//
BOOL CTilePersoDlg::OnInitDialog()
{
	// Call the base class
	CDialog::OnInitDialog();

	// Set the column
	CString	Str;
	Str.LoadStringW( IDS_TILEPERSO_LIST );
	CGlobalIHM::CreateColumnListCtrl( &m_lc_TileList, Str );

	// Add all current tile perso
	for( int i=0; i<theApp.m_TilePersoList.GetCount(); i++ )
	{
		CTilePerso* pTile = (CTilePerso*) theApp.m_TilePersoList.GetAt(i);

		CString Str;
		Str.Format( _T("%s;%i;%i;%s;%s"), pTile->m_Name, pTile->m_NbTile, pTile->m_Quantity, pTile->m_PersonalTexture, pTile->m_PersonalTextureSide );
		CGlobalIHM::AddListItem( &m_lc_TileList, Str, -1, -1 );
	}
	

	return TRUE;
}

// The user want add a tile perso
//
void CTilePersoDlg::OnBnClickedButtonAddtileperso()
{
	CTilePerso1Dlg Dlg;

	// Create the new tile perso
	CTilePerso* pTile = (CTilePerso*) CTile::GetNewTile( TYPE_PERSONAL*1000 );

	Dlg.m_Name = pTile->m_Name;
	Dlg.m_NbHex = pTile->m_NbTile;
	Dlg.m_NbDispo = pTile->m_Quantity;
	Dlg.m_Character = pTile->m_Char;
	Dlg.m_Texture = pTile->m_PersonalTexture;
	Dlg.m_TextureSide = pTile->m_PersonalTextureSide;
	Dlg.m_Color2D = pTile->m_TileColor;

	if( Dlg.DoModal()==IDOK )
	{
		pTile->m_Name = Dlg.m_Name;
		pTile->m_NbTile = Dlg.m_NbHex;
		pTile->m_Quantity = Dlg.m_NbDispo;
		pTile->m_Char = Dlg.m_Character;
		pTile->m_PersonalTexture = Dlg.m_Texture;
		pTile->m_PersonalTextureSide = Dlg.m_TextureSide;
		pTile->m_TileColor = Dlg.m_Color2D;

		pTile->Init();

		// Add the tile to tile perso
		CString Str;
		Str.Format( _T("%s;%i;%i;%s;%s"), pTile->m_Name, pTile->m_NbTile, pTile->m_Quantity, pTile->m_PersonalTexture, pTile->m_PersonalTextureSide );
		CGlobalIHM::AddListItem( &m_lc_TileList, Str, -1, -1 );

		theApp.m_TilePersoList.Add( pTile );
	}
	else
	{
		delete pTile;
	}
}

// The user want delete a tile perso
//
void CTilePersoDlg::OnBnClickedButtonRemove()
{
	// Verify that something is selected
	int nItem = m_lc_TileList.GetNextItem(-1, LVNI_SELECTED);
	if( nItem>=0 )
	{
		// Remove the selected item
		CTilePerso* pTile = (CTilePerso*) theApp.m_TilePersoList.GetAt(nItem);
		delete pTile;
		theApp.m_TilePersoList.RemoveAt(nItem);

		m_lc_TileList.DeleteItem( nItem );
	}
}

// The user want modify a tile perso
//
void CTilePersoDlg::OnBnClickedButtonModify()
{
	int nItem = m_lc_TileList.GetNextItem(-1, LVNI_SELECTED);
	if( nItem>=0 )
	{
		// Edit the selected item
		CTilePerso* pTile = (CTilePerso*) theApp.m_TilePersoList.GetAt(nItem);

		CTilePerso1Dlg Dlg;

		Dlg.m_Name = pTile->m_Name;
		Dlg.m_NbHex = pTile->m_NbTile;
		Dlg.m_NbDispo = pTile->m_Quantity;
		Dlg.m_Character = pTile->m_Char;
		Dlg.m_Texture = pTile->m_PersonalTexture;
		Dlg.m_TextureSide = pTile->m_PersonalTextureSide;
		Dlg.m_Color2D = pTile->m_TileColor;

		if( Dlg.DoModal()==IDOK )
		{
			pTile->m_Name = Dlg.m_Name;
			pTile->m_NbTile = Dlg.m_NbHex;
			pTile->m_Quantity = Dlg.m_NbDispo;
			pTile->m_Char = Dlg.m_Character;
			pTile->m_PersonalTexture = Dlg.m_Texture;
			pTile->m_PersonalTextureSide = Dlg.m_TextureSide;
			pTile->m_TileColor = Dlg.m_Color2D;

			pTile->Init();

			// Set the tile to tile perso
			CString Str;
			Str.Format( _T("%s;%i;%i;%s;%s"), pTile->m_Name, pTile->m_NbTile, pTile->m_Quantity, pTile->m_PersonalTexture, pTile->m_PersonalTextureSide );
			CGlobalIHM::SetListItem( &m_lc_TileList, Str, nItem, -1 );
		}
	}
}
