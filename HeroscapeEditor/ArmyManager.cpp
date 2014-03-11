#include "StdAfx.h"

#include "ArmyCardAgentCarr.h"
#include "ArmyCardAgentsDeKravMaga.h"
#include "ArmyCardEliteAeroportee.h"
#include "ArmyCardFinnLeChampionViking.h"
#include "ArmyCardGardesZettiens.h"
#include "ArmyCardGrimnak.h"
#include "ArmyCardGuerriersMarro.h"
#include "ArmyCardGuerriersVikingsDeTarn.h"
#include "ArmyCardMarchemort9000.h"
#include "ArmyCardMimring.h"
#include "ArmyCardNeGokSa.h"
#include "ArmyCardRaelinLaGuerriereKyrie.h"
#include "ArmyCardSamouraisIzumi.h"
#include "ArmyCardSgtDrakeAlexander.h"
#include "ArmyCardSyvarris.h"
#include "ArmyCardThorgrimLeChampionViking.h"
#include "ArmyManager.h"

// The constructor
//
CArmyManager::CArmyManager(void)
{
}

// The destructor
//
CArmyManager::~CArmyManager(void)
{
}

// Get all army
//
CPtrArray* CArmyManager::GetAllArmy()
{
	CPtrArray* pArray = new CPtrArray;

	// Add all the army card here
	// First, all card of master set
	pArray->Add( new CArmyCardAgentCarr() );
	pArray->Add( new CArmyCardAgentsDeKravMaga() );
	pArray->Add( new CArmyCardSamouraisIzumi() );
	pArray->Add( new CArmyCardEliteAeroportee() );
	pArray->Add( new CArmyCardFinnLeChampionViking() );
	pArray->Add( new CArmyCardGardesZettiens() );
	pArray->Add( new CArmyCardGrimnak() );
	pArray->Add( new CArmyCardGuerriersMarro() );
	pArray->Add( new CArmyCardGuerriersVikingsDeTarn() );
	pArray->Add( new CArmyCardMarchemort9000() );
	pArray->Add( new CArmyCardMimring() );
	pArray->Add( new CArmyCardNeGokSa() );
	pArray->Add( new CArmyCardRaelinLaGuerriereKyrie() );
	pArray->Add( new CArmyCardSgtDrakeAlexander() );
	pArray->Add( new CArmyCardSyvarris() );
	pArray->Add( new CArmyCardThorgrimLeChampionViking() );

	return pArray;
}

