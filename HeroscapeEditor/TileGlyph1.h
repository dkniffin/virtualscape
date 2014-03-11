#ifndef _TILEGLYPH1_H_
#define _TILEGLYPH1_H_

#include "Tile.h"

class CTileGlyph1 : public CTile
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
	CTileGlyph1( char Letter );
	// The destructor
	~CTileGlyph1();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// Draw more on a tile
	void			DrawExtend( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
};

#endif // #ifndef _TILEGLYPH1_H_
