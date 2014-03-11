// HeroscapeEditor.cpp : Définit les comportements de classe pour l'application.
//

#include "StdAfx.h"

#include "ChildFrm.h"
#include "Game3DView.h"
#include "GameDoc.h"
#include "HeroscapeEditor.h"
#include "HeroscapeEditorDoc.h"
#include "HeroscapeEditorView.h"
#include "HeroscapeEditor3DView.h"
#include "MainFrm.h"
#include "MaterialEdit.h"
#include "PreferenceDlg.h"
#include "SocketMessageId.h"
#include "TileGrass24.h"
#include "TilePerso.h"
#include "TilePersoDlg.h"

// CHeroscapeEditorApp

BEGIN_MESSAGE_MAP(CHeroscapeEditorApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CHeroscapeEditorApp::OnAppAbout)
	// Commandes de fichier standard
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// Commande standard de configuration de l'impression
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_CONFIGURATION_MAT_DISPO, &CHeroscapeEditorApp::OnConfigurationMatDispo)
	ON_COMMAND(ID_CONFIGURATION_PREFERENCY, &CHeroscapeEditorApp::OnConfigurationPreferency)
	ON_COMMAND(ID_AIDE_AIDEGLOBALE, &CHeroscapeEditorApp::OnGlobalHelp)
	ON_COMMAND(ID_CONFIGURATION_TILEPERSO, &CHeroscapeEditorApp::OnConfigurationTileperso)
	ON_COMMAND(ID_PLAY_JOINGAME, &CHeroscapeEditorApp::OnPlayJoingame)
END_MESSAGE_MAP()


// The constructor
//
CHeroscapeEditorApp::CHeroscapeEditorApp()
{
	EnableHtmlHelp();
	m_GlExtensionAlreadyInit = false;
	m_TextureType = 0;
	m_AnaglyphiqueMode = 0;
	m_pGameDoc = NULL;
	m_pGameDocServer = NULL;
	//m_pJoinGameDlg = NULL;
	m_pJoinGameListDlg = NULL;
	m_pWaitingConnection = NULL;
	m_pGame3DView = NULL;
}


// Seul et unique objet CHeroscapeEditorApp
CHeroscapeEditorApp theApp;


// initialisation of CHeroscapeEditorApp
//
BOOL CHeroscapeEditorApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	// InitCommonControlsEx() est requis sur Windows XP si le manifeste de l'application
	// spécifie l'utilisation de ComCtl32.dll version 6 ou ultérieure pour activer les
	// styles visuels.  Dans le cas contraire, la création de fenêtres échouera.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// À définir pour inclure toutes les classes de contrôles communs à utiliser
	// dans votre application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	
	AfxInitRichEdit2();

	CWinApp::InitInstance();

	srand( (unsigned)time( NULL ) );

	// Memo the current dir
	CString Str = m_pszHelpFilePath;
	m_CurrentDir = Str.Left( Str.ReverseFind('\\') );
	//m_pszHelpFilePath = m_CurrentDir+_T("Virtualscape.chm");
 
	WSADATA wsad;
	if (!AfxSocketInit(&wsad))
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}
	TRACE( _T("Taille wsad : %d\n"), wsad.iMaxSockets );

	// Initialiser les bibliothèques OLE
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Initialisation standard
	// Si vous n'utilisez pas ces fonctionnalités et que vous souhaitez réduire la taille
	// de votre exécutable final, vous devez supprimer ci-dessous
	// les routines d'initialisation spécifiques dont vous n'avez pas besoin.
	// Changez la clé de Registre sous laquelle nos paramètres sont enregistrés
	// TODO : modifiez cette chaîne avec des informations appropriées,
	// telles que le nom de votre société ou organisation

	// Save in the local file .ini
	free((void*)m_pszProfileName);
	CString Path = m_pszHelpFilePath;
	Path = Path.Left( Path.ReverseFind('\\')+1 );
	Path += _T("VirtualScape.ini");
	m_pszProfileName=_tcsdup(Path);

	HMODULE hLanguageDll = LoadLibrary(_T("Langue.dll"));
	if (hLanguageDll)
		AfxSetResourceHandle(hLanguageDll);

	// Run only on one thread for problem with multi proc
	// SetThreadAffinityMask( m_hThread, 1 );

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Inscrire les modèles de document de l'application. Ces modèles
	//  lient les documents, fenêtres frame et vues entre eux
	m_pDocTemplateView2D = new CMultiDocTemplate(IDR_VIRTUALSCAPE2D,
		RUNTIME_CLASS(CHeroscapeEditorDoc),
		RUNTIME_CLASS(CChildFrame), // frame enfant MDI personnalisé
		RUNTIME_CLASS(CHeroscapeEditorView));
	if (!m_pDocTemplateView2D)
		return FALSE;
	AddDocTemplate(m_pDocTemplateView2D);

	m_pDocTemplateView3D = new CMultiDocTemplate(IDR_VIRTUALSCAPE3D,
		RUNTIME_CLASS(CHeroscapeEditorDoc),
		RUNTIME_CLASS(CChildFrame), // frame enfant MDI personnalisé
		RUNTIME_CLASS(CHeroscapeEditor3DView));
	if (!m_pDocTemplateView3D)
		return FALSE;
	//AddDocTemplate(m_pDocTemplateView3D);

	m_pDocTemplateGame3D = new CMultiDocTemplate(IDR_VIRTUALSCAPEGAME3D,
		RUNTIME_CLASS(CGameDoc),
		RUNTIME_CLASS(CChildFrame), // frame enfant MDI personnalisé
		RUNTIME_CLASS(CGame3DView));
	if (!m_pDocTemplateGame3D)
		return FALSE;
	//AddDocTemplate(m_pDocTemplateGame3D);

	// crée la fenêtre frame MDI principale
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// appelle DragAcceptFiles uniquement s'il y a un suffixe
	//  Dans une application MDI, cet appel doit avoir lieu juste après la définition de m_pMainWnd
	// Activer les ouvertures via glisser-déplacer
	m_pMainWnd->DragAcceptFiles();

	// Activer les ouvertures d'exécution DDE
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Analyser la ligne de commande pour les commandes shell standard, DDE, ouverture de fichiers
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// Commandes de dispatch spécifiées sur la ligne de commande. Retournent FALSE si
	// l'application a été lancée avec /RegServer, /Register, /Unregserver ou /Unregister.
	//if (!ProcessShellCommand(cmdInfo))
	//	return FALSE;

	// Not display shadow now
	m_DisplayShadow = false;

	// La fenêtre principale a été initialisée et peut donc être affichée et mise à jour
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	// no tile now
	for( int i=0; i<30000; i++ )
		m_MaterialNb[i]=0;

	LoadIniFile();

	// We are not in game mode
	m_IsInGameMode = false;

	return TRUE;
}

// boîte de dialogue CAboutDlg utilisée pour la boîte de dialogue 'À propos de' pour votre application

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Données de boîte de dialogue
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

// Implémentation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// Commande App pour exécuter la boîte de dialogue
void CHeroscapeEditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// Inform each view that a tile is currently moving
//
void CHeroscapeEditorApp::InformEachViewTileMoving( CTile* pTile, POINT Point, double DiffPosTileMouseX, double DiffPosTileMouseY )
{
	// For each document
	POSITION Pos = m_pDocTemplateView2D->GetFirstDocPosition();
	while( Pos!=NULL )
	{
		CHeroscapeEditorDoc* pDoc = (CHeroscapeEditorDoc*) m_pDocTemplateView2D->GetNextDoc( Pos );
		pDoc->InformEachViewTileMoving( pTile, Point, DiffPosTileMouseX, DiffPosTileMouseY );
	}
}

