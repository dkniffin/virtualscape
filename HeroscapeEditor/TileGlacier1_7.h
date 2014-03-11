#ifndef _TILEGLACIER1_7_H_
#define _TILEGLACIER1_7_H_

#include "Tile.h"

class CTileGlacier1_7 : public CTile
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
	CTileGlacier1_7();
	// The destructor
	~CTileGlacier1_7();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// Draw more on a tile
	void			DrawExtend( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
	// Render a tile (3D view)
	virtual void	Render1( void* pView, bool ForShadow, bool BindTexture );
};

#endif // #ifndef _TILEGLACIER1_7_H_
