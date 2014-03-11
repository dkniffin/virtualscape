// HeroscapeEditorDoc.cpp : implémentation de la classe CHeroscapeEditorDoc
//

#include "StdAfx.h"

#include "ChildFrm.h"
#include "CreateGameDlg.h"
#include "DocumentConfigDlg.h"
#include "GlobalIHM.h"
#include "HeroscapeEditor.h"
#include "HeroscapeEditorDoc.h"
#include "HeroscapeEditor3DView.h"
#include "HeroscapeEditorView.h"
#include "MainFrm.h"
#include "SocketMessageId.h"
#include "WaitingConnection.h"

// CHeroscapeEditorDoc

IMPLEMENT_DYNCREATE(CHeroscapeEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CHeroscapeEditorDoc, CDocument)
	ON_COMMAND(ID_NEW_3DVIEW, &CHeroscapeEditorDoc::OnNew3dview)
	ON_COMMAND(ID_CONFIGURATION_PARAMDOC, &CHeroscapeEditorDoc::OnConfigurationParamdoc)
	ON_COMMAND(ID_DOC_CHECK, &CHeroscapeEditorDoc::OnDocCheck)
	ON_COMMAND(ID_EDITION_COPIER, &CHeroscapeEditorDoc::OnEditionCopier)
	ON_COMMAND(ID_EDITION_COUPER, &CHeroscapeEditorDoc::OnEditionCouper)
	ON_COMMAND(ID_EDITION_COLLER, &CHeroscapeEditorDoc::OnEditionColler)
	ON_UPDATE_COMMAND_UI(ID_EDITION_COLLER, &CHeroscapeEditorDoc::OnUpdateEditionColler)
	ON_UPDATE_COMMAND_UI(ID_EDITION_COPIER, &CHeroscapeEditorDoc::OnUpdateEditionCopier)
	ON_UPDATE_COMMAND_UI(ID_EDITION_COUPER, &CHeroscapeEditorDoc::OnUpdateEditionCouper)
	ON_COMMAND(ID_PLAY_CREATEGAME, &CHeroscapeEditorDoc::OnPlayCreategame)
END_MESSAGE_MAP()

// The constructor
//
CHeroscapeEditorDoc::CHeroscapeEditorDoc()
{
	// No tile now
	for( int i=0; i<30000; i++ )
		m_MaterialNb[i]=0;

	m_NbLevelByPage = 6;
	m_PrintingTransparency = 80;
	m_PrintingGrid = TRUE;
	m_PrintTileNumber = FALSE;
	// No dimension
	m_FirstX = m_FirstY = m_LastX = m_LastY = 0;
	// No scenario
	m_MyScenario = NULL;
	m_MyScenarioLen = 0;
	m_b_PrintStartAreaAsLevel = TRUE;
}

// The destructor
//
CHeroscapeEditorDoc::~CHeroscapeEditorDoc()
{
}

// A new document is generated
//
BOOL CHeroscapeEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO : ajoutez ici le code de réinitialisation
	// (les documents SDI réutiliseront ce document)

	return TRUE;
}

// Save or load a document
//
void CHeroscapeEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// Save the document version
		double Version = 0.0007;
		ar << Version;

		// Save the name
		ar << m_Name;
		// Save the author
		ar << m_Author;
		// Save the player Number
		ar << m_PlayerNumber;
		// Save the scenario
		ar << m_MyScenarioLen;
		ar.Write( m_MyScenario, m_MyScenarioLen );
		// Save the number of level by page for printing
		ar << m_NbLevelByPage;
		// Save the transparency for printing
		ar << m_PrintingTransparency;
		// Save the display or not the grid on printing
		ar << m_PrintingGrid;
		// Save the display or not the tile number on printing
		ar << m_PrintTileNumber;
		// Save the print start area as level
		ar << m_b_PrintStartAreaAsLevel;
		// Save all the tile
		int NbTile = (int) m_TileList.GetCount();
		ar << NbTile;
		for( int i=0; i<NbTile; i++ )
		{
			CTile* pTile = (CTile*) m_TileList.GetAt(i);
			ar << pTile->m_Type;
			pTile->Serialize( ar );
		}
	}
	else
	{
		// Read the document version
		double Version;
		ar >> Version;

		if( Version==0.0001 )
			LoadVersion0_0001( ar );
		else if( Version==0.0002 )
			LoadVersion0_0002( ar );
		else if( Version==0.0003 )
			LoadVersion0_0003( ar );
		else if( Version==0.0004 )
			LoadVersion0_0004( ar );
		else if( Version==0.0005 )
			LoadVersion0_0005( ar );
		else if( Version==0.0006 )
			LoadVersion0_0006( ar );
		else if( Version==0.0007 )
			LoadVersion0_0007( ar );
		else
		{
			CString	Str;
			Str.LoadString( IDS_FILE_VERSION_TOO_RECENT );
			AfxMessageBox( Str );
		}
		ComputeArea(false);
	}
}

// Load the document
//
void CHeroscapeEditorDoc::LoadVersion0_0001( CArchive& ar )
{
	// Read all the tile
	int NbTile;
	ar >> NbTile;
	for( int i=0; i<NbTile; i++ )
	{
		int Type;
		ar >> Type;
		CTile* pTile = CTile::GetNewTile( Type );
		pTile->Serialize( ar );
		AddTile( pTile );
	}
}

// Load the document
//
void CHeroscapeEditorDoc::LoadVersion0_0002( CArchive& ar )
{
	// Read the name
	ar >> m_Name;
	// Read the author
	ar >> m_Author;
	// Read the number of level by page for printing
	ar >> m_NbLevelByPage;
	// Read the transparency for printing
	ar >> m_PrintingTransparency;
	// Read the display or not the grid on printing
	ar >> m_PrintingGrid;
	// Read all the tile
	int NbTile;
	ar >> NbTile;
	for( int i=0; i<NbTile; i++ )
	{
		int Type;
		ar >> Type;
		CTile* pTile = CTile::GetNewTile( Type );
		pTile->Serialize( ar );
		AddTile( pTile );
	}
}

// Load the document
//
void CHeroscapeEditorDoc::LoadVersion0_0003( CArchive& ar )
{
	// Read the name
	ar >> m_Name;
	// Read the author
	ar >> m_Author;
	// Read player number
	ar >> m_PlayerNumber;
	// Read the scenario
	ar >> m_Scenario;
	// Read the number of level by page for printing
	ar >> m_NbLevelByPage;
	// Read the transparency for printing
	ar >> m_PrintingTransparency;
	// Read the display or not the grid on printing
	ar >> m_PrintingGrid;
	// Read all the tile
	int NbTile;
	ar >> NbTile;
	for( int i=0; i<NbTile; i++ )
	{
		int Type;
		ar >> Type;
		CTile* pTile = CTile::GetNewTile( Type );
		pTile->Serialize( ar );
		AddTile( pTile );
	}
}

// Load the document
//
void CHeroscapeEditorDoc::LoadVersion0_0004( CArchive& ar )
{
	// Read the name
	ar >> m_Name;
	// Read the author
	ar >> m_Author;
	// Read player number
	ar >> m_PlayerNumber;
	// Read the scenario
	ar >> m_MyScenarioLen;
	m_MyScenario = (char*) malloc(m_MyScenarioLen);
	ar.Read( m_MyScenario, m_MyScenarioLen );
	// Read the number of level by page for printing
	ar >> m_NbLevelByPage;
	// Read the transparency for printing
	ar >> m_PrintingTransparency;
	// Read the display or not the grid on printing
	ar >> m_PrintingGrid;
	// Read all the tile
	int NbTile;
	ar >> NbTile;
	for( int i=0; i<NbTile; i++ )
	{
		int Type;
		ar >> Type;
		CTile* pTile = CTile::GetNewTile( Type );
		pTile->Serialize( ar );
		AddTile( pTile );
	}
}

// Load the document
//
void CHeroscapeEditorDoc::LoadVersion0_0005( CArchive& ar )
{
	// Read the name
	ar >> m_Name;
	// Read the author
	ar >> m_Author;
	// Read player number
	ar >> m_PlayerNumber;
	// Read the scenario
	ar >> m_MyScenarioLen;
	m_MyScenario = (char*) malloc(m_MyScenarioLen);
	ar.Read( m_MyScenario, m_MyScenarioLen );
	// Read the number of level by page for printing
	ar >> m_NbLevelByPage;
	// Read the transparency for printing
	ar >> m_PrintingTransparency;
	// Read the display or not the grid on printing
	ar >> m_PrintingGrid;
	// Read the display or not the tile number on printing
	ar >> m_PrintTileNumber;
	// Read all the tile
	int NbTile;
	ar >> NbTile;
	for( int i=0; i<NbTile; i++ )
	{
		int Type;
		ar >> Type;
		CTile* pTile = CTile::GetNewTile( Type );
		pTile->Serialize( ar );
		AddTile( pTile );
	}
}

// Load the document
//
void CHeroscapeEditorDoc::LoadVersion0_0006( CArchive& ar )
{
	// Read the name
	ar >> m_Name;
	// Read the author
	ar >> m_Author;
	// Read player number
	ar >> m_PlayerNumber;
	// Read the scenario
	ar >> m_MyScenarioLen;
	m_MyScenario = (char*) malloc(m_MyScenarioLen);
	ar.Read( m_MyScenario, m_MyScenarioLen );
	// Read the number of level by page for printing
	ar >> m_NbLevelByPage;
	// Read the transparency for printing
	ar >> m_PrintingTransparency;
	// Read the display or not the grid on printing
	ar >> m_PrintingGrid;
	// Read the display or not the tile number on printing
	ar >> m_PrintTileNumber;
	// Read all the tile
	int NbTile;
	ar >> NbTile;
	for( int i=0; i<NbTile; i++ )
	{
		int Type;
		ar >> Type;
		CTile* pTile = CTile::GetNewTile( Type );
		pTile->Serialize( ar );
		AddTile( pTile );
	}
}

