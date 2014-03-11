#ifndef _TILEWATER2_H_
#define _TILEWATER2_H_

#include "Tile.h"

class CTileWater2 : public CTile
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
	CTileWater2();
	// The destructor
	~CTileWater2();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// Render a tile
	void			Render1( void* pView, bool ForShadow, bool BindTexture );
};

#endif // #ifndef _TILEWATER2_H_
