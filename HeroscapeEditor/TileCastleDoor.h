#ifndef _TILECASTLEDOOR_H_
#define _TILECASTLEDOOR_H_

#include "Tile.h"

class CTileCastleDoor : public CTile
{
//************
// The members
//************
protected:
	// The second color
	COLORREF	m_TileColor2;

//************
// The methods
//************
public:
	// The constructor
	CTileCastleDoor();
	// The destructor
	~CTileCastleDoor();
	// Draw the tiles
	void			Draw( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// When the rotation change
	virtual void	OnRotationChange();
	// Render a tile
	virtual void	Render1( void* pView, bool ForShadow, bool BindTexture );
	// Fill the members with members of an other tile
	virtual void	FillCopy( CTile* pTile );
};

#endif // #ifndef _TILECASTLEDOOR_H_
