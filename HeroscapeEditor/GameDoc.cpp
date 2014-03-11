// GameDoc.cpp : fichier d'implémentation
//

#include "StdAfx.h"

#include "ArmyManager.h"
#include "ChooseArmyDlg.h"
#include "FigureObject.h"
#include "GameDoc.h"
#include "HeroscapeEditor.h"
#include "LaunchDiceDlg.h"
#include "MainFrm.h"
#include "SocketMessageId.h"

// CGameDoc

IMPLEMENT_DYNCREATE(CGameDoc, CHeroscapeEditorDoc)

// The constructor
//
CGameDoc::CGameDoc()
:
// no player index now
m_PlayerIndex(-1),
m_GameMode( GAMEMODE_NULL ),
m_AnimationType( ANIMATIONTYPE_SIMPLE )
{
}

// The destructor
//
CGameDoc::~CGameDoc()
{
	// Send information to the dedicated server
	theApp.m_pToDedicatedServerSocket->CreateBuffer();
	theApp.m_pToDedicatedServerSocket->SendMessageW( SMI_TODEDICATEDSERVER_GAME_END );

	// Freeing memory
	for( int i=0; i<m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_TileList.GetAt(i);
		delete pTile;
	}
	m_TileList.RemoveAll();

	if( theApp.m_pGameDoc!=NULL && theApp.m_IsInGameMode )
	{
		// Return to normal game mode
		theApp.ExitGameMode();
	}
	// now, there are no game doc object
	theApp.m_pGameDoc = NULL;
}

BEGIN_MESSAGE_MAP(CGameDoc, CHeroscapeEditorDoc)
	ON_COMMAND(ID_JOUER_QUITTERLEJEU, &CGameDoc::OnJouerQuitterlejeu)
	ON_COMMAND(ID_PLACE_FIGURE_ON_MAP, &CGameDoc::OnPlaceFigureOnMap)
	ON_COMMAND(ID_REMOVE_FIGURE_FROM_MAP, &CGameDoc::OnRemoveFigureFromMap)
	ON_COMMAND(ID_MOVE_FIGURE, &CGameDoc::OnMoveFigure)
	ON_COMMAND(ID_ATTACK_CHOOSE_FIGURE, &CGameDoc::OnAttackChooseFigure)
	ON_COMMAND(ID_ATTACK_DICE, &CGameDoc::OnAttackDice)
	ON_COMMAND(ID_DEFENSE_DICE, &CGameDoc::OnDefenseDice)
	ON_COMMAND(ID_NEXT_TURN, &CGameDoc::OnNextTurn)
	ON_COMMAND(ID_OUTILS_ANIMATIONSSIMPLES, &CGameDoc::OnOutilsAnimationssimples)
	ON_UPDATE_COMMAND_UI(ID_OUTILS_ANIMATIONSSIMPLES, &CGameDoc::OnUpdateOutilsAnimationssimples)
	ON_COMMAND(ID_OUTILS_ANIMATIONSTOURNANTE, &CGameDoc::OnOutilsAnimationstournante)
	ON_UPDATE_COMMAND_UI(ID_OUTILS_ANIMATIONSTOURNANTE, &CGameDoc::OnUpdateOutilsAnimationstournante)
	ON_COMMAND(ID_REPLAY_GAME, &CGameDoc::OnReplayGame)
	ON_COMMAND(ID_REPLAY_TO_FILE, &CGameDoc::OnReplayToFile)
	ON_COMMAND(ID_DIE_20, &CGameDoc::OnDie20Faces)
END_MESSAGE_MAP()

// Serialize the game
//
void CGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO : ajoutez ici le code de stockage
	}
	else
	{
		// TODO : ajoutez ici le code de chargement
	}
}

// Receive the players list
//
void CGameDoc::ReceivePlayersList( CClientSocket* pSocket )
{
	// Remove all previous players
	for( int i=0; i<m_PlayerArray.GetCount(); i++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(i);
		delete pPlayer;
	}
	m_PlayerArray.RemoveAll();

	// Read all the players
	int Nb;
	pSocket->ReadType( Nb );
	pSocket->ReadType( m_PlayerIndex );
	for( int i=0; i<Nb; i++ )
	{
		CPlayer* pPlayer = new CPlayer();
		CString Str;
		pSocket->ReadType( Str );
		pPlayer->SetName( Str );
		pPlayer->m_PointForArmy = m_GamePoint;
		pSocket->ReadType( pPlayer->m_Type );
		m_PlayerArray.Add( pPlayer );
	}

	if( theApp.m_pWaitingConnection )
		theApp.m_pWaitingConnection->RefreshPlayersList();
}

// Add a tile to the list
//
void CGameDoc::AddTile( CTile* pTile )
{
	m_TileList.Add( pTile );
}

// Init the game doc
//
void CGameDoc::Init()
{
	ComputeLevelMax();
	ComputeArea();

	CPtrArray* pArray = CArmyManager::GetAllArmy();
	m_ArmyArray.Append( *pArray );
	delete pArray;

	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CGame3DView* pView = (CGame3DView*) GetNextView(pos);
		pView->InitParams();
	}

	// Inform player bar of the current game doc and so of the players list
	((CMainFrame*) (theApp.m_pMainWnd))->m_wndGamePlayerBar.m_pListCtrlPlayer->SetCurrentGameDoc( this );

	// Update view
	UpdateAll3DViews();
}

// Compute the differents param
//
void CGameDoc::ComputeArea()
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

	if( m_YOffset<0 )
	{
		int DiffY = -m_YOffset;

		for( int i=0; i<m_TileList.GetCount(); i++ )
		{
			CTile* pTile = (CTile*) m_TileList.GetAt(i);

			if( (((int) DiffY)%2==1 || ((int) DiffY)%2==-1) && pTile->m_PosY%2==0 )
				pTile->m_PosX -= 1;
			pTile->m_PosY += (int) DiffY;
		}
		// Now Move X
		ComputeArea();
		SetModifiedFlag();
	}
	else if( XOffsetEven<0 || XOffsetOdd<0 )
	{
		int MoveX;
		// Move everything
		if( XOffsetEven<XOffsetOdd )
			MoveX = -XOffsetEven;
		else
			MoveX = -XOffsetOdd;

		for( int i=0; i<m_TileList.GetCount(); i++ )
		{
			CTile* pTile = (CTile*) m_TileList.GetAt(i);
			pTile->m_PosX += MoveX;
		}
		ComputeArea();
	}
}

// Compute the level Max
//
void CGameDoc::ComputeLevelMax()
{
	m_LevelMax = 0;

	for( int i=0; i<m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_TileList.GetAt(i);
		if( pTile->m_PosZ+1>m_LevelMax )
			m_LevelMax = pTile->m_PosZ+1;
	}
}

// Load all the necessary objects (as figures)
//
void CGameDoc::LoadNecessaryObjects( void* pView )
{
	for( int i=0; i<m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_TileList.GetAt(i);
		pTile->LoadNecessaryObjects( pView );
	}
}

// Redraw all the views
//
void CGameDoc::UpdateAll3DViews()
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
		{
			((CGame3DView*) pView)->UpdateData1();
			((CGame3DView*) pView)->UpdateData2();
			((CGame3DView*) pView)->RenderScene( false );
			((CGame3DView*) pView)->RedrawWindow();
		}
	}
}

// Choose your army
//
void CGameDoc::ChooseArmy()
{
	CChooseArmyDlg Dlg;

	Dlg.SetPoint( ((CPlayer*) m_PlayerArray.GetAt(m_PlayerIndex))->m_PointForArmy );
	Dlg.SetArmyList( &m_ArmyArray );

	int ArmyIndex = -1;

	while( ArmyIndex==-1 )
	{
		if( Dlg.DoModal()==IDOK )
		{
			ArmyIndex = Dlg.m_SelectedIndex;
			if( ArmyIndex>-1 )
			{
				if( theApp.m_GameType==GAMETYPE_EXPERT )
				{
					if( ((CArmyCard*) m_ArmyArray.GetAt(ArmyIndex))->m_ExpertCostPoint>((CPlayer*) m_PlayerArray.GetAt(m_PlayerIndex))->m_PointForArmy )
					{
						ArmyIndex=-1;
					}
				}
			}
		}
	}

	// Inform the server than an army has been choose
	m_ToServerSocket.CreateBuffer();
	m_ToServerSocket.WriteType( m_PlayerIndex );
	m_ToServerSocket.WriteType( ArmyIndex );
	m_ToServerSocket.SendMessageW( SMI_TOSERVER_ARMYCHOOSED );
}

// Set the point for army in this game
//
void CGameDoc::SetGamePoint( int GamePoint )
{
	for( int i=0; i<m_PlayerArray.GetCount(); i++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(i);

		pPlayer->m_PointForArmy = GamePoint;
	}
	m_GamePoint = GamePoint;
}

