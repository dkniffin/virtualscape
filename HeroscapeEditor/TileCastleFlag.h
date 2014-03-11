#ifndef _TILECASTLEFLAG_H_
#define _TILECASTLEFLAG_H_

#include "Tile.h"

class CTileCastleFlag : public CTile
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
	CTileCastleFlag();
	// The destructor
	~CTileCastleFlag();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// Draw the tiles
	void			Draw( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
	// Render a tile 1 hexagon
	virtual void	Render1( void* pView, bool ForShadow, bool BindTexture );
	// Verify that something is under the tile
	virtual void	VerifySomethingUnderTile( void* pTheDoc );
};

#endif // #ifndef _TILECASTLEFLAG_H_
