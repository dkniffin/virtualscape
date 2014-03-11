// LaunchDiceDlg.cpp : implementation file
//

#include "stdafx.h"

#include "HeroscapeEditor.h"
#include "LaunchDiceDlg.h"


// CLaunchDiceDlg dialog

IMPLEMENT_DYNAMIC(CLaunchDiceDlg, CDialog)

// The constructor
//
CLaunchDiceDlg::CLaunchDiceDlg(CWnd* pParent /*=NULL*/)
:
CDialog(CLaunchDiceDlg::IDD, pParent)
, m_i_DiceNumberToLaunch(0)
, m_i_DiceNumberResult(0)
, m_b_ForceResult(FALSE)
{

}

// The destructor
//
CLaunchDiceDlg::~CLaunchDiceDlg()
{
}

// Synchronise members and control
//
void CLaunchDiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SP_DICE_NUMBER_RESULT, m_Sp_NumberResult);
	DDX_Control(pDX, IDC_SP_DICE_NUMBER_TO_LAUNCH, m_Sp_DiceNumberToLaunch);
	DDX_Text(pDX, IDC_ED_DICE_NUMBER_TO_LAUNCH, m_i_DiceNumberToLaunch);
	DDV_MinMaxInt(pDX, m_i_DiceNumberToLaunch, 1, 999);
	DDX_Text(pDX, IDC_ED_DICE_NUMBER_RESULT, m_i_DiceNumberResult);
	DDV_MinMaxInt(pDX, m_i_DiceNumberResult, 0, 999);
	DDX_Check(pDX, IDC_CHECK_FORCE_RESULT, m_b_ForceResult);
}


BEGIN_MESSAGE_MAP(CLaunchDiceDlg, CDialog)
	ON_BN_CLICKED(IDC_BT_LAUNCH_DICE, &CLaunchDiceDlg::OnBnClickedBtLaunchDice)
END_MESSAGE_MAP()


// CLaunchDiceDlg message handlers

BOOL CLaunchDiceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Sp_DiceNumberToLaunch.SetRange(0,999);
	m_Sp_NumberResult.SetRange(0,999);

	return TRUE;
}

// The user want launch dice
//
void CLaunchDiceDlg::OnBnClickedBtLaunchDice()
{
	OnOK();
}

