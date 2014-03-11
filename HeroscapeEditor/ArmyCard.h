#pragma once

class CArmyCard abstract
{
//************
// The defines
//************
protected:

//**********
// The enums
//**********
public:

//************
// The members
//************
public:
	// The name of the card
	CString		m_Name;
	// The basic rule text
	CString		m_BasicText;
	// The basic rule attack
	int			m_BasicAttackDice;
	// The basic rule defense
	int			m_BasicDefenseDice;
	// The basic rule movement
	int			m_BasicMovementSpace;
	// The basic range
	int			m_BasicRangeSpace;
	// The expert rule text
	CString		m_ExpertText;
	// The expert rule cost point
	int			m_ExpertCostPoint;
	// The expert rule attack
	int			m_ExpertAttackDice;
	// The expert rule defense
	int			m_ExpertDefenseDice;
	// The expert rule movement
	int			m_ExpertMovementSpace;
	// The expert range
	int			m_ExpertRangeSpace;
	// The expert rule total life point
	int			m_ExpertTotalLifePoint;
	// The current life point
	int			m_CurrentLifePoint;
	// The ability to fly
	bool		m_CanFly;
	// The bitmap file name
	CString		m_BitmapFileName;
	// The figures list
	CPtrArray	m_Figures;
	// The bitmap
	void*		m_pBits;
	// To know if figure are already place on the battlefield
	bool		m_FigureArePlaced;
	// The marquer list
	CPtrArray	m_MarquerList;

public:

//************
// The methods
//************
public:
	// The constructor
	CArmyCard();
	// The destructor
	~CArmyCard(void);
	// Draw this card on a square
	void Draw( CDC* pDC, int XOffset, int YOffset, int Width, int Height, bool IsSelected, int DisplayPlayerIndex );
	// Load the bitmap
	bool LoadBitmap();
	// Get the figures list
	CPtrArray*	GetFiguresList();
	// Remove all the marquer
	void ResetMarquer();
	// Remove a marquer with a particular value
	void RemoveMarquer( int Value );
	// Add a marquer with a particular value
	void AddMarquer( int Value );
	// Show a marquer with a particular value
	void ShowMarquer( int Value );
	// Return the next hidden marquer or -1
	int	 GetNextHidenMarquer();
};
