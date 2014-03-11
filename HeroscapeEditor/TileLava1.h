#ifndef _TILELAVA1_H_
#define _TILELAVA1_H_

#include "Tile.h"

class CTileLava1 : public CTile
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
	CTileLava1();
	// The destructor
	~CTileLava1();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
};

#endif // #ifndef _TILELAVA1_H_
