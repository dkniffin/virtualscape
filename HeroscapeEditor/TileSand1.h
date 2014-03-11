#ifndef _TILESAND1_H_
#define _TILESAND1_H_

#include "Tile.h"

class CTileSand1 : public CTile
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
	CTileSand1();
	// The destructor
	~CTileSand1();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
};

#endif // #ifndef _TILESAND1_H_
