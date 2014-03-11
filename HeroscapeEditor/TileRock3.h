#ifndef _TILEROCK3_H_
#define _TILEROCK3_H_

#include "Tile.h"

class CTileRock3 : public CTile
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
	CTileRock3();
	// The destructor
	~CTileRock3();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// When the rotation change
	virtual void	OnRotationChange();
};

#endif // #ifndef _TILEROCK3_H_