// Add an army to a player
//
void CGameDoc::AddArmyToPlayer( int PlayerIndex, int ArmyIndex )
{
	CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(PlayerIndex);
	CArmyCard* pArmyCard = (CArmyCard*) m_ArmyArray.GetAt(ArmyIndex);

	// Add the Army to the player
	pPlayer->AddArmy( pArmyCard );

	// Remove the army from this list
	m_ArmyArray.RemoveAt( ArmyIndex );

	// Redraw Players control
	((CMainFrame*) theApp.m_pMainWnd)->m_wndGamePlayerBar.m_pListCtrlPlayer->RedrawWindow();
}

// Place a figure for a player
//
void CGameDoc::PlaceFigureForPlayer( int PlayerIndex, int ArmyIndex, int FigureIndex, int x, int y, int z, int Rotation, double CameraX, double CameraY, double CameraZ, double LookAtX, double LookAtY, double LookAtZ )
{
	// Get the tile
	CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(PlayerIndex);
	CArmyCard* pArmyCard = (CArmyCard*) pPlayer->m_ArmyList.GetAt(ArmyIndex);
	CFigureObject* pFigure = (CFigureObject*) pArmyCard->GetFiguresList()->GetAt(FigureIndex);

	CTile* pTile = pFigure->m_pTileFigure;
	pTile->m_PosX = x;
	pTile->m_PosY = y;
	pTile->m_PosZ = z;
	pTile->m_CurrentRotation = Rotation;
	pFigure->m_IsPlacedOnMap = true;

	// Check if tile exist
	if( !IsTileInTileList( pTile ) )
		AddTile( pTile );
	
	m_pCurrentFigureTile = pTile;
	m_pCurrentFigureTile->m_CreationTime = 0;

	SetModifiedFlag();
	//UpdateAll3DViews();

	// Set all the view in show place figure mode

	if( m_AnimationType==ANIMATIONTYPE_TURNING )
	{
		// Compute 6 animated key
		MyPoint3D PositionCamera1,PositionCamera2,PositionCamera3,PositionCamera4,PositionCamera5;
		MyPoint3D PositionLookAt1,PositionLookAt2,PositionLookAt3,PositionLookAt4,PositionLookAt5;

		PositionLookAt2.x = PositionLookAt3.x = PositionLookAt4.x = PositionLookAt5.x = pTile->m_PosX*TILE3D_WIDTH;
		PositionLookAt2.y = PositionLookAt3.y = PositionLookAt4.y = PositionLookAt5.y = -pTile->m_PosY*TILE3D_HEIGHT;
		PositionLookAt2.z = PositionLookAt3.z = PositionLookAt4.z = PositionLookAt5.z = pTile->m_PosZ*TILE3D_ZHEIGHT;

		double Distance = TILE3D_WIDTH*15;
		srand( GetTickCount() );

		PositionCamera2.x = PositionLookAt2.x + Distance;
		PositionCamera2.y = PositionLookAt2.y;
		PositionCamera2.z = PositionLookAt2.z + Distance*(.1+(((double) rand())/RAND_MAX)*.4);

		PositionCamera3.x = PositionLookAt3.x;
		PositionCamera3.y = PositionLookAt3.y + Distance;
		PositionCamera3.z = PositionLookAt3.z + Distance*(.1+(((double) rand())/RAND_MAX)*.4);

		PositionCamera4.x = PositionLookAt4.x - Distance;
		PositionCamera4.y = PositionLookAt4.y;
		PositionCamera4.z = PositionLookAt4.z + Distance*(.1+(((double) rand())/RAND_MAX)*.4);

		PositionCamera5.x = PositionLookAt2.x;
		PositionCamera5.y = PositionLookAt2.y - Distance;
		PositionCamera5.z = PositionLookAt2.z + Distance*(.1+(((double) rand())/RAND_MAX)*.4);

		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CView* pView = GetNextView(pos);
			if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
			{
				((CGame3DView*) pView)->OnVideoEraseAllPosition();

				PositionCamera1 = ((CGame3DView*) pView)->m_CameraPosition;
				PositionLookAt1 = ((CGame3DView*) pView)->m_CameraLookAt;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera2;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt2;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera3;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt3;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera4;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt4;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera5;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt5;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera1;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt1;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->MoveFigurePlacedRealtime();
			}
		}
	}
	else if ( m_AnimationType==ANIMATIONTYPE_SIMPLE )
	{
		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CView* pView = GetNextView(pos);
			if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
			{
				((CGame3DView*) pView)->OnVideoEraseAllPosition();

				MyPoint3D PositionCamera1 = ((CGame3DView*) pView)->m_CameraPosition;
				MyPoint3D PositionLookAt1 = ((CGame3DView*) pView)->m_CameraLookAt;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition.x = CameraX;
				((CGame3DView*) pView)->m_CameraPosition.y = CameraY;
				((CGame3DView*) pView)->m_CameraPosition.z = CameraZ;
				((CGame3DView*) pView)->m_CameraLookAt.x = LookAtX;
				((CGame3DView*) pView)->m_CameraLookAt.y = LookAtY;
				((CGame3DView*) pView)->m_CameraLookAt.z = LookAtZ;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera1;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt1;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->MoveFigurePlacedRealtime();
			}
		}
	}
	else if ( m_AnimationType==ANIMATIONTYPE_REPLAY )
	{
		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CView* pView = GetNextView(pos);
			if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
			{
				((CGame3DView*) pView)->OnVideoEraseAllPosition();

				MyPoint3D PositionCamera1 = ((CGame3DView*) pView)->m_CameraPosition;
				MyPoint3D PositionLookAt1 = ((CGame3DView*) pView)->m_CameraLookAt;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition.x = CameraX;
				((CGame3DView*) pView)->m_CameraPosition.y = CameraY;
				((CGame3DView*) pView)->m_CameraPosition.z = CameraZ;
				((CGame3DView*) pView)->m_CameraLookAt.x = LookAtX;
				((CGame3DView*) pView)->m_CameraLookAt.y = LookAtY;
				((CGame3DView*) pView)->m_CameraLookAt.z = LookAtZ;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();
				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->MoveFigurePlacedRealtime();
			}
		}
	}
}

// Move a figure for a player
//
void CGameDoc::MoveFigureForPlayer( int PlayerIndex, int ArmyIndex, int FigureIndex, int x, int y, int z, int Rotation, double CameraX, double CameraY, double CameraZ, double LookAtX, double LookAtY, double LookAtZ )
{
	// Get the tile
	CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(PlayerIndex);
	CArmyCard* pArmyCard = (CArmyCard*) pPlayer->m_ArmyList.GetAt(ArmyIndex);
	CFigureObject* pFigure = (CFigureObject*) pArmyCard->GetFiguresList()->GetAt(FigureIndex);

	CTile* pTile = pFigure->m_pTileFigure;
	int OldPosX = pTile->m_PosX;
	int OldPosY = pTile->m_PosY;
	int OldPosZ = pTile->m_PosZ;
	int OldRotation = pTile->m_CurrentRotation;
	//pTile->m_PosX = x;
	//pTile->m_PosY = y;
	//pTile->m_PosZ = z;
	//pTile->m_CurrentRotation = Rotation;
	pFigure->m_IsPlacedOnMap = true;

	m_pCurrentFigureTile = pTile;

	SetModifiedFlag();
	//UpdateAll3DViews();

	if ( m_AnimationType==ANIMATIONTYPE_TURNING )
	{
		// Compute 6 animated key
		MyPoint3D PositionCamera1,PositionCamera2,PositionCamera3,PositionCamera4,PositionCamera5;
		MyPoint3D PositionLookAt1,PositionLookAt2,PositionLookAt3,PositionLookAt4,PositionLookAt5;

		PositionLookAt2.x = PositionLookAt3.x = pTile->m_PosX*TILE3D_WIDTH;
		PositionLookAt4.x = PositionLookAt5.x = x*TILE3D_WIDTH;
		PositionLookAt2.y = PositionLookAt3.y = -pTile->m_PosY*TILE3D_HEIGHT;
		PositionLookAt4.y = PositionLookAt5.y = -y*TILE3D_HEIGHT;
		PositionLookAt2.z = PositionLookAt3.z = pTile->m_PosZ*TILE3D_ZHEIGHT;
		PositionLookAt4.z = PositionLookAt5.z = z*TILE3D_ZHEIGHT;

		double Distance = TILE3D_WIDTH*15;
		srand( GetTickCount() );

		PositionCamera2.x = PositionLookAt2.x + Distance;
		PositionCamera2.y = PositionLookAt2.y;
		PositionCamera2.z = PositionLookAt2.z + Distance*(.1+(((double) rand())/RAND_MAX)*.4);

		PositionCamera3.x = PositionLookAt3.x;
		PositionCamera3.y = PositionLookAt3.y + Distance;
		PositionCamera3.z = PositionLookAt3.z + Distance*(.1+(((double) rand())/RAND_MAX)*.4);

		PositionCamera4.x = PositionLookAt4.x;
		PositionCamera4.y = PositionLookAt4.y + Distance;
		PositionCamera4.z = PositionLookAt4.z + Distance*(.1+(((double) rand())/RAND_MAX)*.4);

		PositionCamera5.x = PositionLookAt2.x - Distance;
		PositionCamera5.y = PositionLookAt2.y;
		PositionCamera5.z = PositionLookAt2.z + Distance*(.1+(((double) rand())/RAND_MAX)*.4);

		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CView* pView = GetNextView(pos);
			if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
			{
				((CGame3DView*) pView)->SetMoveFigurePosition( OldPosX, OldPosY, OldPosZ, OldRotation, x, y, z, Rotation );
				((CGame3DView*) pView)->OnVideoEraseAllPosition();

				PositionCamera1 = ((CGame3DView*) pView)->m_CameraPosition;
				PositionLookAt1 = ((CGame3DView*) pView)->m_CameraLookAt;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera2;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt2;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera3;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt3;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera4;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt4;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera5;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt5;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera1;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt1;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->MoveFigureMovedRealtime();
			}
		}
	}
	else if ( m_AnimationType==ANIMATIONTYPE_SIMPLE )
	{
		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CView* pView = GetNextView(pos);
			if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
			{
				((CGame3DView*) pView)->SetMoveFigurePosition( OldPosX, OldPosY, OldPosZ, OldRotation, x, y, z, Rotation );
				((CGame3DView*) pView)->OnVideoEraseAllPosition();

				MyPoint3D PositionCamera1 = ((CGame3DView*) pView)->m_CameraPosition;
				MyPoint3D PositionLookAt1 = ((CGame3DView*) pView)->m_CameraLookAt;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition.x = CameraX;
				((CGame3DView*) pView)->m_CameraPosition.y = CameraY;
				((CGame3DView*) pView)->m_CameraPosition.z = CameraZ;
				((CGame3DView*) pView)->m_CameraLookAt.x = LookAtX;
				((CGame3DView*) pView)->m_CameraLookAt.y = LookAtY;
				((CGame3DView*) pView)->m_CameraLookAt.z = LookAtZ;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera1;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt1;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->MoveFigureMovedRealtime();
			}
		}
	}
	else if ( m_AnimationType==ANIMATIONTYPE_REPLAY )
	{
		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CView* pView = GetNextView(pos);
			if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
			{
				((CGame3DView*) pView)->SetMoveFigurePosition( OldPosX, OldPosY, OldPosZ, OldRotation, x, y, z, Rotation );
				((CGame3DView*) pView)->OnVideoEraseAllPosition();

				MyPoint3D PositionCamera1 = ((CGame3DView*) pView)->m_CameraPosition;
				MyPoint3D PositionLookAt1 = ((CGame3DView*) pView)->m_CameraLookAt;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition.x = CameraX;
				((CGame3DView*) pView)->m_CameraPosition.y = CameraY;
				((CGame3DView*) pView)->m_CameraPosition.z = CameraZ;
				((CGame3DView*) pView)->m_CameraLookAt.x = LookAtX;
				((CGame3DView*) pView)->m_CameraLookAt.y = LookAtY;
				((CGame3DView*) pView)->m_CameraLookAt.z = LookAtZ;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();
				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->MoveFigureMovedRealtime();
			}
		}
	}
}

