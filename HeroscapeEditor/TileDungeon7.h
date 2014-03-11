#ifndef _TILEDUNGEON7_H_
#define _TILEDUNGEON7_H_

#include "Tile.h"

class CTileDungeon7 : public CTile
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
	CTileDungeon7();
	// The destructor
	~CTileDungeon7();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// Draw more on a tile
	void			DrawExtendTile( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
};

#endif // #ifndef _TILEDUNGEON7_H_
