#ifndef _TILE_H_
#define _TILE_H_

#include "GL\gl.h"

#include "ClientSocket.h"
#include "General.h"
#include "ServerSocket.h"

class CTile : public CObject
{
//************
// The defines
//************
#define TC_BASIC		0
#define	TC_TUNDRA		1
#define	TC_FORTRESS		2
#define	TC_ROAD			3
#define	TC_VOLCARREN	4
#define	TC_TICALLA		5
#define	TC_GLYPH		6
#define	TC_STARTAREA	7
#define	TC_MARVEL		8
#define TC_SWARM		9
#define TC_FIGURE		10
#define TC_PERSONAL_HEX	11
#define TC_DUNGEON		12

#define	TYPE_GRASS		1
#define	TYPE_ROCK		2
#define	TYPE_SAND		3
#define	TYPE_WATER		4
#define	TYPE_ICE		5
#define	TYPE_LAVA		6
#define	TYPE_LAVAFIELD	7
#define	TYPE_ROAD		8
#define TYPE_SNOW		9
#define	TYPE_TREE		10
#define	TYPE_RUIN		11
#define	TYPE_WALL		12
#define	TYPE_GLACIER	13
#define	TYPE_GLYPH		14
#define	TYPE_STARTAREA	15
#define	TYPE_CASTLE		16
#define	TYPE_PERSONAL	17
#define	TYPE_FIGURE		18
#define	TYPE_SWAMPWATER 19
#define TYPE_SWAMP		20
#define TYPE_CONCRETE	21
#define TYPE_ASPHALT	22
#define TYPE_HIVE		23
#define TYPE_TICALLA	24
#define TYPE_SHADOW		25
#define TYPE_DUNGEON	26
#define TYPE_OUTCROP	27

#define TILE3D_X1		-0.8660254
#define TILE3D_X2		0
#define	TILE3D_X3		0.8660254
#define TILE3D_Y1		1
#define TILE3D_Y2		0.5
#define	TILE3D_Y3		-0.5
#define	TILE3D_Y4		-1
#define TILE3D_WIDTH	1.7320508
#define	TILE3D_HEIGHT	1.5
#define	TILE3D_ZHEIGHT	0.4
#define	TILE3D_ZHEIGHT2	0.15

#define TILE3D_NX1		-0.5
#define	TILE3D_NY1		0.8660254
#define TILE3D_NX2		0.5
#define	TILE3D_NY2		0.8660254
#define TILE3D_NX3		1
#define	TILE3D_NY3		0
#define TILE3D_NX4		0.5
#define	TILE3D_NY4		-0.8660254
#define TILE3D_NX5		-0.5
#define	TILE3D_NY5		-0.8660254
#define TILE3D_NX6		-1
#define	TILE3D_NY6		0

#define	SCALE			2.574
#define	TILE_REAL_WIDTH_X_CM	TILE3D_WIDTH*SCALE
#define	TILE_REAL_HEIGHT1_CM	1.5*SCALE
#define	TILE_REAL_HEIGHT2_CM	2*SCALE

//************
// The structs
//************
protected:

struct Target
{
	// The destination point
	MyPoint3D	TargetPoint;
	// The time of launch
	__int64		LaunchTime;
	// The current position of the weapon
	MyPoint3D	CurrentPosition;
	// The target speed
	__int64		Speed;
	// The target speed 2 (explosion)
	__int64		Speed2;
	// The current time
	__int64		CurrentTime;
};

//************
// The members
//************
public:
	// The size of the tile in pixel
	int			m_PixelSizeX;
	int			m_PixelSizeY;
	// The current rotation (0 to 5)
	int			m_CurrentRotation;
	// The number of tile
	int			m_NbTile;
	// The position of each tile
	POINT		m_TilePosition[24];
	// The tile color
	COLORREF	m_TileColor;
	// The printing transparency for printer
	double		m_PrintingTransparency;
	// The tile position in the battelfield
	int			m_PosX, m_PosY, m_PosZ;
	// The tile height
	int			m_Height;
	// To know if the tile is selected or not
	bool		m_IsSelected;
	// To know if tile must be displayed or not
	bool		m_ToDisplay;
	// The tile type
	int			m_Type;
	// The tile height in Z coordinate (for 3D view)
	double		m_TileHeight;
	// For glyph
	char		m_GlyphLetter;
	// For start
	CString		m_StartName;
	// The texture Id
	GLuint		m_TextureId;
	// The texture side Id
	GLuint		m_TextureSideId;
	// The texture file
	CString		m_PersonalTexture;
	// The texture file for side
	CString		m_PersonalTextureSide;
	// The figure name
	CString		m_FigureName;
	// The figure file
	CString		m_FigureFile;
	// The beginning point for attack
	MyPoint3D	m_AttackSource;
	// For optimise drawing
	POINT		m_Points[100];
	POINT		m_Points2[100];
	// To know if points are already computed
	bool		m_PointComputed;
	// At which size the points are already computed
	int			m_XComputed,m_X2Computed,m_YComputed;
	// The number of point for optimisation
	int			m_NbPoint;
	// To know if this is an attack figure
	bool		m_IsAttackFigure;
	// To know if this is a defense figure
	bool		m_IsDefenseFigure;
	// The explode time
	double		m_ExplodeTime;
	// The creation time
	double		m_CreationTime;
	// The number of dice
	int			m_DiceNumber;
	// The attack time
	double		m_AttackTime;
	// Life time of one dice on attack mode
	double		m_AttackTimeOnDice;

protected:
	// The target list
	CPtrArray		m_TargetList;

//************
// The methods
//************
public:
	// The constructor
	CTile();
	// The destructor
	~CTile();
	// Draw the tiles
	virtual void	Draw( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
	// Draw the tiles at the upper level
	virtual void	DrawOnionSkinMode( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
	// Draw a tile
	void			DrawTile( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4);
	// Draw more on each hex
	virtual void	DrawExtendTile( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
	// Draw more on the entire tile
	virtual void	DrawExtend( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
	// Draw the sample of the tile
	void			DrawSample( CDC* pDC, int x, int y );
	// Draw num
	void			DrawNum( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, double OffsetX, double OffsetY);
	// Get a copy of this tile
	virtual CTile*	GetCopy()=0;
	// Get an exact copy of this tile (with placement and other)
	virtual CTile*	GetExactCopy();
	// Fill the members with members of an other tile
	virtual void	FillCopy( CTile* pTile );
	// Init the tile
	void			Init();
	// To know if this tile contain this position on the battlefield
	bool			ContainPos( int PosX, int PosY );
	// Rotate left
	void			RotateLeft();
	// Rotate right
	void			RotateRight();
	// When the rotation change
	virtual void	OnRotationChange();
	// Get a new tyle of a particular type
	static CTile*	GetNewTile( int Type );
	// Load the tile
	void			LoadVersion0_0003( CArchive& ar );
	// Load the tile
	void			LoadVersion0_0002( CArchive& ar );
	// Load the tile
	void			LoadVersion0_0001( CArchive& ar );
	// Get the name of the tile
	virtual CString	GetName();
	// Render for 3D View
	virtual void	Render( void* pView, bool ForShadow=false, bool BindTexture=false );
	// Render a tile 1 hexagon
	virtual void	Render1( void* pView, bool ForShadow, bool BindTexture );
	// Verify a tile
	virtual void	Verify( void* pTheDoc );
	// Verify that something is under the tile
	virtual void	VerifySomethingUnderTile( void* pTheDoc );
	// Verify that there arn't another tile at the same place
	virtual void	VerifyOtherTileAtSamePlace( void* pTheDoc );
	// Get the low color depending of level
	double			GetLowColor( int DrawingLevel );
	// Load the necessary object
	virtual void	LoadNecessaryObjects( void* pView );
	// Begin to define the targets points
	virtual void	BeginTargetPoint( double BeginX, double BeginY, double BeginZ);
	// Add a target point
	virtual void	AddTargetPoint( double TargetX, double TargetY, double TargetZ);
	// End to define the targets points
	virtual void	EndTargetPoint();
	// Free memory used by  all target
	void			FreeAllTargets();
	// Compute the new position of all the weapon
	bool			ComputeWeapons();
	// Render the weapon if necessary
	void			RenderWeapons();
	// To know if this tile is available for a game
	virtual bool	IsGameAvailable();
	// Send the tile by socket
	virtual void	SendBySocket( CServerSocket* pSocket );
	// Receive the tile by socket
	virtual void	ReceiveBySocket( CClientSocket* pSocket );
	// Reset the texture id
	void			ResetTextureId();
	// Set the selected state
	void			SetSelectedState( bool State );
	// Generate smoke for an explode tile
	virtual void	GenerateSmokeForExplode();
	// delete smoke objects
	virtual void	DeleteSmokeObjects();
	// delete smoke from dice
	virtual void	DeleteSmokeDice();
	// Render explode if necessary
	virtual void	RenderExplode( void* pView, bool BindTexture );

public:
	virtual void Serialize(CArchive& ar);
};

#endif // #ifndef _TILE_H_