// To know if a tile is already in the list
//
bool CGameDoc::IsTileInTileList( CTile* pTile )
{
	for( int i=0; i<m_TileList.GetCount(); i++ )
	{
		if(m_TileList.GetAt(i)==pTile )
			return true;
	}

	return false;
}

// Enter in free game mode
//
void CGameDoc::FreeGame()
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
		{
			((CGame3DView*) pView)->EnterFreeGameMode();
		}
	}

	m_GameMode = GAMEMODE_FREE;
}

// User want qui the current game
//
void CGameDoc::OnJouerQuitterlejeu()
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
		{
			((CGame3DView*) pView)->GetParentFrame()->DestroyWindow();
		}
	}
}

// The user want place a figure on map
//
void CGameDoc::OnPlaceFigureOnMap()
{
	m_GameMode = GAMEMODE_PLACEFIGURE;

	// First select your army card
	CChooseArmyDlg Dlg;

	CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(m_PlayerIndex);
	
	// Construct an army list with army of the player wich contains one figure or more not placed on map
	CPtrArray ToPlaceArmyList;
	for( int i=0; i<pPlayer->m_ArmyList.GetCount(); i++ )
	{
		bool IsPlaced = true;
		// Check if a figure is not placed
		CArmyCard* pArmyCard = (CArmyCard*) pPlayer->m_ArmyList.GetAt(i);
		for( int j=0; j<pArmyCard->GetFiguresList()->GetCount(); j++ )
		{
			CFigureObject* pFigure = (CFigureObject*) pArmyCard->GetFiguresList()->GetAt(j);
			if( !pFigure->m_IsPlacedOnMap )
				IsPlaced = false;
		}
		if( !IsPlaced )
			ToPlaceArmyList.Add(pArmyCard);
	}

	if( ToPlaceArmyList.GetCount()==0 )
	{
		AfxMessageBox( IDS_ALL_FIGURE_PLACED );
		return;
	}
	
	Dlg.SetArmyList( &ToPlaceArmyList );

	int ArmyIndex = -1;

	while( ArmyIndex==-1 )
	{
		Dlg.DoModal();
		ArmyIndex = Dlg.m_SelectedIndex;
	}

	ResetAllFigure();

	// We suppose that the user want place the first figure not placed on the map
	CArmyCard* pArmyCard = (CArmyCard*) ToPlaceArmyList.GetAt(ArmyIndex);
	int FigureIndex=0;
	for( ; FigureIndex<pArmyCard->GetFiguresList()->GetCount(); FigureIndex++ )
	{
		CFigureObject* pFigure = (CFigureObject*) pArmyCard->GetFiguresList()->GetAt(FigureIndex);
		if( !pFigure->m_IsPlacedOnMap )
			break;
	}

	for( int i=0; i<pPlayer->m_ArmyList.GetCount(); i++ )
	{
		CArmyCard* pArmyCard2 = (CArmyCard*) pPlayer->m_ArmyList.GetAt(i);
		if( pArmyCard==pArmyCard2 )
			ArmyIndex=i;
	}

	m_CurrentFigureArmyIndex = ArmyIndex;
	m_pCurrentFigure = (CFigureObject*) pArmyCard->GetFiguresList()->GetAt(FigureIndex);
	m_CurrentFigureIndex = FigureIndex;
	m_pCurrentFigure->m_pTileFigure->m_ToDisplay = true;

	// Set all the view in place figure mode
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
		{
			((CGame3DView*) pView)->EnterInSelectPositionMode( m_pCurrentFigure->m_UseTwoHex );
			pView->SetFocus();
		}
	}
}

// The user has choose a position
//
void CGameDoc::SetCurrentSelectedPosition( int x, int y, int z, int Rotation )
{
	CGame3DView* pFirstView;

	// Get first view
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
		{
			pFirstView = (CGame3DView*) pView;
			break;
		}
	}

	if( m_GameMode==GAMEMODE_PLACEFIGURE )
	{
		// Inform the server than a figure has been placed
		m_ToServerSocket.CreateBuffer();
		m_ToServerSocket.WriteType( m_PlayerIndex );
		m_ToServerSocket.WriteType( m_CurrentFigureArmyIndex );
		m_ToServerSocket.WriteType( m_CurrentFigureIndex );
		m_ToServerSocket.WriteType( x );
		m_ToServerSocket.WriteType( y );
		m_ToServerSocket.WriteType( z );
		m_ToServerSocket.WriteType( Rotation );
		m_ToServerSocket.WriteType( pFirstView->m_CameraPosition.x );
		m_ToServerSocket.WriteType( pFirstView->m_CameraPosition.y );
		m_ToServerSocket.WriteType( pFirstView->m_CameraPosition.z );
		m_ToServerSocket.WriteType( pFirstView->m_CameraLookAt.x );
		m_ToServerSocket.WriteType( pFirstView->m_CameraLookAt.y );
		m_ToServerSocket.WriteType( pFirstView->m_CameraLookAt.z );
		m_ToServerSocket.SendMessageW( SMI_TOSERVER_FIGUREPLACED );
		m_GameMode = GAMEMODE_FREE;
	}
	else if( m_GameMode==GAMEMODE_MOVEFIGURE )
	{
		m_ToServerSocket.CreateBuffer();
		m_ToServerSocket.WriteType( m_CurrentFigurePlayerIndex );
		m_ToServerSocket.WriteType( m_CurrentFigureArmyIndex );
		m_ToServerSocket.WriteType( m_CurrentFigureIndex );
		m_ToServerSocket.WriteType( x );
		m_ToServerSocket.WriteType( y );
		m_ToServerSocket.WriteType( z );
		m_ToServerSocket.WriteType( Rotation );
		m_ToServerSocket.WriteType( pFirstView->m_CameraPosition.x );
		m_ToServerSocket.WriteType( pFirstView->m_CameraPosition.y );
		m_ToServerSocket.WriteType( pFirstView->m_CameraPosition.z );
		m_ToServerSocket.WriteType( pFirstView->m_CameraLookAt.x );
		m_ToServerSocket.WriteType( pFirstView->m_CameraLookAt.y );
		m_ToServerSocket.WriteType( pFirstView->m_CameraLookAt.z );
		m_ToServerSocket.SendMessageW( SMI_TOSERVER_FIGUREMOVED );
		m_GameMode = GAMEMODE_FREE;
	}
}

