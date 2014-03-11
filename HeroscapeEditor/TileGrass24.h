#ifndef _TILEGRASS24_H_
#define _TILEGRASS24_H_

#include "Tile.h"

class CTileGrass24 : public CTile
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
	CTileGrass24();
	// The destructor
	~CTileGrass24();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// When the rotation change
	virtual void	OnRotationChange();
};

#endif // #ifndef _TILEGRASS24_H_
