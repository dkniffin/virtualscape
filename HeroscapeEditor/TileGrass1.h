#ifndef _TILEGRASS1_H_
#define _TILEGRASS1_H_

#include "Tile.h"

class CTileGrass1 : public CTile
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
	CTileGrass1();
	// The destructor
	~CTileGrass1();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
};

#endif // #ifndef _TILEGRASS1_H_
