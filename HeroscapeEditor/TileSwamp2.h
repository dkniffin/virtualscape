#ifndef _TILESWAMP2_H_
#define _TILESWAMP2_H_

#include "Tile.h"

class CTileSwamp2 : public CTile
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
	CTileSwamp2();
	// The destructor
	~CTileSwamp2();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// When the rotation change
	virtual void	OnRotationChange();
};

#endif // #ifndef _TILESWAMP2_H_
