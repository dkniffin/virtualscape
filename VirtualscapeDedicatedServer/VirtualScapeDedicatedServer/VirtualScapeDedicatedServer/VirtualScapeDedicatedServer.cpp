// VirtualScapeDedicatedServer.cpp : Définit les comportements de classe pour l'application.
//

#include "stdafx.h"
#include "VirtualScapeDedicatedServer.h"
#include "VirtualScapeDedicatedServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVirtualScapeDedicatedServerApp

BEGIN_MESSAGE_MAP(CVirtualScapeDedicatedServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// construction CVirtualScapeDedicatedServerApp

CVirtualScapeDedicatedServerApp::CVirtualScapeDedicatedServerApp()
{
	// TODO : ajoutez ici du code de construction,
	// Placez toutes les initialisations significatives dans InitInstance
}


// Seul et unique objet CVirtualScapeDedicatedServerApp

CVirtualScapeDedicatedServerApp theApp;


// initialisation de CVirtualScapeDedicatedServerApp

BOOL CVirtualScapeDedicatedServerApp::InitInstance()
{
	// InitCommonControlsEx() est requis sur Windows XP si le manifeste de l'application
	// spécifie l'utilisation de ComCtl32.dll version 6 ou ultérieure pour activer les
	// styles visuels.  Dans le cas contraire, la création de fenêtres échouera.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// À définir pour inclure toutes les classes de contrôles communs à utiliser
	// dans votre application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Initialisation standard
	// Si vous n'utilisez pas ces fonctionnalités et que vous souhaitez réduire la taille
	// de votre exécutable final, vous devez supprimer ci-dessous
	// les routines d'initialisation spécifiques dont vous n'avez pas besoin.
	// Changez la clé de Registre sous laquelle nos paramètres sont enregistrés
	// TODO : modifiez cette chaîne avec des informations appropriées,
	// telles que le nom de votre société ou organisation
	SetRegistryKey(_T("Applications locales générées par AppWizard"));

	m_pMainWnd = new CVirtualScapeDedicatedServerDlg;
	((CVirtualScapeDedicatedServerDlg*) m_pMainWnd)->Create( IDD_VIRTUALSCAPEDEDICATEDSERVER_DIALOG );
	m_pMainWnd->ShowWindow( SW_NORMAL );
	// Lorsque la boîte de dialogue est fermée, retourner FALSE afin de quitter
	//  l'application, plutôt que de démarrer la pompe de messages de l'application.
	return TRUE;
}

// Add a Socket to the list
//
//void CVirtualScapeDedicatedServerApp::AddSocket( void* pSocket )
//{
//	m_SocketList.Add( pSocket );
//}