// Load the document
//
void CHeroscapeEditorDoc::LoadVersion0_0007( CArchive& ar )
{
	// Read the name
	ar >> m_Name;
	// Read the author
	ar >> m_Author;
	// Read player number
	ar >> m_PlayerNumber;
	// Read the scenario
	ar >> m_MyScenarioLen;
	m_MyScenario = (char*) malloc(m_MyScenarioLen);
	ar.Read( m_MyScenario, m_MyScenarioLen );
	// Read the number of level by page for printing
	ar >> m_NbLevelByPage;
	// Read the transparency for printing
	ar >> m_PrintingTransparency;
	// Read the display or not the grid on printing
	ar >> m_PrintingGrid;
	// Read the display or not the tile number on printing
	ar >> m_PrintTileNumber;
	// Read the print start area as level
	ar >> m_b_PrintStartAreaAsLevel;
	// Read all the tile
	int NbTile;
	ar >> NbTile;
	for( int i=0; i<NbTile; i++ )
	{
		int Type;
		ar >> Type;
		CTile* pTile = CTile::GetNewTile( Type );
		pTile->Serialize( ar );
		AddTile( pTile );
	}
}

// Inform each view that a tile is currently moving
//
void CHeroscapeEditorDoc::InformEachViewTileMoving( CTile* pTile, POINT Point, double DiffPosTileMouseX, double DiffPosTileMouseY )
{
	POSITION Pos = GetFirstViewPosition();
	while( Pos!=NULL )
	{
		CView* pView = GetNextView( Pos );
		if( pView->IsKindOf( RUNTIME_CLASS(CHeroscapeEditorView) ) )
			((CHeroscapeEditorView*) pView)->InformTileMoving( pTile, Point, DiffPosTileMouseX, DiffPosTileMouseY );
	}
}

// Inform each view that a tile is currently launching
//
bool CHeroscapeEditorDoc::InformEachViewTileLaunch( CTile* pTile, POINT Point, double DiffPosTileMouseX, double DiffPosTileMouseY )
{
	bool Ret = false;

	POSITION Pos = GetFirstViewPosition();
	while( Pos!=NULL )
	{
		CView* pView = GetNextView( Pos );
		if( pView->IsKindOf( RUNTIME_CLASS(CHeroscapeEditorView) ) )
		{
			if( CWnd::WindowFromPoint(Point)==pView )
				if( ((CHeroscapeEditorView*) pView)->InformTileLaunch( pTile, Point, DiffPosTileMouseX, DiffPosTileMouseY ) )
				{
					Ret = true;

					// Add this tile to this document
					AddTile( pTile );
					ComputeArea(((CHeroscapeEditorView*) pView)->m_DisplayNumber);
				}
		}
	}

	return Ret;
}

// Add a tile to the document
//
void CHeroscapeEditorDoc::AddTile( CTile* pTile )
{
	m_TileList.Add( pTile );
	if( pTile->m_Type==TYPE_CASTLE*1000+404 )
		m_MaterialNb[TYPE_CASTLE*1000+401]++;
	else if( pTile->m_Type==TYPE_WATER*1000+2 )
		m_MaterialNb[TYPE_WATER*1000+1] += 2;
	else
		m_MaterialNb[pTile->m_Type]++;
	SetModifiedFlag();

	((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.RedrawObjectCtrl();
	ComputeArea(false);

	UpdateAll3DViews();
}

// Redraw all the views
//
void CHeroscapeEditorDoc::UpdateAll3DViews()
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if( pView->IsKindOf( RUNTIME_CLASS(CHeroscapeEditor3DView) ) )
		{
			((CHeroscapeEditor3DView*) pView)->UpdateData1();
			((CHeroscapeEditor3DView*) pView)->UpdateData2();
			((CHeroscapeEditor3DView*) pView)->RenderScene( false );
			((CHeroscapeEditor3DView*) pView)->RedrawWindow();
		}
	}
}

// Redraw all the views
//
void CHeroscapeEditorDoc::RedrawAllViews()
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		pView->RedrawWindow();
	}
}

// Remove all the object in this document
//
void CHeroscapeEditorDoc::DeleteContents()
{
	// Freeing memory
	for( int i=0; i<m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_TileList.GetAt(i);
		delete pTile;
	}
	m_TileList.RemoveAll();

	if( m_MyScenario!=NULL )
	{
		free( m_MyScenario );
		m_MyScenario = NULL;
	}

	// Call the base class
	CDocument::DeleteContents();
}

// Unselect all tile of the document
//
void CHeroscapeEditorDoc::UnselectAllTile()
{
	for( int i=0; i<m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_TileList.GetAt(i);
		pTile->m_IsSelected = false;
	}

	UpdateAllViews( NULL );
	RedrawAllViews();

	DisplaySelectedCount();
}

