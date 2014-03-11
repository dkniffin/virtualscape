#ifndef _TILEROCK1_H_
#define _TILEROCK1_H_

#include "Tile.h"

class CTileRock1 : public CTile
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
	CTileRock1();
	// The destructor
	~CTileRock1();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
};

#endif // #ifndef _TILEROCK1_H_
