// ObjectView.cpp : implementation file
//

#include "StdAfx.h"

#include "HeroscapeEditor.h"
#include "ObjectView.h"
#include "TileAsphalt1.h"
#include "TileAsphalt2.h"
#include "TileAsphalt7.h"
#include "TileCastle1.h"
#include "TileCastle7.h"
#include "TileCastle9.h"
#include "TileCastleArch.h"
#include "TileCastleBaseCorner.h"
#include "TileCastleBaseEnd.h"
#include "TileCastleBaseStraight.h"
#include "TileCastleBattlement.h"
#include "TileCastleDoor.h"
#include "TileCastleFlag.h"
#include "TileCastleLadder.h"
#include "TileCastleWallCorner.h"
#include "TileCastleWallStraight.h"
#include "TileCastleWallEnd.h"
#include "TileConcrete1.h"
#include "TileConcrete2.h"
#include "TileConcrete7.h"
#include "TileDungeon1.h"
#include "TileDungeon2.h"
#include "TileDungeon3.h"
#include "TileDungeon7.h"
#include "TileDungeon24.h"
#include "TileFigure.h"
#include "TileFigure2.h"
#include "TileGlacier1_7.h"
#include "TileGlacier3.h"
#include "TileGlacier4.h"
#include "TileGlacier6.h"
#include "TileGlyph1.h"
#include "TileGrass1.h"
#include "TileGrass2.h"
#include "TileGrass3.h"
#include "TileGrass7.h"
#include "TileGrass24.h"
#include "TileHive6.h"
#include "TileIce1.h"
#include "TileLava1.h"
#include "TileLavaField7.h"
#include "TileLavaField2.h"
#include "TileLavaField1.h"
#include "TileMarvelWall6.h"
#include "TileMarvelWall6Breaked.h"
#include "TileOutcrop1_7.h"
#include "TileOutcrop3.h"
#include "TilePalm14.h"
#include "TilePalm15.h"
#include "TilePalm16.h"
#include "TilePerso.h"
#include "TileRoad1.h"
#include "TileRoad2.h"
#include "TileRoad5.h"
#include "TileRock1.h"
#include "TileRock2.h"
#include "TileRock3.h"
#include "TileRock7.h"
#include "TileRock24.h"
#include "TileRuin2.h"
#include "TileRuin3.h"
#include "TileSand1.h"
#include "TileSand2.h"
#include "TileSand3.h"
#include "TileSand7.h"
#include "TileShadow1.h"
#include "TileShadow2.h"
#include "TileSnow1.h"
#include "TileSnow2.h"
#include "TileStart1.h"
#include "TileSwamp1.h"
#include "TileSwamp2.h"
#include "TileSwamp3.h"
#include "TileSwamp7.h"
#include "TileSwamp24.h"
#include "TileSwampWater1.h"
#include "TileTicallaGrass1.h"
#include "TileTree4.h"
#include "TileTree1_10.h"
#include "TileTree1_11.h"
#include "TileTree1_12.h"
#include "TileWater1.h"
#include "TileWater2.h"
#include "TileWall4.h"

IMPLEMENT_DYNCREATE(CObjectView, CFormView)

// The constructor
//
CObjectView::CObjectView()
:
// Call the base class
CFormView(CObjectView::IDD)
{
	//{{AFX_DATA_INIT(CObjectView)
	//}}AFX_DATA_INIT
	m_pObjectList = NULL;
}

// The destructor
//
CObjectView::~CObjectView()
{
}

// Exchange data between control and members
//
void CObjectView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObjectView)
	//}}AFX_DATA_MAP
}

// The window messaging
//
BEGIN_MESSAGE_MAP(CObjectView, CFormView)
	//{{AFX_MSG_MAP(CInfoView)
	//}}AFX_MSG_MAP
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_OBJECT_TYPE, &CObjectView::OnTcnSelchangeTabObjectType)
	ON_WM_MOVE()
END_MESSAGE_MAP()

// Create the window
//
void CObjectView::Create(CWnd* Parent)
{
	CFormView::Create( NULL, NULL, WS_CHILD|WS_VISIBLE, CRect(0,16,2000,2000), Parent, 3008, NULL );
}

