#ifndef _TILELAVAFIELD2_H_
#define _TILELAVAFIELD2_H_

#include "Tile.h"

class CTileLavaField2 : public CTile
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
	CTileLavaField2();
	// The destructor
	~CTileLavaField2();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// When the rotation change
	virtual void	OnRotationChange();
};

#endif // #ifndef _TILELAVAFIELD2_H_
