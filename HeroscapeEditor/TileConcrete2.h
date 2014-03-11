#ifndef _TILECONCRETE2_H_
#define _TILECONCRETE2_H_

#include "Tile.h"

class CTileConcrete2 : public CTile
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
	CTileConcrete2();
	// The destructor
	~CTileConcrete2();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// When the rotation change
	virtual void	OnRotationChange();
};

#endif // #ifndef _TILECONCRETE2_H_
