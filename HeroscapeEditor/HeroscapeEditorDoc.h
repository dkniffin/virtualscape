// HeroscapeEditorDoc.h : interface de la classe CHeroscapeEditorDoc
//

#ifndef _HEROSCAPEEDITORDOC_H_
#define _HEROSCAPEEDITORDOC_H_

#include "Tile.h"
#include "TilePerso.h"

class CHeroscapeEditorDoc : public CDocument
{
	DECLARE_DYNCREATE(CHeroscapeEditorDoc)

//**********
// The enums
//**********
public:
enum InformationBarType
{
	IB_INFO=0,
	IB_WARNING,
	IB_CRITICAL
};

//************
// The structs
//************
public:
struct InformationDatas
{
	int	x;
	int y;
	int z;
};

//************
// The members
//************
public:
	// The battle field name
	CString		m_Name;
	// The battle field author
	CString		m_Author;
	// The tile list
	CPtrArray	m_TileList;
	// The number of player for this battlefield
	CString		m_PlayerNumber;
	// The scenario
	CString		m_Scenario;
	// The scenario
	char*		m_MyScenario;
	int			m_MyScenarioLen;
	// The number of used tile
	int			m_MaterialNb[30000];
	// The level max
	int			m_LevelMax;
	// The printing params
	int			m_XOffset, m_YOffset;
	int			m_XWidth, m_YHeight;
	// The number of level by page for printing
	int			m_NbLevelByPage;
	// The transparency for printing
	int			m_PrintingTransparency;
	// Display or not the grid on printing
	BOOL		m_PrintingGrid;
	// Print or not the tile number (at the beginning of the scenario)
	BOOL		m_PrintTileNumber;
	// To know the size of the document
	double		m_FirstX, m_FirstY, m_LastX, m_LastY;
	// The number of information line
	int			m_NbInfo;
	// The number of warning line
	int			m_NbWarning;
	// The number of critical line
	int			m_NbCritical;
	// Use for print scenario in a richedit control
	int			m_ScenarioWriteBufferPos;
	// Use for print to know if the level has start area
	bool		m_HasStartArea;
	// To know if we must print start area as level
	BOOL		m_b_PrintStartAreaAsLevel;

//************
// The methods
//************
protected:
	// The constructor
	CHeroscapeEditorDoc();
	// Erase the information windows
	void			EraseInformation();

public:
	// The destructor
	virtual			~CHeroscapeEditorDoc();
	// Inform each view that a tile is currently moving
	void			InformEachViewTileMoving( CTile* pTile, POINT Point, double DiffPosTileMouseX, double DiffPosTileMouseY );
	// Inform each view that a tile is launch
	bool			InformEachViewTileLaunch( CTile* pTile, POINT Point, double DiffPosTileMouseX, double DiffPosTileMouseY );
	// A new document is created
	virtual BOOL	OnNewDocument();
	// Save or load the document
	virtual void	Serialize(CArchive& ar);
	// Redraw all the views
	void			RedrawAllViews();
	// Redraw all the views
	void			UpdateAll3DViews();
	// Unselect all tile of the document
	void			UnselectAllTile();
	// Return the nb selected tile
	int				GetNbSelectedTile();
	// Load the document
	void			LoadVersion0_0001( CArchive& ar );
	// Load the document
	void			LoadVersion0_0002( CArchive& ar );
	// Load the document
	void			LoadVersion0_0003( CArchive& ar );
	// Load the document
	void			LoadVersion0_0004( CArchive& ar );
	// Load the document
	void			LoadVersion0_0005( CArchive& ar );
	// Load the document
	void			LoadVersion0_0006( CArchive& ar );
	// Load the document (same as 0006 but with dungeon set add)
	void			LoadVersion0_0007( CArchive& ar );
	// Rotate the selection to left
	void			RotateSelectionLeft();
	// Rotate the selection to right
	void			RotateSelectionRight();
	// Remove all the selected tile
	void			RemoveSelection();
	// Add a tile to the document
	void			AddTile( CTile* pTile );
	// Prepare the printing job
	BOOL			OnPreparePrinting(CPrintInfo* pInfo);
	// Compute the level Max
	void			ComputeLevelMax();
	// To know if the map contains start area
	BOOL			ContainsStartArea();
	// Begin printing job
	void			OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	// Compute the area of the battlefield
	void			ComputeArea(bool WithNumberDisplayed);
	// Print the document
	void			OnPrint(CDC* pDC, CPrintInfo* pInfo);
	// Print the document with num
	void			OnPrintNum(CDC* pDC, CPrintInfo* pInfo);
	// Draw the first page
	void			DrawFirstPage( CDC* pDC );
	// Draw the last page
	void			DrawLastPage( CDC* pDC );
	// Write the data to the richedit text for scenario
	static DWORD CALLBACK MyStreamInCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
	// Draw a level
	void			DrawLevel( CDC* pDC, int Level, int OffsetX, int OffsetY, int Width, int Height );
	// Draw last level with num
	void			DrawWithNum( CDC* pDC, int OffsetX, int OffsetY, int Width, int Height );
	// To know if a position is used
	bool			IsPositionUsed( int PosX, int PosY, int PosZ );
	// Add a line on the information view
	void			AddInformation( int Type, int Level, CString TileName, CString Text, int x, int y, int z );
	// Return the nb of master set
	int				ComputeNbMasterSet();
	// Return the nb of volcarren set
	int				ComputeNbVolcarrenSet();
	// Return the nb of glacier set
	int				ComputeNbGlacierSet();
	// Return the nb of forest set
	int				ComputeNbForestSet();
	// Return the nb of castle set
	int				ComputeNbCastleSet();
	// Return the nb of tile of this type
	int				GetNbTileType( int Type );
	// Load all the necesary objects (as figures)
	void			LoadNecessaryObjects( void* pView );
	// Display the selected tile count in the status bar
	void			DisplaySelectedCount();
	// Get the number of personal tile of a particular type
	int				GetPersonalTileOfType( CTilePerso* pTilePerso );
	// Remove a tile from the document
	void			RemoveTileIndex( int Index );

//*****************
// Generate by VC++
//*****************

// Fonctions générées de la table des messages
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DeleteContents();
public:
	afx_msg void OnNew3dview();
public:
	afx_msg void OnConfigurationParamdoc();
public:
	afx_msg void OnDocCheck();
public:
	afx_msg void OnEditionCopier();
public:
	afx_msg void OnEditionCouper();
public:
	afx_msg void OnEditionColler();
public:
	afx_msg void OnUpdateEditionColler(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateEditionCopier(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateEditionCouper(CCmdUI *pCmdUI);
public:
	afx_msg void OnPlayCreategame();
};

#endif //#ifndef _HEROSCAPEEDITORDOC_H_
