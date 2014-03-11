#include "StdAfx.h"

#include "ArmyCardGardesZettiens.h"
#include "FigureObject.h"
#include "Resource.h"

// The constructor
//
CArmyCardGardesZettiens::CArmyCardGardesZettiens()
:
// Call the base constructor
CArmyCard()
{
	// The name of the card
	m_Name.LoadString(IDS_GARDESZETTIENSNAME);
	// The basic rule text
	//m_BasicText.LoadStringW(IDS_);
	// The basic rule movement
	m_BasicMovementSpace = 4;
	// The basic range
	m_BasicRangeSpace = 7;
	// The basic rule attack
	m_BasicAttackDice = 2;
	// The basic rule defense
	m_BasicDefenseDice = 7;
	// The expert rule text
	//m_ExpertText.LoadStringW(IDS_);
	// The expert rule movement
	m_ExpertMovementSpace = 4;
	// The expert rule range
	m_ExpertRangeSpace = 7;
	// The expert rule attack
	m_ExpertAttackDice = 2;
	// The expert rule defense
	m_ExpertDefenseDice = 7;
	// The expert rule cost point
	m_ExpertCostPoint = 80;
	// The expert rule total life point
	m_ExpertTotalLifePoint = 1;
	// The current life point
	m_CurrentLifePoint = m_ExpertTotalLifePoint;
	// The ability to fly
	m_CanFly = false;
	// The bitmap file name
	m_BitmapFileName = _T("Gardes_Zettiens");
	// The figures list
	CString Str;
	Str.LoadStringW( IDS_GUARDSZETTIAN1_2 );
	CFigureObject* pFigureObject = new CFigureObject( false, Str, _T("GARDES ZETTIAN 1-2"), this );
	m_Figures.Add( pFigureObject );
	Str.LoadStringW( IDS_GUARDSZETTIAN2_2 );
	pFigureObject = new CFigureObject( false, Str, _T("GARDES ZETTIAN 2-2"), this );
	m_Figures.Add( pFigureObject );
}

// The destructor
//
CArmyCardGardesZettiens::~CArmyCardGardesZettiens(void)
{
}

