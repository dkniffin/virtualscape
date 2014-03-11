#include "StdAfx.h"

#include "ArmyCardAgentCarr.h"
#include "FigureObject.h"
#include "Resource.h"

// The constructor
//
CArmyCardAgentCarr::CArmyCardAgentCarr()
:
// Call the base constructor
CArmyCard()
{
	// The name of the card
	m_Name.LoadString(IDS_AGENTCARRNAME);
	// The basic rule text
	m_BasicText.LoadStringW(IDS_AGENTCARRBASICRULE);
	// The basic rule movement
	m_BasicMovementSpace = 7;
	// The basic range
	m_BasicRangeSpace = 4;
	// The basic rule attack
	m_BasicAttackDice = 4;
	// The basic rule defense
	m_BasicDefenseDice = 6;
	// The expert rule text
	m_ExpertText.LoadStringW(IDS_AGENTCARREXPERTRULE);
	// The expert rule movement
	m_ExpertMovementSpace = 5;
	// The expert rule range
	m_ExpertRangeSpace = 6;
	// The expert rule attack
	m_ExpertAttackDice = 2;
	// The expert rule defense
	m_ExpertDefenseDice = 4;
	// The expert rule cost point
	m_ExpertCostPoint = 100;
	// The expert rule total life point
	m_ExpertTotalLifePoint = 3;
	// The current life point
	m_CurrentLifePoint = m_ExpertTotalLifePoint;
	// The ability to fly
	m_CanFly = false;
	// The bitmap file name
	m_BitmapFileName = _T("AGENT_CARR");
	// The figures list
	CString Str;
	Str.LoadStringW( IDS_AGENTCARR );
	CFigureObject* pFigureObject = new CFigureObject( false, Str, _T("AGENT CARR"), this );
	m_Figures.Add( pFigureObject );
}

// The destructor
//
CArmyCardAgentCarr::~CArmyCardAgentCarr(void)
{
}

