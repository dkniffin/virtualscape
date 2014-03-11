#ifndef _TILECASTLE1_H_
#define _TILECASTLE1_H_

#include "Tile.h"

class CTileCastle1 : public CTile
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
	CTileCastle1();
	// The destructor
	~CTileCastle1();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// Draw more on a tile
	void			DrawExtendTile( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
	// Verify that something is under the tile
	virtual void	VerifySomethingUnderTile( void* pTheDoc );
};

#endif // #ifndef _TILECASTLE1_H_