// All the tile of all the document need to be unselect
//
void CHeroscapeEditorApp::UnselectAllTile()
{
	// For each document
	POSITION Pos = m_pDocTemplateView2D->GetFirstDocPosition();
	while( Pos!=NULL )
	{
		CHeroscapeEditorDoc* pDoc = (CHeroscapeEditorDoc*) m_pDocTemplateView2D->GetNextDoc( Pos );
		pDoc->UnselectAllTile();
	}
}

// Inform each view that the user launch a tile
//
bool CHeroscapeEditorApp::InformEachViewTileLaunch( CTile* pTile, POINT Point, double DiffPosTileMouseX, double DiffPosTileMouseY )
{
	bool Ret = false;

	// For each document
	POSITION Pos = m_pDocTemplateView2D->GetFirstDocPosition();
	while( Pos!=NULL )
	{
		CHeroscapeEditorDoc* pDoc = (CHeroscapeEditorDoc*) m_pDocTemplateView2D->GetNextDoc( Pos );
		if( pDoc->InformEachViewTileLaunch( pTile, Point, DiffPosTileMouseX, DiffPosTileMouseY ) )
		{
			Ret = true;
			pDoc->UpdateAllViews( NULL );
		}

		pDoc->RedrawAllViews();
	}

	return Ret;
}

// When we exit the instance
//
int CHeroscapeEditorApp::ExitInstance()
{
	if( m_IsInGameMode )
		ExitGameMode();

	SaveIniFile();

	delete m_pDocTemplateView3D;
	delete m_pDocTemplateGame3D;

	// Free all tile perso list
	for( int i=0; i<m_TilePersoList.GetCount(); i++ )
	{
		CTilePerso* pTile = (CTilePerso*) m_TilePersoList.GetAt(i);
		delete pTile;
	}
	m_TilePersoList.RemoveAll();

	RemoveClipboard();

	if( m_pGameDoc!=NULL )
	{
		delete m_pGameDoc;
		m_pGameDoc = NULL;
	}

	if( m_pGameDocServer!=NULL )
	{
		delete m_pGameDocServer;
		m_pGameDocServer = NULL;
	}

	if( m_pGame3DView!=NULL )
	{
		delete m_pGame3DView;
		m_pGame3DView = NULL;
	}

	// Free all game message list
	FreeChatMessage();
	for( int i=0; i<m_ChatMessageList.GetCount(); i++ )
	{
		ChatMessage* pCM = (ChatMessage*) m_ChatMessageList.GetAt(i);
		free(pCM);
	}
	m_ChatMessageList.RemoveAll();

	// Call the base class
	return CWinApp::ExitInstance();
}

// Free the memory used by chat message
//
void CHeroscapeEditorApp::FreeChatMessage()
{
	for( int i=0; i<m_ChatMessageList.GetCount(); i++ )
	{
		ChatMessage* pCM = (ChatMessage*) m_ChatMessageList.GetAt(i);
		free(pCM);
	}
	m_ChatMessageList.RemoveAll();
}

// Remove all tile of the clipboard and free memory
//
void CHeroscapeEditorApp::RemoveClipboard()
{
	// Free all tile in clipboard
	for( int i=0; i<m_TileClipboard.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_TileClipboard.GetAt(i);
		delete pTile;
	}
	m_TileClipboard.RemoveAll();
}

// When the application have nothing to do then test if the user want move the 3D view
//
BOOL CHeroscapeEditorApp::OnIdle(LONG lCount)
{
	// Call the base class
	BOOL bMore = CWinApp::OnIdle(lCount);

	return bMore;

	if( lCount%10==9 )
	{
		// Get the active MDI child window.
		CMDIChildWnd *pChild = (CMDIChildWnd *) ((CMDIFrameWnd*) m_pMainWnd)->GetActiveFrame();

		if( pChild!=NULL )
		{
			// Get the active view attached to the active MDI child window.
			CView *pView = pChild->GetActiveView();
			if( pView!=NULL )
			{
				if( pView->IsKindOf( RUNTIME_CLASS(CHeroscapeEditor3DView) ) )
				{
					//if( ((CHeroscapeEditor3DView*) pView)->VerifyKey(TimeDif) )
					//	((CHeroscapeEditor3DView*) pView)->RedrawWindow();
				}
			}
		}
	}

	// More idle processing
	return 1;
}