// Remove all the selected tile
//
void CHeroscapeEditorDoc::RemoveSelection()
{
	for( int i=0; i<m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_TileList.GetAt(i);
		if( pTile->m_IsSelected )
		{
			RemoveTileIndex(i);
			i--;
		}
	}

	ComputeArea(false);
	SetModifiedFlag();
	((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.RedrawObjectCtrl();
	UpdateAll3DViews();
	UpdateAllViews( NULL );
	RedrawAllViews();

	DisplaySelectedCount();
}

// Remove a tile from the document
//
void CHeroscapeEditorDoc::RemoveTileIndex( int Index )
{
	if( Index>=m_TileList.GetCount() )
		return;

	CTile* pTile = (CTile*) m_TileList.GetAt( Index );
	if( pTile->m_Type==TYPE_CASTLE*1000+404 )
		m_MaterialNb[TYPE_CASTLE*1000+401]--;
	else if( pTile->m_Type==TYPE_WATER*1000+2 )
		m_MaterialNb[TYPE_WATER*1000+1] -= 2;
	else
		m_MaterialNb[pTile->m_Type]--;
	
	delete pTile;
	m_TileList.RemoveAt( Index );
}

// Return the nb selected tile
//
int CHeroscapeEditorDoc::GetNbSelectedTile()
{
	int Nb = 0;

	for( int i=0; i<m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_TileList.GetAt(i);
		if( pTile->m_IsSelected )
			Nb++;
	}

	return Nb;
}

// Rotate the selection to right
//
void CHeroscapeEditorDoc::RotateSelectionRight()
{
	for( int i=0; i<m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_TileList.GetAt(i);
		if( pTile->m_IsSelected )
			pTile->RotateRight();
	}

	ComputeArea(false);
	SetModifiedFlag();
	UpdateAll3DViews();
	UpdateAllViews( NULL );
	RedrawAllViews();
}

// Rotate the selection to left
//
void CHeroscapeEditorDoc::RotateSelectionLeft()
{
	for( int i=0; i<m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_TileList.GetAt(i);
		if( pTile->m_IsSelected )
			pTile->RotateLeft();
	}

	ComputeArea(false);
	SetModifiedFlag();
	UpdateAll3DViews();
	UpdateAllViews( NULL );
	RedrawAllViews();
}

// The user want a new 3D view
//
void CHeroscapeEditorDoc::OnNew3dview()
{
	CMDIChildWnd* pFrame = (CMDIChildWnd*) theApp.m_pDocTemplateView3D->CreateNewFrame( this, NULL );

	theApp.m_pDocTemplateView3D->InitialUpdateFrame( pFrame, this, FALSE );

	pFrame->ShowWindow( SW_SHOW );
	pFrame->MDIActivate();
	CHeroscapeEditor3DView* pView = (CHeroscapeEditor3DView*) pFrame->GetActiveView();
	pView->AfterCreate();
	OnChangedViewList();
}

// Prepare the printing job
//
BOOL CHeroscapeEditorDoc::OnPreparePrinting(CPrintInfo* pInfo)
{
	if( m_TileList.GetCount()<1 )
		return FALSE;

	ComputeLevelMax();

	if( !m_b_PrintStartAreaAsLevel )
		m_HasStartArea = FALSE;
	else if( ContainsStartArea() )
		m_LevelMax ++;

	pInfo->SetMinPage(1);
	if( pInfo->m_nNumPreviewPages==1 )
		pInfo->SetMaxPage(1);
	else
	{
		if( ((m_LevelMax+1)%m_NbLevelByPage)==0 )
			pInfo->SetMaxPage( (m_LevelMax+1)/m_NbLevelByPage + 2 );
		else
			pInfo->SetMaxPage( (m_LevelMax+1)/m_NbLevelByPage + 3 );
	}

	return TRUE;
}

// To know if the map contains start area
// Because these start area are print on a particular map (as an option)
//
BOOL CHeroscapeEditorDoc::ContainsStartArea()
{
	m_HasStartArea = true;
	for( int i=0; i<m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_TileList.GetAt(i);
		if( pTile->m_Type/1000==TYPE_STARTAREA )
			return TRUE;
	}

	m_HasStartArea = false;
	return FALSE;
}

// Compute the level Max
//
void CHeroscapeEditorDoc::ComputeLevelMax()
{
	m_LevelMax = 0;

	for( int i=0; i<m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_TileList.GetAt(i);
		if( pTile->m_PosZ>m_LevelMax && (pTile->m_Type!=TYPE_STARTAREA*1000+1 || !m_b_PrintStartAreaAsLevel))
			m_LevelMax = pTile->m_PosZ;
	}
}

// Begin printing job
//
void CHeroscapeEditorDoc::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	ComputeArea(false);
}

// Compute the differents printing param
//
void CHeroscapeEditorDoc::ComputeArea(bool WithNumberDisplayed)
{
	m_XOffset = m_YOffset = 10000;
	int MaxXEven;
	int MaxXOdd;
	int XOffsetEven;
	int	XOffsetOdd;
	int	MaxY;
	MaxXEven=0;
	MaxXOdd=0;
	XOffsetEven = 10000;
	XOffsetOdd = 10000;
	MaxY=0;

	for( int i=0; i<m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_TileList.GetAt(i);
		for( int j=0; j<pTile->m_NbTile; j++ )
		{
			if( pTile->m_PosX+pTile->m_TilePosition[j].x<m_XOffset )
				m_XOffset = pTile->m_PosX+pTile->m_TilePosition[j].x;
			if( pTile->m_PosY+pTile->m_TilePosition[j].y<m_YOffset )
				m_YOffset = pTile->m_PosY+pTile->m_TilePosition[j].y;
			if(pTile->m_PosY%2==0)
			{
				if( (pTile->m_TilePosition[j].y)%2==1 )
				{
					if( pTile->m_PosX+pTile->m_TilePosition[j].x>MaxXOdd )
						MaxXOdd = pTile->m_PosX+pTile->m_TilePosition[j].x;
					if( pTile->m_PosX+pTile->m_TilePosition[j].x<XOffsetOdd )
						XOffsetOdd = pTile->m_PosX+pTile->m_TilePosition[j].x;
				}
				else
				{
					if( pTile->m_PosX+pTile->m_TilePosition[j].x>MaxXEven )
						MaxXEven = pTile->m_PosX+pTile->m_TilePosition[j].x;
					if( pTile->m_PosX+pTile->m_TilePosition[j].x<XOffsetEven )
						XOffsetEven = pTile->m_PosX+pTile->m_TilePosition[j].x;
				}
			}
			else
			{
				if( (pTile->m_TilePosition[j].y)%2==1 )
				{
					if( pTile->m_PosX+pTile->m_TilePosition[j].x+1>MaxXEven )
						MaxXEven = pTile->m_PosX+pTile->m_TilePosition[j].x+1;
					if( pTile->m_PosX+pTile->m_TilePosition[j].x+1<XOffsetEven )
						XOffsetEven = pTile->m_PosX+pTile->m_TilePosition[j].x+1;
				}
				else
				{
					if( pTile->m_PosX+pTile->m_TilePosition[j].x>MaxXOdd )
						MaxXOdd = pTile->m_PosX+pTile->m_TilePosition[j].x;
					if( pTile->m_PosX+pTile->m_TilePosition[j].x<XOffsetOdd )
						XOffsetOdd = pTile->m_PosX+pTile->m_TilePosition[j].x;
				}
			}
			if( pTile->m_PosY+pTile->m_TilePosition[j].y>MaxY )
				MaxY = pTile->m_PosY+pTile->m_TilePosition[j].y;
		}
	}
	m_XWidth = max(MaxXEven,MaxXOdd)-m_XOffset+1;
	m_YHeight = MaxY-m_YOffset+1;

	if( MaxXOdd>=MaxXEven )
		m_LastX = MaxXOdd+1.5;
	else
		m_LastX = MaxXEven+1;
	if( XOffsetEven<=XOffsetOdd )
		m_FirstX = XOffsetEven;
	else
		m_FirstX = XOffsetOdd+.5;
	m_FirstY = m_YOffset;
	m_LastY = MaxY+1;

	if( (WithNumberDisplayed==false && m_YOffset<0) || (WithNumberDisplayed==true && m_YOffset<2) )
	{
		int DiffY;
		if( WithNumberDisplayed )
			DiffY = 2-m_YOffset;
		else
			DiffY = -m_YOffset;

		for( int i=0; i<m_TileList.GetCount(); i++ )
		{
			CTile* pTile = (CTile*) m_TileList.GetAt(i);

			if( (((int) DiffY)%2==1 || ((int) DiffY)%2==-1) && pTile->m_PosY%2==0 )
				pTile->m_PosX -= 1;
			pTile->m_PosY += (int) DiffY;
		}
		// Now Move X
		ComputeArea(WithNumberDisplayed);
		SetModifiedFlag();
	}
	else if( (WithNumberDisplayed==false && (XOffsetEven<0 || XOffsetOdd<0)) || (WithNumberDisplayed==true && (XOffsetEven<1 || XOffsetOdd<1)) )
	{
		int MoveX;
		// Move everything
		if( WithNumberDisplayed )
		{
			if( XOffsetEven<XOffsetOdd )
				MoveX = 1-XOffsetEven;
			else
				MoveX = 1-XOffsetOdd;
		}
		else
		{
			if( XOffsetEven<XOffsetOdd )
				MoveX = -XOffsetEven;
			else
				MoveX = -XOffsetOdd;
		}

		for( int i=0; i<m_TileList.GetCount(); i++ )
		{
			CTile* pTile = (CTile*) m_TileList.GetAt(i);
			pTile->m_PosX += MoveX;
		}
		ComputeArea(WithNumberDisplayed);
		SetModifiedFlag();
	}
}

// Print the document
//
void CHeroscapeEditorDoc::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// Compute TileSize
	int cx = pDC->GetDeviceCaps(HORZRES);
	int cy = pDC->GetDeviceCaps(VERTRES);

	if( pInfo->m_nCurPage==1 )
	{
		DrawFirstPage( pDC );
		return;
	}
	else if( pInfo->m_nCurPage==pInfo->GetMaxPage() )
	{
		DrawLastPage( pDC );
		return;
	}

	switch( m_NbLevelByPage )
	{
	case 1:
		DrawLevel( pDC, pInfo->m_nCurPage-2, (int) (cx*0.05), (int) (cy*0.05), (int) (cx*0.9), (int) (cy*0.9) );
		break;
	case 2:
		DrawLevel( pDC, (pInfo->m_nCurPage-2)*2, (int) (cx*0.05), (int) (cy*0.05), (int) (cx*0.9), (int) (cy*0.4) );
		DrawLevel( pDC, (pInfo->m_nCurPage-2)*2+1, (int) (cx*0.05), (int) (cy*0.55), (int) (cx*0.9), (int) (cy*0.4) );
		break;
	case 4:
		DrawLevel( pDC, (pInfo->m_nCurPage-2)*4, (int) (cx*0.05), (int) (cy*0.05), (int) (cx*0.4), (int) (cy*0.4) );
		DrawLevel( pDC, (pInfo->m_nCurPage-2)*4+1, (int) (cx*0.05), (int) (cy*0.55), (int) (cx*0.4), (int) (cy*0.4) );
		DrawLevel( pDC, (pInfo->m_nCurPage-2)*4+2, (int) (cx*0.55), (int) (cy*0.05), (int) (cx*0.4), (int) (cy*0.4) );
		DrawLevel( pDC, (pInfo->m_nCurPage-2)*4+3, (int) (cx*0.55), (int) (cy*0.55), (int) (cx*0.4), (int) (cy*0.4) );
		break;
	case 6:
		DrawLevel( pDC, (pInfo->m_nCurPage-2)*6, (int) (cx*0.05), (int) (cy*0.05), (int) (cx*0.4), (int) (cy*0.26) );
		DrawLevel( pDC, (pInfo->m_nCurPage-2)*6+1, (int) (cx*0.05), (int) (cy*0.37), (int) (cx*0.4), (int) (cy*0.26) );
		DrawLevel( pDC, (pInfo->m_nCurPage-2)*6+2, (int) (cx*0.05), (int) (cy*0.69), (int) (cx*0.4), (int) (cy*0.26) );
		DrawLevel( pDC, (pInfo->m_nCurPage-2)*6+3, (int) (cx*0.55), (int) (cy*0.05), (int) (cx*0.4), (int) (cy*0.26) );
		DrawLevel( pDC, (pInfo->m_nCurPage-2)*6+4, (int) (cx*0.55), (int) (cy*0.37), (int) (cx*0.4), (int) (cy*0.26) );
		DrawLevel( pDC, (pInfo->m_nCurPage-2)*6+5, (int) (cx*0.55), (int) (cy*0.69), (int) (cx*0.4), (int) (cy*0.26) );
		break;
	}
}

// Print the document with num
//
void CHeroscapeEditorDoc::OnPrintNum(CDC* pDC, CPrintInfo* pInfo)
{
	// Compute TileSize
	int cx = pDC->GetDeviceCaps(HORZRES);
	int cy = pDC->GetDeviceCaps(VERTRES);

	DrawWithNum( pDC, (int) (cx*0.05), (int) (cy*0.05), (int) (cx*0.9), (int) (cy*0.9) );
}

