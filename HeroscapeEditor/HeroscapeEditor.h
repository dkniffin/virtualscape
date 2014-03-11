// HeroscapeEditor.h : fichier d'en-tête principal pour l'application HeroscapeEditor
//
#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#include "Game3DView.h"
#include "GameDoc.h"
#include "GameDocServer.h"
#include "JoinGameDlg.h"
#include "JoinGameListDlg.h"
#include "Resource.h"
#include "Tile.h"
#include "ToDedicatedServerSocket.h"
#include "WaitingConnection.h"

class CHeroscapeEditorApp : public CWinApp
{
//************
// The defines
//************
#define PI	3.14159265358979323846

//************
// The structs
//************
public:
	struct ChatMessage
	{
		bool		IsMine;
		CString*	pFrom;
		CString*	pMessage;
	};

//**********
// The enums
//**********

public:

	enum SocketMessage
	{
		SOCKETMSG_GAME_NAME = 1
	};

//************
// The members
//************
public:
	// The current dir
	CString				m_CurrentDir;
	// The template for document
	CMultiDocTemplate*	m_pDocTemplateView2D;
	CMultiDocTemplate*	m_pDocTemplateView3D;
	// The template for game
	CMultiDocTemplate*	m_pDocTemplateGame3D;
	// The number of tile
	int					m_MaterialNb[30000];
	// To know if we must display shadow or not
	bool				m_DisplayShadow;
	// The contrast for shadow on 3D view
	int					m_ShadowContrast;
	// The quality for shadow on 3D view
	int					m_ShadowQuality;
	// The quality for photo view
	int					m_PhotoQuality;
	// The luminosity for photo view
	int					m_Luminosity;
	// The depth field is activated or not
	BOOL				m_IsDepthField;
	// The depth field aperture
	double				m_DepthField_Aperture;
	// The depth field distance
	double				m_DepthField_Distance;
	// The depth field quality
	int					m_DepthField_Quality;
	bool				m_GlExtensionAlreadyInit;
	// To know if we must display table or not
	BOOL				m_DisplayTable;
	// To know if we must move camera like solidscape or not
	BOOL				m_MoveSolidscape;
	// The view background color
	COLORREF			m_BackgroundColor2D;
	COLORREF			m_BackgroundColor3D;
	// The topographic view color
	COLORREF			m_TopographicColorLow;
	COLORREF			m_TopographicColorHigh;
	// The texture type
	int					m_TextureType;
	// The anaglyphique mode
	int					m_AnaglyphiqueMode;
	// The tile perso list
	CPtrArray			m_TilePersoList;
	// The clipboard tile
	CPtrArray			m_TileClipboard;
	// The current unit (0=cm, 1=inch)
	int					m_Unit;
	// The default player name
	CString				m_PlayerName;
	// The default game name
	CString				m_GameName;
	// The default game password
	CString				m_GamePassword;
	// The game language
	CString				m_GameLanguage;
	// The default game type (0 = basic, 1 = expert)
	int					m_GameType;
	// The default game point
	int					m_GamePoint;
	// The default game players max
	int					m_GamePlayerMax;
	// The default game watcher max
	int					m_GameWatcherMax;
	// The default welcome message
	CString				m_GameWelcomeMessage;
	// The default game port
	int					m_GamePort;
	// The default IP address
	CString				m_IP_Address;
	// The current game server (if you are the server)
	CGameDocServer*		m_pGameDocServer;
	// The current game
	CGameDoc*			m_pGameDoc;
	// The dialog box for trying to connect to a server
	// CJoinGameDlg*		m_pJoinGameDlg;
	// The dialog box for trying to connect to a server
	CJoinGameListDlg*		m_pJoinGameListDlg;
	// The dialog box with current connected players
	CWaitingConnection*	m_pWaitingConnection;
	// The display window for game
	CGame3DView*		m_pGame3DView;
	// To know if we are in game mode or not
	bool				m_IsInGameMode;
	// The chat message list
	CPtrArray			m_ChatMessageList;
	// The number of frame for render video
	int					m_RenderVideo_FrameCount;
	// The first frame to render
	int					m_RenderVideo_FirstFrame;
	// The last frame to render
	int					m_RenderVideo_LastFrame;
	// The file name for render video
	CString				m_RenderVideo_FileName;
	// The High Quality state for render video
	bool				m_RenderVideo_HighQuality;
	// The socket toward the dedicated server
	CToDedicatedServerSocket* m_pToDedicatedServerSocket;

//************
// The methods
//************
public:
	// The constructor
	CHeroscapeEditorApp();
	// init the instance of the application
	virtual BOOL	InitInstance();
	// Inform each view that a tile is currently moving
	void			InformEachViewTileMoving( CTile* pTile, POINT Point, double DiffPosTileMouseX, double DiffPosTileMouseY );
	// Inform each view tha the user launch a tile
	bool			InformEachViewTileLaunch( CTile* pTile, POINT Point, double DiffPosTileMouseX, double DiffPosTileMouseY );
	// All the tile of all the document need to be unselect
	void			UnselectAllTile();
	// Save the informations on the ini file
	void			SaveIniFile();
	// Load the informations on the ini file
	void			LoadIniFile();
	// Create a char* from a unicode CString
	char*			GetAsciiString( CString Str );
	// Remove all tile of the clipboard and free memory
	void			RemoveClipboard();
	// The user want information about VirtualScape
	afx_msg void	OnAppAbout();
	// End of the application
	virtual int		ExitInstance();
	// The application is idle
	virtual BOOL	OnIdle(LONG lCount);
	// The user want change the material disponible
	afx_msg void	OnConfigurationMatDispo();
	// The user want change the configuration
	afx_msg void	OnConfigurationPreferency();
	// The user want display the help manual
	afx_msg void	OnGlobalHelp();
	// The user want configure personal tile
	afx_msg void	OnConfigurationTileperso();
	// The user want join a game
	afx_msg void	OnPlayJoingame();
	// We enter in game mode so hide unusefull tool windows
	void			EnterGameMode();
	// We exit the game mode so restore tool windows state
	void			ExitGameMode();
	// Add a chat message to the memory
	void			AddChatMessage( bool IsMine, CString From, CString Message );
	// Free the memory used by chat message
	void			FreeChatMessage();

// Substitutions
public:

// Implémentation
	DECLARE_MESSAGE_MAP()
};

extern CHeroscapeEditorApp theApp;