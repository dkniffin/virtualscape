#ifndef _TILECASTLE7_H_
#define _TILECASTLE7_H_

#include "Tile.h"

class CTileCastle7 : public CTile
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
	CTileCastle7();
	// The destructor
	~CTileCastle7();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// When the rotation change
	virtual void	OnRotationChange();
	// Draw more on a tile
	void			DrawExtendTile( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
	// Verify that something is under the tile
	virtual void	VerifySomethingUnderTile( void* pTheDoc );
};

#endif // #ifndef _TILECASTLE7_H_
