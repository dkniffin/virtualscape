#ifndef _TILESWAMP1_H_
#define _TILESWAMP1_H_

#include "Tile.h"

class CTileSwamp1 : public CTile
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
	CTileSwamp1();
	// The destructor
	~CTileSwamp1();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
};

#endif // #ifndef _TILESWAMP1_H_