// Draw the second page
//
void CHeroscapeEditorDoc::DrawLastPage( CDC* pDC )
{
	int cx = pDC->GetDeviceCaps(HORZRES);
	int cy = pDC->GetDeviceCaps(VERTRES);

	CFont Font;
	Font.CreateFont( (int) (cy*0.01), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, PROOF_QUALITY, FF_DONTCARE, _T("Arial") );
	CFont* pOldFont = pDC->SelectObject( &Font );

	// Draw Nb player
	CString Str;
	Str.LoadString( IDS_NB_PLAYER );
	pDC->DrawText( Str + m_PlayerNumber, CRect((int) (cx*0.05),(int) (cy*0.04), (int) (cx*0.95),(int) (cy*0.1)), DT_LEFT | DT_WORDBREAK | DT_TOP );

	// Draw size
	CString StrSize;
	switch( theApp.m_Unit )
	{
	case 0: // Cm
		Str.Format( _T("%0.2f"), (m_LastX-m_FirstX)*TILE_REAL_WIDTH_X_CM );
		break;
	case 1: // Inch
		Str.Format( _T("%0.2f"), (m_LastX-m_FirstX)*TILE_REAL_WIDTH_X_CM/2.55 );
		break;
	case 2: // hex
		Str.Format( _T("%0.2f"), (m_LastX-m_FirstX) );
		break;
	}
	StrSize.LoadString( IDS_SIZE );
	StrSize += Str+_T("x");
	switch( theApp.m_Unit )
	{
	case 0: // Cm
		Str.Format( _T("%0.2f cm"), (m_LastY-m_FirstY-1)*TILE_REAL_HEIGHT1_CM+TILE_REAL_HEIGHT2_CM );
		break;
	case 1: // Inch
		Str.Format( _T("%0.2f inch"), ((m_LastY-m_FirstY-1)*TILE_REAL_HEIGHT1_CM+TILE_REAL_HEIGHT2_CM)/2.55 );
		break;
	case 2: // Hex
		Str.Format( _T("%0.2f hex"), (m_LastY-m_FirstY-1) );
		break;
	}
	StrSize += Str;
	pDC->DrawText( StrSize, CRect( (int) (cx*0.05),(int) (cy*0.04), (int) (cx*0.95),(int) (cy*0.1)), DT_RIGHT | DT_WORDBREAK | DT_TOP );

	// Draw Number of tile for each king of tile
	double OffsetY = 0.08;
	if( m_PrintTileNumber )
	{
		int NbType=0;
		int CurrentColumn = 0;
		for( int i=0; i<30000; i++ )
		{
			if( m_MaterialNb[i]>0 )
			{
				if( i/1000!=TYPE_FIGURE && i/1000!=TYPE_PERSONAL && i/1000!=TYPE_STARTAREA )
				{
					CTile* pTile = CTile::GetNewTile(i);
					CString Str;
					Str.Format( _T("%s : %i"), pTile->GetName(), m_MaterialNb[i] );
					delete pTile;

					pDC->DrawText( Str, CRect( (int) (cx*(0.05+CurrentColumn*0.18)),(int) (cy*OffsetY), (int) (cx*(0.05+CurrentColumn*0.18+0.18)),(int) (cy*(OffsetY+0.012))), DT_LEFT | DT_WORDBREAK | DT_TOP );

					if( ++CurrentColumn>4 )
					{
						CurrentColumn = 0;
						OffsetY += 0.012;
					}
				}
			}
		}
		if( CurrentColumn>0 )
			OffsetY += 0.012;
		OffsetY += 0.012;
	}

	// Draw scenario
	if( !m_Scenario.IsEmpty() )
	{
		// For old file format
		pDC->DrawText( m_Scenario, CRect( (int) (cx*0.05), (int) (cy*OffsetY), (int) (cx*0.95), (int) (cy*0.95)), DT_LEFT | DT_WORDBREAK | DT_TOP );
	}
	else
	{
		// Get the page width and height from the printer.
		long lPageWidth = ::MulDiv(pDC->GetDeviceCaps(PHYSICALWIDTH),1440, pDC->GetDeviceCaps(LOGPIXELSX));
		long lPageHeight = ::MulDiv(pDC->GetDeviceCaps(PHYSICALHEIGHT),1440, pDC->GetDeviceCaps(LOGPIXELSY));
		CRect rcPage(0, 0, lPageWidth, lPageHeight);

		// Print scenario with a CRicheEditCtrl
		CRichEditCtrl re;
		re.Create( ES_MULTILINE, rcPage, theApp.m_pMainWnd, 4567 );

		::ScaleWindowExtEx(pDC->m_hDC,
			::GetDeviceCaps(pDC->m_hDC, LOGPIXELSX),
			::GetDeviceCaps(pDC->m_hAttribDC, LOGPIXELSX),
			::GetDeviceCaps(pDC->m_hDC, LOGPIXELSY),
			::GetDeviceCaps(pDC->m_hAttribDC, LOGPIXELSY), NULL);

		EDITSTREAM es;
		es.dwCookie	= (intptr_t) this;
		es.dwError = 0;
		es.pfnCallback = MyStreamInCallback;
		m_ScenarioWriteBufferPos = 0;
		re.StreamIn(SF_RTF, es);

		FORMATRANGE fr;
		fr.hdc = pDC->m_hDC;
		fr.hdcTarget = pDC->m_hAttribDC;
		fr.rc = CRect((int) (lPageWidth*0.05),(int) (lPageHeight*OffsetY),(int) (lPageWidth*0.95), (int) (lPageHeight*0.95));
		fr.rcPage = rcPage;
		fr.chrg.cpMin = 0;
		fr.chrg.cpMax = -1;

		re.SetRect( rcPage );
		long LastChar = re.FormatRange( &fr, TRUE );
		re.FormatRange( NULL, FALSE );
	}

	pDC->SelectObject( pOldFont );
}

// Write the data to the richedit text
//
DWORD CALLBACK CHeroscapeEditorDoc::MyStreamInCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	CHeroscapeEditorDoc* pDoc = (CHeroscapeEditorDoc*) dwCookie;
	if( pDoc->m_ScenarioWriteBufferPos+cb>pDoc->m_MyScenarioLen )
	{
		memcpy( pbBuff, pDoc->m_MyScenario+pDoc->m_ScenarioWriteBufferPos, pDoc->m_MyScenarioLen-pDoc->m_ScenarioWriteBufferPos );
		*pcb = pDoc->m_MyScenarioLen-pDoc->m_ScenarioWriteBufferPos;
		pDoc->m_ScenarioWriteBufferPos = pDoc->m_MyScenarioLen;
	}
	else
	{
		memcpy( pbBuff, pDoc->m_MyScenario+pDoc->m_ScenarioWriteBufferPos, cb );
		*pcb = cb;
		pDoc->m_ScenarioWriteBufferPos += cb;
	}

	return 0;
}

// Draw the first page
//
void CHeroscapeEditorDoc::DrawFirstPage( CDC* pDC )
{
	int cx = pDC->GetDeviceCaps(HORZRES);
	int cy = pDC->GetDeviceCaps(VERTRES);

	// Draw title
	CFont Font;
	Font.CreateFont( (int) (cy*0.05), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, PROOF_QUALITY, FF_DONTCARE, _T("Arial") );
	CFont* pOldFont = pDC->SelectObject( &Font );

	pDC->DrawText( m_Name, CRect(0,(int) (cy*0.05),cx,(int) (cy*0.15)), DT_CENTER | DT_WORDBREAK | DT_TOP );

	// try to find 3D view
	POSITION Pos = GetFirstViewPosition();
	bool Find=false;
	CView* pView;
	while( Pos!=NULL && Find==false )
	{
		pView = GetNextView( Pos );
		if( pView->IsKindOf( RUNTIME_CLASS(CHeroscapeEditor3DView) ) )
		{
			WINDOWPLACEMENT WndPl;
			pView->GetParentFrame()->GetWindowPlacement(&WndPl);
			if( WndPl.showCmd!=SW_SHOWMINIMIZED && WndPl.showCmd!=SW_SHOWMINNOACTIVE )
				Find = true;
		}
	}
	// Copy 3D view to the page
	if( Find )
	{
		unsigned char* pPixelData;
		int Width, Height;

		// Save image in memory
		((CHeroscapeEditor3DView*) pView)->SaveImageInMemory();

		pPixelData = ((CHeroscapeEditor3DView*) pView)->m_pViewPoint;
		Width = ((CHeroscapeEditor3DView*) pView)->m_i_Width;
		Height = ((CHeroscapeEditor3DView*) pView)->m_i_Heigth;

		BITMAPINFO bmi;
		memset(&bmi, 0, sizeof(BITMAPINFO));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = Width;
		bmi.bmiHeader.biHeight = Height;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 24;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = 0;
		bmi.bmiHeader.biXPelsPerMeter = 0;
		bmi.bmiHeader.biYPelsPerMeter = 0;
		bmi.bmiHeader.biClrUsed = 0;
		bmi.bmiHeader.biClrImportant = 0;

		double CoefX = Width/((double) cx);
		double CoefY = Height/(cy*0.7);
		double Coef;

		if( CoefX>CoefY )
			Coef=CoefX;
		else
			Coef=CoefY;

		SetStretchBltMode( pDC->m_hDC, HALFTONE );
		StretchDIBits( pDC->m_hDC, (int) ((cx-Width/Coef)/2.0), (int) (cy*0.15+((cy*0.7-Height/Coef)/2.0)), (int) (Width/Coef), (int) (Height/Coef), 0, 0, Width, Height, pPixelData, &bmi, DIB_RGB_COLORS, SRCCOPY );
	}

	// Draw author
	CFont Font2;
	Font2.CreateFont( (int) (cy*0.03), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, PROOF_QUALITY, FF_DONTCARE, _T("Arial") );
	pDC->SelectObject( &Font2 );

	CString	Str;
	Str.LoadString( IDS_AUTHOR2P );
	pDC->DrawText( Str+m_Author, CRect(0,(int) (cy*0.90), cx, cy), DT_CENTER | DT_WORDBREAK | DT_BOTTOM );

	pDC->SelectObject( pOldFont );
}