// Define the disponible material
//
void CHeroscapeEditorApp::OnConfigurationMatDispo()
{
	CMaterialEdit MatEditDlg;

	MatEditDlg.m_Nb_Grass24 = m_MaterialNb[TYPE_GRASS*1000+24];
	MatEditDlg.m_Nb_Grass7 = m_MaterialNb[TYPE_GRASS*1000+7];
	MatEditDlg.m_Nb_Grass3 = m_MaterialNb[TYPE_GRASS*1000+3];
	MatEditDlg.m_Nb_Grass2 = m_MaterialNb[TYPE_GRASS*1000+2];
	MatEditDlg.m_Nb_Grass1 = m_MaterialNb[TYPE_GRASS*1000+1];

	MatEditDlg.m_Nb_Rock24 = m_MaterialNb[TYPE_ROCK*1000+24];
	MatEditDlg.m_Nb_Rock7 = m_MaterialNb[TYPE_ROCK*1000+7];
	MatEditDlg.m_Nb_Rock3 = m_MaterialNb[TYPE_ROCK*1000+3];
	MatEditDlg.m_Nb_Rock2 = m_MaterialNb[TYPE_ROCK*1000+2];
	MatEditDlg.m_Nb_Rock1 = m_MaterialNb[TYPE_ROCK*1000+1];

	MatEditDlg.m_Nb_Sand7 = m_MaterialNb[TYPE_SAND*1000+7];
	MatEditDlg.m_Nb_Sand3 = m_MaterialNb[TYPE_SAND*1000+3];
	MatEditDlg.m_Nb_Sand2 = m_MaterialNb[TYPE_SAND*1000+2];
	MatEditDlg.m_Nb_Sand1 = m_MaterialNb[TYPE_SAND*1000+1];

	MatEditDlg.m_Nb_Tree15 = m_MaterialNb[TYPE_TREE*1000+4];
	MatEditDlg.m_Nb_Tree12 = m_MaterialNb[TYPE_TREE*1000+1+12];
	MatEditDlg.m_Nb_Tree11 = m_MaterialNb[TYPE_TREE*1000+1+11];
	MatEditDlg.m_Nb_Tree10 = m_MaterialNb[TYPE_TREE*1000+1+10];

	MatEditDlg.m_Nb_Glacier6 = m_MaterialNb[TYPE_GLACIER*1000+6];
	MatEditDlg.m_Nb_Glacier4 = m_MaterialNb[TYPE_GLACIER*1000+4];
	MatEditDlg.m_Nb_Glacier3 = m_MaterialNb[TYPE_GLACIER*1000+3];
	MatEditDlg.m_Nb_Glacier1 = m_MaterialNb[TYPE_GLACIER*1000+1];

	MatEditDlg.m_Nb_LavaField7 = m_MaterialNb[TYPE_LAVAFIELD*1000+7];
	MatEditDlg.m_Nb_LavaField2 = m_MaterialNb[TYPE_LAVAFIELD*1000+2];
	MatEditDlg.m_Nb_LavaField1 = m_MaterialNb[TYPE_LAVAFIELD*1000+1];

	MatEditDlg.m_Nb_Wall4 = m_MaterialNb[TYPE_WALL*1000+4];

	MatEditDlg.m_Nb_Road5 = m_MaterialNb[TYPE_ROAD*1000+5];
	MatEditDlg.m_Nb_Road2 = m_MaterialNb[TYPE_ROAD*1000+2];
	MatEditDlg.m_Nb_Road1 = m_MaterialNb[TYPE_ROAD*1000+1];

	MatEditDlg.m_Nb_Water1 = m_MaterialNb[TYPE_WATER*1000+1];
	MatEditDlg.m_Nb_Lava1 = m_MaterialNb[TYPE_LAVA*1000+1];
	MatEditDlg.m_Nb_Ice1 = m_MaterialNb[TYPE_ICE*1000+1];

	MatEditDlg.m_Nb_Snow2 = m_MaterialNb[TYPE_SNOW*1000+2];
	MatEditDlg.m_Nb_Snow1 = m_MaterialNb[TYPE_SNOW*1000+1];

	MatEditDlg.m_Nb_Ruin3 = m_MaterialNb[TYPE_RUIN*1000+3];
	MatEditDlg.m_Nb_Ruin2 = m_MaterialNb[TYPE_RUIN*1000+2];

	MatEditDlg.m_Nb_GlyphA = m_MaterialNb[TYPE_GLYPH*1000+'A'];
	MatEditDlg.m_Nb_GlyphG = m_MaterialNb[TYPE_GLYPH*1000+'G'];
	MatEditDlg.m_Nb_GlyphI = m_MaterialNb[TYPE_GLYPH*1000+'I'];
	MatEditDlg.m_Nb_GlyphV = m_MaterialNb[TYPE_GLYPH*1000+'V'];
	MatEditDlg.m_Nb_GlyphD = m_MaterialNb[TYPE_GLYPH*1000+'D'];
	MatEditDlg.m_Nb_GlyphB = m_MaterialNb[TYPE_GLYPH*1000+'B'];
	MatEditDlg.m_Nb_GlyphK = m_MaterialNb[TYPE_GLYPH*1000+'K'];
	MatEditDlg.m_Nb_GlyphE = m_MaterialNb[TYPE_GLYPH*1000+'E'];
	MatEditDlg.m_Nb_GlyphM = m_MaterialNb[TYPE_GLYPH*1000+'M'];
	MatEditDlg.m_Nb_GlyphL = m_MaterialNb[TYPE_GLYPH*1000+'L'];
	MatEditDlg.m_Nb_GlyphS = m_MaterialNb[TYPE_GLYPH*1000+'S'];
	MatEditDlg.m_Nb_GlyphR = m_MaterialNb[TYPE_GLYPH*1000+'R'];
	MatEditDlg.m_Nb_GlyphJ = m_MaterialNb[TYPE_GLYPH*1000+'J'];
	MatEditDlg.m_Nb_GlyphW = m_MaterialNb[TYPE_GLYPH*1000+'W'];
	MatEditDlg.m_Nb_GlyphP = m_MaterialNb[TYPE_GLYPH*1000+'P'];
	MatEditDlg.m_Nb_GlyphO = m_MaterialNb[TYPE_GLYPH*1000+'O'];
	MatEditDlg.m_Nb_GlyphN = m_MaterialNb[TYPE_GLYPH*1000+'N'];
	MatEditDlg.m_Nb_GlyphC = m_MaterialNb[TYPE_GLYPH*1000+'C'];
	MatEditDlg.m_Nb_GlyphT = m_MaterialNb[TYPE_GLYPH*1000+'T'];
	MatEditDlg.m_Nb_GlyphU = m_MaterialNb[TYPE_GLYPH*1000+'U'];

	MatEditDlg.m_Nb_CastleBaseCorner = m_MaterialNb[TYPE_CASTLE*1000+101];
	MatEditDlg.m_Nb_CastleBaseStraight = m_MaterialNb[TYPE_CASTLE*1000+102];
	MatEditDlg.m_Nb_CastleBaseEnd = m_MaterialNb[TYPE_CASTLE*1000+103];
	MatEditDlg.m_Nb_CastleWallCorner = m_MaterialNb[TYPE_CASTLE*1000+201];
	MatEditDlg.m_Nb_CastleWallStraight = m_MaterialNb[TYPE_CASTLE*1000+202];
	MatEditDlg.m_Nb_CastleWallEnd = m_MaterialNb[TYPE_CASTLE*1000+203];
	MatEditDlg.m_Nb_Castle9 = m_MaterialNb[TYPE_CASTLE*1000+9];
	MatEditDlg.m_Nb_Castle7 = m_MaterialNb[TYPE_CASTLE*1000+7];
	MatEditDlg.m_Nb_Castle1 = m_MaterialNb[TYPE_CASTLE*1000+1];
	MatEditDlg.m_Nb_CastleBattlement = m_MaterialNb[TYPE_CASTLE*1000+301];
	MatEditDlg.m_Nb_CastleDoor = m_MaterialNb[TYPE_CASTLE*1000+401];
	MatEditDlg.m_Nb_CastleLadder = m_MaterialNb[TYPE_CASTLE*1000+402];
	MatEditDlg.m_Nb_CastleFlag = m_MaterialNb[TYPE_CASTLE*1000+403];

	MatEditDlg.m_Nb_MarvelConcrete7 = m_MaterialNb[TYPE_CONCRETE*1000+7];
	MatEditDlg.m_Nb_MarvelConcrete2 = m_MaterialNb[TYPE_CONCRETE*1000+2];
	MatEditDlg.m_Nb_MarvelConcrete1 = m_MaterialNb[TYPE_CONCRETE*1000+1];
	MatEditDlg.m_Nb_MarvelAsphalt7 = m_MaterialNb[TYPE_ASPHALT*1000+7];
	MatEditDlg.m_Nb_MarvelAsphalt2 = m_MaterialNb[TYPE_ASPHALT*1000+2];
	MatEditDlg.m_Nb_MarvelAsphalt1 = m_MaterialNb[TYPE_ASPHALT*1000+1];
	MatEditDlg.m_Nb_MarvelRuin6 = m_MaterialNb[TYPE_RUIN*1000+6];

	MatEditDlg.m_Nb_Swamp24 = m_MaterialNb[TYPE_SWAMP*1000+24];
	MatEditDlg.m_Nb_Swamp7 = m_MaterialNb[TYPE_SWAMP*1000+7];
	MatEditDlg.m_Nb_Swamp3 = m_MaterialNb[TYPE_SWAMP*1000+3];
	MatEditDlg.m_Nb_Swamp2 = m_MaterialNb[TYPE_SWAMP*1000+2];
	MatEditDlg.m_Nb_Swamp1 = m_MaterialNb[TYPE_SWAMP*1000+1];
	MatEditDlg.m_Nb_SwampWater1 = m_MaterialNb[TYPE_SWAMPWATER*1000+1];
	MatEditDlg.m_Nb_SwampHive6 = m_MaterialNb[TYPE_HIVE*1000+6];

	MatEditDlg.m_Nb_TicallaPalm = m_MaterialNb[TYPE_TICALLA*1000+1];
	MatEditDlg.m_Nb_TicallaGrass = m_MaterialNb[TYPE_TICALLA*1000+2];

	MatEditDlg.m_Nb_Dungeon24 = m_MaterialNb[TYPE_DUNGEON*1000+24];
	MatEditDlg.m_Nb_Dungeon7 = m_MaterialNb[TYPE_DUNGEON*1000+7];
	MatEditDlg.m_Nb_Dungeon3 = m_MaterialNb[TYPE_DUNGEON*1000+3];
	MatEditDlg.m_Nb_Dungeon2 = m_MaterialNb[TYPE_DUNGEON*1000+2];
	MatEditDlg.m_Nb_Dungeon1 = m_MaterialNb[TYPE_DUNGEON*1000+1];
	MatEditDlg.m_Nb_Shadow1 = m_MaterialNb[TYPE_SHADOW*1000+1];
	MatEditDlg.m_Nb_Outcrop3 = m_MaterialNb[TYPE_OUTCROP*1000+3];
	MatEditDlg.m_Nb_Outcrop1 = m_MaterialNb[TYPE_OUTCROP*1000+1];

	if( MatEditDlg.DoModal()==IDOK )
	{
		m_MaterialNb[TYPE_GRASS*1000+24] = MatEditDlg.m_Nb_Grass24;
		m_MaterialNb[TYPE_GRASS*1000+7] = MatEditDlg.m_Nb_Grass7;
		m_MaterialNb[TYPE_GRASS*1000+3] = MatEditDlg.m_Nb_Grass3;
		m_MaterialNb[TYPE_GRASS*1000+2] = MatEditDlg.m_Nb_Grass2;
		m_MaterialNb[TYPE_GRASS*1000+1] = MatEditDlg.m_Nb_Grass1;

		m_MaterialNb[TYPE_ROCK*1000+24] = MatEditDlg.m_Nb_Rock24;
		m_MaterialNb[TYPE_ROCK*1000+7] = MatEditDlg.m_Nb_Rock7;
		m_MaterialNb[TYPE_ROCK*1000+3] = MatEditDlg.m_Nb_Rock3;
		m_MaterialNb[TYPE_ROCK*1000+2] = MatEditDlg.m_Nb_Rock2;
		m_MaterialNb[TYPE_ROCK*1000+1] = MatEditDlg.m_Nb_Rock1;

		m_MaterialNb[TYPE_SAND*1000+7] = MatEditDlg.m_Nb_Sand7;
		m_MaterialNb[TYPE_SAND*1000+3] = MatEditDlg.m_Nb_Sand3;
		m_MaterialNb[TYPE_SAND*1000+2] = MatEditDlg.m_Nb_Sand2;
		m_MaterialNb[TYPE_SAND*1000+1] = MatEditDlg.m_Nb_Sand1;

		m_MaterialNb[TYPE_TREE*1000+4] = MatEditDlg.m_Nb_Tree15;
		m_MaterialNb[TYPE_TREE*1000+1+12] = MatEditDlg.m_Nb_Tree12;
		m_MaterialNb[TYPE_TREE*1000+1+11] = MatEditDlg.m_Nb_Tree11;
		m_MaterialNb[TYPE_TREE*1000+1+10] = MatEditDlg.m_Nb_Tree10;

		m_MaterialNb[TYPE_GLACIER*1000+6] = MatEditDlg.m_Nb_Glacier6;
		m_MaterialNb[TYPE_GLACIER*1000+4] = MatEditDlg.m_Nb_Glacier4;
		m_MaterialNb[TYPE_GLACIER*1000+3] = MatEditDlg.m_Nb_Glacier3;
		m_MaterialNb[TYPE_GLACIER*1000+1] = MatEditDlg.m_Nb_Glacier1;

		m_MaterialNb[TYPE_LAVAFIELD*1000+7] = MatEditDlg.m_Nb_LavaField7;
		m_MaterialNb[TYPE_LAVAFIELD*1000+2] = MatEditDlg.m_Nb_LavaField2;
		m_MaterialNb[TYPE_LAVAFIELD*1000+1] = MatEditDlg.m_Nb_LavaField1;

		m_MaterialNb[TYPE_WALL*1000+4] = MatEditDlg.m_Nb_Wall4;

		m_MaterialNb[TYPE_ROAD*1000+5] = MatEditDlg.m_Nb_Road5;
		m_MaterialNb[TYPE_ROAD*1000+2] = MatEditDlg.m_Nb_Road2;
		m_MaterialNb[TYPE_ROAD*1000+1] = MatEditDlg.m_Nb_Road1;

		m_MaterialNb[TYPE_WATER*1000+1] = MatEditDlg.m_Nb_Water1;
		m_MaterialNb[TYPE_LAVA*1000+1] = MatEditDlg.m_Nb_Lava1;
		m_MaterialNb[TYPE_ICE*1000+1] = MatEditDlg.m_Nb_Ice1;

		m_MaterialNb[TYPE_SNOW*1000+2] = MatEditDlg.m_Nb_Snow2;
		m_MaterialNb[TYPE_SNOW*1000+1] = MatEditDlg.m_Nb_Snow1;

		m_MaterialNb[TYPE_RUIN*1000+3] = MatEditDlg.m_Nb_Ruin3;
		m_MaterialNb[TYPE_RUIN*1000+2] = MatEditDlg.m_Nb_Ruin2;

		m_MaterialNb[TYPE_GLYPH*1000+'A'] = MatEditDlg.m_Nb_GlyphA;
		m_MaterialNb[TYPE_GLYPH*1000+'G'] = MatEditDlg.m_Nb_GlyphG;
		m_MaterialNb[TYPE_GLYPH*1000+'I'] = MatEditDlg.m_Nb_GlyphI;
		m_MaterialNb[TYPE_GLYPH*1000+'V'] = MatEditDlg.m_Nb_GlyphV;
		m_MaterialNb[TYPE_GLYPH*1000+'D'] = MatEditDlg.m_Nb_GlyphD;
		m_MaterialNb[TYPE_GLYPH*1000+'B'] = MatEditDlg.m_Nb_GlyphB;
		m_MaterialNb[TYPE_GLYPH*1000+'K'] = MatEditDlg.m_Nb_GlyphK;
		m_MaterialNb[TYPE_GLYPH*1000+'E'] = MatEditDlg.m_Nb_GlyphE;
		m_MaterialNb[TYPE_GLYPH*1000+'M'] = MatEditDlg.m_Nb_GlyphM;
		m_MaterialNb[TYPE_GLYPH*1000+'L'] = MatEditDlg.m_Nb_GlyphL;
		m_MaterialNb[TYPE_GLYPH*1000+'S'] = MatEditDlg.m_Nb_GlyphS;
		m_MaterialNb[TYPE_GLYPH*1000+'R'] = MatEditDlg.m_Nb_GlyphR;
		m_MaterialNb[TYPE_GLYPH*1000+'J'] = MatEditDlg.m_Nb_GlyphJ;
		m_MaterialNb[TYPE_GLYPH*1000+'W'] = MatEditDlg.m_Nb_GlyphW;
		m_MaterialNb[TYPE_GLYPH*1000+'P'] = MatEditDlg.m_Nb_GlyphP;
		m_MaterialNb[TYPE_GLYPH*1000+'O'] = MatEditDlg.m_Nb_GlyphO;
		m_MaterialNb[TYPE_GLYPH*1000+'N'] = MatEditDlg.m_Nb_GlyphN;
		m_MaterialNb[TYPE_GLYPH*1000+'C'] = MatEditDlg.m_Nb_GlyphC;
		m_MaterialNb[TYPE_GLYPH*1000+'T'] = MatEditDlg.m_Nb_GlyphT;
		m_MaterialNb[TYPE_GLYPH*1000+'U'] = MatEditDlg.m_Nb_GlyphU;

		m_MaterialNb[TYPE_CASTLE*1000+101] = MatEditDlg.m_Nb_CastleBaseCorner;
		m_MaterialNb[TYPE_CASTLE*1000+102] = MatEditDlg.m_Nb_CastleBaseStraight;
		m_MaterialNb[TYPE_CASTLE*1000+103] = MatEditDlg.m_Nb_CastleBaseEnd;
		m_MaterialNb[TYPE_CASTLE*1000+201] = MatEditDlg.m_Nb_CastleWallCorner;
		m_MaterialNb[TYPE_CASTLE*1000+202] = MatEditDlg.m_Nb_CastleWallStraight;
		m_MaterialNb[TYPE_CASTLE*1000+203] = MatEditDlg.m_Nb_CastleWallEnd;
		m_MaterialNb[TYPE_CASTLE*1000+9] = MatEditDlg.m_Nb_Castle9;
		m_MaterialNb[TYPE_CASTLE*1000+7] = MatEditDlg.m_Nb_Castle7;
		m_MaterialNb[TYPE_CASTLE*1000+1] = MatEditDlg.m_Nb_Castle1;
		m_MaterialNb[TYPE_CASTLE*1000+301] = MatEditDlg.m_Nb_CastleBattlement;
		m_MaterialNb[TYPE_CASTLE*1000+401] = MatEditDlg.m_Nb_CastleDoor;
		m_MaterialNb[TYPE_CASTLE*1000+402] = MatEditDlg.m_Nb_CastleLadder;
		m_MaterialNb[TYPE_CASTLE*1000+403] = MatEditDlg.m_Nb_CastleFlag;

		m_MaterialNb[TYPE_CONCRETE*1000+7] = MatEditDlg.m_Nb_MarvelConcrete7;
		m_MaterialNb[TYPE_CONCRETE*1000+2] = MatEditDlg.m_Nb_MarvelConcrete2;
		m_MaterialNb[TYPE_CONCRETE*1000+1] = MatEditDlg.m_Nb_MarvelConcrete1;
		m_MaterialNb[TYPE_ASPHALT*1000+7] = MatEditDlg.m_Nb_MarvelAsphalt7;
		m_MaterialNb[TYPE_ASPHALT*1000+2] = MatEditDlg.m_Nb_MarvelAsphalt2;
		m_MaterialNb[TYPE_ASPHALT*1000+1] = MatEditDlg.m_Nb_MarvelAsphalt1;
		m_MaterialNb[TYPE_RUIN*1000+6] = MatEditDlg.m_Nb_MarvelRuin6;

		m_MaterialNb[TYPE_SWAMP*1000+24] = MatEditDlg.m_Nb_Swamp24;
		m_MaterialNb[TYPE_SWAMP*1000+7] = MatEditDlg.m_Nb_Swamp7;
		m_MaterialNb[TYPE_SWAMP*1000+3] = MatEditDlg.m_Nb_Swamp3;
		m_MaterialNb[TYPE_SWAMP*1000+2] = MatEditDlg.m_Nb_Swamp2;
		m_MaterialNb[TYPE_SWAMP*1000+1] = MatEditDlg.m_Nb_Swamp1;
		m_MaterialNb[TYPE_SWAMPWATER*1000+1] = MatEditDlg.m_Nb_SwampWater1;
		m_MaterialNb[TYPE_HIVE*1000+6] = MatEditDlg.m_Nb_SwampHive6;

		m_MaterialNb[TYPE_TICALLA*1000+1] = MatEditDlg.m_Nb_TicallaPalm;
		m_MaterialNb[TYPE_TICALLA*1000+2] = MatEditDlg.m_Nb_TicallaGrass;

		m_MaterialNb[TYPE_DUNGEON*1000+24] = MatEditDlg.m_Nb_Dungeon24;
		m_MaterialNb[TYPE_DUNGEON*1000+7] = MatEditDlg.m_Nb_Dungeon7;
		m_MaterialNb[TYPE_DUNGEON*1000+3] = MatEditDlg.m_Nb_Dungeon3;
		m_MaterialNb[TYPE_DUNGEON*1000+2] = MatEditDlg.m_Nb_Dungeon2;
		m_MaterialNb[TYPE_DUNGEON*1000+1] = MatEditDlg.m_Nb_Dungeon1;
		m_MaterialNb[TYPE_SHADOW*1000+1] = MatEditDlg.m_Nb_Shadow1;
		m_MaterialNb[TYPE_OUTCROP*1000+3] = MatEditDlg.m_Nb_Outcrop3;
		m_MaterialNb[TYPE_OUTCROP*1000+1] = MatEditDlg.m_Nb_Outcrop1;

		SaveIniFile();
	}
}

