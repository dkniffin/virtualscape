#ifndef _TILESTART1_H_
#define _TILESTART1_H_

#include "Tile.h"

class CTileStart1 : public CTile
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
	CTileStart1( CString Name, COLORREF Color );
	// The destructor
	~CTileStart1();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// Draw the tiles
	virtual void	Draw( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
	// Render a tile 1 hexagon
	void			Render1( void* pView, bool ForShadow, bool BindTexture );
};

#endif // #ifndef _TILESTART1_H_
