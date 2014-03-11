#ifndef _TILESWAMP24_H_
#define _TILESWAMP24_H_

#include "Tile.h"

class CTileSwamp24 : public CTile
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
	CTileSwamp24();
	// The destructor
	~CTileSwamp24();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// When the rotation change
	virtual void	OnRotationChange();
};

#endif // #ifndef _TILESWAMP24_H_
