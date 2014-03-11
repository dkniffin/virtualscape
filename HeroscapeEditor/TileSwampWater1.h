#ifndef _TILESWAMPWATER1_H_
#define _TILESWAMPWATER1_H_

#include "Tile.h"

class CTileSwampWater1 : public CTile
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
	CTileSwampWater1();
	// The destructor
	~CTileSwampWater1();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
};

#endif // #ifndef _TILESWAMPWATER1_H_
