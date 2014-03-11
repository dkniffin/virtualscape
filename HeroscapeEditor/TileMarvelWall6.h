#ifndef _TILEMARVELWALL6_H_
#define _TILEMARVELWALL6_H_

#include "Tile.h"

class CTileMarvelWall6 : public CTile
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
	CTileMarvelWall6();
	// The destructor
	~CTileMarvelWall6();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// When the rotation change
	virtual void	OnRotationChange();
	// Draw more on a tile
	void			DrawExtend( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
	// Render a tile (3D view)
	virtual void	Render1( void* pView, bool ForShadow, bool BindTexture );
};

#endif // #ifndef _TILEMARVELWALL6_H_