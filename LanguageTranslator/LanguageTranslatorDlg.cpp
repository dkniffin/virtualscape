// LanguageTranslatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LanguageTranslator.h"
#include "LanguageTranslatorDlg.h"

// The one and only CLanguageTranslatorApp object
extern CLanguageTranslatorApp theApp;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLanguageTranslatorDlg dialog

CLanguageTranslatorDlg::CLanguageTranslatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLanguageTranslatorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLanguageTranslatorDlg)
	m_cs_OriginFile = _T("..\\..\\HeroscapeEditor.rc");
	m_cs_DestinationFile = _T("..\\..\\HeroscapeEditor-UK.rc");
	m_cs_TraductionFile = _T("Traduction.txt");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLanguageTranslatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLanguageTranslatorDlg)
	DDX_Control(pDX, IDC_LIST_LOG, m_cb_Log);
	DDX_Text(pDX, IDC_EDIT_ORIGINFILE, m_cs_OriginFile);
	DDX_Text(pDX, IDC_EDIT_DESTINATIONFILE, m_cs_DestinationFile);
	DDX_Text(pDX, IDC_EDIT_TRADUCTIONFILE, m_cs_TraductionFile);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLanguageTranslatorDlg, CDialog)
	//{{AFX_MSG_MAP(CLanguageTranslatorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_TRADUCTION, OnButtonTraduction)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLanguageTranslatorDlg message handlers

BOOL CLanguageTranslatorDlg::OnInitDialog()
{
	m_cs_OriginFile = theApp.m_Origin_File;
	m_cs_DestinationFile = theApp.m_Destination_File;
	m_cs_TraductionFile = theApp.m_Traduction_File;

	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLanguageTranslatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLanguageTranslatorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLanguageTranslatorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// The user want traduct the file
//
void CLanguageTranslatorDlg::OnButtonTraduction() 
{
	// Charge le fichier de traduction
	LoadTranslatorFile();
	// Traduit le fichier
	TraductFile();
}

// Traduct the file
//
void CLanguageTranslatorDlg::TraductFile()
{
	int NbTranslated = 0;
	int	NbLine = 0;

	// Open file for read
	CStdioFile ReadFile( m_cs_OriginFile, CFile::modeRead | CFile::shareDenyWrite | CFile::typeText );
	// Open destination file for write
	CStdioFile DestinationFile( m_cs_DestinationFile, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyRead | CFile::typeBinary );

	// Open file for information
	CStdioFile ToTranslateFile( _T("d:\\ToTranslate.txt") , CFile::modeCreate | CFile::modeWrite | CFile::shareDenyRead | CFile::typeBinary );

	char pBuff[6];
	pBuff[0] = (char) 0xff;
	pBuff[1] = (char) 0xfe;

	DestinationFile.Write( pBuff, 2 );

	CString Str;
	CString	StrTranslate;
	while ( ReadFile.ReadString(Str)!=NULL )
	{
		int FirstTraduction = 0;
		while( Str.Find('"',FirstTraduction)>=0 )
		{
			int Index = Str.Find('"',FirstTraduction);

			// Try to translate this line
			int Index2 = Str.Find('"',Index+1);
			if( Index2>=0 )
			{
				// Extract string to translate
				CString	StringToTranslate = Str.Mid(Index,Index2-Index+1);

				// Search the traduction in the hash map
				CString StrNew;
				if( m_TranslateTable.Lookup( StringToTranslate, StrNew )!=0 )
				{
					CString Str2 = Str.Left(Index);
					Str2 += StrNew;
					FirstTraduction = Str2.GetLength();
					Str2 += Str.Mid(Index2+1);
					Str = Str2;
					NbTranslated++;
				}
				else
				{
					// Translate not found
					CString Str2;
					Str2.Format(_T("Ligne %i, la chaine '%s' n'a pas été traduite dans le fichier"), NbLine, StringToTranslate );
					m_cb_Log.AddString(Str2);
					FirstTraduction = Index2+1;
					// Save in the file c:\ToTranslate.txt
					CString StrToTranslate;
					StrToTranslate.Format( _T("%s§%s"), StringToTranslate, StringToTranslate );
					ToTranslateFile.Write( StrToTranslate.GetBuffer(0), StrToTranslate.GetLength()*2);
					pBuff[0] = (char) 0x0d;
					pBuff[1] = (char) 0x00;
					pBuff[2] = (char) 0x0a;
					pBuff[3] = (char) 0x00;
					ToTranslateFile.Write(pBuff,4);
				}
			}
			else
			{
				CString Str2;
				Str2.Format(_T("La ligne %i contient un nombre impair de '\"'"), NbLine );
				m_cb_Log.AddString(Str2);
				break;
			}
		}
		DestinationFile.Write(Str.GetBuffer(0),Str.GetLength()*2);
		pBuff[0] = (char) 0x0d;
		pBuff[1] = (char) 0x00;
		pBuff[2] = (char) 0x0a;
		pBuff[3] = (char) 0x00;
		DestinationFile.Write(pBuff,4);
		NbLine++;
	}

	CString Str2;
	Str2.Format(_T("%i traductions pour %i lignes"), NbTranslated, NbLine );
	m_cb_Log.AddString(Str2);

	// Close the files
	ReadFile.Close();
	DestinationFile.Close();
	ToTranslateFile.Close();
}

// Load the translator file
//
void CLanguageTranslatorDlg::LoadTranslatorFile()
{
	char Buffer[1000];
	char* pBuff = Buffer;

	UpdateData( TRUE );

	m_cb_Log.ResetContent();
	m_cb_Log.AddString(_T("Charge le fichier de traduction"));

	m_TranslateTable.RemoveAll();
	m_TranslateTable.InitHashTable( 257 );

	CStdioFile f( m_cs_TraductionFile, CFile::modeRead | CFile::shareDenyWrite | CFile::typeBinary );
	// Because unicode text file begin with FF FE
	f.Read(pBuff,2);

	CString Str;
	while ( f.Read(pBuff,2)==2 )
	{
		CString Char;
		memcpy( Char.GetBuffer(2), pBuff, 2 );
		memset( Char.GetBuffer()+1, 0, 2 );
		Char.ReleaseBuffer();

		if( Char==_T("\n") )
		{
			Str = Str.Left(Str.GetLength()-1);
			TRACE(_T("Str : %s\n"), Str );
			int Index = Str.Find(_T("§"));
			if( Index>=0 )
			{
				CString	StrKey = Str.Left(Index);
				CString	StrValue = Str.Mid(Index+1);
				m_TranslateTable.SetAt( StrKey, StrValue );
			}
			Str = "";
		}
		else
		{
			Str += Char;
		}
	}

	m_cb_Log.AddString(_T("Fin du chargement du fichier de traduction"));

	f.Close();
}
