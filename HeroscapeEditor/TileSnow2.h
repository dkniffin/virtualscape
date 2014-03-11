#ifndef _TILESNOW2_H_
#define _TILESNOW2_H_

#include "Tile.h"

class CTileSnow2 : public CTile
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
	CTileSnow2();
	// The destructor
	~CTileSnow2();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// When the rotation change
	virtual void	OnRotationChange();
};

#endif // #ifndef _TILESNOW2_H_
