#ifndef _TILESWAMP7_H_
#define _TILESWAMP7_H_

#include "Tile.h"

class CTileSwamp7 : public CTile
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
	CTileSwamp7();
	// The destructor
	~CTileSwamp7();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
};

#endif // #ifndef _TILESWAMP7_H_
