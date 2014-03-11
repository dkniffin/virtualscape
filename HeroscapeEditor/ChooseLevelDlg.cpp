// ChooseLevelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HeroscapeEditor.h"
#include "ChooseLevelDlg.h"


// CChooseLevelDlg dialog

IMPLEMENT_DYNAMIC(CChooseLevelDlg, CDialog)

CChooseLevelDlg::CChooseLevelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChooseLevelDlg::IDD, pParent)
	, m_Level(0)
{

}

CChooseLevelDlg::~CChooseLevelDlg()
{
}

void CChooseLevelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ED_LEVEL, m_Level);
	DDV_MinMaxUInt(pDX, m_Level, 1, 10000);
	DDX_Control(pDX, IDC_SP_LEVEL, m_Sp_Level);
}


BEGIN_MESSAGE_MAP(CChooseLevelDlg, CDialog)
END_MESSAGE_MAP()


// CChooseLevelDlg message handlers

BOOL CChooseLevelDlg::OnInitDialog()
{
	// Call the base class
	CDialog::OnInitDialog();

	m_Sp_Level.SetRange( 1, 10000 );

	return TRUE;
}
