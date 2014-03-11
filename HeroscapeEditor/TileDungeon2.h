#ifndef _TILEDUNGEON2_H_
#define _TILEDUNGEON2_H_

#include "Tile.h"

class CTileDungeon2 : public CTile
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
	CTileDungeon2();
	// The destructor
	~CTileDungeon2();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// When the rotation change
	virtual void	OnRotationChange();
	// Draw more on a tile
	void			DrawExtendTile( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
};

#endif // #ifndef _TILEDUNGEON2_H_
