#pragma once

#include "ArmyCard.h"
#include "Object3D.h"
#include "Tile.h"

class CFigureObject
{
//************
// The members
//************
public:
	// The figure name
	CString		m_FigureName;
	// The figure file
	CString		m_FigureFile;
	// The CTileFigure object
	CTile*		m_pTileFigure;
	// The CObject3D;
	CObject3D*	m_pObject;
	// The basic figure life point
	int			m_BasicLifePoint;
	// The expert figure life point
	int			m_ExpertLifePoint;
	// The current life point
	int			m_CurrentLifePoint;
	// To know if the figure is placed on map or not
	bool		m_IsPlacedOnMap;
	// To know if this figure use two hex
	bool		m_UseTwoHex;
	// The corresponding army card
	CArmyCard*	m_pArmyCard;

//************
// The methods
//************
public:
	// The constructor
	CFigureObject( bool UseTwoHex, CString FigureName, CString FigureFile, CArmyCard* pArmyCard );
	// The destructor
	~CFigureObject(void);
};
