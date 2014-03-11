#ifndef _TILECASTLELADDER_H_
#define _TILECASTLELADDER_H_

#include "Tile.h"

class CTileCastleLadder : public CTile
{
//************
// The members
//************
protected:

//************
// The methods
//************
public:
	// The constructor
	CTileCastleLadder();
	// The destructor
	~CTileCastleLadder();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// Draw the tiles
	void			Draw( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
	// Render a tile 1 hexagon
	virtual void	Render1( void* pView, bool ForShadow, bool BindTexture );
	// Verify that something is under the tile
	virtual void	VerifySomethingUnderTile( void* pTheDoc );
};

#endif // #ifndef _TILECASTLELADDER_H_
