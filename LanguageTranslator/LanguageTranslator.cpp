// LanguageTranslator.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "LanguageTranslator.h"
#include "LanguageTranslatorDlg.h"

BEGIN_MESSAGE_MAP(CLanguageTranslatorApp, CWinApp)
	//{{AFX_MSG_MAP(CLanguageTranslatorApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

// The constructor
//
CLanguageTranslatorApp::CLanguageTranslatorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CLanguageTranslatorApp object
CLanguageTranslatorApp theApp;

// initialize the instance
//
BOOL CLanguageTranslatorApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// Read the ini
	ReadIni();

	CLanguageTranslatorDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

// Read the ini file
//
void CLanguageTranslatorApp::ReadIni()
{
	CString Str;

	// Read the origin file
	GetPrivateProfileString( _T("File"), _T("Origin"), _T("..\\..\\CartoGL.rc"), Str.GetBuffer(1000), 1000, _T(".\\LanguageTranslator.ini") );
	Str.ReleaseBuffer();
	m_Origin_File = Str;

	// Read the destination file
	GetPrivateProfileString( _T("File"), _T("Destination"), _T("..\\..\\CartoGL-Test.rc"), Str.GetBuffer(1000), 1000, _T(".\\LanguageTranslator.ini") );
	Str.ReleaseBuffer();
	m_Destination_File = Str;

	// Read the traduction file
	GetPrivateProfileString( _T("File"), _T("Traduction"), _T("Traduction.txt"), Str.GetBuffer(1000), 1000, _T(".\\LanguageTranslator.ini") );
	Str.ReleaseBuffer();
	m_Traduction_File = Str;
}