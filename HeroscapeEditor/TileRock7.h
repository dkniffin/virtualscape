#ifndef _TILEROCK7_H_
#define _TILEROCK7_H_

#include "Tile.h"

class CTileRock7 : public CTile
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
	CTileRock7();
	// The destructor
	~CTileRock7();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
};

#endif // #ifndef _TILEROCK7_H_
