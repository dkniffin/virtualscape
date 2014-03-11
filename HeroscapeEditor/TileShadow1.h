#ifndef _TILESHADOW1_H_
#define _TILESHADOW1_H_

#include "Tile.h"

class CTileShadow1 : public CTile
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
	CTileShadow1();
	// The destructor
	~CTileShadow1();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
};

#endif // #ifndef _TILESHADOW1_H_
