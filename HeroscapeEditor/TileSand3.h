#ifndef _TILESAND3_H_
#define _TILESAND3_H_

#include "Tile.h"

class CTileSand3 : public CTile
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
	CTileSand3();
	// The destructor
	~CTileSand3();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// When the rotation change
	virtual void	OnRotationChange();
};

#endif // #ifndef _TILESAND3_H_
