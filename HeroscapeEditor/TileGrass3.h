#ifndef _TILEGRASS3_H_
#define _TILEGRASS3_H_

#include "Tile.h"

class CTileGrass3 : public CTile
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
	CTileGrass3();
	// The destructor
	~CTileGrass3();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// When the rotation change
	virtual void	OnRotationChange();
};

#endif // #ifndef _TILEGRASS3_H_
