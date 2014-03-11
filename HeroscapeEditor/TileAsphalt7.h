#ifndef _TILEASPHALT7_H_
#define _TILEASPHALT7_H_

#include "Tile.h"

class CTileAsphalt7 : public CTile
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
	CTileAsphalt7();
	// The destructor
	~CTileAsphalt7();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
};

#endif // #ifndef _TILEASPHALT7_H_