// Draw a level
//
void CHeroscapeEditorDoc::DrawLevel( CDC* pDC, int LevelToDisplay, int OffsetX, int OffsetY, int Width, int Height )
{
	CString Str,Str2;
	CFont* pOldFont;

	if( LevelToDisplay>m_LevelMax )
		return;

	// Compute tile size
	double TileSizeX = Width/(cos(30.0*PI/180.0)*2.0)/m_XWidth;
	double TileSizeY = Height/(1+sin(30.0*PI/180.0))/m_YHeight;

	double TileSize = min(TileSizeX,TileSizeY);

	// Compute size
	int TileStepX2 = (int) (cos(30.0*PI/180.0)*TileSize);
	int TileStepX3 = 2*TileStepX2;
	int TileStepY2 = (int) (sin(30.0*PI/180.0)*TileSize);
	int TileStepY3 = (int) (TileStepY2+TileSize);
	int TileStepY4 = (int) (TileStepY3+sin(30.0*PI/180.0)*TileSize);

	// Draw the already placed tile under current level
	for( int Level=0; Level<=LevelToDisplay-1; Level++ )
	{
		for( int i=0; i<m_TileList.GetCount(); i++ )
		{
			CTile* pTile = (CTile*) m_TileList.GetAt(i);
			// Don't draw start area
			if( pTile->m_Type/1000!=TYPE_STARTAREA || !m_HasStartArea )
			{
				int PosX = (pTile->m_PosX-m_XOffset)*TileStepX3+OffsetX;
				int PosY = (pTile->m_PosY-m_YOffset)*TileStepY3+TileStepY2+OffsetY;

				if( pTile->m_PosY%2!=0 )
					PosX += TileStepX2;

				if( pTile->m_PosZ==Level )
				{
					pTile->m_PrintingTransparency = m_PrintingTransparency/100.0;
					pTile->Draw( pDC, PosX, PosY, TileStepX2, TileStepX3, TileStepY2, TileStepY3, TileStepY4, 0 );
					pTile->m_PrintingTransparency = -1;
				}
			}
		}
	}

	CPen Pen;
	Pen.CreatePen( PS_SOLID, 1, RGB(192,192,192) );
	CPen* pOldPen = pDC->SelectObject( &Pen );
	if( m_PrintingGrid )
	{
		// Draw the grid
		for( int x=m_XOffset; x<m_XOffset+m_XWidth+1; x++ )
		{
			for( int y=m_YOffset; y<m_YOffset+m_YHeight; y++ )
			{
				int MyOffsetX = (x-m_XOffset)*TileStepX3+OffsetX;
				int MyOffsetY = (y-m_YOffset)*TileStepY3+OffsetY;
				if( y%2==1 )
					MyOffsetX += TileStepX2;
				pDC->MoveTo( MyOffsetX, MyOffsetY+TileStepY2 );
				pDC->LineTo( MyOffsetX+TileStepX2, MyOffsetY );
				pDC->LineTo( MyOffsetX+TileStepX3, MyOffsetY+TileStepY2 );
				pDC->LineTo( MyOffsetX+TileStepX3, MyOffsetY+TileStepY3 );
				pDC->LineTo( MyOffsetX+TileStepX2, MyOffsetY+TileStepY4 );
				pDC->LineTo( MyOffsetX, MyOffsetY+TileStepY3 );
				pDC->LineTo( MyOffsetX, MyOffsetY+TileStepY2 );
			}
		}
	}

	// Draw the already placed tile on this current level
	for( int i=0; i<m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_TileList.GetAt(i);
		int PosX = (pTile->m_PosX-m_XOffset)*TileStepX3+OffsetX;
		int PosY = (pTile->m_PosY-m_YOffset)*TileStepY3+TileStepY2+OffsetY;

		if( pTile->m_PosY%2!=0 )
			PosX += TileStepX2;

		// Don't draw start area
		if( pTile->m_Type/1000!=TYPE_STARTAREA || !m_HasStartArea )
		{
			if( pTile->m_PosZ==LevelToDisplay )
				pTile->Draw( pDC, PosX, PosY, TileStepX2, TileStepX3, TileStepY2, TileStepY3, TileStepY4, -1 );
		}
	}

	// Draw the start area on the last level
	if( LevelToDisplay==m_LevelMax && m_HasStartArea )
	{
		// Draw the already placed tile on this current level
		for( int i=0; i<m_TileList.GetCount(); i++ )
		{
			CTile* pTile = (CTile*) m_TileList.GetAt(i);
			int PosX = (pTile->m_PosX-m_XOffset)*TileStepX3+OffsetX;
			int PosY = (pTile->m_PosY-m_YOffset)*TileStepY3+TileStepY2+OffsetY;

			if( pTile->m_PosY%2!=0 )
				PosX += TileStepX2;

			// Don't draw start area
			if( pTile->m_Type/1000==TYPE_STARTAREA )
				pTile->Draw( pDC, PosX, PosY, TileStepX2, TileStepX3, TileStepY2, TileStepY3, TileStepY4, -1 );
		}

		// Display current level
		CFont Font;
		Font.CreateFont( Width/20, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, PROOF_QUALITY, FF_DONTCARE, _T("Arial") );
		pOldFont = pDC->SelectObject( &Font );

		Str.LoadString( IDS_START );
	}
	else
	{
		// Display current level
		CFont Font;
		Font.CreateFont( Width/20, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, PROOF_QUALITY, FF_DONTCARE, _T("Arial") );
		pOldFont = pDC->SelectObject( &Font );

		Str2.LoadString( IDS_LEVELNUMBER );
		Str.Format( Str2, LevelToDisplay+1 );
	}

	CRect TextRect;
	TextRect.left = OffsetX;
	TextRect.right = OffsetX+Width;
	TextRect.top = OffsetY-Width/20;
	TextRect.bottom = OffsetY+Height;
	pDC->SetBkMode( TRANSPARENT );
	pDC->SetTextColor( RGB(0,0,0) );
	pDC->DrawText( Str, TextRect, DT_LEFT | DT_TOP );

	pDC->SelectObject( pOldPen );
	pDC->SelectObject( pOldFont );
}

// Draw a level
//
void CHeroscapeEditorDoc::DrawWithNum( CDC* pDC, int OffsetX, int OffsetY, int Width, int Height )
{
	// Compute tile size
	double TileSizeX = Width/(cos(30.0*PI/180.0)*2.0)/m_XWidth;
	double TileSizeY = Height/(1+sin(30.0*PI/180.0))/m_YHeight;

	double TileSize = min(TileSizeX,TileSizeY);

	// Compute size
	int TileStepX2 = (int) (cos(30.0*PI/180.0)*TileSize);
	int TileStepX3 = 2*TileStepX2;
	int TileStepY2 = (int) (sin(30.0*PI/180.0)*TileSize);
	int TileStepY3 = (int) (TileStepY2+TileSize);
	int TileStepY4 = (int) (TileStepY3+sin(30.0*PI/180.0)*TileSize);

	CFont Font;
	Font.CreateFont( (int) (TileSize/4*2), (int) (TileSize/4*2), 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, PROOF_QUALITY, FF_DONTCARE, _T("Arial") );

	CFont* pOldFont = pDC->SelectObject( &Font );

	// Draw the already placed tile under current level
	for( int i=0; i<m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_TileList.GetAt(i);
		int PosX = (pTile->m_PosX-m_XOffset)*TileStepX3+OffsetX;
		int PosY = (pTile->m_PosY-m_YOffset)*TileStepY3+TileStepY2+OffsetY;

		if( pTile->m_PosY%2!=0 )
			PosX += TileStepX2;

		pTile->m_PrintingTransparency = m_PrintingTransparency/100.0;
		pTile->Draw( pDC, PosX, PosY, TileStepX2, TileStepX3, TileStepY2, TileStepY3, TileStepY4, 0 );
		pTile->m_PrintingTransparency = -1;

		pDC->SetTextColor( RGB(0,0,0) );
		pDC->SetBkMode( TRANSPARENT );
		pDC->SelectObject( &Font );

		pTile->DrawNum( pDC, PosX, PosY, TileStepX2, TileStepX3, TileStepY2, TileStepY3, TileStepY4, m_FirstX, m_FirstY );
	}
	pDC->SelectObject( pOldFont );

	CPen Pen;
	Pen.CreatePen( PS_SOLID, 1, RGB(192,192,192) );
	CPen* pOldPen = pDC->SelectObject( &Pen );
	if( m_PrintingGrid )
	{
		// Draw the grid
		for( int x=m_XOffset; x<m_XOffset+m_XWidth+1; x++ )
		{
			for( int y=m_YOffset; y<m_YOffset+m_YHeight; y++ )
			{
				int MyOffsetX = (x-m_XOffset)*TileStepX3+OffsetX;
				int MyOffsetY = (y-m_YOffset)*TileStepY3+OffsetY;
				if( y%2==1 )
					MyOffsetX += TileStepX2;
				pDC->MoveTo( MyOffsetX, MyOffsetY+TileStepY2 );
				pDC->LineTo( MyOffsetX+TileStepX2, MyOffsetY );
				pDC->LineTo( MyOffsetX+TileStepX3, MyOffsetY+TileStepY2 );
				pDC->LineTo( MyOffsetX+TileStepX3, MyOffsetY+TileStepY3 );
				pDC->LineTo( MyOffsetX+TileStepX2, MyOffsetY+TileStepY4 );
				pDC->LineTo( MyOffsetX, MyOffsetY+TileStepY3 );
				pDC->LineTo( MyOffsetX, MyOffsetY+TileStepY2 );
			}
		}
	}
}

