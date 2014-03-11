#include "StdAfx.h"

#include "FigureObject.h"
#include "TileFigure.h"
#include "TileFigure2.h"

// The constructor
//
CFigureObject::CFigureObject( bool UseTwoHex, CString FigureName, CString FigureFile, CArmyCard* pArmyCard )
:
m_IsPlacedOnMap(false)
{
	m_FigureName = FigureName;
	m_FigureFile = FigureFile;

	m_UseTwoHex = UseTwoHex;
	if( m_UseTwoHex )
	{
		m_pTileFigure = new CTileFigure2;
		((CTileFigure2*) m_pTileFigure)->m_FigureName = m_FigureName;
		((CTileFigure2*) m_pTileFigure)->m_FigureFile = m_FigureFile;
	}
	else
	{
		m_pTileFigure = new CTileFigure;
		((CTileFigure*) m_pTileFigure)->m_FigureName = m_FigureName;
		((CTileFigure*) m_pTileFigure)->m_FigureFile = m_FigureFile;
	}

	m_pArmyCard = pArmyCard;
}

// The destructor
//
CFigureObject::~CFigureObject(void)
{
}