// The user want remove a figure from map
//
void CGameDoc::OnRemoveFigureFromMap()
{
	m_GameMode = GAMEMODE_REMOVEFIGURE;

	ResetAllFigure();

	// Set all the view in remove figure mode
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
		{
			((CGame3DView*) pView)->EnterInSelectFigureMode();
			pView->SetFocus();
		}
	}
}

// To display if the user can clic on this item or not
//
//void CGameDoc::OnUpdateRemoveFigureFromMap(CCmdUI *pCmdUI)
//{
//	if( m_GameMode==GAMEMODE_FREE || m_GameMode!=GAMEMODE_REMOVEFIGURE )
//		pCmdUI->Enable();
//	else
//		pCmdUI->Enable(FALSE);
//}

// The user has choose a figure
//
void CGameDoc::SetCurrentSelectedFigure( CFigureObject* pFigure )
{
	if( pFigure==NULL )
		return;

	int aPlayerIndex, aArmyIndex, aFigureIndex;

	CGame3DView* pFirstView;

	// Get first view
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
		{
			pFirstView = (CGame3DView*) pView;
			break;
		}
	}

	for( int PlayerIndex=0; PlayerIndex<m_PlayerArray.GetCount(); PlayerIndex++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(PlayerIndex);
		for( int ArmyIndex=0; ArmyIndex<pPlayer->m_ArmyList.GetCount(); ArmyIndex++ )
		{
			CArmyCard* pArmyCard = (CArmyCard*) pPlayer->m_ArmyList.GetAt(ArmyIndex);
			for( int FigureIndex=0; FigureIndex<pArmyCard->GetFiguresList()->GetCount(); FigureIndex++ )
			{
				CFigureObject* pFigure2 = (CFigureObject*) pArmyCard->GetFiguresList()->GetAt(FigureIndex);
				if( pFigure==pFigure2 )
				{
					aPlayerIndex = PlayerIndex;
					aArmyIndex = ArmyIndex	;
					aFigureIndex = FigureIndex;
					break;
				}
			}
		}
	}

	// Unselect the figure
	pFigure->m_pTileFigure->SetSelectedState(false);

	if( m_GameMode==GAMEMODE_REMOVEFIGURE )
	{
		// Inform the server than a figure has been removed
		m_ToServerSocket.CreateBuffer();
		m_ToServerSocket.WriteType( m_PlayerIndex );
		m_ToServerSocket.WriteType( aPlayerIndex );
		m_ToServerSocket.WriteType( aArmyIndex );
		m_ToServerSocket.WriteType( aFigureIndex );
		m_ToServerSocket.WriteType( pFirstView->m_CameraPosition.x );
		m_ToServerSocket.WriteType( pFirstView->m_CameraPosition.y );
		m_ToServerSocket.WriteType( pFirstView->m_CameraPosition.z );
		m_ToServerSocket.WriteType( pFirstView->m_CameraLookAt.x );
		m_ToServerSocket.WriteType( pFirstView->m_CameraLookAt.y );
		m_ToServerSocket.WriteType( pFirstView->m_CameraLookAt.z );
		m_ToServerSocket.SendMessageW( SMI_TOSERVER_FIGUREREMOVED );
		m_GameMode = GAMEMODE_FREE;
	}
	else if( m_GameMode==GAMEMODE_MOVEFIGURE )
	{
		pFigure->m_pTileFigure->SetSelectedState( false );
		m_pCurrentFigure = pFigure;
		m_CurrentFigurePlayerIndex = aPlayerIndex;
		m_CurrentFigureArmyIndex = aArmyIndex;
		m_CurrentFigureIndex = aFigureIndex;
		// Set all the view in select position mode
		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CView* pView = GetNextView(pos);
			if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
			{
				((CGame3DView*) pView)->EnterInSelectPositionMode( pFigure->m_UseTwoHex );
				((CGame3DView*) pView)->m_DisplayPositionRotation = pFigure->m_pTileFigure->m_CurrentRotation;
				pView->SetFocus();
			}
		}
	}
	else if( m_GameMode==GAMEMODE_ATTACK_CHOOSEFIGUREATTACK )
	{
		m_GameMode=GAMEMODE_ATTACK_CHOOSEFIGUREENEMI;
		pFigure->m_pTileFigure->SetSelectedState( false );
		pFigure->m_pTileFigure->m_IsAttackFigure = true;
		pFigure->m_pTileFigure->m_DiceNumber = 0;
		m_FigureAttack.pFigure = pFigure;
		m_FigureAttack.PlayerIndex = aPlayerIndex;
		m_FigureAttack.ArmyIndex = aArmyIndex;
		m_FigureAttack.FigureIndex = aFigureIndex;

		// Clean all defense list
		while( m_FigureDefenseList.GetCount()>0 )
		{
			free( m_FigureDefenseList.GetAt(0) );
			m_FigureDefenseList.RemoveAt(0);
		}

		// Set all the view in select position mode
		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CView* pView = GetNextView(pos);
			if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
			{
				((CGame3DView*) pView)->EnterInSelectFigureMode();
				((CGame3DView*) pView)->ComputeShadow();
				((CGame3DView*) pView)->SetModified();
				((CGame3DView*) pView)->RedrawWindow();
				pView->SetFocus();
			}
		}
	}
	else if( m_GameMode==GAMEMODE_ATTACK_CHOOSEFIGUREENEMI )
	{
		pFigure->m_pTileFigure->SetSelectedState( false );
		pFigure->m_pTileFigure->m_IsAttackFigure = false;
		pFigure->m_pTileFigure->m_IsDefenseFigure = true;
		pFigure->m_pTileFigure->m_DiceNumber = 0;
		FigureInfos* pFigureInfos = (FigureInfos*) malloc( sizeof(FigureInfos) );
		m_FigureDefenseList.Add( pFigureInfos );
		pFigureInfos->pFigure = pFigure;
		pFigureInfos->PlayerIndex = aPlayerIndex;
		pFigureInfos->ArmyIndex = aArmyIndex;
		pFigureInfos->FigureIndex = aFigureIndex;
		// Set all the view in select position mode
		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CView* pView = GetNextView(pos);
			if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
			{
				((CGame3DView*) pView)->EnterInSelectFigureMode();
				((CGame3DView*) pView)->ComputeShadow();
				((CGame3DView*) pView)->SetModified();
				((CGame3DView*) pView)->RedrawWindow();
				pView->SetFocus();
			}
		}
	}
	else if( m_GameMode==GAMEMODE_DEFENSEFIGURE )
	{
		// Choose number of dice
		CLaunchDiceDlg Dlg;

		Dlg.m_i_DiceNumberToLaunch = pFigure->m_pArmyCard->m_BasicDefenseDice;

		m_GameMode = GAMEMODE_FREE;
		if( Dlg.DoModal()==IDOK )
		{
			int Result;
			int	IsValueForced=0;
			if( Dlg.m_b_ForceResult )
			{
				IsValueForced = 1;
				Result = Dlg.m_i_DiceNumberResult;
			}
			else
			{
				Result = 0;	
				for( int i=0; i<Dlg.m_i_DiceNumberToLaunch; i++ )
					Result += (rand()%6)<2?1:0;
			}

			m_ToServerSocket.CreateBuffer();
			m_ToServerSocket.WriteType( m_PlayerIndex );
			m_ToServerSocket.WriteType( aPlayerIndex );
			m_ToServerSocket.WriteType( aArmyIndex );
			m_ToServerSocket.WriteType( aFigureIndex );
			m_ToServerSocket.WriteType( (int) Dlg.m_i_DiceNumberToLaunch );
			m_ToServerSocket.WriteType( Result );
			m_ToServerSocket.WriteType( IsValueForced );
			m_ToServerSocket.WriteType( pFirstView->m_CameraPosition.x );
			m_ToServerSocket.WriteType( pFirstView->m_CameraPosition.y );
			m_ToServerSocket.WriteType( pFirstView->m_CameraPosition.z );
			m_ToServerSocket.WriteType( pFirstView->m_CameraLookAt.x );
			m_ToServerSocket.WriteType( pFirstView->m_CameraLookAt.y );
			m_ToServerSocket.WriteType( pFirstView->m_CameraLookAt.z );
			m_ToServerSocket.SendMessageW( SMI_TOSERVER_DEFENSE );
		}
	}
}

