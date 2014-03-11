#ifndef _TILEWATER1_H_
#define _TILEWATER1_H_

#include "Tile.h"

class CTileWater1 : public CTile
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
	CTileWater1();
	// The destructor
	~CTileWater1();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
};

#endif // #ifndef _TILEWATER1_H_
