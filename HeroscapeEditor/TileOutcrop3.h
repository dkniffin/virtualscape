#ifndef _TILEOUTCROP3_H_
#define _TILEOUTCROP3_H_

#include "Tile.h"

class CTileOutcrop3 : public CTile
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
	CTileOutcrop3();
	// The destructor
	~CTileOutcrop3();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// When the rotation change
	virtual void	OnRotationChange();
	// Draw more on a tile
	void			DrawExtend( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
	// Render a tile (3D view)
	virtual void	Render1( void* pView, bool ForShadow, bool BindTexture );
};

#endif // #ifndef _TILEOUTCROP3_H_
