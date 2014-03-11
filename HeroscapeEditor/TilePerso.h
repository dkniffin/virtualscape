#ifndef _TILEPERSO_H_
#define _TILEPERSO_H_

#include "Tile.h"

class CTilePerso : public CTile
{
//************
// The members
//************
public:
	// The name
	CString m_Name;
	// The quantity
	int		m_Quantity;
	// The char
	CString	m_Char;

//************
// The methods
//************
public:
	// The constructor
	CTilePerso();
	// The destructor
	~CTilePerso();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// When the rotation change
	virtual void	OnRotationChange();
	// Get the name of the tile
	CString			GetName();
	// Draw more on a tile
	void			DrawExtend( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
	// Fill the members with members of an other tile
	virtual void	FillCopy( CTile* pTile );
};

#endif // #ifndef _TILEPERSO_H_
