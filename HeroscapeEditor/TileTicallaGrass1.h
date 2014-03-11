#ifndef _TILETICALLAGRASS1_H_
#define _TILETICALLAGRASS1_H_

#include "Tile.h"

class CTileTicallaGrass1 : public CTile
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
	CTileTicallaGrass1();
	// The destructor
	~CTileTicallaGrass1();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// Draw more on a tile
	void			DrawExtend( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
	// Render a tile 1 hexagon
	virtual void	Render1( void* pView, bool ForShadow, bool BindTexture );
};

#endif // #ifndef _TILETICALLAGRASS1_H_
