#ifndef _TILEROAD1_H_
#define _TILEROAD1_H_

#include "Tile.h"

class CTileRoad1 : public CTile
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
	CTileRoad1();
	// The destructor
	~CTileRoad1();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// Draw more on a tile
	void			DrawExtendTile( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
};

#endif // #ifndef _TILEROAD1_H_
