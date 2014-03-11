#ifndef _TILECASTLEBASECORNER_H_
#define _TILECASTLEBASECORNER_H_

#include "Tile.h"

class CTileCastleBaseCorner : public CTile
{
//************
// The members
//************
protected:
	// The second color
	COLORREF	m_TileColor2;

//************
// The methods
//************
public:
	// The constructor
	CTileCastleBaseCorner();
	// The destructor
	~CTileCastleBaseCorner();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// Draw the tiles
	void			Draw( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
	// Draw the surround tiles
	void			DrawSurround( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
	// Draw more on a tile
	void			DrawExtend( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
	// Render a tile 1 hexagon
	virtual void	Render1( void* pView, bool ForShadow, bool BindTexture );
	// Fill the members with members of an other tile
	virtual void	FillCopy( CTile* pTile );
};

#endif // #ifndef _TILECASTLEBASECORNER_H_
