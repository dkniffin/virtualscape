#include "StdAfx.h"

#include "ArmyCardMimring.h"
#include "FigureObject.h"
#include "Resource.h"

// The constructor
//
CArmyCardMimring::CArmyCardMimring()
:
// Call the base constructor
CArmyCard()
{
	// The name of the card
	m_Name.LoadString(IDS_MIMRINGNAME);
	// The basic rule text
	//m_BasicText.LoadStringW(IDS_);
	// The basic rule movement
	m_BasicMovementSpace = 6;
	// The basic range
	m_BasicRangeSpace = 6;
	// The basic rule attack
	m_BasicAttackDice = 6;
	// The basic rule defense
	m_BasicDefenseDice = 8;
	// The expert rule text
	//m_ExpertText.LoadStringW(IDS_);
	// The expert rule movement
	m_ExpertMovementSpace = 6;
	// The expert rule range
	m_ExpertRangeSpace = 1;
	// The expert rule attack
	m_ExpertAttackDice = 4;
	// The expert rule defense
	m_ExpertDefenseDice = 3;
	// The expert rule cost point
	m_ExpertCostPoint = 150;
	// The expert rule total life point
	m_ExpertTotalLifePoint = 5;
	// The current life point
	m_CurrentLifePoint = m_ExpertTotalLifePoint;
	// The ability to fly
	m_CanFly = true;
	// The bitmap file name
	m_BitmapFileName = _T("Mimring");
	// The figures list
	CString Str;
	Str.LoadStringW( IDS_MIMRING );
	CFigureObject* pFigureObject = new CFigureObject( true, Str, _T("MIMRING"), this );
	m_Figures.Add( pFigureObject );
}

// The destructor
//
CArmyCardMimring::~CArmyCardMimring(void)
{
}

