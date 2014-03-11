#ifndef _TILESWAMP3_H_
#define _TILESWAMP3_H_

#include "Tile.h"

class CTileSwamp3 : public CTile
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
	CTileSwamp3();
	// The destructor
	~CTileSwamp3();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// When the rotation change
	virtual void	OnRotationChange();
};

#endif // #ifndef _TILESWAMP3_H_
