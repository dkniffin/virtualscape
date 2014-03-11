#ifndef _TILESHADOW2_H_
#define _TILESHADOW2_H_

#include "Tile.h"

class CTileShadow2 : public CTile
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
	CTileShadow2();
	// The destructor
	~CTileShadow2();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// Render a tile
	void			Render1( void* pView, bool ForShadow, bool BindTexture );
};

#endif // #ifndef _TILESHADOW2_H_
