#ifndef _TILESNOW1_H_
#define _TILESNOW1_H_

#include "Tile.h"

class CTileSnow1 : public CTile
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
	CTileSnow1();
	// The destructor
	~CTileSnow1();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
};

#endif // #ifndef _TILESNOW1_H_
