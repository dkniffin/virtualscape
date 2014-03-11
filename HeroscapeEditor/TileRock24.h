#ifndef _TILEROCK24_H_
#define _TILEROCK24_H_

#include "Tile.h"

class CTileRock24 : public CTile
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
	CTileRock24();
	// The destructor
	~CTileRock24();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// When the rotation change
	virtual void	OnRotationChange();
};

#endif // #ifndef _TILEROCK24_H_
