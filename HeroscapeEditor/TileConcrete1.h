#ifndef _TILECONCRETE1_H_
#define _TILECONCRETE1_H_

#include "Tile.h"

class CTileConcrete1 : public CTile
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
	CTileConcrete1();
	// The destructor
	~CTileConcrete1();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
};

#endif // #ifndef _TILECONCRETE1_H_
