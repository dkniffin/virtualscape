// LanguageTranslator.h : main header file for the LANGUAGETRANSLATOR application
//

#ifndef _LANGUAGETRANSLATOR_H_
#define _LANGUAGETRANSLATOR_H_

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

class CLanguageTranslatorApp : public CWinApp
{
public:
	// The origine file
	CString	m_Origin_File;
	// the destination file
	CString	m_Destination_File;
	// the traduction file
	CString	m_Traduction_File;

public:
	// The constructor
	CLanguageTranslatorApp();
	// Read the ini file
	void ReadIni();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLanguageTranslatorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLanguageTranslatorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // #ifndef _LANGUAGETRANSLATOR_H_
