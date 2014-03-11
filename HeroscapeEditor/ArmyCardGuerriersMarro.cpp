#include "StdAfx.h"

#include "ArmyCardGuerriersMarro.h"
#include "FigureObject.h"
#include "Resource.h"

// The constructor
//
CArmyCardGuerriersMarro::CArmyCardGuerriersMarro()
:
// Call the base constructor
CArmyCard()
{
	// The name of the card
	m_Name.LoadString(IDS_GUERRIERSMARRONAME);
	// The basic rule text
	//m_BasicText.LoadStringW(IDS_);
	// The basic rule movement
	m_BasicMovementSpace = 6;
	// The basic range
	m_BasicRangeSpace = 6;
	// The basic rule attack
	m_BasicAttackDice = 2;
	// The basic rule defense
	m_BasicDefenseDice = 4;
	// The expert rule text
	//m_ExpertText.LoadStringW(IDS_);
	// The expert rule movement
	m_ExpertMovementSpace = 6;
	// The expert rule range
	m_ExpertRangeSpace = 6;
	// The expert rule attack
	m_ExpertAttackDice = 2;
	// The expert rule defense
	m_ExpertDefenseDice = 3;
	// The expert rule cost point
	m_ExpertCostPoint = 50;
	// The expert rule total life point
	m_ExpertTotalLifePoint = 1;
	// The current life point
	m_CurrentLifePoint = m_ExpertTotalLifePoint;
	// The ability to fly
	m_CanFly = false;
	// The bitmap file name
	m_BitmapFileName = _T("Guerriers_Marro");
	// The figures list
	CString Str;
	Str.LoadStringW( IDS_GUERRIERSMARRO1_4 );
	CFigureObject* pFigureObject = new CFigureObject( false, Str, _T("GUERRIERS MARRO 1-4"), this );
	m_Figures.Add( pFigureObject );
	Str.LoadStringW( IDS_GUERRIERSMARRO2_4 );
	pFigureObject = new CFigureObject( false, Str, _T("GUERRIERS MARRO 2-4"), this );
	m_Figures.Add( pFigureObject );
	Str.LoadStringW( IDS_GUERRIERSMARRO3_4 );
	pFigureObject = new CFigureObject( false, Str, _T("GUERRIERS MARRO 3-4"), this );
	m_Figures.Add( pFigureObject );
	Str.LoadStringW( IDS_GUERRIERSMARRO4_4 );
	pFigureObject = new CFigureObject( false, Str, _T("GUERRIERS MARRO 4-4"), this );
	m_Figures.Add( pFigureObject );
}

// The destructor
//
CArmyCardGuerriersMarro::~CArmyCardGuerriersMarro(void)
{
}

