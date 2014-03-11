#pragma once

#include "General.h"
#include "HeroscapeEditor3DView.h"
#include "Point.h"

class CSmoke
{
public:
	// The different texture type
	enum SmokeColor
	{
		SC_BLACK = 0,
		SC_WHITE,
		SC_RED,
		SC_BLUE,
		SC_GREEN,
		SC_REDBLUE
	};

protected:
	// The current position
	MyPoint3D	m_Position;
	// The rotate speed
	double		m_Rotate;
	// The x,y,z speed
	double		m_MoveX, m_MoveY, m_MoveZ;
	// White smoke or not
	GLuint		m_SmokeTextureId;

public:
	// The constructor
	CSmoke( double PositionX, double PositionY, double PositionZ, SmokeColor aSmokeColor, CHeroscapeEditor3DView* pView  );
	// The destructor
	~CSmoke(void);
	// Render the object
	void Render( int ExplodeTime, CHeroscapeEditor3DView* pView, bool BindTexture );
};
