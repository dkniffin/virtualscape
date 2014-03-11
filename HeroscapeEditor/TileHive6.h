#ifndef _TILEHIVE6_H_
#define _TILEHIVE6_H_

#include "Tile.h"

class CTileHive6 : public CTile
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
	CTileHive6();
	// The destructor
	~CTileHive6();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// When the rotation change
	virtual void	OnRotationChange();
	// Render a tile (3D view)
	virtual void	Render1( void* pView, bool ForShadow, bool BindTexture );
};

#endif // #ifndef _TILEHIVE6_H_
