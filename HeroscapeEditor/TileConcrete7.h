#ifndef _TILECONCRETE7_H_
#define _TILECONCRETE7_H_

#include "Tile.h"

class CTileConcrete7 : public CTile
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
	CTileConcrete7();
	// The destructor
	~CTileConcrete7();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
};

#endif // #ifndef _TILECONCRETE7_H_
