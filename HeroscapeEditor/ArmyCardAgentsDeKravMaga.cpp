#include "StdAfx.h"

#include "ArmyCardAgentsDeKravMaga.h"
#include "FigureObject.h"
#include "Resource.h"

// The constructor
//
CArmyCardAgentsDeKravMaga::CArmyCardAgentsDeKravMaga()
:
// Call the base constructor
CArmyCard()
{
	// The name of the card
	m_Name.LoadString(IDS_AGENTSDEKRAVMAGANAME);
	// The basic rule text
	//m_BasicText.LoadStringW(IDS_);
	// The basic rule movement
	m_BasicMovementSpace = 5;
	// The basic range
	m_BasicRangeSpace = 7;
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
	m_BitmapFileName = _T("Agents_de_Krav_Maga");
	// The figures list
	CString Str;
	Str.LoadStringW( IDS_AGENTS_KRAV_MAGA1_3 );
	CFigureObject* pFigureObject = new CFigureObject( false, Str, _T("AGENTS KRAV MAGA 1-3"), this );
	m_Figures.Add( pFigureObject );
	Str.LoadStringW( IDS_AGENTS_KRAV_MAGA2_3 );
	pFigureObject = new CFigureObject( false, Str, _T("AGENTS KRAV MAGA 2-3"), this );
	m_Figures.Add( pFigureObject );
	Str.LoadStringW( IDS_AGENTS_KRAV_MAGA3_3 );
	pFigureObject = new CFigureObject( false, Str, _T("AGENTS KRAV MAGA 3-3"), this );
	m_Figures.Add( pFigureObject );
}

// The destructor
//
CArmyCardAgentsDeKravMaga::~CArmyCardAgentsDeKravMaga(void)
{
}