// Destroy the non client area
//
void CObjectView::PostNcDestroy() 
{
	// Do nothing
}

// Init the view at first time
//
void CObjectView::OnInitialUpdate() 
{
	// Call the base class
	CFormView::OnInitialUpdate();
}

// Create the controls when the view is created
//
int CObjectView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pObjectList = new CListCtrlObject;
    if (!m_pObjectList->Create(NULL,_T(""),WS_CHILD|WS_VISIBLE,CRect(0,0,1000,1000),this, 30003))
        return -1;

	return 0;
}

// Init the window
//
void CObjectView::Init()
{
	CTabCtrl* pTabCtrl = (CTabCtrl*) GetDlgItem(IDC_TAB_OBJECT_TYPE);

	CString Str;
	Str.LoadString( IDS_BASIC );
	pTabCtrl->InsertItem( TC_BASIC, Str );
	Str.LoadString( IDS_TUNDRA );
	pTabCtrl->InsertItem( TC_TUNDRA, Str );
	Str.LoadString( IDS_FORTRESS );
	pTabCtrl->InsertItem( TC_FORTRESS, Str );
	Str.LoadString( IDS_ROAD );
	pTabCtrl->InsertItem( TC_ROAD, Str );
	Str.LoadString( IDS_VOLCARREN );
	pTabCtrl->InsertItem( TC_VOLCARREN, Str );
	Str.LoadString( IDS_TICALLA );
	pTabCtrl->InsertItem( TC_TICALLA, Str );
	Str.LoadString( IDS_GLYPH );
	pTabCtrl->InsertItem( TC_GLYPH, Str );
	Str.LoadString( IDS_START );
	pTabCtrl->InsertItem( TC_STARTAREA, Str );
	Str.LoadString( IDS_MARVEL );
	pTabCtrl->InsertItem( TC_MARVEL, Str );
	Str.LoadString( IDS_SWARM );
	pTabCtrl->InsertItem( TC_SWARM, Str );
	Str.LoadString( IDS_DUNGEON_HEX );
	pTabCtrl->InsertItem( TC_DUNGEON, Str );
	Str.LoadString( IDS_FIGURE );
	pTabCtrl->InsertItem( TC_FIGURE, Str );
	Str.LoadString( IDS_PERSONAL_HEX );
	pTabCtrl->InsertItem( TC_PERSONAL_HEX, Str );

	pTabCtrl->SetCurSel( TC_BASIC );
	OnTcnSelchangeTabObjectType( NULL, NULL );
}

// When the view is resize then resize the controls
//
void CObjectView::OnSize(UINT nType, int cx, int cy)
{
	// Call the base class
	CFormView::OnSize(nType, cx, cy);

	CTabCtrl* pTabCtrl = (CTabCtrl*) GetDlgItem(IDC_TAB_OBJECT_TYPE);

	if( pTabCtrl!=NULL )
	{
		// Change size of the ListCtrlObject
		CRect Rect1,Rect2;
		int yMin=-1000;
		if( ::IsWindow(pTabCtrl->m_hWnd) )
		{
			// Resize the tab ctrl
			pTabCtrl->SetWindowPos( NULL, 0, 0, cx, cy, SWP_NOZORDER|SWP_NOACTIVATE );

			for( int i=0; i<pTabCtrl->GetItemCount(); i++ )
			{
				pTabCtrl->GetItemRect( i, &Rect1 );
				if( Rect1.bottom>yMin )
					yMin = Rect1.bottom;
			}
			pTabCtrl->GetClientRect( &Rect2 );
			m_pObjectList->SetWindowPos( NULL, 2, yMin+2, cx-6, Rect2.bottom-yMin-6, SWP_NOZORDER|SWP_NOACTIVATE );
		}
	}
}

