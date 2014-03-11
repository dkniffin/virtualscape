#include "StdAfx.h"

#include "ArmyCardMarchemort9000.h"
#include "FigureObject.h"
#include "Resource.h"

// The constructor
//
CArmyCardMarchemort9000::CArmyCardMarchemort9000()
:
// Call the base constructor
CArmyCard()
{
	// The name of the card
	m_Name.LoadString(IDS_MARCHEMORT9000NAME);
	// The basic rule text
	//m_BasicText.LoadStringW(IDS_);
	// The basic rule movement
	m_BasicMovementSpace = 5;
	// The basic range
	m_BasicRangeSpace = 7;
	// The basic rule attack
	m_BasicAttackDice = 4;
	// The basic rule defense
	m_BasicDefenseDice = 9;
	// The expert rule text
	//m_ExpertText.LoadStringW(IDS_);
	// The expert rule movement
	m_ExpertMovementSpace = 5;
	// The expert rule range
	m_ExpertRangeSpace = 7;
	// The expert rule attack
	m_ExpertAttackDice = 4;
	// The expert rule defense
	m_ExpertDefenseDice = 9;
	// The expert rule cost point
	m_ExpertCostPoint = 140;
	// The expert rule total life point
	m_ExpertTotalLifePoint = 1;
	// The current life point
	m_CurrentLifePoint = m_ExpertTotalLifePoint;
	// The ability to fly
	m_CanFly = false;
	// The bitmap file name
	m_BitmapFileName = _T("Marchemort_9000");
	// The figures list
	CString Str;
	Str.LoadStringW( IDS_MARCHEMORT9000 );
	CFigureObject* pFigureObject = new CFigureObject( false, Str, _T("MARCHEMORT 9000"), this );
	m_Figures.Add( pFigureObject );
}

// The destructor
//
CArmyCardMarchemort9000::~CArmyCardMarchemort9000(void)
{
}

