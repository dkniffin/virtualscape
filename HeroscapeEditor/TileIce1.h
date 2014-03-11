#ifndef _TILEICE1_H_
#define _TILEICE1_H_

#include "Tile.h"

class CTileIce1 : public CTile
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
	CTileIce1();
	// The destructor
	~CTileIce1();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
};

#endif // #ifndef _TILEICE1_H_