// Remove a figure for a player
//
void CGameDoc::RemoveFigureForPlayer( int PlayerIndex, int ArmyIndex, int FigureIndex, double CameraX, double CameraY, double CameraZ, double LookAtX, double LookAtY, double LookAtZ )
{
	// Get the tile
	m_pCurrentFigure = (CFigureObject*) ((CArmyCard*) ((CPlayer*) m_PlayerArray.GetAt(PlayerIndex))->m_ArmyList.GetAt(ArmyIndex))->GetFiguresList()->GetAt(FigureIndex) ;
	m_pCurrentFigureTile = m_pCurrentFigure->m_pTileFigure;

	SetModifiedFlag();
	//UpdateAll3DViews();

	// Set all the view in show remove figure mode

	if ( m_AnimationType==ANIMATIONTYPE_TURNING )
	{
		// Compute 6 animated key
		MyPoint3D PositionCamera1,PositionCamera2,PositionCamera3,PositionCamera4,PositionCamera5;
		MyPoint3D PositionLookAt1,PositionLookAt2,PositionLookAt3,PositionLookAt4,PositionLookAt5;

		PositionLookAt2.x = PositionLookAt3.x = PositionLookAt4.x = PositionLookAt5.x = m_pCurrentFigure->m_pTileFigure->m_PosX*TILE3D_WIDTH;
		PositionLookAt2.y = PositionLookAt3.y = PositionLookAt4.y = PositionLookAt5.y = -m_pCurrentFigure->m_pTileFigure->m_PosY*TILE3D_HEIGHT;
		PositionLookAt2.z = PositionLookAt3.z = PositionLookAt4.z = PositionLookAt5.z = m_pCurrentFigure->m_pTileFigure->m_PosZ*TILE3D_ZHEIGHT;

		double Distance = TILE3D_WIDTH*15;
		srand( GetTickCount() );

		PositionCamera2.x = PositionLookAt2.x + Distance;
		PositionCamera2.y = PositionLookAt2.y;
		PositionCamera2.z = PositionLookAt2.z + Distance*(.1+(((double) rand())/RAND_MAX)*.4);

		PositionCamera3.x = PositionLookAt3.x;
		PositionCamera3.y = PositionLookAt3.y + Distance;
		PositionCamera3.z = PositionLookAt3.z + Distance*(.1+(((double) rand())/RAND_MAX)*.4);

		PositionCamera4.x = PositionLookAt4.x - Distance;
		PositionCamera4.y = PositionLookAt4.y;
		PositionCamera4.z = PositionLookAt4.z + Distance*(.1+(((double) rand())/RAND_MAX)*.4);

		PositionCamera5.x = PositionLookAt2.x;
		PositionCamera5.y = PositionLookAt2.y - Distance;
		PositionCamera5.z = PositionLookAt2.z + Distance*(.1+(((double) rand())/RAND_MAX)*.4);

		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CView* pView = GetNextView(pos);
			if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
			{
				((CGame3DView*) pView)->OnVideoEraseAllPosition();

				PositionCamera1 = ((CGame3DView*) pView)->m_CameraPosition;
				PositionLookAt1 = ((CGame3DView*) pView)->m_CameraLookAt;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera2;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt2;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera3;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt3;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera4;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt4;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera5;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt5;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera1;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt1;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->MoveFigureRemovedRealtime();
			}
		}
	}
	else if ( m_AnimationType==ANIMATIONTYPE_SIMPLE )
	{
		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CView* pView = GetNextView(pos);
			if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
			{
				((CGame3DView*) pView)->OnVideoEraseAllPosition();

				MyPoint3D PositionCamera1 = ((CGame3DView*) pView)->m_CameraPosition;
				MyPoint3D PositionLookAt1 = ((CGame3DView*) pView)->m_CameraLookAt;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition.x = CameraX;
				((CGame3DView*) pView)->m_CameraPosition.y = CameraY;
				((CGame3DView*) pView)->m_CameraPosition.z = CameraZ;
				((CGame3DView*) pView)->m_CameraLookAt.x = LookAtX;
				((CGame3DView*) pView)->m_CameraLookAt.y = LookAtY;
				((CGame3DView*) pView)->m_CameraLookAt.z = LookAtZ;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera1;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt1;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->MoveFigureRemovedRealtime();
			}
		}
	}
	else if ( m_AnimationType==ANIMATIONTYPE_REPLAY )
	{
		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CView* pView = GetNextView(pos);
			if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
			{
				((CGame3DView*) pView)->OnVideoEraseAllPosition();

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition.x = CameraX;
				((CGame3DView*) pView)->m_CameraPosition.y = CameraY;
				((CGame3DView*) pView)->m_CameraPosition.z = CameraZ;
				((CGame3DView*) pView)->m_CameraLookAt.x = LookAtX;
				((CGame3DView*) pView)->m_CameraLookAt.y = LookAtY;
				((CGame3DView*) pView)->m_CameraLookAt.z = LookAtZ;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();
				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->MoveFigureRemovedRealtime();
			}
		}
	}
}

// Get the figure at a particular pos
//
CFigureObject* CGameDoc::GetFigureAtPos( int PositionX, int PositionY, int PositionZ )
{
	for( int PlayerIndex=0; PlayerIndex<m_PlayerArray.GetCount(); PlayerIndex++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(PlayerIndex);
		for( int ArmyIndex=0; ArmyIndex<pPlayer->m_ArmyList.GetCount(); ArmyIndex++ )
		{
			CArmyCard* pArmyCard = (CArmyCard*) pPlayer->m_ArmyList.GetAt(ArmyIndex);
			for( int FigureIndex=0; FigureIndex<pArmyCard->GetFiguresList()->GetCount(); FigureIndex++ )
			{
				CFigureObject* pFigure = (CFigureObject*) pArmyCard->GetFiguresList()->GetAt(FigureIndex);
				if( pFigure->m_IsPlacedOnMap && pFigure->m_pTileFigure->m_PosX==PositionX && pFigure->m_pTileFigure->m_PosY==PositionY && pFigure->m_pTileFigure->m_PosZ==PositionZ )
					return pFigure;
			}
		}
	}
	return NULL;
}

// Remove a figure from the map
//
void CGameDoc::RemoveFigureFromMap( CFigureObject* pFigure )
{
	pFigure->m_IsPlacedOnMap = false;
	RemoveTile( pFigure->m_pTileFigure );
}

// Remove a tile to the list
//
void CGameDoc::RemoveTile( CTile* pTile )
{
	for( int i=0; i<m_TileList.GetCount(); i++ )
		if( m_TileList.GetAt(i)==pTile )
		{
			m_TileList.RemoveAt(i);
			return;
		}
}

// The user want move a figure
//
void CGameDoc::OnMoveFigure()
{
	m_GameMode = GAMEMODE_MOVEFIGURE;

	ResetAllFigure();

	// Set all the view in remove figure mode
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
		{
			((CGame3DView*) pView)->EnterInSelectFigureMode();
			pView->SetFocus();
		}
	}
}

// The user want choose figure to launch attack
//
void CGameDoc::OnAttackChooseFigure()
{
	m_GameMode = GAMEMODE_ATTACK_CHOOSEFIGUREATTACK;

	ResetAllFigure();

	// Set all the view in remove figure mode
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
		{
			((CGame3DView*) pView)->EnterInSelectFigureMode();
			pView->SetFocus();
		}
	}
}

// The user has terminate to choose attack and defense and want get dice random
//
void CGameDoc::OnAttackDice()
{
	// Choose number of dice
	CLaunchDiceDlg Dlg;

	Dlg.m_i_DiceNumberToLaunch = m_FigureAttack.pFigure->m_pArmyCard->m_BasicAttackDice;

	if( Dlg.DoModal()==IDOK )
	{
		int DiceNumberToLaunch = Dlg.m_i_DiceNumberToLaunch;
		int Result;
		int	IsValueForced=0;

		CGame3DView* pFirstView;

		// Get first view
		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CView* pView = GetNextView(pos);
			if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
			{
				pFirstView = (CGame3DView*) pView;
				break;
			}
		}

		if( Dlg.m_b_ForceResult )
		{
			IsValueForced = 1;
			Result = Dlg.m_i_DiceNumberResult;
		}
		else
		{
			Result = 0;	
			for( int i=0; i<Dlg.m_i_DiceNumberToLaunch; i++ )
				Result += (rand()%6)<3?1:0;
		}

		m_ToServerSocket.CreateBuffer();
		m_ToServerSocket.WriteType( m_PlayerIndex );
		m_ToServerSocket.WriteType( m_FigureAttack.PlayerIndex );
		m_ToServerSocket.WriteType( m_FigureAttack.ArmyIndex );
		m_ToServerSocket.WriteType( m_FigureAttack.FigureIndex );
		int NbEnnemi = m_FigureDefenseList.GetCount();
		m_ToServerSocket.WriteType( NbEnnemi );
		for( int i=0; i<NbEnnemi; i++ )
		{
			FigureInfos* pFigureInfo = (FigureInfos*) m_FigureDefenseList.GetAt(i);
			m_ToServerSocket.WriteType( pFigureInfo->PlayerIndex );
			m_ToServerSocket.WriteType( pFigureInfo->ArmyIndex );
			m_ToServerSocket.WriteType( pFigureInfo->FigureIndex );
		}
		m_ToServerSocket.WriteType( DiceNumberToLaunch );
		m_ToServerSocket.WriteType( Result );
		m_ToServerSocket.WriteType( IsValueForced );
		m_ToServerSocket.WriteType( pFirstView->m_CameraPosition.x );
		m_ToServerSocket.WriteType( pFirstView->m_CameraPosition.y );
		m_ToServerSocket.WriteType( pFirstView->m_CameraPosition.z );
		m_ToServerSocket.WriteType( pFirstView->m_CameraLookAt.x );
		m_ToServerSocket.WriteType( pFirstView->m_CameraLookAt.y );
		m_ToServerSocket.WriteType( pFirstView->m_CameraLookAt.z );
		m_ToServerSocket.SendMessageW( SMI_TOSERVER_ATTACK );
		m_GameMode = GAMEMODE_FREE;
	}
}

