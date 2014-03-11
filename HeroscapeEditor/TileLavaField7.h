#ifndef _TILELAVAFIELD7_H_
#define _TILELAVAFIELD7_H_

#include "Tile.h"

class CTileLavaField7 : public CTile
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
	CTileLavaField7();
	// The destructor
	~CTileLavaField7();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
};

#endif // #ifndef _TILELAVAFIELD7_H_
