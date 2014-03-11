#ifndef _TILEASPHALT2_H_
#define _TILEASPHALT2_H_

#include "Tile.h"

class CTileAsphalt2 : public CTile
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
	CTileAsphalt2();
	// The destructor
	~CTileAsphalt2();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// When the rotation change
	virtual void	OnRotationChange();
};

#endif // #ifndef _TILEASPHALT2_H_
