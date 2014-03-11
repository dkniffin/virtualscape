#ifndef _TILEDUNGEON1_H_
#define _TILEDUNGEON1_H_

#include "Tile.h"

class CTileDungeon1 : public CTile
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
	CTileDungeon1();
	// The destructor
	~CTileDungeon1();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// Draw more on a tile
	void			DrawExtendTile( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
};

#endif // #ifndef _TILEDUNGEON1_H_
