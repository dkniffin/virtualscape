#ifndef _TILEFIGURE_H_
#define _TILEFIGURE_H_

#include "HeroscapeEditor3DView.h"
#include "Tile.h"

class CTileFigure : public CTile
{
//************
// The members
//************
protected:
	// The smoke objects for explode
	CPtrArray	m_SmokeList;
	// The smoke objects for exploded dice
	CPtrArray*	m_SmokeDiceList[100];

//************
// The methods
//************
public:
	// The constructor
	CTileFigure();
	// The destructor
	~CTileFigure();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// Get the name of the tile
	CString			GetName();
	// Render the tile
	virtual void	Render1( void* pView, bool ForShadow, bool BindTexture );
	// Draw more on a tile
	void			DrawExtendTile( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
	// Load the necessary object
	virtual void	LoadNecessaryObjects( void* pView );
	// To know if this tile is available for a game
	virtual bool	IsGameAvailable();
	// Generate smoke for an explode figure
	void			GenerateSmokeForExplode( CHeroscapeEditor3DView* pView );
	// Generate smoke for an explode dice
	void			GenerateSmokeForDice( CHeroscapeEditor3DView* pView, int DiceIndex );
	// Delete smoke object
	void			DeleteSmokeObjects();
	// Delete smoke dice
	void			DeleteSmokeDice();
	// Render explode
	void			RenderExplode( void* pView, bool BindTexture );
	// Render explode dice
	void			RenderExplodeDice( void* pView, bool BindTexture, int DiceIndex, double Time );
};

#endif // #ifndef _TILEFIGURE_H_
