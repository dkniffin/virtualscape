#include "StdAfx.h"

#include "ArmyCardEliteAeroportee.h"
#include "FigureObject.h"
#include "Resource.h"

// The constructor
//
CArmyCardEliteAeroportee::CArmyCardEliteAeroportee()
:
// Call the base constructor
CArmyCard()
{
	// The name of the card
	m_Name.LoadString(IDS_ELITEAEROPORTEENAME);
	// The basic rule text
	//m_BasicText.LoadStringW(IDS_);
	// The basic rule movement
	m_BasicMovementSpace = 4;
	// The basic range
	m_BasicRangeSpace = 8;
	// The basic rule attack
	m_BasicAttackDice = 3;
	// The basic rule defense
	m_BasicDefenseDice = 2;
	// The expert rule text
	//m_ExpertText.LoadStringW(IDS_);
	// The expert rule movement
	m_ExpertMovementSpace = 4;
	// The expert rule range
	m_ExpertRangeSpace = 8;
	// The expert rule attack
	m_ExpertAttackDice = 3;
	// The expert rule defense
	m_ExpertDefenseDice = 2;
	// The expert rule cost point
	m_ExpertCostPoint = 110;
	// The expert rule total life point
	m_ExpertTotalLifePoint = 4;
	// The current life point
	m_CurrentLifePoint = m_ExpertTotalLifePoint;
	// The ability to fly
	m_CanFly = false;
	// The bitmap file name
	m_BitmapFileName = _T("Elite_aeroportee");
	// The figures list
	CString Str;
	Str.LoadStringW( IDS_ELITEAEROPORTEE1_4 );
	CFigureObject* pFigureObject = new CFigureObject( false, Str, _T("ELITE AEROPORTEE 1-4"), this );
	m_Figures.Add( pFigureObject );
	Str.LoadStringW( IDS_ELITEAEROPORTEE2_4 );
	pFigureObject = new CFigureObject( false, Str, _T("ELITE AEROPORTEE 2-4"), this );
	m_Figures.Add( pFigureObject );
	Str.LoadStringW( IDS_ELITEAEROPORTEE3_4 );
	pFigureObject = new CFigureObject( false, Str, _T("ELITE AEROPORTEE 3-4"), this );
	m_Figures.Add( pFigureObject );
	Str.LoadStringW( IDS_ELITEAEROPORTEE4_4 );
	pFigureObject = new CFigureObject( false, Str, _T("ELITE AEROPORTEE 4-4"), this );
	m_Figures.Add( pFigureObject );
}

// The destructor
//
CArmyCardEliteAeroportee::~CArmyCardEliteAeroportee(void)
{
}

