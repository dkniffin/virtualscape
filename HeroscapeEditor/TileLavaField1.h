#ifndef _TILELAVAFIELD1_H_
#define _TILELAVAFIELD1_H_

#include "Tile.h"

class CTileLavaField1 : public CTile
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
	CTileLavaField1();
	// The destructor
	~CTileLavaField1();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
};

#endif // #ifndef _TILELAVAFIELD1_H_