// Config of the document
//
void CHeroscapeEditorDoc::OnConfigurationParamdoc()
{
	CDocumentConfigDlg Dlg;

	Dlg.m_BattleFieldName = m_Name;
	Dlg.m_Author = m_Author;
	Dlg.m_PlayerNumber = m_PlayerNumber;
	Dlg.m_reScenario = m_Scenario;
	Dlg.m_b_PrintStartAreaAsLevel = m_b_PrintStartAreaAsLevel;
	if( m_MyScenario!=NULL )
	{
		memcpy( Dlg.m_ScenarioBuffScenario, m_MyScenario, m_MyScenarioLen);
		Dlg.m_ScenarioBufferPos = m_MyScenarioLen;
	}
	else
	{
		Dlg.m_Scenario = m_Scenario;
	}
	Dlg.m_PrintTransparency = m_PrintingTransparency;
	Dlg.m_NbLevelByPage = m_NbLevelByPage;
	Dlg.m_PrintingGrid = m_PrintingGrid;
	Dlg.m_PrintTileNumber = m_PrintTileNumber;
	if( Dlg.DoModal()==IDOK )
	{
		m_Name = Dlg.m_BattleFieldName;
		m_Author = Dlg.m_Author;
		m_PlayerNumber = Dlg.m_PlayerNumber;
		m_Scenario = "";
		if( Dlg.m_ScenarioBufferPos>0 )
		{
			if( m_MyScenario!=NULL )
				free( m_MyScenario );

			m_MyScenario = (char*) malloc(Dlg.m_ScenarioBufferPos);
			memcpy( m_MyScenario, Dlg.m_ScenarioBuffScenario, Dlg.m_ScenarioBufferPos);
			m_MyScenarioLen = Dlg.m_ScenarioBufferPos;
		}
		m_PrintingTransparency = Dlg.m_PrintTransparency;
		m_NbLevelByPage = Dlg.m_NbLevelByPage;
		m_PrintingGrid = Dlg.m_PrintingGrid;
		m_PrintTileNumber = Dlg.m_PrintTileNumber;
		m_b_PrintStartAreaAsLevel = Dlg.m_b_PrintStartAreaAsLevel;
		SetModifiedFlag();
	}
}

// To know if a position is used
//
bool CHeroscapeEditorDoc::IsPositionUsed( int PosX, int PosY, int PosZ )
{
	for( int i=0; i<m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_TileList.GetAt(i);
		if( pTile->ContainPos( PosX, PosY ) && pTile->m_PosZ==PosZ )
			return true;
	}

	return false;
}

// Verify that all tile are OK
//
void CHeroscapeEditorDoc::OnDocCheck()
{
	CWaitCursor WCursor;

	ComputeLevelMax();

	m_NbInfo = 0;
	m_NbWarning = 0;
	m_NbCritical = 0;

	// Empty the information window
	EraseInformation();	

	for( int i=0; i<m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_TileList.GetAt(i);
		pTile->Verify( this );
	}

	// Compute Nb tile and max Z
	CString StrFormat;
	StrFormat.LoadStringW( IDS_NBTILE_ANDZMAX );
	CString Str;
	Str.Format( StrFormat, m_NbWarning+m_NbCritical, m_NbWarning, m_NbCritical, m_TileList.GetCount(), m_LevelMax );
	AddInformation( IB_INFO, -1, _T(""), Str, -1, -1, -1 );

	// Compute Nb master set and other ext
	int NbMasterSet = ComputeNbMasterSet();
	int NbVolcarren = ComputeNbVolcarrenSet();
	int NbGlacier = ComputeNbGlacierSet();
	int NbForest = ComputeNbForestSet();
	int NbCastle = ComputeNbCastleSet();
	StrFormat.LoadStringW( IDS_NBMASTERSET_ETC );
	Str.Format( StrFormat, NbMasterSet, NbVolcarren, NbGlacier, NbForest, NbCastle );
	AddInformation( IB_INFO, -1, _T(""), Str, -1, -1, -1 );
}

// Return the nb of castle
//
int CHeroscapeEditorDoc::ComputeNbCastleSet()
{
	int NbCastle = 0;

	if( (GetNbTileType(TYPE_CASTLE*1000+101)+9)/10>NbCastle )
		NbCastle = (GetNbTileType(TYPE_CASTLE*1000+101)+9)/10;
	if( (GetNbTileType(TYPE_CASTLE*1000+102)+6)/7>NbCastle )
		NbCastle = (GetNbTileType(TYPE_CASTLE*1000+102)+6)/7;
	if( (GetNbTileType(TYPE_CASTLE*1000+103)+3)/4>NbCastle )
		NbCastle = (GetNbTileType(TYPE_CASTLE*1000+103)+3)/4;

	if( (GetNbTileType(TYPE_CASTLE*1000+201)+9)/10>NbCastle )
		NbCastle = (GetNbTileType(TYPE_CASTLE*1000+201)+9)/10;
	if( (GetNbTileType(TYPE_CASTLE*1000+202)+6)/7>NbCastle )
		NbCastle = (GetNbTileType(TYPE_CASTLE*1000+202)+6)/7;
	if( (GetNbTileType(TYPE_CASTLE*1000+203)+3)/4>NbCastle )
		NbCastle = (GetNbTileType(TYPE_CASTLE*1000+203)+3)/4;

	if( GetNbTileType(TYPE_CASTLE*1000+9)>NbCastle )
		NbCastle = GetNbTileType(TYPE_CASTLE*1000+9);
	if( GetNbTileType(TYPE_CASTLE*1000+7)>NbCastle )
		NbCastle = GetNbTileType(TYPE_CASTLE*1000+7);
	if( (GetNbTileType(TYPE_CASTLE*1000+1)+20)/21>NbCastle )
		NbCastle = (GetNbTileType(TYPE_CASTLE*1000+1)+20)/21;

	if( (GetNbTileType(TYPE_CASTLE*1000+301)+49)/50>NbCastle )
		NbCastle = (GetNbTileType(TYPE_CASTLE*1000+301)+49)/50;

	if( GetNbTileType(TYPE_CASTLE*1000+401)>NbCastle )
		NbCastle = GetNbTileType(TYPE_CASTLE*1000+401);
	if( (GetNbTileType(TYPE_CASTLE*1000+402)+21)/22>NbCastle )
		NbCastle = (GetNbTileType(TYPE_CASTLE*1000+402)+21)/22;
	if( GetNbTileType(TYPE_CASTLE*1000+403)>NbCastle )
		NbCastle = GetNbTileType(TYPE_CASTLE*1000+403);

	return NbCastle;
}

// Return the nb of forest
//
int CHeroscapeEditorDoc::ComputeNbForestSet()
{
	int NbForest = 0;

	if( GetNbTileType(TYPE_TREE*1000+1+10)>NbForest )
		NbForest = GetNbTileType(TYPE_TREE*1000+1+10);
	if( (GetNbTileType(TYPE_TREE*1000+1+11)+1)/2>NbForest )
		NbForest = (GetNbTileType(TYPE_TREE*1000+1+11)+1)/2;
	if( GetNbTileType(TYPE_TREE*1000+1+12)>NbForest )
		NbForest = GetNbTileType(TYPE_TREE*1000+1+12);
	if( GetNbTileType(TYPE_TREE*1000+4)>NbForest )
		NbForest = GetNbTileType(TYPE_TREE*1000+4);

	if( (GetNbTileType(TYPE_WALL*1000+4)+1)/2>NbForest )
		NbForest = (GetNbTileType(TYPE_WALL*1000+4)+1)/2;

	if( GetNbTileType(TYPE_ROAD*1000+5)>NbForest )
		NbForest = GetNbTileType(TYPE_ROAD*1000+5);
	if( (GetNbTileType(TYPE_ROAD*1000+2)+7)/8>NbForest )
		NbForest = (GetNbTileType(TYPE_ROAD*1000+2)+7)/8;
	if( (GetNbTileType(TYPE_ROAD*1000+1)+7)/8>NbForest )
		NbForest = (GetNbTileType(TYPE_ROAD*1000+1)+7)/8;

	return NbForest;
}

// Return the nb of glacier
//
int CHeroscapeEditorDoc::ComputeNbGlacierSet()
{
	int NbGlacier = 0;

	if( (GetNbTileType(TYPE_GLACIER*1000+1)+2)/3>NbGlacier )
		NbGlacier = (GetNbTileType(TYPE_GLACIER*1000+1)+2)/3;
	if( GetNbTileType(TYPE_GLACIER*1000+3)>NbGlacier )
		NbGlacier = GetNbTileType(TYPE_GLACIER*1000+3);
	if( GetNbTileType(TYPE_GLACIER*1000+4)>NbGlacier )
		NbGlacier = GetNbTileType(TYPE_GLACIER*1000+4);
	if( GetNbTileType(TYPE_GLACIER*1000+6)>NbGlacier )
		NbGlacier = GetNbTileType(TYPE_GLACIER*1000+6);

	if( (GetNbTileType(TYPE_SNOW*1000+2)+11)/12>NbGlacier )
		NbGlacier = (GetNbTileType(TYPE_SNOW*1000+2)+11)/12;
	if( (GetNbTileType(TYPE_SNOW*1000+1)+11)/12>NbGlacier )
		NbGlacier = (GetNbTileType(TYPE_SNOW*1000+1)+11)/12;

	if( (GetNbTileType(TYPE_ICE*1000+1)+20)/21>NbGlacier )
		NbGlacier = (GetNbTileType(TYPE_ICE*1000+1)+20)/21;

	return NbGlacier;
}

// Return the nb of volcarren
//
int CHeroscapeEditorDoc::ComputeNbVolcarrenSet()
{
	int NbVolcarren = 0;

	if( (GetNbTileType(TYPE_LAVAFIELD*1000+7)+3)/4>NbVolcarren )
		NbVolcarren = (GetNbTileType(TYPE_LAVAFIELD*1000+7)+3)/4;
	if( (GetNbTileType(TYPE_LAVAFIELD*1000+2)+4)/5>NbVolcarren )
		NbVolcarren = (GetNbTileType(TYPE_LAVAFIELD*1000+2)+4)/5;
	if( (GetNbTileType(TYPE_LAVAFIELD*1000+1)+4)/5>NbVolcarren )
		NbVolcarren = (GetNbTileType(TYPE_LAVAFIELD*1000+1)+4)/5;

	if( (GetNbTileType(TYPE_LAVA*1000+1)+10)/11>NbVolcarren )
		NbVolcarren = (GetNbTileType(TYPE_LAVA*1000+1)+10)/11;

	return NbVolcarren;
}

