#ifndef _MATERIALEDITOR_H_ 
#define _MATERIALEDITOR_H_ 
#include "afxcmn.h"

// CMaterialEdit dialog

class CMaterialEdit : public CDialog
{
	DECLARE_DYNAMIC(CMaterialEdit)

//************
// The methods
//************
public:
	// The constructor
	CMaterialEdit(CWnd* pParent = NULL);
	// The destructor
	virtual ~CMaterialEdit();

//***********************
// Generate by Visual C++
//***********************

// Dialog Data
	enum { IDD = IDD_CONFIG_MATERIAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	UINT m_Nb_Grass24;
	UINT m_Nb_Grass7;
	UINT m_Nb_Grass3;
	UINT m_Nb_Grass2;
	UINT m_Nb_Grass1;
	CSpinButtonCtrl m_Sp_Grass24;
	CSpinButtonCtrl m_Sp_Grass7;
	CSpinButtonCtrl m_Sp_Grass3;
	CSpinButtonCtrl m_Sp_Grass2;
	CSpinButtonCtrl m_Sp_Grass1;

	UINT m_Nb_Rock24;
	UINT m_Nb_Rock7;
	UINT m_Nb_Rock3;
	UINT m_Nb_Rock2;
	UINT m_Nb_Rock1;
	CSpinButtonCtrl m_Sp_Rock24;
	CSpinButtonCtrl m_Sp_Rock7;
	CSpinButtonCtrl m_Sp_Rock3;
	CSpinButtonCtrl m_Sp_Rock2;
	CSpinButtonCtrl m_Sp_Rock1;

	UINT m_Nb_Sand7;
	UINT m_Nb_Sand3;
	UINT m_Nb_Sand2;
	UINT m_Nb_Sand1;
	CSpinButtonCtrl m_Sp_Sand7;
	CSpinButtonCtrl m_Sp_Sand3;
	CSpinButtonCtrl m_Sp_Sand2;
	CSpinButtonCtrl m_Sp_Sand1;

	UINT m_Nb_Tree15;
	UINT m_Nb_Tree12;
	UINT m_Nb_Tree11;
	UINT m_Nb_Tree10;
	CSpinButtonCtrl m_Sp_Tree15;
	CSpinButtonCtrl m_Sp_Tree12;
	CSpinButtonCtrl m_Sp_Tree11;
	CSpinButtonCtrl m_Sp_Tree10;

	UINT m_Nb_Glacier6;
	UINT m_Nb_Glacier4;
	UINT m_Nb_Glacier3;
	UINT m_Nb_Glacier1;
	CSpinButtonCtrl m_Sp_Glacier6;
	CSpinButtonCtrl m_Sp_Glacier4;
	CSpinButtonCtrl m_Sp_Glacier3;
	CSpinButtonCtrl m_Sp_Glacier1;

	UINT m_Nb_LavaField7;
	UINT m_Nb_LavaField2;
	UINT m_Nb_LavaField1;
	CSpinButtonCtrl m_Sp_LavaField7;
	CSpinButtonCtrl m_Sp_LavaField2;
	CSpinButtonCtrl m_Sp_LavaField1;

	UINT m_Nb_Wall4;
	CSpinButtonCtrl m_Sp_Wall4;

	UINT m_Nb_Road5;
	UINT m_Nb_Road2;
	UINT m_Nb_Road1;
	CSpinButtonCtrl m_Sp_Road5;
	CSpinButtonCtrl m_Sp_Road2;
	CSpinButtonCtrl m_Sp_Road1;

	UINT m_Nb_Water1;
	UINT m_Nb_Lava1;
	UINT m_Nb_Ice1;
	CSpinButtonCtrl m_Sp_Water1;
	CSpinButtonCtrl m_Sp_Lava1;
	CSpinButtonCtrl m_Sp_Ice1;

	UINT m_Nb_Snow2;
	UINT m_Nb_Snow1;
	CSpinButtonCtrl m_Sp_Snow2;
	CSpinButtonCtrl m_Sp_Snow1;

	UINT m_Nb_Ruin3;
	UINT m_Nb_Ruin2;
	CSpinButtonCtrl m_Sp_Ruin3;
	CSpinButtonCtrl m_Sp_Ruin2;

	UINT m_Nb_GlyphA;
	UINT m_Nb_GlyphG;
	UINT m_Nb_GlyphI;
	UINT m_Nb_GlyphV;
	UINT m_Nb_GlyphD;
	UINT m_Nb_GlyphB;
	UINT m_Nb_GlyphK;
	UINT m_Nb_GlyphE;
	UINT m_Nb_GlyphM;
	UINT m_Nb_GlyphL;
	UINT m_Nb_GlyphS;
	UINT m_Nb_GlyphR;
	UINT m_Nb_GlyphJ;
	UINT m_Nb_GlyphW;
	UINT m_Nb_GlyphP;
	UINT m_Nb_GlyphO;
	UINT m_Nb_GlyphN;
	UINT m_Nb_GlyphC;
	UINT m_Nb_GlyphT;
	UINT m_Nb_GlyphU;

	CSpinButtonCtrl m_Sp_GlyphA;
	CSpinButtonCtrl m_Sp_GlyphG;
	CSpinButtonCtrl m_Sp_GlyphI;
	CSpinButtonCtrl m_Sp_GlyphV;
	CSpinButtonCtrl m_Sp_GlyphD;
	CSpinButtonCtrl m_Sp_GlyphB;
	CSpinButtonCtrl m_Sp_GlyphK;
	CSpinButtonCtrl m_Sp_GlyphE;
	CSpinButtonCtrl m_Sp_GlyphM;
	CSpinButtonCtrl m_Sp_GlyphL;
	CSpinButtonCtrl m_Sp_GlyphS;
	CSpinButtonCtrl m_Sp_GlyphR;
	CSpinButtonCtrl m_Sp_GlyphJ;
	CSpinButtonCtrl m_Sp_GlyphW;
	CSpinButtonCtrl m_Sp_GlyphP;
	CSpinButtonCtrl m_Sp_GlyphO;
	CSpinButtonCtrl m_Sp_GlyphN;
	CSpinButtonCtrl m_Sp_GlyphC;
	CSpinButtonCtrl m_Sp_GlyphT;
	CSpinButtonCtrl m_Sp_GlyphU;