// Save the informations on the ini file
//
void CHeroscapeEditorApp::SaveIniFile()
{
	CString	Str,Str2;
	int Nb=1;
	int i;

	for( i=0; i<30000; i++ )
	{
		if( m_MaterialNb[i]!=0 )
		{
			Str.Format( _T("Tile%i"), Nb );
			Str2.Format( _T("%i,%i"), i, m_MaterialNb[i] );
			WriteProfileString( _T("Tile"), Str, Str2 );
			Nb++;
		}
	}
	Str.Format( _T("Tile%i"), Nb );
	WriteProfileString( _T("Tile"), Str, _T("") );

	// Save if the user like shadowing
	WriteProfileInt( _T("Shadowing"), _T("DisplayShadow"), m_DisplayShadow?1:0 );
	WriteProfileInt( _T("Shadowing"), _T("Quality"), m_ShadowQuality );
	WriteProfileInt( _T("Shadowing"), _T("Contrast"), m_ShadowContrast );
	// Save Photo quality
	WriteProfileInt( _T("Photo"), _T("Quality"), m_PhotoQuality );
	WriteProfileInt( _T("Photo"), _T("Luminosity"), m_Luminosity );
	WriteProfileInt( _T("Photo"), _T("DepthField"), m_IsDepthField );
	WriteProfileInt( _T("Photo"), _T("DepthFieldAperture"), (int) m_DepthField_Aperture );
	WriteProfileInt( _T("Photo"), _T("DepthFieldDistance"), (int) m_DepthField_Distance );
	WriteProfileInt( _T("Photo"), _T("DepthFieldQuality"), m_DepthField_Quality );
	// Save 3D parameters
	WriteProfileInt( _T("3D"), _T("DisplayTable"), m_DisplayTable );
	WriteProfileInt( _T("3D"), _T("AlternativeMove"), m_MoveSolidscape );
	WriteProfileInt( _T("3D"), _T("BackgroundColor"), m_BackgroundColor3D );
	WriteProfileInt( _T("3D"), _T("TextureType"), m_TextureType );
	WriteProfileInt( _T("3D"), _T("AnaglyphiqueMode"), m_AnaglyphiqueMode );
	// Save 2D parameters
	WriteProfileInt( _T("2D"), _T("BackgroundColor"), m_BackgroundColor2D );
	WriteProfileInt( _T("2D"), _T("Unit"), m_Unit );
	// Save Topographic parameters
	WriteProfileInt( _T("Topographic"), _T("LowColor"), m_TopographicColorLow );
	WriteProfileInt( _T("Topographic"), _T("HighColor"), m_TopographicColorHigh );
	// Save tile perso
	for( i=0; i<m_TilePersoList.GetCount(); i++ )
	{
		CTilePerso* pTile = (CTilePerso*) m_TilePersoList.GetAt(i);

		Str.Format( _T("Tile%i"), i );
		WriteProfileString( _T("TilePerso"), Str, _T("true") );
		Str.Format( _T("Tile%iName"), i );
		WriteProfileString( _T("TilePerso"), Str, pTile->m_Name );
		Str.Format( _T("Tile%iNbHex"), i );
		WriteProfileInt( _T("TilePerso"), Str, pTile->m_NbTile );
		Str.Format( _T("Tile%iQuantity"), i );
		WriteProfileInt( _T("TilePerso"), Str, pTile->m_Quantity );
		Str.Format( _T("Tile%iTexture"), i );
		WriteProfileString( _T("TilePerso"), Str, pTile->m_PersonalTexture );
		Str.Format( _T("Tile%iTextureSide"), i );
		WriteProfileString( _T("TilePerso"), Str, pTile->m_PersonalTextureSide );
		Str.Format( _T("Tile%iChar"), i );
		WriteProfileString( _T("TilePerso"), Str, pTile->m_Char );
		Str.Format( _T("Tile%iColor"), i );
		WriteProfileInt( _T("TilePerso"), Str, pTile->m_TileColor );
	}
	Str.Format( _T("Tile%i"), i );
	WriteProfileString( _T("TilePerso"), Str, _T("false") );
	// Save default game parameters
	WriteProfileString( _T("Game"), _T("PlayerName"), m_PlayerName );
	WriteProfileString( _T("Game"), _T("GameName"), m_GameName );
	WriteProfileString( _T("Game"), _T("GameLanguage"), m_GameLanguage );
	WriteProfileString( _T("Game"), _T("IPAddress"), m_IP_Address );
	WriteProfileString( _T("Game"), _T("GamePassword"), m_GamePassword );
	WriteProfileInt( _T("Game"), _T("GameType"), m_GameType );
	WriteProfileInt( _T("Game"), _T("GamePoint"), m_GamePoint );
	WriteProfileInt( _T("Game"), _T("PlayerMax"), m_GamePlayerMax );
	WriteProfileInt( _T("Game"), _T("WatcherMax"), m_GameWatcherMax );
	m_GameWelcomeMessage.Replace( _T("\r\n"), _T("|") );
	WriteProfileString( _T("Game"), _T("WelcomeMessage"), m_GameWelcomeMessage );
	m_GameWelcomeMessage.Replace( _T("|"), _T("\r\n") );
	WriteProfileInt( _T("Game"), _T("Port"), m_GamePort );
	// Save default render video parameters
	WriteProfileInt( _T("Video"), _T("FrameCount"), m_RenderVideo_FrameCount );
	WriteProfileInt( _T("Video"), _T("FirstFrame"), m_RenderVideo_FirstFrame );
	WriteProfileInt( _T("Video"), _T("LastFrame"), m_RenderVideo_LastFrame );
	WriteProfileString( _T("Video"), _T("FileName"), m_RenderVideo_FileName );
	WriteProfileInt( _T("Video"), _T("HighQuality"), m_RenderVideo_HighQuality?1:0 );
}

