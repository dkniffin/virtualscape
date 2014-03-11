#ifndef _TILEPALM16_H_
#define _TILEPALM16_H_

#include "Tile.h"

class CTilePalm16 : public CTile
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
	CTilePalm16();
	// The destructor
	~CTilePalm16();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// Draw more on a tile
	void			DrawExtend( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
	// Render a tile 1 hexagon
	virtual void	Render1( void* pView, bool ForShadow, bool BindTexture );
};

#endif // #ifndef _TILEPALM16_H_
