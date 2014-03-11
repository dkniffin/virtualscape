// VirtualScapeDedicatedServer.h : fichier d'en-tête principal pour l'application PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resource.h"		// symboles principaux


// CVirtualScapeDedicatedServerApp:
// Consultez VirtualScapeDedicatedServer.cpp pour l'implémentation de cette classe
//

class CVirtualScapeDedicatedServerApp : public CWinApp
{
protected:
	// The socket list
	//CPtrArray m_SocketList;

public:
	// The constructor
	CVirtualScapeDedicatedServerApp();

// Substitutions
	public:
	virtual BOOL InitInstance();
	// Add a Socket to the list
	//void AddSocket( void* pSocket );

// Implémentation

	DECLARE_MESSAGE_MAP()
};

extern CVirtualScapeDedicatedServerApp theApp;