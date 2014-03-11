#ifndef _TILERUIN3_H_
#define _TILERUIN3_H_

#include "Tile.h"

class CTileRuin3 : public CTile
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
	CTileRuin3();
	// The destructor
	~CTileRuin3();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// When the rotation change
	virtual void	OnRotationChange();
	// Draw the tiles
	virtual void	Draw( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
	// Render a tile
	virtual void	Render1( void* pView, bool ForShadow, bool BindTexture );
};

#endif // #ifndef _TILERUIN3_H_