// Return the nb of master set
//
int CHeroscapeEditorDoc::ComputeNbMasterSet()
{
	int NbMasterSet = 0;

	if( (GetNbTileType(TYPE_GRASS*1000+24)+5)/6>NbMasterSet )
		NbMasterSet = (GetNbTileType(TYPE_GRASS*1000+24)+5)/6;
	if( (GetNbTileType(TYPE_GRASS*1000+7)+4)/5>NbMasterSet )
		NbMasterSet = (GetNbTileType(TYPE_GRASS*1000+7)+4)/5;
	if( (GetNbTileType(TYPE_GRASS*1000+3)+4)/5>NbMasterSet )
		NbMasterSet = (GetNbTileType(TYPE_GRASS*1000+3)+4)/5;
	if( (GetNbTileType(TYPE_GRASS*1000+2)+4)/5>NbMasterSet )
		NbMasterSet = (GetNbTileType(TYPE_GRASS*1000+2)+4)/5;
	if( (GetNbTileType(TYPE_GRASS*1000+1)+15)/16>NbMasterSet )
		NbMasterSet = (GetNbTileType(TYPE_GRASS*1000+1)+15)/16;

	if( (GetNbTileType(TYPE_ROCK*1000+24)+1)/2>NbMasterSet )
		NbMasterSet = (GetNbTileType(TYPE_ROCK*1000+24)+1)/2;
	if( (GetNbTileType(TYPE_ROCK*1000+7)+2)/3>NbMasterSet )
		NbMasterSet = (GetNbTileType(TYPE_ROCK*1000+7)+2)/3;
	if( (GetNbTileType(TYPE_ROCK*1000+3)+2)/3>NbMasterSet )
		NbMasterSet = (GetNbTileType(TYPE_ROCK*1000+3)+2)/3;
	if( (GetNbTileType(TYPE_ROCK*1000+2)+2)/3>NbMasterSet )
		NbMasterSet = (GetNbTileType(TYPE_ROCK*1000+2)+2)/3;
	if( (GetNbTileType(TYPE_ROCK*1000+1)+5)/6>NbMasterSet )
		NbMasterSet = (GetNbTileType(TYPE_ROCK*1000+1)+5)/6;

	if( (GetNbTileType(TYPE_SAND*1000+7)+1)/2>NbMasterSet )
		NbMasterSet = (GetNbTileType(TYPE_SAND*1000+7)+1)/2;
	if( (GetNbTileType(TYPE_SAND*1000+3)+1)/2>NbMasterSet )
		NbMasterSet = (GetNbTileType(TYPE_SAND*1000+3)+1)/2;
	if( (GetNbTileType(TYPE_SAND*1000+2)+1)/2>NbMasterSet )
		NbMasterSet = (GetNbTileType(TYPE_SAND*1000+2)+1)/2;
	if( (GetNbTileType(TYPE_SAND*1000+1)+3)/4>NbMasterSet )
		NbMasterSet = (GetNbTileType(TYPE_SAND*1000+1)+3)/4;

	if( (GetNbTileType(TYPE_WATER*1000+1)+20)/21>NbMasterSet )
		NbMasterSet = (GetNbTileType(TYPE_WATER*1000+1)+20)/21;

	if( GetNbTileType(TYPE_RUIN*1000+3)>NbMasterSet )
		NbMasterSet = GetNbTileType(TYPE_RUIN*1000+3);
	if( GetNbTileType(TYPE_RUIN*1000+2)>NbMasterSet )
		NbMasterSet = GetNbTileType(TYPE_RUIN*1000+2);

	if( GetNbTileType(TYPE_GLYPH*1000+'A')>NbMasterSet )
		NbMasterSet = GetNbTileType(TYPE_GLYPH*1000+'A');
	if( GetNbTileType(TYPE_GLYPH*1000+'G')>NbMasterSet )
		NbMasterSet = GetNbTileType(TYPE_GLYPH*1000+'G');
	if( GetNbTileType(TYPE_GLYPH*1000+'I')>NbMasterSet )
		NbMasterSet = GetNbTileType(TYPE_GLYPH*1000+'I');
	if( GetNbTileType(TYPE_GLYPH*1000+'V')>NbMasterSet )
		NbMasterSet = GetNbTileType(TYPE_GLYPH*1000+'V');
	if( GetNbTileType(TYPE_GLYPH*1000+'D')>NbMasterSet )
		NbMasterSet = GetNbTileType(TYPE_GLYPH*1000+'D');
	if( (GetNbTileType(TYPE_GLYPH*1000+'B')+1)/2>NbMasterSet )
		NbMasterSet = (GetNbTileType(TYPE_GLYPH*1000+'B')+1)/2;
	if( GetNbTileType(TYPE_GLYPH*1000+'K')>NbMasterSet )
		NbMasterSet = GetNbTileType(TYPE_GLYPH*1000+'K');
	if( GetNbTileType(TYPE_GLYPH*1000+'E')>NbMasterSet )
		NbMasterSet = GetNbTileType(TYPE_GLYPH*1000+'E');
	if( GetNbTileType(TYPE_GLYPH*1000+'M')>NbMasterSet )
		NbMasterSet = GetNbTileType(TYPE_GLYPH*1000+'M');

	return NbMasterSet;
}

// Return the nb of tile of this type
//
int CHeroscapeEditorDoc::GetNbTileType( int Type )
{
	int Nb = 0;
	for( int i=0; i<m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_TileList.GetAt(i);
		if( pTile->m_Type==Type )
			Nb++;
	}

	return Nb;
}

// Erase the information windows
//
void CHeroscapeEditorDoc::EraseInformation()
{
	((CMainFrame*) theApp.m_pMainWnd)->m_wndInfoBar.GetListCtrl()->DeleteAllItems();
	((CMainFrame*) theApp.m_pMainWnd)->m_wndInfoBar.GetListCtrl()->RedrawWindow();
	((CMyListCtrl*) ((CMainFrame*) theApp.m_pMainWnd)->m_wndInfoBar.GetListCtrl())->DeleteAllDatas();
}

// Add a line on the information view
//
void CHeroscapeEditorDoc::AddInformation( int Type, int Level, CString TileName, CString Text, int x, int y, int z )
{
	int NoImage;
	CString StrType;

	switch( Type )
	{
	case IB_INFO:
		m_NbInfo++;
		NoImage=0;
		StrType.LoadStringW( IDS_INFORMATION );
		break;
	case IB_WARNING:
		m_NbWarning++;
		NoImage=1;
		StrType.LoadStringW( IDS_WARNING );
		break;
	case IB_CRITICAL:
		m_NbCritical++;
		NoImage=2;
		StrType.LoadStringW( IDS_CRITICAL );
		break;
	}
	CString Str;
	if( Level<0 )
		Str.Format( _T("%s;;%s;%s"), StrType, TileName, Text );
	else
		Str.Format( _T("%s;%i;%s;%s"), StrType, Level+1, TileName, Text );
	CGlobalIHM::AddListItem( ((CMainFrame*) theApp.m_pMainWnd)->m_wndInfoBar.GetListCtrl(), Str, -1, NoImage );
	((CMainFrame*) theApp.m_pMainWnd)->m_wndInfoBar.GetListCtrl()->EnsureVisible( ((CMainFrame*) theApp.m_pMainWnd)->m_wndInfoBar.GetListCtrl()->GetItemCount()-1, FALSE );

	InformationDatas* pDatas = (InformationDatas*) malloc( sizeof(InformationDatas) );
	pDatas->x = x;
	pDatas->y = y;
	pDatas->z = z;
	((CMyListCtrl*) ((CMainFrame*) theApp.m_pMainWnd)->m_wndInfoBar.GetListCtrl())->AddInformationDatas( pDatas );
}

// Load all the necesary objects (as figures)
//
void CHeroscapeEditorDoc::LoadNecessaryObjects( void* pView )
{
	for( int i=0; i<m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_TileList.GetAt(i);
		pTile->LoadNecessaryObjects( pView );
	}
}

// Copy all the selected tile in the application clipboard
//
void CHeroscapeEditorDoc::OnEditionCopier()
{
	// Remove all the tile from the clipboard
	theApp.RemoveClipboard();

	// Now, copy the selection to the clipboard
	for( int i=0; i<m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_TileList.GetAt(i);
		if( pTile->m_IsSelected )
		{
			theApp.m_TileClipboard.Add( pTile->GetExactCopy() );
		}
	}
}

// Move all the selected tile in the application clipboard
//
void CHeroscapeEditorDoc::OnEditionCouper()
{
	// Remove all the tile from the clipboard
	theApp.RemoveClipboard();

	// Now, copy the selection to the clipboard
	for( int i=0; i<m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_TileList.GetAt(i);
		if( pTile->m_IsSelected )
		{
			theApp.m_TileClipboard.Add( pTile->GetExactCopy() );
		}
	}

	// Then remove the selection
	RemoveSelection();

	UpdateAll3DViews();
	UpdateAllViews(NULL);
	RedrawAllViews();

	DisplaySelectedCount();
}