// The user change the tab
//
void CObjectView::OnTcnSelchangeTabObjectType(NMHDR *pNMHDR, LRESULT *pResult)
{
	CTabCtrl* pTabCtrl = (CTabCtrl*) GetDlgItem(IDC_TAB_OBJECT_TYPE);

	int Index = pTabCtrl->GetCurSel();

	CString Str;

	m_pObjectList->RemoveAllObjects();
	switch( Index )
	{
	case TC_BASIC:
		m_pObjectList->AddObject( new CTileGrass24 );
		m_pObjectList->AddObject( new CTileGrass7 );
		m_pObjectList->AddObject( new CTileGrass3 );
		m_pObjectList->AddObject( new CTileGrass2 );
		m_pObjectList->AddObject( new CTileGrass1 );
		m_pObjectList->AddObject( new CTileRock24 );
		m_pObjectList->AddObject( new CTileRock7 );
		m_pObjectList->AddObject( new CTileRock3 );
		m_pObjectList->AddObject( new CTileRock2 );
		m_pObjectList->AddObject( new CTileRock1 );
		m_pObjectList->AddObject( new CTileSand7 );
		m_pObjectList->AddObject( new CTileSand3 );
		m_pObjectList->AddObject( new CTileSand2 );
		m_pObjectList->AddObject( new CTileSand1 );
		m_pObjectList->AddObject( new CTileWater1 );
		m_pObjectList->AddObject( new CTileWater2 );
		m_pObjectList->AddObject( new CTileRuin3 );
		m_pObjectList->AddObject( new CTileRuin2 );
		break;
	case TC_TUNDRA:
		m_pObjectList->AddObject( new CTileSnow1 );
		m_pObjectList->AddObject( new CTileSnow2 );
		m_pObjectList->AddObject( new CTileIce1 );
		m_pObjectList->AddObject( new CTileGlacier6 );
		m_pObjectList->AddObject( new CTileGlacier4 );
		m_pObjectList->AddObject( new CTileGlacier3 );
		m_pObjectList->AddObject( new CTileGlacier1_7 );
		break;
	case TC_FORTRESS:
		m_pObjectList->AddObject( new CTileCastle9 );
		m_pObjectList->AddObject( new CTileCastle7 );
		m_pObjectList->AddObject( new CTileCastle1 );
		m_pObjectList->AddObject( new CTileCastleBaseCorner );
		m_pObjectList->AddObject( new CTileCastleBaseStraight );
		m_pObjectList->AddObject( new CTileCastleBaseEnd );
		m_pObjectList->AddObject( new CTileCastleWallCorner );
		m_pObjectList->AddObject( new CTileCastleWallStraight );
		m_pObjectList->AddObject( new CTileCastleWallEnd );
		m_pObjectList->AddObject( new CTileCastleDoor );
		m_pObjectList->AddObject( new CTileCastleArch );
		m_pObjectList->AddObject( new CTileCastleBattlement );
		m_pObjectList->AddObject( new CTileCastleLadder );
		m_pObjectList->AddObject( new CTileCastleFlag );
		break;
	case TC_ROAD:
		m_pObjectList->AddObject( new CTileRoad5 );
		m_pObjectList->AddObject( new CTileRoad2 );
		m_pObjectList->AddObject( new CTileRoad1 );
		m_pObjectList->AddObject( new CTileWall4 );
		m_pObjectList->AddObject( new CTileTree4 );
		m_pObjectList->AddObject( new CTileTree1_12 );
		m_pObjectList->AddObject( new CTileTree1_11 );
		m_pObjectList->AddObject( new CTileTree1_10 );
		break;
	case TC_VOLCARREN:
		m_pObjectList->AddObject( new CTileLavaField7 );
		m_pObjectList->AddObject( new CTileLavaField2 );
		m_pObjectList->AddObject( new CTileLavaField1 );
		m_pObjectList->AddObject( new CTileLava1 );
		break;
	case TC_TICALLA:
		m_pObjectList->AddObject( new CTilePalm14 );
		m_pObjectList->AddObject( new CTilePalm15 );
		m_pObjectList->AddObject( new CTilePalm16 );
		m_pObjectList->AddObject( new CTileTicallaGrass1 );
		break;
	case TC_GLYPH:
		m_pObjectList->AddObject( new CTileGlyph1( '?' ) );
		m_pObjectList->AddObject( new CTileGlyph1( 'A' ) );
		m_pObjectList->AddObject( new CTileGlyph1( 'G' ) );
		m_pObjectList->AddObject( new CTileGlyph1( 'I' ) );
		m_pObjectList->AddObject( new CTileGlyph1( 'V' ) );
		m_pObjectList->AddObject( new CTileGlyph1( 'D' ) );
		m_pObjectList->AddObject( new CTileGlyph1( 'B' ) );
		m_pObjectList->AddObject( new CTileGlyph1( 'K' ) );
		m_pObjectList->AddObject( new CTileGlyph1( 'E' ) );
		m_pObjectList->AddObject( new CTileGlyph1( 'M' ) );
		m_pObjectList->AddObject( new CTileGlyph1( 'L' ) );
		m_pObjectList->AddObject( new CTileGlyph1( 'S' ) );
		m_pObjectList->AddObject( new CTileGlyph1( 'R' ) );
		m_pObjectList->AddObject( new CTileGlyph1( 'J' ) );
		m_pObjectList->AddObject( new CTileGlyph1( 'W' ) );
		m_pObjectList->AddObject( new CTileGlyph1( 'P' ) );
		m_pObjectList->AddObject( new CTileGlyph1( 'O' ) );
		m_pObjectList->AddObject( new CTileGlyph1( 'N' ) );
		m_pObjectList->AddObject( new CTileGlyph1( 'C' ) );
		m_pObjectList->AddObject( new CTileGlyph1( 'T' ) );
		m_pObjectList->AddObject( new CTileGlyph1( 'U' ) );
		break;
	case TC_STARTAREA:
		Str.LoadString( IDS_RED );
		m_pObjectList->AddObject( new CTileStart1( Str, RGB(255,0,0) ) );
		Str.LoadString( IDS_GREEN );
		m_pObjectList->AddObject( new CTileStart1( Str, RGB(0,255,0) ) );
		Str.LoadString( IDS_BLUE );
		m_pObjectList->AddObject( new CTileStart1( Str, RGB(0,0,255) ) );
		Str.LoadString( IDS_YELLOW );
		m_pObjectList->AddObject( new CTileStart1( Str, RGB(255,255,0) ) );
		Str.LoadString( IDS_VIOLET );
		m_pObjectList->AddObject( new CTileStart1( Str, RGB(255,0,255) ) );
		Str.LoadString( IDS_CYAN );
		m_pObjectList->AddObject( new CTileStart1( Str, RGB(0,255,255) ) );
		Str.LoadString( IDS_ORANGE );
		m_pObjectList->AddObject( new CTileStart1( Str, RGB(255,128,0) ) );
		Str.LoadString( IDS_PURPLE );
		m_pObjectList->AddObject( new CTileStart1( Str, RGB(128,0,255) ) );
		break;
	case TC_MARVEL:
		m_pObjectList->AddObject( new CTileConcrete7 );
		m_pObjectList->AddObject( new CTileConcrete2 );
		m_pObjectList->AddObject( new CTileConcrete1 );
		m_pObjectList->AddObject( new CTileAsphalt7 );
		m_pObjectList->AddObject( new CTileAsphalt2 );
		m_pObjectList->AddObject( new CTileAsphalt1 );
		m_pObjectList->AddObject( new CTileMarvelWall6 );
		m_pObjectList->AddObject( new CTileMarvelWall6Breaked );
		break;
	case TC_SWARM:
		m_pObjectList->AddObject( new CTileSwampWater1 );
		m_pObjectList->AddObject( new CTileSwamp1 );
		m_pObjectList->AddObject( new CTileSwamp2 );
		m_pObjectList->AddObject( new CTileSwamp3 );
		m_pObjectList->AddObject( new CTileSwamp7 );
		m_pObjectList->AddObject( new CTileSwamp24 );
		m_pObjectList->AddObject( new CTileHive6 );
		break;
	case TC_DUNGEON:
		m_pObjectList->AddObject( new CTileDungeon1 );
		m_pObjectList->AddObject( new CTileDungeon2 );
		m_pObjectList->AddObject( new CTileDungeon3 );
		m_pObjectList->AddObject( new CTileDungeon7 );
		m_pObjectList->AddObject( new CTileDungeon24 );
		m_pObjectList->AddObject( new CTileOutcrop1_7 );
		m_pObjectList->AddObject( new CTileOutcrop3 );
		m_pObjectList->AddObject( new CTileShadow1 );
		m_pObjectList->AddObject( new CTileShadow2 );
		break;
	case TC_FIGURE:
		{
			CTileFigure* pTileFigure = new CTileFigure;
			pTileFigure->m_FigureName.LoadStringW( IDS_NEGOKSA );
			pTileFigure->m_FigureFile = _T("NE-GOK-SA");
			m_pObjectList->AddObject( pTileFigure );
			CTileFigure* pTileFigure2 = new CTileFigure;
			pTileFigure2->m_FigureName.LoadStringW( IDS_AGENTCARR );
			pTileFigure2->m_FigureFile = _T("AGENT CARR");
			m_pObjectList->AddObject( pTileFigure2 );
			CTileFigure2* pTileFigure3 = new CTileFigure2;
			pTileFigure3->m_FigureName.LoadStringW( IDS_MIMRING );
			pTileFigure3->m_FigureFile = _T("MIMRING");
			m_pObjectList->AddObject( pTileFigure3 );
			CTileFigure* pTileFigure4 = new CTileFigure;
			pTileFigure4->m_FigureName.LoadStringW( IDS_SYVARRIS );
			pTileFigure4->m_FigureFile = _T("SYVARRIS");
			m_pObjectList->AddObject( pTileFigure4 );
			CTileFigure* pTileFigure5 = new CTileFigure;
			pTileFigure5->m_FigureName.LoadStringW( IDS_MARCHEMORT9000 );
			pTileFigure5->m_FigureFile = _T("MARCHEMORT 9000");
			m_pObjectList->AddObject( pTileFigure5 );
			CTileFigure* pTileFigure6 = new CTileFigure;
			pTileFigure6->m_FigureName.LoadStringW( IDS_SGTDRAKEALEXANDER );
			pTileFigure6->m_FigureFile = _T("SGT DRAKE ALEXANDER");
			m_pObjectList->AddObject( pTileFigure6 );
			CTileFigure2* pTileFigure7 = new CTileFigure2;
			pTileFigure7->m_FigureName.LoadStringW( IDS_GRIMNAK );
			pTileFigure7->m_FigureFile = _T("GRIMNAK");
			m_pObjectList->AddObject( pTileFigure7 );
			CTileFigure* pTileFigure8 = new CTileFigure;
			pTileFigure8->m_FigureName.LoadStringW( IDS_FINNLECHAMPIONVIKING );
			pTileFigure8->m_FigureFile = _T("FINN LE CHAMPION VIKING");
			m_pObjectList->AddObject( pTileFigure8 );
			CTileFigure* pTileFigure9 = new CTileFigure;
			pTileFigure9->m_FigureName.LoadStringW( IDS_RAELINLAGUERRIEREKYRIE );
			pTileFigure9->m_FigureFile = _T("RAELIN LA GUERRIERE KYRIE");
			m_pObjectList->AddObject( pTileFigure9 );
			CTileFigure* pTileFigure10 = new CTileFigure;
			pTileFigure10->m_FigureName.LoadStringW( IDS_THORGRIMLECHAMPIONVIKING );
			pTileFigure10->m_FigureFile = _T("THORGRIM LE CHAMPION VIKING");
			m_pObjectList->AddObject( pTileFigure10 );
			CTileFigure* pTileFigure11 = new CTileFigure;
			pTileFigure11->m_FigureName.LoadStringW( IDS_GUERRIERSMARRO1_4 );
			pTileFigure11->m_FigureFile = _T("GUERRIERS MARRO 1-4");
			m_pObjectList->AddObject( pTileFigure11 );
			CTileFigure* pTileFigure12 = new CTileFigure;
			pTileFigure12->m_FigureName.LoadStringW( IDS_GUERRIERSMARRO2_4 );
			pTileFigure12->m_FigureFile = _T("GUERRIERS MARRO 2-4");
			m_pObjectList->AddObject( pTileFigure12 );
			CTileFigure* pTileFigure13 = new CTileFigure;
			pTileFigure13->m_FigureName.LoadStringW( IDS_GUERRIERSMARRO3_4 );
			pTileFigure13->m_FigureFile = _T("GUERRIERS MARRO 3-4");
			m_pObjectList->AddObject( pTileFigure13 );
			CTileFigure* pTileFigure14 = new CTileFigure;
			pTileFigure14->m_FigureName.LoadStringW( IDS_GUERRIERSMARRO4_4 );
			pTileFigure14->m_FigureFile = _T("GUERRIERS MARRO 4-4");
			m_pObjectList->AddObject( pTileFigure14 );
			CTileFigure* pTileFigure15 = new CTileFigure;
			pTileFigure15->m_FigureName.LoadStringW( IDS_GUARDSZETTIAN1_2 );
			pTileFigure15->m_FigureFile = _T("GARDES ZETTIAN 1-2");
			m_pObjectList->AddObject( pTileFigure15 );
			CTileFigure* pTileFigure16 = new CTileFigure;
			pTileFigure16->m_FigureName.LoadStringW( IDS_GUARDSZETTIAN2_2 );
			pTileFigure16->m_FigureFile = _T("GARDES ZETTIAN 2-2");
			m_pObjectList->AddObject( pTileFigure16 );
			CTileFigure* pTileFigure17 = new CTileFigure;
			pTileFigure17->m_FigureName.LoadStringW( IDS_GUERRIERSVIKINGTARN1_4 );
			pTileFigure17->m_FigureFile = _T("GUERRIERS VIKING TARN 1-4");
			m_pObjectList->AddObject( pTileFigure17 );
			CTileFigure* pTileFigure18 = new CTileFigure;
			pTileFigure18->m_FigureName.LoadStringW( IDS_GUERRIERSVIKINGTARN2_4 );
			pTileFigure18->m_FigureFile = _T("GUERRIERS VIKING TARN 2-4");
			m_pObjectList->AddObject( pTileFigure18 );
			CTileFigure* pTileFigure19 = new CTileFigure;
			pTileFigure19->m_FigureName.LoadStringW( IDS_GUERRIERSVIKINGTARN3_4 );
			pTileFigure19->m_FigureFile = _T("GUERRIERS VIKING TARN 3-4");
			m_pObjectList->AddObject( pTileFigure19 );
			CTileFigure* pTileFigure20 = new CTileFigure;
			pTileFigure20->m_FigureName.LoadStringW( IDS_GUERRIERSVIKINGTARN4_4 );
			pTileFigure20->m_FigureFile = _T("GUERRIERS VIKING TARN 4-4");
			m_pObjectList->AddObject( pTileFigure20 );
			CTileFigure* pTileFigure21 = new CTileFigure;
			pTileFigure21->m_FigureName.LoadStringW( IDS_ELITEAEROPORTEE1_4 );
			pTileFigure21->m_FigureFile = _T("ELITE AEROPORTEE 1-4");
			m_pObjectList->AddObject( pTileFigure21 );
			CTileFigure* pTileFigure22 = new CTileFigure;
			pTileFigure22->m_FigureName.LoadStringW( IDS_ELITEAEROPORTEE2_4 );
			pTileFigure22->m_FigureFile = _T("ELITE AEROPORTEE 2-4");
			m_pObjectList->AddObject( pTileFigure22 );
			CTileFigure* pTileFigure23 = new CTileFigure;
			pTileFigure23->m_FigureName.LoadStringW( IDS_ELITEAEROPORTEE3_4 );
			pTileFigure23->m_FigureFile = _T("ELITE AEROPORTEE 3-4");
			m_pObjectList->AddObject( pTileFigure23 );
			CTileFigure* pTileFigure24 = new CTileFigure;
			pTileFigure24->m_FigureName.LoadStringW( IDS_ELITEAEROPORTEE4_4 );
			pTileFigure24->m_FigureFile = _T("ELITE AEROPORTEE 4-4");
			m_pObjectList->AddObject( pTileFigure24 );
			CTileFigure* pTileFigure25 = new CTileFigure;
			pTileFigure25->m_FigureName.LoadStringW( IDS_SAMURAI_IZUMI1_3 );
			pTileFigure25->m_FigureFile = _T("SAMURAI IZUMI 1-3");
			m_pObjectList->AddObject( pTileFigure25 );
			CTileFigure* pTileFigure26 = new CTileFigure;
			pTileFigure26->m_FigureName.LoadStringW( IDS_SAMURAI_IZUMI2_3 );
			pTileFigure26->m_FigureFile = _T("SAMURAI IZUMI 2-3");
			m_pObjectList->AddObject( pTileFigure26 );
			CTileFigure* pTileFigure27 = new CTileFigure;
			pTileFigure27->m_FigureName.LoadStringW( IDS_SAMURAI_IZUMI3_3 );
			pTileFigure27->m_FigureFile = _T("SAMURAI IZUMI 3-3");
			m_pObjectList->AddObject( pTileFigure27 );
			CTileFigure* pTileFigure28 = new CTileFigure;
			pTileFigure28->m_FigureName.LoadStringW( IDS_AGENTS_KRAV_MAGA1_3 );
			pTileFigure28->m_FigureFile = _T("AGENTS KRAV MAGA 1-3");
			m_pObjectList->AddObject( pTileFigure28 );
			CTileFigure* pTileFigure29 = new CTileFigure;
			pTileFigure29->m_FigureName.LoadStringW( IDS_AGENTS_KRAV_MAGA2_3 );
			pTileFigure29->m_FigureFile = _T("AGENTS KRAV MAGA 2-3");
			m_pObjectList->AddObject( pTileFigure29 );
			CTileFigure* pTileFigure30 = new CTileFigure;
			pTileFigure30->m_FigureName.LoadStringW( IDS_AGENTS_KRAV_MAGA3_3 );
			pTileFigure30->m_FigureFile = _T("AGENTS KRAV MAGA 3-3");
			m_pObjectList->AddObject( pTileFigure30 );
			CTileFigure* pTileFigure31 = new CTileFigure;
			pTileFigure31->m_FigureName.LoadStringW( IDS_ARROW_GRUTS1_3 );
			pTileFigure31->m_FigureFile = _T("ARROW GRUTS 1-3");
			m_pObjectList->AddObject( pTileFigure31 );
			CTileFigure* pTileFigure32 = new CTileFigure;
			pTileFigure32->m_FigureName.LoadStringW( IDS_ARROW_GRUTS2_3 );
			pTileFigure32->m_FigureFile = _T("ARROW GRUTS 2-3");
			m_pObjectList->AddObject( pTileFigure32 );
			CTileFigure* pTileFigure33 = new CTileFigure;
			pTileFigure33->m_FigureName.LoadStringW( IDS_ARROW_GRUTS3_3 );
			pTileFigure33->m_FigureFile = _T("ARROW GRUTS 3-3");
			m_pObjectList->AddObject( pTileFigure33 );
			CTileFigure* pTileFigure34 = new CTileFigure;
			pTileFigure34->m_FigureName.LoadStringW( IDS_KELDA_THE_KYRIE_WARRIOR );
			pTileFigure34->m_FigureFile = _T("KELDA THE KYRIE WARRIOR");
			m_pObjectList->AddObject( pTileFigure34 );
			CTileFigure* pTileFigure35 = new CTileFigure;
			pTileFigure35->m_FigureName.LoadStringW( IDS_BLADE_GRUTS1_4 );
			pTileFigure35->m_FigureFile = _T("BLADE GRUTS 1-4");
			m_pObjectList->AddObject( pTileFigure35 );
			CTileFigure* pTileFigure36 = new CTileFigure;
			pTileFigure36->m_FigureName.LoadStringW( IDS_BLADE_GRUTS2_4 );
			pTileFigure36->m_FigureFile = _T("BLADE GRUTS 2-4");
			m_pObjectList->AddObject( pTileFigure36 );
			CTileFigure* pTileFigure37 = new CTileFigure;
			pTileFigure37->m_FigureName.LoadStringW( IDS_BLADE_GRUTS3_4 );
			pTileFigure37->m_FigureFile = _T("BLADE GRUTS 3-4");
			m_pObjectList->AddObject( pTileFigure37 );
			CTileFigure* pTileFigure38 = new CTileFigure;
			pTileFigure38->m_FigureName.LoadStringW( IDS_BLADE_GRUTS4_4 );
			pTileFigure38->m_FigureFile = _T("BLADE GRUTS 4-4");
			m_pObjectList->AddObject( pTileFigure38 );
			CTileFigure* pTileFigure39 = new CTileFigure;
			pTileFigure39->m_FigureName.LoadStringW( IDS_MARCUS_DECIMUS_GALLUS );
			pTileFigure39->m_FigureFile = _T("MARCUS DECIMUS GALLUS");
			m_pObjectList->AddObject( pTileFigure39 );
			CTileFigure* pTileFigure40 = new CTileFigure;
			pTileFigure40->m_FigureName.LoadStringW( IDS_OMNICRON_SNIPERS1_3 );
			pTileFigure40->m_FigureFile = _T("OMNICRON SNIPERS 1-3");
			m_pObjectList->AddObject( pTileFigure40 );
			CTileFigure* pTileFigure41 = new CTileFigure;
			pTileFigure41->m_FigureName.LoadStringW( IDS_ROMAN_ARCHERS );
			pTileFigure41->m_FigureFile = _T("ROMAN ARCHERS");
			m_pObjectList->AddObject( pTileFigure41 );
			CTileFigure* pTileFigure42 = new CTileFigure;
			pTileFigure42->m_FigureName.LoadStringW( IDS_ROMAN_LEGIONNAIRS1_4 );
			pTileFigure42->m_FigureFile = _T("ROMAN LEGIONNAIRS 1-4");
			m_pObjectList->AddObject( pTileFigure42 );
			CTileFigure* pTileFigure43 = new CTileFigure;
			pTileFigure43->m_FigureName.LoadStringW( IDS_ROMAN_LEGIONNAIRS2_4 );
			pTileFigure43->m_FigureFile = _T("ROMAN LEGIONNAIRS 2-4");
			m_pObjectList->AddObject( pTileFigure43 );
			CTileFigure* pTileFigure44 = new CTileFigure;
			pTileFigure44->m_FigureName.LoadStringW( IDS_ROMAN_LEGIONNAIRS3_4 );
			pTileFigure44->m_FigureFile = _T("ROMAN LEGIONNAIRS 3-4");
			m_pObjectList->AddObject( pTileFigure44 );
			CTileFigure* pTileFigure45 = new CTileFigure;
			pTileFigure45->m_FigureName.LoadStringW( IDS_ROMAN_LEGIONNAIRS4_4 );
			pTileFigure45->m_FigureFile = _T("ROMAN LEGIONNAIRS 4-4");
			m_pObjectList->AddObject( pTileFigure45 );
			CTileFigure* pTileFigure46 = new CTileFigure;
			pTileFigure46->m_FigureName.LoadStringW( IDS_TAELORD_THE_KYRIE_WARRIOR );
			pTileFigure46->m_FigureFile = _T("TAELORD THE KYRIE WARRIOR");
			m_pObjectList->AddObject( pTileFigure46 );
			CTileFigure* pTileFigure47 = new CTileFigure;
			pTileFigure47->m_FigureName.LoadStringW( IDS_VENOC_VIPERS );
			pTileFigure47->m_FigureFile = _T("VENOC VIPERS");
			m_pObjectList->AddObject( pTileFigure47 );
			CTileFigure* pTileFigure48 = new CTileFigure;
			pTileFigure48->m_FigureName.LoadStringW( IDS_VENOC_WARLORD );
			pTileFigure48->m_FigureFile = _T("VENOC WARLORD");
			m_pObjectList->AddObject( pTileFigure48 );
			}
		break;
	case TC_PERSONAL_HEX:
		for( int i=0; i<theApp.m_TilePersoList.GetCount(); i++ )
		{
			m_pObjectList->AddObject( ((CTilePerso*) theApp.m_TilePersoList.GetAt(i))->GetCopy() );
		}
		break;
	}

	m_pObjectList->RedrawWindow();
	if( pResult!= NULL )
		*pResult = 0;
}

// When the window move
//
void CObjectView::OnMove(int x, int y)
{
	// Call the base class
	CFormView::OnMove(x, y);

	RedrawWindow();
}

// Set the current document
//
void CObjectView::SetCurrentDoc( void* pDoc )
{
	m_pObjectList->SetCurrentDoc( pDoc );
}

// Redraw the object control
//
void CObjectView::RedrawObjectCtrl()
{
	m_pObjectList->RedrawWindow();
}
