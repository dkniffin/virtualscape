#ifndef _TILEGRASS7_H_
#define _TILEGRASS7_H_

#include "Tile.h"

class CTileGrass7 : public CTile
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
	CTileGrass7();
	// The destructor
	~CTileGrass7();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
};

#endif // #ifndef _TILEGRASS7_H_
