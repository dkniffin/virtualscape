#include "StdAfx.h"

#include "ArmyCardFinnLeChampionViking.h"
#include "FigureObject.h"
#include "Resource.h"

// The constructor
//
CArmyCardFinnLeChampionViking::CArmyCardFinnLeChampionViking()
:
// Call the base constructor
CArmyCard()
{
	// The name of the card
	m_Name.LoadString(IDS_FINNLECHAMPIONVIKINGNAME);
	// The basic rule text
	//m_BasicText.LoadStringW(IDS_);
	// The basic rule movement
	m_BasicMovementSpace = 5;
	// The basic range
	m_BasicRangeSpace = 1;
	// The basic rule attack
	m_BasicAttackDice = 3;
	// The basic rule defense
	m_BasicDefenseDice = 6;
	// The expert rule text
	//m_ExpertText.LoadStringW(IDS_);
	// The expert rule movement
	m_ExpertMovementSpace = 5;
	// The expert rule range
	m_ExpertRangeSpace = 1;
	// The expert rule attack
	m_ExpertAttackDice = 3;
	// The expert rule defense
	m_ExpertDefenseDice = 4;
	// The expert rule cost point
	m_ExpertCostPoint = 80;
	// The expert rule total life point
	m_ExpertTotalLifePoint = 4;
	// The current life point
	m_CurrentLifePoint = m_ExpertTotalLifePoint;
	// The ability to fly
	m_CanFly = false;
	// The bitmap file name
	m_BitmapFileName = _T("Finn_le_champion_viking");
	// The figures list
	CString Str;
	Str.LoadStringW( IDS_FINNLECHAMPIONVIKING );
	CFigureObject* pFigureObject = new CFigureObject( false, Str, _T("FINN LE CHAMPION VIKING"), this );
	m_Figures.Add( pFigureObject );
}

// The destructor
//
CArmyCardFinnLeChampionViking::~CArmyCardFinnLeChampionViking(void)
{
}