	UINT m_Nb_CastleBaseCorner;
	UINT m_Nb_CastleBaseStraight;
	UINT m_Nb_CastleBaseEnd;
	UINT m_Nb_CastleWallCorner;
	UINT m_Nb_CastleWallStraight;
	UINT m_Nb_CastleWallEnd;
	UINT m_Nb_Castle9;
	UINT m_Nb_Castle7;
	UINT m_Nb_Castle1;
	UINT m_Nb_CastleBattlement;
	UINT m_Nb_CastleDoor;
	UINT m_Nb_CastleLadder;
	UINT m_Nb_CastleFlag;

	CSpinButtonCtrl m_Sp_CastleBaseCorner;
	CSpinButtonCtrl m_Sp_CastleBaseStraight;
	CSpinButtonCtrl m_Sp_CastleBaseEnd;
	CSpinButtonCtrl m_Sp_CastleWallCorner;
	CSpinButtonCtrl m_Sp_CastleWallStraight;
	CSpinButtonCtrl m_Sp_CastleWallEnd;
	CSpinButtonCtrl m_Sp_Castle9;
	CSpinButtonCtrl m_Sp_Castle7;
	CSpinButtonCtrl m_Sp_Castle1;
	CSpinButtonCtrl m_Sp_CastleBattlement;
	CSpinButtonCtrl m_Sp_CastleDoor;
	CSpinButtonCtrl m_Sp_CastleLadder;
	CSpinButtonCtrl m_Sp_CastleFlag;

	UINT m_Nb_MarvelConcrete7;
	UINT m_Nb_MarvelConcrete2;
	UINT m_Nb_MarvelConcrete1;
	UINT m_Nb_MarvelAsphalt7;
	UINT m_Nb_MarvelAsphalt2;
	UINT m_Nb_MarvelAsphalt1;
	UINT m_Nb_MarvelRuin6;

	CSpinButtonCtrl m_Sp_MarvelConcrete7;
	CSpinButtonCtrl m_Sp_MarvelConcrete2;
	CSpinButtonCtrl m_Sp_MarvelConcrete1;
	CSpinButtonCtrl m_Sp_MarvelAsphalt7;
	CSpinButtonCtrl m_Sp_MarvelAsphalt2;
	CSpinButtonCtrl m_Sp_MarvelAsphalt1;
	CSpinButtonCtrl m_Sp_MarvelRuin6;

	UINT m_Nb_Swamp24;
	UINT m_Nb_Swamp7;
	UINT m_Nb_Swamp3;
	UINT m_Nb_Swamp2;
	UINT m_Nb_Swamp1;
	UINT m_Nb_SwampWater1;
	UINT m_Nb_SwampHive6;

	CSpinButtonCtrl m_Sp_Swamp24;
	CSpinButtonCtrl m_Sp_Swamp7;
	CSpinButtonCtrl m_Sp_Swamp3;
	CSpinButtonCtrl m_Sp_Swamp2;
	CSpinButtonCtrl m_Sp_Swamp1;
	CSpinButtonCtrl m_Sp_SwampWater1;
	CSpinButtonCtrl m_Sp_SwampHive6;

	UINT m_Nb_TicallaPalm;
	UINT m_Nb_TicallaGrass;

	CSpinButtonCtrl m_Sp_TicallaPalm;
	CSpinButtonCtrl m_Sp_TicallaGrass;

	UINT m_Nb_Dungeon24;
	UINT m_Nb_Dungeon7;
	UINT m_Nb_Dungeon3;
	UINT m_Nb_Dungeon2;
	UINT m_Nb_Dungeon1;
	UINT m_Nb_Shadow1;
	UINT m_Nb_Outcrop1;
	UINT m_Nb_Outcrop3;

	CSpinButtonCtrl m_Sp_Dungeon24;
	CSpinButtonCtrl m_Sp_Dungeon7;
	CSpinButtonCtrl m_Sp_Dungeon3;
	CSpinButtonCtrl m_Sp_Dungeon2;
	CSpinButtonCtrl m_Sp_Dungeon1;
	CSpinButtonCtrl m_Sp_Shadow1;
	CSpinButtonCtrl m_Sp_Outcrop1;
	CSpinButtonCtrl m_Sp_Outcrop3;

public:
	afx_msg void OnBnClickedBtEraseAll();
public:
	afx_msg void OnBnClickedBtAddMasterSet();
public:
	afx_msg void OnBnClickedBtAddForgottenForest();
public:
	afx_msg void OnBnClickedBtAddVolcarenWasteland();
public:
	afx_msg void OnBnClickedBtAddTundra();
public:
	afx_msg void OnBnClickedBtAddTerrain();
public:
	afx_msg void OnBnClickedBtAddCastle();
public:
	afx_msg void OnBnClickedBtSaveCollection();
public:
	afx_msg void OnBnClickedBtLoadCollection2();
public:
	afx_msg void OnBnClickedBtAddMarvel();
public:
	afx_msg void OnBnClickedBtAddSwarm();
	afx_msg void OnBnClickedBtAddTicallaJungle();
	afx_msg void OnBnClickedBtAddDungeon();
};

#endif // #ifndef _MATERIALEDITOR_H_ 
