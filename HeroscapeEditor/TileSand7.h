#ifndef _TILESAND7_H_
#define _TILESAND7_H_

#include "Tile.h"

class CTileSand7 : public CTile
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
	CTileSand7();
	// The destructor
	~CTileSand7();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
};

#endif // #ifndef _TILESAND7_H_