// Copy all the clipboard tile into the document
//
void CHeroscapeEditorDoc::OnEditionColler()
{
	// unselect all the document
	UnselectAllTile();

	// Now, copy the selection from the clipboard
	for( int i=0; i<theApp.m_TileClipboard.GetSize(); i++ )
	{
		CTile* pTile = (CTile*) theApp.m_TileClipboard.GetAt(i);
		AddTile( pTile->GetExactCopy() );
	}

	DisplaySelectedCount();

	UpdateAll3DViews();
	UpdateAllViews(NULL);
	RedrawAllViews();
}

// To know if the paste function must be validate or not
//
void CHeroscapeEditorDoc::OnUpdateEditionColler(CCmdUI *pCmdUI)
{
	if( theApp.m_TileClipboard.GetCount()>0 )
		pCmdUI->Enable( true );
	else
		pCmdUI->Enable( false );
}

// To know if the copy function must be validate or not
//
void CHeroscapeEditorDoc::OnUpdateEditionCopier(CCmdUI *pCmdUI)
{
	if( GetNbSelectedTile()>0 )
	{
		pCmdUI->Enable( TRUE );
		return;
	}

	pCmdUI->Enable( FALSE );
}

// To know if the cut function must be validate or not
//
void CHeroscapeEditorDoc::OnUpdateEditionCouper(CCmdUI *pCmdUI)
{
	if( GetNbSelectedTile()>0 )
	{
		pCmdUI->Enable( TRUE );
		return;
	}

	pCmdUI->Enable( FALSE );
}

// Display the selected tile count in the status bar
//
void CHeroscapeEditorDoc::DisplaySelectedCount()
{
	CString Str;

	int MinLevel = 1000;
	int MaxLevel = 0;
	int Nb = 0;

	for( int i=0; i<m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_TileList.GetAt(i);
		if( pTile->m_IsSelected )
		{
			if( pTile->m_PosZ<MinLevel )
				MinLevel = pTile->m_PosZ;
			if( pTile->m_PosZ>MaxLevel )
				MaxLevel = pTile->m_PosZ;

			Nb++;
		}
	}

	if( Nb==0 )
		Str.LoadStringW(IDS_NOTHING_SELECTED);
	else
	{
		CString Str2;
		Str2.LoadStringW(IDS_DISPLAY_SELECTED);
		Str.Format( Str2, Nb, MaxLevel-MinLevel+1, MinLevel, MaxLevel );
	}

	((CMainFrame*) theApp.m_pMainWnd)->m_wndStatusBar.SetPaneText( 1, Str );
}

// The user want create a game
//
void CHeroscapeEditorDoc::OnPlayCreategame()
{
	//AfxMessageBox( _T("Impossible de creer un jeu avec cette version de Virtualscape (Reservé a Zzzzz)") );
	//return;
	CCreateGameDlg cgd;

	// Set default parameters
	cgd.m_PlayerName = theApp.m_PlayerName;
	cgd.m_GameName = theApp.m_GameName;
	cgd.m_GamePassword = theApp.m_GamePassword;
	cgd.m_GameType = theApp.m_GameType;
	cgd.m_GamePoint = theApp.m_GamePoint;
	cgd.m_PlayerMax = theApp.m_GamePlayerMax;
	cgd.m_WatcherMax = theApp.m_GameWatcherMax;
	cgd.m_WelcomeMessage = theApp.m_GameWelcomeMessage;
	cgd.m_ServerPort = theApp.m_GamePort;
	cgd.m_IP_Address = theApp.m_IP_Address;
	cgd.m_Game_Language = theApp.m_GameLanguage;

	if( cgd.DoModal()==IDOK )
	{
		// Get default parameters
		theApp.m_PlayerName = cgd.m_PlayerName;
		theApp.m_GameName = cgd.m_GameName;
		theApp.m_IP_Address = cgd.m_IP_Address;
		theApp.m_GamePassword = cgd.m_GamePassword;
		theApp.m_GameType = cgd.m_GameType;
		theApp.m_GamePoint = cgd.m_GamePoint;
		theApp.m_GamePlayerMax = cgd.m_PlayerMax;
		theApp.m_GameWatcherMax = cgd.m_WatcherMax;
		theApp.m_GameWelcomeMessage = cgd.m_WelcomeMessage;
		theApp.m_GamePort = cgd.m_ServerPort;
		theApp.m_GameLanguage = cgd.m_Game_Language;

		// Create the game server
		if( theApp.m_pGameDocServer!=NULL )
			delete theApp.m_pGameDocServer;
		theApp.m_pGameDocServer = new CGameDocServer();
		// Set the game name
		theApp.m_pGameDocServer->m_BattleFieldName = m_Name;
		// Add all the usefull tile to the doc
		for( int i=0; i<m_TileList.GetCount(); i++ )
		{
			CTile* pTile = (CTile*) m_TileList.GetAt(i);
			if( pTile->IsGameAvailable() )
				theApp.m_pGameDocServer->AddTile( pTile->GetExactCopy() );
		}

		// Create the game
		if( theApp.m_pGameDoc!=NULL )
			delete theApp.m_pGameDoc;
		theApp.m_pGameDoc = new CGameDoc();
		theApp.m_pGameDoc->m_IsServer = true;
		theApp.m_pDocTemplateGame3D->AddDocument( theApp.m_pGameDoc );
		CChildFrame* pFrame = (CChildFrame*) theApp.m_pDocTemplateGame3D->CreateNewFrame( theApp.m_pGameDoc, NULL );
		theApp.m_pDocTemplateGame3D->InitialUpdateFrame( pFrame, theApp.m_pGameDoc, FALSE );
		pFrame->MDIActivate();
		CGame3DView* pView = (CGame3DView*) pFrame->GetActiveView();
		pView->InitParams();
		pFrame->ShowWindow( SW_SHOWMAXIMIZED );
		pView->AfterCreate();

		theApp.m_pGameDoc->m_ToServerSocket.Create();

		DWORD	dw=0;
		int opt = 1;

		// Register this server to the dedicated Server
		theApp.m_pToDedicatedServerSocket = new CToDedicatedServerSocket();
		theApp.m_pToDedicatedServerSocket->Create();
		theApp.m_pToDedicatedServerSocket->SetSockOpt( SO_DONTLINGER, (const void*) &opt, sizeof( bool), SOL_SOCKET );
		if( theApp.m_pToDedicatedServerSocket->Connect(_T("88.186.169.121"),2811)==0 )
		{
			theApp.m_pToDedicatedServerSocket->SocketError();
			AfxMessageBox( _T("Unable to connect to dedicated server !") );
			pFrame->DestroyWindow();
			delete theApp.m_pGameDoc;
			theApp.m_pGameDoc=NULL;
			delete theApp.m_pGameDocServer;
			theApp.m_pGameDocServer = NULL;
			return;
		}

		// Send information to the dedicated server
		theApp.m_pToDedicatedServerSocket->CreateBuffer();
		theApp.m_pToDedicatedServerSocket->WriteType( m_Name );
		theApp.m_pToDedicatedServerSocket->WriteType( theApp.m_PlayerName );
		theApp.m_pToDedicatedServerSocket->WriteType( theApp.m_GameLanguage );
		theApp.m_pToDedicatedServerSocket->WriteType( theApp.m_GameType );
		theApp.m_pToDedicatedServerSocket->WriteType( theApp.m_IP_Address );
		theApp.m_pToDedicatedServerSocket->WriteType( theApp.m_GamePort );
		theApp.m_pToDedicatedServerSocket->SendMessageW( SMI_TODEDICATEDSERVER_NEW_SERVER );

		theApp.m_pGameDoc->m_ToServerSocket.SetSockOpt( SO_DONTLINGER, (const void*) &opt, sizeof( bool), SOL_SOCKET );
		CString IPAddress = _T("127.0.0.1");
		if( theApp.m_pGameDoc->m_ToServerSocket.Connect(IPAddress,theApp.m_GamePort)==0 )
			theApp.m_pGameDoc->m_ToServerSocket.SocketError();

		// Create the waiting dialog
		theApp.m_pWaitingConnection = new CWaitingConnection();

		theApp.m_pWaitingConnection->m_pGameDoc = theApp.m_pGameDoc;
		theApp.m_pWaitingConnection->m_IsServer = true;

		if( theApp.m_pWaitingConnection->DoModal()==IDOK )
		{
			delete theApp.m_pWaitingConnection;
			theApp.m_pWaitingConnection = NULL;

			// Send information to the dedicated server
			theApp.m_pToDedicatedServerSocket->CreateBuffer();
			theApp.m_pToDedicatedServerSocket->WriteType( (int) theApp.m_pGameDoc->m_PlayerArray.GetCount() );
			theApp.m_pToDedicatedServerSocket->SendMessageW( SMI_TODEDICATEDSERVER_GAME_BEGIN );

			theApp.m_pGameDocServer->InitGame();
		}
		else
		{
			// Send information to the dedicated server
			theApp.m_pToDedicatedServerSocket->CreateBuffer();
			theApp.m_pToDedicatedServerSocket->SendMessageW( SMI_TODEDICATEDSERVER_GAME_END );

			pFrame->DestroyWindow();
			delete theApp.m_pGameDoc;
			theApp.m_pGameDoc=NULL;
			delete theApp.m_pGameDocServer;
			theApp.m_pGameDocServer = NULL;
		}
	}
}

// Get the number of personal tile of a particular type
//
int CHeroscapeEditorDoc::GetPersonalTileOfType( CTilePerso* pTilePerso )
{
	int Nb=0;

	for( int i=0; i<m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_TileList.GetAt(i);
		if( pTile->GetName() == pTilePerso->GetName() )
		{
			if( pTile->m_NbTile==pTilePerso->m_NbTile )
				Nb++;
		}
	}

	return Nb;
}
