#ifndef _TILEGRASS2_H_
#define _TILEGRASS2_H_

#include "Tile.h"

class CTileGrass2 : public CTile
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
	CTileGrass2();
	// The destructor
	~CTileGrass2();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// When the rotation change
	virtual void	OnRotationChange();
};

#endif // #ifndef _TILEGRASS2_H_
