#include "StdAfx.h"

#include "ArmyCardSamouraisIzumi.h"
#include "FigureObject.h"
#include "Resource.h"

// The constructor
//
CArmyCardSamouraisIzumi::CArmyCardSamouraisIzumi()
:
// Call the base constructor
CArmyCard()
{
	// The name of the card
	m_Name.LoadString(IDS_SAMOURAISIZUMINAME);
	// The basic rule text
	m_BasicText.LoadStringW(IDS_SAMOURAISIZUMIBASICRULE);
	// The basic rule movement
	m_BasicMovementSpace = 6;
	// The basic range
	m_BasicRangeSpace = 1;
	// The basic rule attack
	m_BasicAttackDice = 3;
	// The basic rule defense
	m_BasicDefenseDice = 6;
	// The expert rule text
	m_ExpertText.LoadStringW(IDS_SAMOURAISIZUMIEXPERTRULE);
	// The expert rule movement
	m_ExpertMovementSpace = 6;
	// The expert rule range
	m_ExpertRangeSpace = 1;
	// The expert rule attack
	m_ExpertAttackDice = 2;
	// The expert rule defense
	m_ExpertDefenseDice = 5;
	// The expert rule cost point
	m_ExpertCostPoint = 60;
	// The expert rule total life point
	m_ExpertTotalLifePoint = 3;
	// The current life point
	m_CurrentLifePoint = m_ExpertTotalLifePoint;
	// The ability to fly
	m_CanFly = false;
	// The bitmap file name
	m_BitmapFileName = _T("SAMOURAIS_IZUMI");
	// The figures list
	CString Str;
	Str.LoadStringW( IDS_SAMURAI_IZUMI1_3 );
	CFigureObject* pFigureObject = new CFigureObject( false, Str, _T("SAMURAI IZUMI 1-3"), this );
	m_Figures.Add( pFigureObject );
	Str.LoadStringW( IDS_SAMURAI_IZUMI2_3 );
	pFigureObject = new CFigureObject( false, Str, _T("SAMURAI IZUMI 2-3"), this );
	m_Figures.Add( pFigureObject );
	Str.LoadStringW( IDS_SAMURAI_IZUMI3_3 );
	pFigureObject = new CFigureObject( false, Str, _T("SAMURAI IZUMI 3-3"), this );
	m_Figures.Add( pFigureObject );
}

// The destructor
//
CArmyCardSamouraisIzumi::~CArmyCardSamouraisIzumi(void)
{
}

