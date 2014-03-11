#ifndef _TILENUMBER_H_
#define _TILENUMBER_H_

#include "Tile.h"

class CTileNumber : public CTile
{
//************
// The members
//************
public:
	// The drawing text
	CString		m_Text;

//************
// The methods
//************
public:
	// The constructor
	CTileNumber();
	// The destructor
	~CTileNumber();
	// Get a copy of this tile
	virtual CTile*	GetCopy();
	// Draw more on a tile
	void			DrawExtend( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel);
};

#endif // #ifndef _TILENUMBER_H_