// Load the informations on the ini file
//
void CHeroscapeEditorApp::LoadIniFile()
{
	CString	Str,Str2;
	int Nb=1;
	bool Found=true;

	while( Found )
	{
		Str.Format( _T("Tile%i"), Nb++ );
		Str2 = GetProfileString( _T("Tile"), Str, _T("") );
		if( Str2!="" )
		{
			int i,j;
			swscanf_s( Str2, _T("%i,%i"), &i, &j );
			m_MaterialNb[i]=j;
		}
		else
			Found=false;
	}
	// Particular case
	m_MaterialNb[TYPE_GLYPH*1000+'?'] = 9999;
	m_MaterialNb[TYPE_STARTAREA*1000+1] = 9999;
	m_MaterialNb[TYPE_FIGURE*1000+1] = 9999;
	m_MaterialNb[TYPE_FIGURE*1000+2] = 9999;

	// Load if the user like shadowing
	m_DisplayShadow = GetProfileInt( _T("Shadowing"), _T("DisplayShadow"), 0 )==0?0:1;
	m_ShadowQuality = GetProfileInt( _T("Shadowing"), _T("Quality"), 2 );
	m_ShadowContrast = GetProfileInt( _T("Shadowing"), _T("Contrast"), 20 );
	// Load Photo quality
	m_PhotoQuality = GetProfileInt( _T("Photo"), _T("Quality"), 10 );
	m_Luminosity = GetProfileInt( _T("Photo"), _T("Luminosity"), 15 );
	m_IsDepthField = GetProfileInt( _T("Photo"), _T("DepthField"), 0 );
	m_DepthField_Aperture = GetProfileInt( _T("Photo"), _T("DepthFieldAperture"), 10 );
	m_DepthField_Distance = GetProfileInt( _T("Photo"), _T("DepthFieldDistance"), 30 );
	m_DepthField_Quality = GetProfileInt( _T("Photo"), _T("DepthFieldQuality"), 3 );
	// Load 3D parameters
	m_DisplayTable = GetProfileInt( _T("3D"), _T("DisplayTable"), 1 );
	m_MoveSolidscape = GetProfileInt( _T("3D"), _T("AlternativeMove"), 0 );
	m_BackgroundColor3D = GetProfileInt( _T("3D"), _T("BackgroundColor"), RGB(255*0.8,255*0.8,255) );
	m_TextureType = GetProfileInt( _T("3D"), _T("TextureType"), 0 );
	m_AnaglyphiqueMode = GetProfileInt( _T("3D"), _T("AnaglyphiqueMode"), 0 );
	// Load 2D parameters
	m_BackgroundColor2D = GetProfileInt( _T("2D"), _T("BackgroundColor"), RGB(225,196,224) );
	m_Unit = GetProfileInt( _T("2D"), _T("Unit"), 0 );
	// Load Topographic parameters
	m_TopographicColorLow = GetProfileInt( _T("Topographic"), _T("LowColor"), RGB(0,255,0) );
	m_TopographicColorHigh = GetProfileInt( _T("Topographic"), _T("HighColor"), RGB(255,0,255) );
	// Load tile perso
	for( int i=0; i<30000; i++ )
	{
		Str.Format( _T("Tile%i"), i );
		Str2 = GetProfileString( _T("TilePerso"), Str, _T("false") );
		if( Str2==_T("false") )
		{
			break;
		}
		else
		{
			CTilePerso* pTile = (CTilePerso*) CTile::GetNewTile( TYPE_PERSONAL*1000 );

			Str.Format( _T("Tile%iName"), i );
			pTile->m_Name = GetProfileString( _T("TilePerso"), Str, _T("") );
			Str.Format( _T("Tile%iNbHex"), i );
			pTile->m_NbTile = GetProfileInt( _T("TilePerso"), Str, 1 );
			Str.Format( _T("Tile%iQuantity"), i );
			pTile->m_Quantity = GetProfileInt( _T("TilePerso"), Str, 0 );
			Str.Format( _T("Tile%iTexture"), i );
			pTile->m_PersonalTexture = GetProfileString( _T("TilePerso"), Str, _T("") );
			Str.Format( _T("Tile%iTextureSide"), i );
			pTile->m_PersonalTextureSide = GetProfileString( _T("TilePerso"), Str, _T("") );
			Str.Format( _T("Tile%iChar"), i );
			pTile->m_Char = GetProfileString( _T("TilePerso"), Str, _T("") );
			Str.Format( _T("Tile%iColor"), i );
			pTile->m_TileColor = GetProfileInt( _T("TilePerso"), Str, 0 );

			pTile->Init();

			m_TilePersoList.Add( pTile );
		}
	}
	// Load default game parameters
	m_PlayerName = GetProfileString( _T("Game"), _T("PlayerName"), _T("") );
	m_GameName = GetProfileString( _T("Game"), _T("GameName"), _T("") );
	m_GameLanguage = GetProfileString( _T("Game"), _T("GameLanguage"), _T("") );
	m_IP_Address = GetProfileString( _T("Game"), _T("IPAddress"), _T("") );
	m_GamePassword = GetProfileString( _T("Game"), _T("GamePassword"), _T("") );
	m_GameType = GetProfileInt( _T("Game"), _T("GameType"), 0 );
	m_GamePoint = GetProfileInt( _T("Game"), _T("GamePoint"), 2 );
	m_GamePlayerMax = GetProfileInt( _T("Game"), _T("PlayerMax"), 2 );
	m_GameWatcherMax = GetProfileInt( _T("Game"), _T("WatcherMax"), 100 );
	m_GameWelcomeMessage = GetProfileString( _T("Game"), _T("WelcomeMessage"), _T("") );
	m_GameWelcomeMessage.Replace( _T("|"), _T("\r\n") );
	m_GamePort = GetProfileInt( _T("Game"), _T("Port"), 1399 );
	// Load default render video parameters
	m_RenderVideo_FrameCount = GetProfileInt( _T("Video"), _T("FrameCount"), 500 );
	m_RenderVideo_FirstFrame = GetProfileInt( _T("Video"), _T("FirstFrame"), 1 );
	m_RenderVideo_LastFrame = GetProfileInt( _T("Video"), _T("LastFrame"), 500 );
	m_RenderVideo_FileName = GetProfileString( _T("Video"), _T("FileName"), _T("Test") );
	m_RenderVideo_HighQuality = GetProfileInt( _T("Video"), _T("HighQuality"), 1 )?true:false;
}

