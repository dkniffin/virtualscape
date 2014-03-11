#ifndef _TILEASPHALT1_H_
#define _TILEASPHALT1_H_

#include "Tile.h"

class CTileAsphalt1 : public CTile
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
	CTileAsphalt1();
	// The destructor
	~CTileAsphalt1();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
};

#endif // #ifndef _TILEASPHALT1_H_