// An attack
//
void CGameDoc::Attack( int PlayerIndex, int AttackPlayerIndex, int AttackArmyIndex, int AttackFigureIndex, int NbEnnemi, CPtrArray* pEnnemiList, int DiceLaunch, int DiceResult, int IsValueForced, double CameraX, double CameraY, double CameraZ, double LookAtX, double LookAtY, double LookAtZ )
{
	// Remove attack and defense of all the figure
	for( int PlayerIndex=0; PlayerIndex<m_PlayerArray.GetCount(); PlayerIndex++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(PlayerIndex);
		for( int ArmyIndex=0; ArmyIndex<pPlayer->m_ArmyList.GetCount(); ArmyIndex++ )
		{
			CArmyCard* pArmyCard = (CArmyCard*) pPlayer->m_ArmyList.GetAt(ArmyIndex);
			for( int FigureIndex=0; FigureIndex<pArmyCard->GetFiguresList()->GetCount(); FigureIndex++ )
			{
				CFigureObject* pFigure = (CFigureObject*) pArmyCard->GetFiguresList()->GetAt(FigureIndex);
				pFigure->m_pTileFigure->m_IsAttackFigure = false;
				pFigure->m_pTileFigure->m_IsDefenseFigure = false;
			}
		}
	}

	// Get the tile
	m_pCurrentFigure = (CFigureObject*) ((CArmyCard*) ((CPlayer*) m_PlayerArray.GetAt(AttackPlayerIndex))->m_ArmyList.GetAt(AttackArmyIndex))->GetFiguresList()->GetAt(AttackFigureIndex) ;
	m_pCurrentFigureAttack = m_pCurrentFigure;
	m_pCurrentFigureTile = m_pCurrentFigure->m_pTileFigure;
	m_pCurrentFigureTile->m_IsAttackFigure = true;
	m_pCurrentFigureTile->m_DiceNumber = DiceResult;

	for( int i=0; i<NbEnnemi; i++ )
	{
		m_FigureDefenseList.Add( pEnnemiList->GetAt(i) );
		FigureInfos* pFigureInfos = (FigureInfos*) pEnnemiList->GetAt(i);
		pFigureInfos->pFigure = (CFigureObject*) ((CArmyCard*) ((CPlayer*) m_PlayerArray.GetAt(pFigureInfos->PlayerIndex))->m_ArmyList.GetAt(pFigureInfos->ArmyIndex))->GetFiguresList()->GetAt(pFigureInfos->FigureIndex) ;	
		pFigureInfos->pFigure->m_pTileFigure->m_IsDefenseFigure = true;
		pFigureInfos->pFigure->m_pTileFigure->m_DiceNumber = 0;
	}

	SetModifiedFlag();
	//UpdateAll3DViews();

	if ( m_AnimationType==ANIMATIONTYPE_TURNING )
	{
		// Compute 6 animated key
		MyPoint3D PositionCamera1,PositionCamera2,PositionCamera3,PositionCamera4,PositionCamera5;
		MyPoint3D PositionLookAt1,PositionLookAt2,PositionLookAt3,PositionLookAt4,PositionLookAt5;

		PositionLookAt2.x = PositionLookAt3.x = PositionLookAt4.x = PositionLookAt5.x = m_pCurrentFigure->m_pTileFigure->m_PosX*TILE3D_WIDTH;
		PositionLookAt2.y = PositionLookAt3.y = PositionLookAt4.y = PositionLookAt5.y = -m_pCurrentFigure->m_pTileFigure->m_PosY*TILE3D_HEIGHT;
		PositionLookAt2.z = PositionLookAt3.z = PositionLookAt4.z = PositionLookAt5.z = m_pCurrentFigure->m_pTileFigure->m_PosZ*TILE3D_ZHEIGHT;

		double Distance = TILE3D_WIDTH*15;
		srand( GetTickCount() );

		PositionCamera2.x = PositionLookAt2.x + Distance;
		PositionCamera2.y = PositionLookAt2.y;
		PositionCamera2.z = PositionLookAt2.z + Distance*(.1+(((double) rand())/RAND_MAX)*.4);

		PositionCamera3.x = PositionLookAt3.x;
		PositionCamera3.y = PositionLookAt3.y + Distance;
		PositionCamera3.z = PositionLookAt3.z + Distance*(.1+(((double) rand())/RAND_MAX)*.4);

		PositionCamera4.x = PositionLookAt4.x - Distance;
		PositionCamera4.y = PositionLookAt4.y;
		PositionCamera4.z = PositionLookAt4.z + Distance*(.1+(((double) rand())/RAND_MAX)*.4);

		PositionCamera5.x = PositionLookAt2.x;
		PositionCamera5.y = PositionLookAt2.y - Distance;
		PositionCamera5.z = PositionLookAt2.z + Distance*(.1+(((double) rand())/RAND_MAX)*.4);

		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CView* pView = GetNextView(pos);
			if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
			{
				((CGame3DView*) pView)->OnVideoEraseAllPosition();

				PositionCamera1 = ((CGame3DView*) pView)->m_CameraPosition;
				PositionLookAt1 = ((CGame3DView*) pView)->m_CameraLookAt;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera2;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt2;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera3;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt3;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera4;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt4;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera5;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt5;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera1;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt1;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->AttackRealtime();
			}
		}
	}
	else if ( m_AnimationType==ANIMATIONTYPE_SIMPLE )
	{
		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CView* pView = GetNextView(pos);
			if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
			{
				((CGame3DView*) pView)->OnVideoEraseAllPosition();

				MyPoint3D PositionCamera1 = ((CGame3DView*) pView)->m_CameraPosition;
				MyPoint3D PositionLookAt1 = ((CGame3DView*) pView)->m_CameraLookAt;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition.x = CameraX;
				((CGame3DView*) pView)->m_CameraPosition.y = CameraY;
				((CGame3DView*) pView)->m_CameraPosition.z = CameraZ;
				((CGame3DView*) pView)->m_CameraLookAt.x = LookAtX;
				((CGame3DView*) pView)->m_CameraLookAt.y = LookAtY;
				((CGame3DView*) pView)->m_CameraLookAt.z = LookAtZ;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera1;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt1;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->AttackRealtime();
			}
		}
	}
	else if ( m_AnimationType==ANIMATIONTYPE_REPLAY )
	{
		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CView* pView = GetNextView(pos);
			if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
			{
				((CGame3DView*) pView)->OnVideoEraseAllPosition();

				MyPoint3D PositionCamera1 = ((CGame3DView*) pView)->m_CameraPosition;
				MyPoint3D PositionLookAt1 = ((CGame3DView*) pView)->m_CameraLookAt;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition.x = CameraX;
				((CGame3DView*) pView)->m_CameraPosition.y = CameraY;
				((CGame3DView*) pView)->m_CameraPosition.z = CameraZ;
				((CGame3DView*) pView)->m_CameraLookAt.x = LookAtX;
				((CGame3DView*) pView)->m_CameraLookAt.y = LookAtY;
				((CGame3DView*) pView)->m_CameraLookAt.z = LookAtZ;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();
				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->AttackRealtime();
			}
		}
	}
}