// The user want set preferency
//
void CHeroscapeEditorApp::OnConfigurationPreferency()
{
	CPreferenceDlg Dlg;

	Dlg.m_ShadowQuality = m_ShadowQuality;
	Dlg.m_ShadowContrast = m_ShadowContrast;
	Dlg.m_PhotoQuality = m_PhotoQuality;
	Dlg.m_Luminosity = m_Luminosity;
	Dlg.m_IsDepthField = m_IsDepthField;
	Dlg.m_DepthField_Aperture = (int) m_DepthField_Aperture;
	Dlg.m_DepthField_Distance = (int) m_DepthField_Distance;
	Dlg.m_DepthField_Quality = m_DepthField_Quality;
	Dlg.m_DisplayTable = m_DisplayTable;
	Dlg.m_MoveSolidscape = m_MoveSolidscape;
	Dlg.m_BackgroundColor2D = m_BackgroundColor2D;
	Dlg.m_BackgroundColor3D = m_BackgroundColor3D;
	Dlg.m_TopographicColorLow = m_TopographicColorLow;
	Dlg.m_TopographicColorHigh = m_TopographicColorHigh;
	Dlg.m_i_TextureType = m_TextureType;
	Dlg.m_i_AnaglyphiqueMode = m_AnaglyphiqueMode;
	Dlg.m_i_Unit = m_Unit;

	if( Dlg.DoModal()==IDOK )
	{
		m_ShadowQuality = Dlg.m_ShadowQuality;
		m_ShadowContrast = Dlg.m_ShadowContrast;
		m_PhotoQuality = Dlg.m_PhotoQuality;
		m_Luminosity = Dlg.m_Luminosity;
		m_IsDepthField = Dlg.m_IsDepthField;
		m_DepthField_Aperture = Dlg.m_DepthField_Aperture;
		m_DepthField_Distance = Dlg.m_DepthField_Distance;
		m_DepthField_Quality = Dlg.m_DepthField_Quality;
		m_DisplayTable = Dlg.m_DisplayTable;
		m_MoveSolidscape = Dlg.m_MoveSolidscape;
		m_BackgroundColor2D = Dlg.m_BackgroundColor2D;
		m_BackgroundColor3D = Dlg.m_BackgroundColor3D;
		m_TopographicColorLow = Dlg.m_TopographicColorLow;
		m_TopographicColorHigh = Dlg.m_TopographicColorHigh;
		m_TextureType = Dlg.m_i_TextureType;
		m_AnaglyphiqueMode = Dlg.m_i_AnaglyphiqueMode;
		m_Unit = Dlg.m_i_Unit;

		POSITION Pos = m_pDocTemplateView2D->GetFirstDocPosition();
		while( Pos!=NULL )
		{
			CHeroscapeEditorDoc* pDoc = (CHeroscapeEditorDoc*) m_pDocTemplateView2D->GetNextDoc(Pos);
			pDoc->UpdateAllViews( NULL );
			pDoc->RedrawAllViews();
		}
	}
}

