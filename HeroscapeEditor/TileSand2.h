#ifndef _TILESAND2_H_
#define _TILESAND2_H_

#include "Tile.h"

class CTileSand2 : public CTile
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
	CTileSand2();
	// The destructor
	~CTileSand2();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// When the rotation change
	virtual void	OnRotationChange();
};

#endif // #ifndef _TILESAND2_H_