// A defense
//
void CGameDoc::Defense( int PlayerIndex, int DefensePlayerIndex, int DefenseArmyIndex, int DefenseFigureIndex, int DiceLaunch, int DiceResult, int IsValueForced, double CameraX, double CameraY, double CameraZ, double LookAtX, double LookAtY, double LookAtZ )
{
	// Get the tile
	m_pCurrentFigure = (CFigureObject*) ((CArmyCard*) ((CPlayer*) m_PlayerArray.GetAt(DefensePlayerIndex))->m_ArmyList.GetAt(DefenseArmyIndex))->GetFiguresList()->GetAt(DefenseFigureIndex);
	m_pCurrentFigureDefense = m_pCurrentFigure;
	m_pCurrentFigureTile = m_pCurrentFigure->m_pTileFigure;
	m_pCurrentFigureTile->m_IsDefenseFigure = true;
	m_pCurrentFigureTile->m_DiceNumber = DiceResult;
	m_pCurrentFigureDefense->m_pTileFigure->m_AttackTimeOnDice = 1.0/min(DiceResult,m_pCurrentFigureAttack->m_pTileFigure->m_DiceNumber)/2.0;
	m_pCurrentFigureAttack->m_pTileFigure->m_AttackTimeOnDice = m_pCurrentFigureDefense->m_pTileFigure->m_AttackTimeOnDice;

	SetModifiedFlag();
	//UpdateAll3DViews();

	if ( m_AnimationType==ANIMATIONTYPE_TURNING )
	{
		// Compute 6 animated key
		MyPoint3D PositionCamera1,PositionCamera2,PositionCamera3,PositionCamera4,PositionCamera5;
		MyPoint3D PositionLookAt1,PositionLookAt2,PositionLookAt3,PositionLookAt4,PositionLookAt5;

		PositionLookAt2.x = PositionLookAt3.x = PositionLookAt4.x = PositionLookAt5.x = m_pCurrentFigure->m_pTileFigure->m_PosX*TILE3D_WIDTH;
		PositionLookAt2.y = PositionLookAt3.y = PositionLookAt4.y = PositionLookAt5.y = -m_pCurrentFigure->m_pTileFigure->m_PosY*TILE3D_HEIGHT;
		PositionLookAt2.z = PositionLookAt3.z = PositionLookAt4.z = PositionLookAt5.z = m_pCurrentFigure->m_pTileFigure->m_PosZ*TILE3D_ZHEIGHT;

		double Distance = TILE3D_WIDTH*15;
		srand( GetTickCount() );

		PositionCamera2.x = PositionLookAt2.x + Distance;
		PositionCamera2.y = PositionLookAt2.y;
		PositionCamera2.z = PositionLookAt2.z + Distance*(.1+(((double) rand())/RAND_MAX)*.4);

		PositionCamera3.x = PositionLookAt3.x;
		PositionCamera3.y = PositionLookAt3.y + Distance;
		PositionCamera3.z = PositionLookAt3.z + Distance*(.1+(((double) rand())/RAND_MAX)*.4);

		PositionCamera4.x = PositionLookAt4.x - Distance;
		PositionCamera4.y = PositionLookAt4.y;
		PositionCamera4.z = PositionLookAt4.z + Distance*(.1+(((double) rand())/RAND_MAX)*.4);

		PositionCamera5.x = PositionLookAt2.x;
		PositionCamera5.y = PositionLookAt2.y - Distance;
		PositionCamera5.z = PositionLookAt2.z + Distance*(.1+(((double) rand())/RAND_MAX)*.4);

		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CView* pView = GetNextView(pos);
			if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
			{
				((CGame3DView*) pView)->OnVideoEraseAllPosition();

				PositionCamera1 = ((CGame3DView*) pView)->m_CameraPosition;
				PositionLookAt1 = ((CGame3DView*) pView)->m_CameraLookAt;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera2;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt2;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera3;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt3;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera4;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt4;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera5;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt5;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera1;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt1;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->DefenseRealtime();
			}
		}
	}
	else if ( m_AnimationType==ANIMATIONTYPE_SIMPLE )
	{
		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CView* pView = GetNextView(pos);
			if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
			{
				((CGame3DView*) pView)->OnVideoEraseAllPosition();

				MyPoint3D PositionCamera1 = ((CGame3DView*) pView)->m_CameraPosition;
				MyPoint3D PositionLookAt1 = ((CGame3DView*) pView)->m_CameraLookAt;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition.x = CameraX;
				((CGame3DView*) pView)->m_CameraPosition.y = CameraY;
				((CGame3DView*) pView)->m_CameraPosition.z = CameraZ;
				((CGame3DView*) pView)->m_CameraLookAt.x = LookAtX;
				((CGame3DView*) pView)->m_CameraLookAt.y = LookAtY;
				((CGame3DView*) pView)->m_CameraLookAt.z = LookAtZ;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition = PositionCamera1;
				((CGame3DView*) pView)->m_CameraLookAt = PositionLookAt1;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->DefenseRealtime();
			}
		}
	}
	else if ( m_AnimationType==ANIMATIONTYPE_REPLAY )
	{
		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CView* pView = GetNextView(pos);
			if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
			{
				((CGame3DView*) pView)->OnVideoEraseAllPosition();

				MyPoint3D PositionCamera1 = ((CGame3DView*) pView)->m_CameraPosition;
				MyPoint3D PositionLookAt1 = ((CGame3DView*) pView)->m_CameraLookAt;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->m_CameraPosition.x = CameraX;
				((CGame3DView*) pView)->m_CameraPosition.y = CameraY;
				((CGame3DView*) pView)->m_CameraPosition.z = CameraZ;
				((CGame3DView*) pView)->m_CameraLookAt.x = LookAtX;
				((CGame3DView*) pView)->m_CameraLookAt.y = LookAtY;
				((CGame3DView*) pView)->m_CameraLookAt.z = LookAtZ;

				((CGame3DView*) pView)->OnVideoAddCurrentPosition();
				((CGame3DView*) pView)->OnVideoAddCurrentPosition();

				((CGame3DView*) pView)->DefenseRealtime();
			}
		}
	}
}

// The user want launch defense dice
//
void CGameDoc::OnDefenseDice()
{
	m_GameMode = GAMEMODE_DEFENSEFIGURE;

	// Set all the view in remove figure mode
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
		{
			((CGame3DView*) pView)->EnterInSelectFigureMode();
			pView->SetFocus();
		}
	}
}

// Remove all the marquer
//
void CGameDoc::ResetAllMarquer()
{
	for( int PlayerIndex=0; PlayerIndex<m_PlayerArray.GetCount(); PlayerIndex++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(PlayerIndex);
		for( int ArmyIndex=0; ArmyIndex<pPlayer->m_ArmyList.GetCount(); ArmyIndex++ )
		{
			CArmyCard* pArmyCard = (CArmyCard*) pPlayer->m_ArmyList.GetAt(ArmyIndex);
			pArmyCard->ResetMarquer();
		}
	}

	((CMainFrame*) theApp.m_pMainWnd)->m_wndGamePlayerBar.m_pListCtrlPlayer->RedrawWindow();
}

// Set all the figures to normal state
//
void CGameDoc::ResetAllFigure()
{
	for( int PlayerIndex=0; PlayerIndex<m_PlayerArray.GetCount(); PlayerIndex++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(PlayerIndex);
		for( int ArmyIndex=0; ArmyIndex<pPlayer->m_ArmyList.GetCount(); ArmyIndex++ )
		{
			CArmyCard* pArmyCard = (CArmyCard*) pPlayer->m_ArmyList.GetAt(ArmyIndex);
			for( int FigureIndex=0; FigureIndex<pArmyCard->GetFiguresList()->GetCount(); FigureIndex++ )
			{
				CFigureObject* pFigure = (CFigureObject*) pArmyCard->GetFiguresList()->GetAt(FigureIndex);
				pFigure->m_pTileFigure->m_IsAttackFigure = false;
				pFigure->m_pTileFigure->m_IsDefenseFigure = false;
				pFigure->m_pTileFigure->m_CreationTime = -1;
				pFigure->m_pTileFigure->m_IsSelected = false;
				pFigure->m_pTileFigure->m_ToDisplay = true;
				pFigure->m_pTileFigure->m_AttackTime = -1;
			}
		}
	}

	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
		{
			((CGame3DView*) pView)->ComputeShadow();
			((CGame3DView*) pView)->SetModified();
			((CGame3DView*) pView)->RedrawWindow();
		}
	}
}

// Set all the figures to normal state but not displayed
//
void CGameDoc::ResetAllFigureToBegining()
{
	for( int PlayerIndex=0; PlayerIndex<m_PlayerArray.GetCount(); PlayerIndex++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(PlayerIndex);
		for( int ArmyIndex=0; ArmyIndex<pPlayer->m_ArmyList.GetCount(); ArmyIndex++ )
		{
			CArmyCard* pArmyCard = (CArmyCard*) pPlayer->m_ArmyList.GetAt(ArmyIndex);
			pArmyCard->m_CurrentLifePoint = pArmyCard->m_ExpertTotalLifePoint;
			for( int FigureIndex=0; FigureIndex<pArmyCard->GetFiguresList()->GetCount(); FigureIndex++ )
			{
				CFigureObject* pFigure = (CFigureObject*) pArmyCard->GetFiguresList()->GetAt(FigureIndex);
				pFigure->m_pTileFigure->m_IsAttackFigure = false;
				pFigure->m_pTileFigure->m_IsDefenseFigure = false;
				pFigure->m_pTileFigure->m_CreationTime = -1;
				pFigure->m_pTileFigure->m_IsSelected = false;
				pFigure->m_pTileFigure->m_ToDisplay = false;
				pFigure->m_pTileFigure->m_AttackTime = -1;
			}
		}
	}
}

// The user inform that this is next turn
//
void CGameDoc::OnNextTurn()
{
	m_ToServerSocket.CreateBuffer();
	m_ToServerSocket.WriteType( m_PlayerIndex );
	m_ToServerSocket.SendMessageW( SMI_TOSERVER_NEXT_TURN );
	m_GameMode = GAMEMODE_FREE;
}

// Receive a message that this is next turn
//
void CGameDoc::NextTurn( int PlayerIndex )
{
	ResetAllFigure();
	//ResetAllMarquer();
	((CMainFrame*) theApp.m_pMainWnd)->m_wndGamePlayerBar.m_pListCtrlPlayer->RedrawWindow();
	m_GameMode = GAMEMODE_FREE;
}

// replay the game
//
void CGameDoc::OnReplayGame()
{
	ResetAllFigureToBegining();
	ResetAllArmyCard();
	ResetAllChat();
	ResetAllAction();
	m_OldAnimationType = m_AnimationType;
	m_AnimationType = ANIMATIONTYPE_REPLAY;
	m_ToServerSocket.Replay( false );
}

