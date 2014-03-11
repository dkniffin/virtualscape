#ifndef _TILEROCK2_H_
#define _TILEROCK2_H_

#include "Tile.h"

class CTileRock2 : public CTile
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
	CTileRock2();
	// The destructor
	~CTileRock2();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// When the rotation change
	virtual void	OnRotationChange();
};

#endif // #ifndef _TILEROCK2_H_