// Display global help
//
void CHeroscapeEditorApp::OnGlobalHelp()
{
	HtmlHelp( NULL, HH_DISPLAY_TOC );
}

// Configuration of personal tiles
//
void CHeroscapeEditorApp::OnConfigurationTileperso()
{
	// Create the dialog box about tile perso
	CTilePersoDlg Dlg;

	Dlg.DoModal();

	// Refresh if necessary
	((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.m_ObjectFV.OnTcnSelchangeTabObjectType(NULL, NULL);
}

// Create a char* from a unicode CString
//
char* CHeroscapeEditorApp::GetAsciiString( CString Str )
{
	char* NewStr = (char*) malloc(Str.GetLength()+1);

	for( int i=0; i<Str.GetLength(); i++ )
	{
		unsigned short us = _mbbtombc( Str.GetAt(i) );
		if( us<256 )
			NewStr[i] = (char) us;
		else
			NewStr[i] = ' ';
	}
	NewStr[Str.GetLength()] = 0;

	return NewStr;
}

// The user want join a game
//
// This version will be available only when Hasbro will give authorisation
//
/*void CHeroscapeEditorApp::OnPlayJoingame()
{
	// Create a Game
	if( m_pGameDoc!=NULL )
		delete m_pGameDoc;

	m_pGameDoc = new CGameDoc();
	m_pGameDoc->m_IsServer = false;

	theApp.m_pDocTemplateGame3D->AddDocument( theApp.m_pGameDoc );
	CChildFrame* pFrame = (CChildFrame*) theApp.m_pDocTemplateGame3D->CreateNewFrame( theApp.m_pGameDoc, NULL );
	theApp.m_pDocTemplateGame3D->InitialUpdateFrame( pFrame, theApp.m_pGameDoc, FALSE );
	pFrame->MDIActivate();
	CGame3DView* pView = (CGame3DView*) pFrame->GetActiveView();
	pView->InitParams();
	pFrame->ShowWindow( SW_SHOWMAXIMIZED );
	pView->AfterCreate();

	// Create a socket to broadcast and wait to receive all game
	CClientSocket cs;
	if( cs.Create(0,SOCK_DGRAM)==0 )
		cs.SocketError();
	int opt = 1;
	cs.SetSockOpt( SO_BROADCAST, (const void*) &opt, sizeof( bool), SOL_SOCKET );
	DWORD dw;
	cs.IOCtl( FIONBIO, &dw );
	
	// Affiche la boite de dialogue avec tous les hosts
	m_pJoinGameDlg = new CJoinGameDlg();

	m_pJoinGameDlg->m_PlayerName = m_PlayerName;

	// Lance la recherche les hosts
	cs.CreateBuffer();
	cs.SendMessageTo(SMI_TOSERVER_SEARCH_SERVER,5186,NULL);

	if( m_pJoinGameDlg->DoModal()==IDOK )
	{
		m_PlayerName = m_pJoinGameDlg->m_PlayerName;
		// The user want connexion with server
		cs.Close();
		CString IPAddress;
		IPAddress.Format( _T("%d.%d.%d.%d"), m_pJoinGameDlg->m_Byte1, m_pJoinGameDlg->m_Byte2, m_pJoinGameDlg->m_Byte3, m_pJoinGameDlg->m_Byte4 );
		if( m_pGameDoc->m_ToServerSocket.Create()==0 )
			m_pGameDoc->m_ToServerSocket.SocketError();
		else
		{
			m_pGameDoc->m_ToServerSocket.AsyncSelect( FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE );
			if( m_pGameDoc->m_ToServerSocket.Connect(IPAddress,m_pJoinGameDlg->m_ServerPort)==0 )
				m_pGameDoc->m_ToServerSocket.SocketError();
			else
			{
				// Create the waiting dialog
				theApp.m_pWaitingConnection = new CWaitingConnection();

				theApp.m_pWaitingConnection->m_pGameDoc = theApp.m_pGameDoc;

				if( theApp.m_pWaitingConnection->DoModal()==IDCANCEL )
				{
					pFrame->DestroyWindow();
					delete m_pGameDoc;
					m_pGameDoc=NULL;
				}

				delete theApp.m_pWaitingConnection;
				theApp.m_pWaitingConnection = NULL;
			}
		}
	}
	else
	{
		pFrame->DestroyWindow();
		delete m_pGameDoc;
		m_pGameDoc = NULL;
	}

	delete m_pJoinGameDlg;
	m_pJoinGameDlg = NULL;
}*/

// The user want join a game
//
void CHeroscapeEditorApp::OnPlayJoingame()
{
	// Create a Game
	if( m_pGameDoc!=NULL )
		delete m_pGameDoc;

	m_pGameDoc = new CGameDoc();
	m_pGameDoc->m_IsServer = false;

	theApp.m_pDocTemplateGame3D->AddDocument( theApp.m_pGameDoc );
	CChildFrame* pFrame = (CChildFrame*) theApp.m_pDocTemplateGame3D->CreateNewFrame( theApp.m_pGameDoc, NULL );
	theApp.m_pDocTemplateGame3D->InitialUpdateFrame( pFrame, theApp.m_pGameDoc, FALSE );
	pFrame->MDIActivate();
	CGame3DView* pView = (CGame3DView*) pFrame->GetActiveView();
	pView->InitParams();
	pFrame->ShowWindow( SW_SHOWMAXIMIZED );
	pView->AfterCreate();

	// Affiche la boite de dialogue avec tous les hosts
	m_pJoinGameListDlg = new CJoinGameListDlg;

	m_pJoinGameListDlg->m_PlayerName = m_PlayerName;

	// Lance la recherche les hosts
	if( m_pJoinGameListDlg->DoModal()==IDOK )
	{
		m_PlayerName = m_pJoinGameListDlg->m_PlayerName;
		CString IPAddress = m_pJoinGameListDlg->GetIPAddress();
		if( m_pGameDoc->m_ToServerSocket.Create()==0 )
			m_pGameDoc->m_ToServerSocket.SocketError();
		else
		{
			m_pGameDoc->m_ToServerSocket.AsyncSelect( FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE );
			if( m_pGameDoc->m_ToServerSocket.Connect(IPAddress,m_pJoinGameListDlg->GetPort())==0 )
			//if( m_pGameDoc->m_ToServerSocket.Connect(_T("88.186.169.121"),m_pJoinGameListDlg->GetPort())==0 )
				m_pGameDoc->m_ToServerSocket.SocketError();
			else
			{
				// Create the waiting dialog
				theApp.m_pWaitingConnection = new CWaitingConnection();

				theApp.m_pWaitingConnection->m_pGameDoc = theApp.m_pGameDoc;

				if( theApp.m_pWaitingConnection->DoModal()==IDCANCEL )
				{
					pFrame->DestroyWindow();
					delete m_pGameDoc;
					m_pGameDoc=NULL;
				}

				delete theApp.m_pWaitingConnection;
				theApp.m_pWaitingConnection = NULL;
			}
		}
	}
	else
	{
		pFrame->DestroyWindow();
		delete m_pGameDoc;
		m_pGameDoc = NULL;
	}

	delete m_pJoinGameListDlg;
	m_pJoinGameListDlg = NULL;

	/*if( m_pJoinGameDlg->DoModal()==IDOK )
	{
		m_PlayerName = m_pJoinGameDlg->m_PlayerName;
		// The user want connexion with server
		cs.Close();
		CString IPAddress;
		IPAddress.Format( _T("%d.%d.%d.%d"), m_pJoinGameDlg->m_Byte1, m_pJoinGameDlg->m_Byte2, m_pJoinGameDlg->m_Byte3, m_pJoinGameDlg->m_Byte4 );
		if( m_pGameDoc->m_ToServerSocket.Create()==0 )
			m_pGameDoc->m_ToServerSocket.SocketError();
		else
		{
			m_pGameDoc->m_ToServerSocket.AsyncSelect( FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE );
			if( m_pGameDoc->m_ToServerSocket.Connect(IPAddress,m_pJoinGameDlg->m_ServerPort)==0 )
				m_pGameDoc->m_ToServerSocket.SocketError();
			else
			{
				// Create the waiting dialog
				theApp.m_pWaitingConnection = new CWaitingConnection();

				theApp.m_pWaitingConnection->m_pGameDoc = theApp.m_pGameDoc;

				if( theApp.m_pWaitingConnection->DoModal()==IDCANCEL )
				{
					pFrame->DestroyWindow();
					delete m_pGameDoc;
					m_pGameDoc=NULL;
				}

				delete theApp.m_pWaitingConnection;
				theApp.m_pWaitingConnection = NULL;
			}
		}
	}
	else
	{
		pFrame->DestroyWindow();
		delete m_pGameDoc;
		m_pGameDoc = NULL;
	}

	delete m_pJoinGameDlg;
	m_pJoinGameDlg = NULL;*/
}

// We enter in game mode so hide unusefull tool windows and show usefull windows
//
void CHeroscapeEditorApp::EnterGameMode()
{
	if( m_IsInGameMode )
		return;

	// Inform the main window
	((CMainFrame*) theApp.m_pMainWnd)->EnterGameMode();

	// Add all message to the message window
	for( int i=0; i<m_ChatMessageList.GetCount(); i++ )
	{
		ChatMessage* pCM = (ChatMessage*) m_ChatMessageList.GetAt(i);
		((CMainFrame*) m_pMainWnd)->m_wndGameChatBar.AddMessage( pCM->IsMine, *pCM->pFrom, *pCM->pMessage );
	}

	m_IsInGameMode = true;
}

// We exit the game mode so restore tool windows state
//
void CHeroscapeEditorApp::ExitGameMode()
{
	// Inform the main window
	((CMainFrame*) theApp.m_pMainWnd)->ExitGameMode();
	m_IsInGameMode = false;
}

// Add a chat message to the memory
//
void CHeroscapeEditorApp::AddChatMessage( bool IsMine, CString From, CString Message )
{
	ChatMessage* pCM = (ChatMessage*) malloc( sizeof(ChatMessage) );

	pCM->IsMine = IsMine;
	pCM->pFrom = new CString(From);
	pCM->pMessage = new CString(Message);

	m_ChatMessageList.Add( pCM );
}