// Reset all the army card
//
void CGameDoc::ResetAllArmyCard()
{
	// If this marquer already exist then remove it
	for( int aPlayerIndex=0; aPlayerIndex<m_PlayerArray.GetCount(); aPlayerIndex++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(aPlayerIndex);
		for( int ArmyIndex=0; ArmyIndex<pPlayer->m_ArmyList.GetCount(); ArmyIndex++ )
		{
			CArmyCard* pArmyCard = (CArmyCard*) pPlayer->m_ArmyList.GetAt(ArmyIndex);
			pArmyCard->ResetMarquer();
			if( theApp.m_GameType==GAMETYPE_EXPERT )
				pArmyCard->m_CurrentLifePoint=pArmyCard->m_ExpertTotalLifePoint;
		}
	}
}

// Reset all the chat
//
void CGameDoc::ResetAllChat()
{
	((CMainFrame*) theApp.m_pMainWnd)->m_wndGameChatBar.ResetMessage();
}

// Reset all the action
//
void CGameDoc::ResetAllAction()
{
	((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.ResetAction();
}

// Save the game replay as a picture files list
//
void CGameDoc::OnReplayToFile()
{
	CFileDialog fdlg( false, NULL, _T("Replay"), OFN_PATHMUSTEXIST | OFN_NOTESTFILECREATE );

	if( fdlg.DoModal()==IDOK )
	{
		ResetAllFigureToBegining();
		m_OldAnimationType = m_AnimationType;
		m_AnimationType = ANIMATIONTYPE_REPLAY;
		m_ToServerSocket.Replay( true, fdlg.GetPathName() );
	}
}

// Set animation as simple animation
//
void CGameDoc::OnOutilsAnimationssimples()
{
	m_AnimationType=ANIMATIONTYPE_SIMPLE;
}

// Set the check box
//
void CGameDoc::OnUpdateOutilsAnimationssimples(CCmdUI *pCmdUI)
{
	if( m_AnimationType==ANIMATIONTYPE_SIMPLE )
		pCmdUI->SetCheck();
	else
		pCmdUI->SetCheck( 0 );
}

// Set animation as turning around animation
//
void CGameDoc::OnOutilsAnimationstournante()
{
	m_AnimationType=ANIMATIONTYPE_TURNING;
}

// Set the check box
//
void CGameDoc::OnUpdateOutilsAnimationstournante(CCmdUI *pCmdUI)
{
	if( m_AnimationType==ANIMATIONTYPE_TURNING )
		pCmdUI->SetCheck();
	else
		pCmdUI->SetCheck( 0 );
}

// Set the game type
//
void CGameDoc::SetGameType( int GameType )
{
	theApp.m_GameType = GameType;
}

// Incremente life of an army
//
void CGameDoc::OnIncrementLife( int PlayerIndex, int ArmyIndex )
{
	m_ToServerSocket.CreateBuffer();
	m_ToServerSocket.WriteType( m_PlayerIndex );
	m_ToServerSocket.WriteType( PlayerIndex );
	m_ToServerSocket.WriteType( ArmyIndex );
	m_ToServerSocket.SendMessageW( SMI_TOSERVER_INCREMENT_LIFE );
}

// Decremente life of an army
//
void CGameDoc::OnDecrementLife( int PlayerIndex, int ArmyIndex )
{
	m_ToServerSocket.CreateBuffer();
	m_ToServerSocket.WriteType( m_PlayerIndex );
	m_ToServerSocket.WriteType( PlayerIndex );
	m_ToServerSocket.WriteType( ArmyIndex );
	m_ToServerSocket.SendMessageW( SMI_TOSERVER_DECREMENT_LIFE );
}

// Receive message to increment life of an army
//
void CGameDoc::IncrementLife( int IncrementPlayerIndex, int IncrementArmyIndex )
{
	CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(IncrementPlayerIndex);
	CArmyCard* pArmyCard = (CArmyCard*) pPlayer->m_ArmyList.GetAt(IncrementArmyIndex);

	pArmyCard->m_CurrentLifePoint++;

	((CMainFrame*) theApp.m_pMainWnd)->m_wndGamePlayerBar.m_pListCtrlPlayer->RedrawWindow();
}

// Receive message to decrement life of an army
//
void CGameDoc::DecrementLife( int DecrementPlayerIndex, int DecrementArmyIndex )
{
	CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(DecrementPlayerIndex);
	CArmyCard* pArmyCard = (CArmyCard*) pPlayer->m_ArmyList.GetAt(DecrementArmyIndex);

	pArmyCard->m_CurrentLifePoint--;

	((CMainFrame*) theApp.m_pMainWnd)->m_wndGamePlayerBar.m_pListCtrlPlayer->RedrawWindow();
}

// Add a predicted marquer
//
void CGameDoc::OnAddPredictedMarquer( int PlayerIndex, int ArmyIndex, int PredictedMarquer )
{
	m_ToServerSocket.CreateBuffer();
	m_ToServerSocket.WriteType( m_PlayerIndex );
	m_ToServerSocket.WriteType( PlayerIndex );
	m_ToServerSocket.WriteType( ArmyIndex );
	m_ToServerSocket.WriteType( PredictedMarquer );
	m_ToServerSocket.SendMessageW( SMI_TOSERVER_ADD_PREDICTED_MARQUER );
}

// Remove marquer
//
void CGameDoc::OnRemoveMarquer( int PlayerIndex, int ArmyIndex )
{
	m_ToServerSocket.CreateBuffer();
	m_ToServerSocket.WriteType( m_PlayerIndex );
	m_ToServerSocket.SendMessageW( SMI_TOSERVER_REMOVE_MARQUER );
}

// Remove marquer
//
void CGameDoc::RemoveMarquer( int PlayerIndex )
{
	CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(PlayerIndex);
	for( int ArmyIndex=0; ArmyIndex<pPlayer->m_ArmyList.GetCount(); ArmyIndex++ )
	{
		CArmyCard* pArmyCard = (CArmyCard*) pPlayer->m_ArmyList.GetAt(ArmyIndex);
		pArmyCard->ResetMarquer();
	}

	((CMainFrame*) theApp.m_pMainWnd)->m_wndGamePlayerBar.m_pListCtrlPlayer->RedrawWindow();
}

// Receive message to add a predicted marquer
//
void CGameDoc::AddPredictedMarquer( int PlayerIndex, int ArmyIndex, int PredictedMarquer )
{
	CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(PlayerIndex);
	CArmyCard* pArmyCard = (CArmyCard*) pPlayer->m_ArmyList.GetAt(ArmyIndex);

	// If this marquer already exist for this player then remove it
	for( int ArmyIndex=0; ArmyIndex<pPlayer->m_ArmyList.GetCount(); ArmyIndex++ )
	{
		CArmyCard* pArmyCard = (CArmyCard*) pPlayer->m_ArmyList.GetAt(ArmyIndex);
		pArmyCard->RemoveMarquer( PredictedMarquer );
	}

	pArmyCard->AddMarquer( PredictedMarquer );

	((CMainFrame*) theApp.m_pMainWnd)->m_wndGamePlayerBar.m_pListCtrlPlayer->RedrawWindow();
}

// Show a predicted marquer
//
void CGameDoc::OnShowPredictedMarquer( int PlayerIndex, int ArmyIndex )
{
	// Compute the next marquer
	CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(PlayerIndex);
	CArmyCard* pArmyCard = (CArmyCard*) pPlayer->m_ArmyList.GetAt(ArmyIndex);
	int PredictedMarquer = pArmyCard->GetNextHidenMarquer();

	if( PredictedMarquer>=0 )
	{
		m_ToServerSocket.CreateBuffer();
		m_ToServerSocket.WriteType( m_PlayerIndex );
		m_ToServerSocket.WriteType( PlayerIndex );
		m_ToServerSocket.WriteType( ArmyIndex );
		m_ToServerSocket.WriteType( PredictedMarquer );
		m_ToServerSocket.SendMessageW( SMI_TOSERVER_SHOW_PREDICTED_MARQUER );
	}
}

// Receive message to show a predicted marquer
//
void CGameDoc::ShowPredictedMarquer( int PlayerIndex, int ArmyIndex, int PredictedMarquer )
{
	CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(PlayerIndex);
	CArmyCard* pArmyCard = (CArmyCard*) pPlayer->m_ArmyList.GetAt(ArmyIndex);

	pArmyCard->ShowMarquer( PredictedMarquer );

	((CMainFrame*) theApp.m_pMainWnd)->m_wndGamePlayerBar.m_pListCtrlPlayer->RedrawWindow();
}

// User want launch die 20 faces
//
void CGameDoc::OnDie20Faces()
{
	int result = (rand()%20)+1;

	m_ToServerSocket.CreateBuffer();
	m_ToServerSocket.WriteType( m_PlayerIndex );
	m_ToServerSocket.WriteType( result );
	m_ToServerSocket.SendMessageW( SMI_TOSERVER_DIE_20_FACES );
}

