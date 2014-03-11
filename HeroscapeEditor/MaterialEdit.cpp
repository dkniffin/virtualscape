// MaterialEdit.cpp : implementation file
//

#include "StdAfx.h"

#include "HeroscapeEditor.h"
#include "MaterialEdit.h"


// CMaterialEdit dialog

IMPLEMENT_DYNAMIC(CMaterialEdit, CDialog)

// The constructor
//
CMaterialEdit::CMaterialEdit(CWnd* pParent /*=NULL*/)
:
// Call the base class
CDialog(CMaterialEdit::IDD, pParent)
, m_Nb_Grass24(0)
, m_Nb_Grass7(0)
, m_Nb_Grass3(0)
, m_Nb_Grass2(0)
, m_Nb_Grass1(0)
, m_Nb_Rock24(0)
, m_Nb_Rock7(0)
, m_Nb_Rock3(0)
, m_Nb_Rock2(0)
, m_Nb_Rock1(0)
, m_Nb_Sand7(0)
, m_Nb_Sand3(0)
, m_Nb_Sand2(0)
, m_Nb_Sand1(0)
, m_Nb_Tree15(0)
, m_Nb_Tree12(0)
, m_Nb_Tree11(0)
, m_Nb_Tree10(0)
, m_Nb_Glacier6(0)
, m_Nb_Glacier4(0)
, m_Nb_Glacier3(0)
, m_Nb_Glacier1(0)
, m_Nb_LavaField7(0)
, m_Nb_LavaField2(0)
, m_Nb_LavaField1(0)
, m_Nb_Wall4(0)
, m_Nb_Road5(0)
, m_Nb_Road2(0)
, m_Nb_Road1(0)
, m_Nb_Water1(0)
, m_Nb_Lava1(0)
, m_Nb_Ice1(0)
, m_Nb_Snow2(0)
, m_Nb_Snow1(0)
, m_Nb_Ruin3(0)
, m_Nb_Ruin2(0)
, m_Nb_GlyphA(0)
, m_Nb_GlyphG(0)
, m_Nb_GlyphI(0)
, m_Nb_GlyphV(0)
, m_Nb_GlyphD(0)
, m_Nb_GlyphB(0)
, m_Nb_GlyphK(0)
, m_Nb_GlyphE(0)
, m_Nb_GlyphM(0)
, m_Nb_GlyphL(0)
, m_Nb_GlyphS(0)
, m_Nb_GlyphR(0)
, m_Nb_GlyphJ(0)
, m_Nb_GlyphW(0)
, m_Nb_GlyphP(0)
, m_Nb_GlyphO(0)
, m_Nb_GlyphN(0)
, m_Nb_GlyphC(0)
, m_Nb_GlyphT(0)
, m_Nb_GlyphU(0)
, m_Nb_CastleBaseCorner(0)
, m_Nb_CastleBaseStraight(0)
, m_Nb_CastleBaseEnd(0)
, m_Nb_CastleWallCorner(0)
, m_Nb_CastleWallStraight(0)
, m_Nb_CastleWallEnd(0)
, m_Nb_Castle9(0)
, m_Nb_Castle7(0)
, m_Nb_Castle1(0)
, m_Nb_CastleBattlement(0)
, m_Nb_CastleDoor(0)
, m_Nb_CastleLadder(0)
, m_Nb_CastleFlag(0)
, m_Nb_MarvelConcrete7(0)
, m_Nb_MarvelConcrete2(0)
, m_Nb_MarvelConcrete1(0)
, m_Nb_MarvelAsphalt7(0)
, m_Nb_MarvelAsphalt2(0)
, m_Nb_MarvelAsphalt1(0)
, m_Nb_MarvelRuin6(0)
, m_Nb_Swamp24(0)
, m_Nb_Swamp7(0)
, m_Nb_Swamp3(0)
, m_Nb_Swamp2(0)
, m_Nb_Swamp1(0)
, m_Nb_SwampWater1(0)
, m_Nb_SwampHive6(0)
, m_Nb_TicallaPalm(0)
, m_Nb_TicallaGrass(0)
, m_Nb_Dungeon24(0)
, m_Nb_Dungeon7(0)
, m_Nb_Dungeon3(0)
, m_Nb_Dungeon2(0)
, m_Nb_Dungeon1(0)
, m_Nb_Shadow1(0)
, m_Nb_Outcrop1(0)
, m_Nb_Outcrop3(0)
{
}

// The destructor
//
CMaterialEdit::~CMaterialEdit()
{
}

// Synchronize members and control
//
void CMaterialEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ED_MAT_GRASS24, m_Nb_Grass24);
	DDV_MinMaxUInt(pDX, m_Nb_Grass24, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GRASS7, m_Nb_Grass7);
	DDV_MinMaxUInt(pDX, m_Nb_Grass7, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GRASS3, m_Nb_Grass3);
	DDV_MinMaxUInt(pDX, m_Nb_Grass3, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GRASS2, m_Nb_Grass2);
	DDV_MinMaxUInt(pDX, m_Nb_Grass2, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GRASS1, m_Nb_Grass1);
	DDV_MinMaxUInt(pDX, m_Nb_Grass1, 0, 999);
	DDX_Control(pDX, IDC_SP_MAT_GRASS24, m_Sp_Grass24);
	DDX_Control(pDX, IDC_SP_MAT_GRASS7, m_Sp_Grass7);
	DDX_Control(pDX, IDC_SP_MAT_GRASS3, m_Sp_Grass3);
	DDX_Control(pDX, IDC_SP_MAT_GRASS2, m_Sp_Grass2);
	DDX_Control(pDX, IDC_SP_MAT_GRASS1, m_Sp_Grass1);

	DDX_Text(pDX, IDC_ED_MAT_ROCK24, m_Nb_Rock24);
	DDV_MinMaxUInt(pDX, m_Nb_Rock24, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_ROCK7, m_Nb_Rock7);
	DDV_MinMaxUInt(pDX, m_Nb_Rock7, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_ROCK3, m_Nb_Rock3);
	DDV_MinMaxUInt(pDX, m_Nb_Rock3, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_ROCK2, m_Nb_Rock2);
	DDV_MinMaxUInt(pDX, m_Nb_Rock2, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_ROCK1, m_Nb_Rock1);
	DDV_MinMaxUInt(pDX, m_Nb_Rock1, 0, 999);
	DDX_Control(pDX, IDC_SP_MAT_ROCK24, m_Sp_Rock24);
	DDX_Control(pDX, IDC_SP_MAT_ROCK7, m_Sp_Rock7);
	DDX_Control(pDX, IDC_SP_MAT_ROCK3, m_Sp_Rock3);
	DDX_Control(pDX, IDC_SP_MAT_ROCK2, m_Sp_Rock2);
	DDX_Control(pDX, IDC_SP_MAT_ROCK1, m_Sp_Rock1);

	DDX_Text(pDX, IDC_ED_MAT_SAND7, m_Nb_Sand7);
	DDV_MinMaxUInt(pDX, m_Nb_Sand7, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_SAND3, m_Nb_Sand3);
	DDV_MinMaxUInt(pDX, m_Nb_Sand3, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_SAND2, m_Nb_Sand2);
	DDV_MinMaxUInt(pDX, m_Nb_Sand2, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_SAND1, m_Nb_Sand1);
	DDV_MinMaxUInt(pDX, m_Nb_Sand1, 0, 999);
	DDX_Control(pDX, IDC_SP_MAT_SAND7, m_Sp_Sand7);
	DDX_Control(pDX, IDC_SP_MAT_SAND3, m_Sp_Sand3);
	DDX_Control(pDX, IDC_SP_MAT_SAND2, m_Sp_Sand2);
	DDX_Control(pDX, IDC_SP_MAT_SAND1, m_Sp_Sand1);

	DDX_Text(pDX, IDC_ED_MAT_TREE15, m_Nb_Tree15);
	DDV_MinMaxUInt(pDX, m_Nb_Tree15, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_TREE12, m_Nb_Tree12);
	DDV_MinMaxUInt(pDX, m_Nb_Tree12, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_TREE11, m_Nb_Tree11);
	DDV_MinMaxUInt(pDX, m_Nb_Tree11, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_TREE10, m_Nb_Tree10);
	DDV_MinMaxUInt(pDX, m_Nb_Tree10, 0, 999);
	DDX_Control(pDX, IDC_SP_MAT_TREE15, m_Sp_Tree15);
	DDX_Control(pDX, IDC_SP_MAT_TREE12, m_Sp_Tree12);
	DDX_Control(pDX, IDC_SP_MAT_TREE11, m_Sp_Tree11);
	DDX_Control(pDX, IDC_SP_MAT_TREE10, m_Sp_Tree10);

	DDX_Text(pDX, IDC_ED_MAT_GLACIER6, m_Nb_Glacier6);
	DDV_MinMaxUInt(pDX, m_Nb_Glacier6, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GLACIER4, m_Nb_Glacier4);
	DDV_MinMaxUInt(pDX, m_Nb_Glacier4, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GLACIER3, m_Nb_Glacier3);
	DDV_MinMaxUInt(pDX, m_Nb_Glacier3, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GLACIER1, m_Nb_Glacier1);
	DDV_MinMaxUInt(pDX, m_Nb_Glacier1, 0, 999);
	DDX_Control(pDX, IDC_SP_MAT_GLACIER6, m_Sp_Glacier6);
	DDX_Control(pDX, IDC_SP_MAT_GLACIER4, m_Sp_Glacier4);
	DDX_Control(pDX, IDC_SP_MAT_GLACIER3, m_Sp_Glacier3);
	DDX_Control(pDX, IDC_SP_MAT_GLACIER1, m_Sp_Glacier1);

	DDX_Text(pDX, IDC_ED_MAT_LAVAFIELD7, m_Nb_LavaField7);
	DDV_MinMaxUInt(pDX, m_Nb_LavaField7, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_LAVAFIELD2, m_Nb_LavaField2);
	DDV_MinMaxUInt(pDX, m_Nb_LavaField2, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_LAVAFIELD1, m_Nb_LavaField1);
	DDV_MinMaxUInt(pDX, m_Nb_LavaField1, 0, 999);
	DDX_Control(pDX, IDC_SP_MAT_LAVAFIELD7, m_Sp_LavaField7);
	DDX_Control(pDX, IDC_SP_MAT_LAVAFIELD2, m_Sp_LavaField2);
	DDX_Control(pDX, IDC_SP_MAT_LAVAFIELD1, m_Sp_LavaField1);

	DDX_Text(pDX, IDC_ED_MAT_WALL4, m_Nb_Wall4);
	DDV_MinMaxUInt(pDX, m_Nb_Wall4, 0, 999);
	DDX_Control(pDX, IDC_SP_MAT_WALL4, m_Sp_Wall4);

	DDX_Text(pDX, IDC_ED_MAT_ROAD5, m_Nb_Road5);
	DDV_MinMaxUInt(pDX, m_Nb_Road5, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_ROAD2, m_Nb_Road2);
	DDV_MinMaxUInt(pDX, m_Nb_Road2, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_ROAD1, m_Nb_Road1);
	DDV_MinMaxUInt(pDX, m_Nb_Road1, 0, 999);
	DDX_Control(pDX, IDC_SP_MAT_ROAD5, m_Sp_Road5);
	DDX_Control(pDX, IDC_SP_MAT_ROAD2, m_Sp_Road2);
	DDX_Control(pDX, IDC_SP_MAT_ROAD1, m_Sp_Road1);

	DDX_Text(pDX, IDC_ED_MAT_WATER1, m_Nb_Water1);
	DDV_MinMaxUInt(pDX, m_Nb_Water1, 0, 999);
	DDX_Control(pDX, IDC_SP_MAT_WATER1, m_Sp_Water1);
	DDX_Text(pDX, IDC_ED_MAT_LAVA1, m_Nb_Lava1);
	DDV_MinMaxUInt(pDX, m_Nb_Lava1, 0, 999);
	DDX_Control(pDX, IDC_SP_MAT_LAVA1, m_Sp_Lava1);
	DDX_Text(pDX, IDC_ED_MAT_ICE1, m_Nb_Ice1);
	DDV_MinMaxUInt(pDX, m_Nb_Ice1, 0, 999);
	DDX_Control(pDX, IDC_SP_MAT_ICE1, m_Sp_Ice1);

	DDX_Text(pDX, IDC_ED_MAT_SNOW2, m_Nb_Snow2);
	DDV_MinMaxUInt(pDX, m_Nb_Snow2, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_SNOW1, m_Nb_Snow1);
	DDV_MinMaxUInt(pDX, m_Nb_Snow1, 0, 999);
	DDX_Control(pDX, IDC_SP_MAT_SNOW2, m_Sp_Snow2);
	DDX_Control(pDX, IDC_SP_MAT_SNOW1, m_Sp_Snow1);

	DDX_Text(pDX, IDC_ED_MAT_RUIN3, m_Nb_Ruin3);
	DDV_MinMaxUInt(pDX, m_Nb_Ruin3, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_RUIN2, m_Nb_Ruin2);
	DDV_MinMaxUInt(pDX, m_Nb_Ruin2, 0, 999);
	DDX_Control(pDX, IDC_SP_MAT_RUIN3, m_Sp_Ruin3);
	DDX_Control(pDX, IDC_SP_MAT_RUIN2, m_Sp_Ruin2);

	DDX_Text(pDX, IDC_ED_MAT_GLYPHA, m_Nb_GlyphA);
	DDV_MinMaxUInt(pDX, m_Nb_GlyphA, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GLYPHG, m_Nb_GlyphG);
	DDV_MinMaxUInt(pDX, m_Nb_GlyphG, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GLYPHI, m_Nb_GlyphI);
	DDV_MinMaxUInt(pDX, m_Nb_GlyphI, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GLYPHV, m_Nb_GlyphV);
	DDV_MinMaxUInt(pDX, m_Nb_GlyphV, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GLYPHD, m_Nb_GlyphD);
	DDV_MinMaxUInt(pDX, m_Nb_GlyphD, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GLYPHB, m_Nb_GlyphB);
	DDV_MinMaxUInt(pDX, m_Nb_GlyphB, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GLYPHK, m_Nb_GlyphK);
	DDV_MinMaxUInt(pDX, m_Nb_GlyphK, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GLYPHE, m_Nb_GlyphE);
	DDV_MinMaxUInt(pDX, m_Nb_GlyphE, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GLYPHM, m_Nb_GlyphM);
	DDV_MinMaxUInt(pDX, m_Nb_GlyphM, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GLYPHL, m_Nb_GlyphL);
	DDV_MinMaxUInt(pDX, m_Nb_GlyphL, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GLYPHS, m_Nb_GlyphS);
	DDV_MinMaxUInt(pDX, m_Nb_GlyphS, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GLYPHR, m_Nb_GlyphR);
	DDV_MinMaxUInt(pDX, m_Nb_GlyphR, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GLYPHJ, m_Nb_GlyphJ);
	DDV_MinMaxUInt(pDX, m_Nb_GlyphJ, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GLYPHW, m_Nb_GlyphW);
	DDV_MinMaxUInt(pDX, m_Nb_GlyphW, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GLYPHP, m_Nb_GlyphP);
	DDV_MinMaxUInt(pDX, m_Nb_GlyphP, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GLYPHO, m_Nb_GlyphO);
	DDV_MinMaxUInt(pDX, m_Nb_GlyphO, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GLYPHN, m_Nb_GlyphN);
	DDV_MinMaxUInt(pDX, m_Nb_GlyphN, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GLYPHC, m_Nb_GlyphC);
	DDV_MinMaxUInt(pDX, m_Nb_GlyphC, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GLYPHT, m_Nb_GlyphT);
	DDV_MinMaxUInt(pDX, m_Nb_GlyphT, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_GLYPHU, m_Nb_GlyphU);
	DDV_MinMaxUInt(pDX, m_Nb_GlyphU, 0, 999);
	DDX_Control(pDX, IDC_SP_MAT_GLYPHA, m_Sp_GlyphA);
	DDX_Control(pDX, IDC_SP_MAT_GLYPHG, m_Sp_GlyphG);
	DDX_Control(pDX, IDC_SP_MAT_GLYPHI, m_Sp_GlyphI);
	DDX_Control(pDX, IDC_SP_MAT_GLYPHV, m_Sp_GlyphV);
	DDX_Control(pDX, IDC_SP_MAT_GLYPHD, m_Sp_GlyphD);
	DDX_Control(pDX, IDC_SP_MAT_GLYPHB, m_Sp_GlyphB);
	DDX_Control(pDX, IDC_SP_MAT_GLYPHK, m_Sp_GlyphK);
	DDX_Control(pDX, IDC_SP_MAT_GLYPHE, m_Sp_GlyphE);
	DDX_Control(pDX, IDC_SP_MAT_GLYPHM, m_Sp_GlyphM);
	DDX_Control(pDX, IDC_SP_MAT_GLYPHL, m_Sp_GlyphL);
	DDX_Control(pDX, IDC_SP_MAT_GLYPHS, m_Sp_GlyphS);
	DDX_Control(pDX, IDC_SP_MAT_GLYPHR, m_Sp_GlyphR);
	DDX_Control(pDX, IDC_SP_MAT_GLYPHJ, m_Sp_GlyphJ);
	DDX_Control(pDX, IDC_SP_MAT_GLYPHW, m_Sp_GlyphW);
	DDX_Control(pDX, IDC_SP_MAT_GLYPHP, m_Sp_GlyphP);
	DDX_Control(pDX, IDC_SP_MAT_GLYPHO, m_Sp_GlyphO);
	DDX_Control(pDX, IDC_SP_MAT_GLYPHN, m_Sp_GlyphN);
	DDX_Control(pDX, IDC_SP_MAT_GLYPHC, m_Sp_GlyphC);
	DDX_Control(pDX, IDC_SP_MAT_GLYPHT, m_Sp_GlyphT);
	DDX_Control(pDX, IDC_SP_MAT_GLYPHU, m_Sp_GlyphU);

	DDX_Text(pDX, IDC_ED_MAT_CASTLE_BCORNER, m_Nb_CastleBaseCorner);
	DDV_MinMaxUInt(pDX, m_Nb_CastleBaseCorner, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_CASTLE_BSTRAIGHT, m_Nb_CastleBaseStraight);
	DDV_MinMaxUInt(pDX, m_Nb_CastleBaseStraight, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_CASTLE_BEND, m_Nb_CastleBaseEnd);
	DDV_MinMaxUInt(pDX, m_Nb_CastleBaseEnd, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_CASTLE_WCORNER, m_Nb_CastleWallCorner);
	DDV_MinMaxUInt(pDX, m_Nb_CastleWallCorner, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_CASTLE_WSTRAIGHT, m_Nb_CastleWallStraight);
	DDV_MinMaxUInt(pDX, m_Nb_CastleWallStraight, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_CASTLE_WEND, m_Nb_CastleWallEnd);
	DDV_MinMaxUInt(pDX, m_Nb_CastleWallEnd, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_CASTLE_9, m_Nb_Castle9);
	DDV_MinMaxUInt(pDX, m_Nb_Castle9, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_CASTLE_7, m_Nb_Castle7);
	DDV_MinMaxUInt(pDX, m_Nb_Castle7, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_CASTLE_1, m_Nb_Castle1);
	DDV_MinMaxUInt(pDX, m_Nb_Castle1, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_CASTLE_BATTLEMENT, m_Nb_CastleBattlement);
	DDV_MinMaxUInt(pDX, m_Nb_CastleBattlement, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_CASTLE_DOOR, m_Nb_CastleDoor);
	DDV_MinMaxUInt(pDX, m_Nb_CastleDoor, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_CASTLE_LADDER, m_Nb_CastleLadder);
	DDV_MinMaxUInt(pDX, m_Nb_CastleLadder, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_CASTLE_FLAG, m_Nb_CastleFlag);
	DDV_MinMaxUInt(pDX, m_Nb_CastleFlag, 0, 999);

	DDX_Control(pDX, IDC_SP_MAT_CASTLE_BCORNER, m_Sp_CastleBaseCorner);
	DDX_Control(pDX, IDC_SP_MAT_CASTLE_BSTRAIGHT, m_Sp_CastleBaseStraight);
	DDX_Control(pDX, IDC_SP_MAT_CASTLE_BEND, m_Sp_CastleBaseEnd);
	DDX_Control(pDX, IDC_SP_MAT_CASTLE_WCORNER, m_Sp_CastleWallCorner);
	DDX_Control(pDX, IDC_SP_MAT_CASTLE_WSTRAIGHT, m_Sp_CastleWallStraight);
	DDX_Control(pDX, IDC_SP_MAT_CASTLE_WEND, m_Sp_CastleWallEnd);
	DDX_Control(pDX, IDC_SP_MAT_CASTLE_9, m_Sp_Castle9);
	DDX_Control(pDX, IDC_SP_MAT_CASTLE_7, m_Sp_Castle7);
	DDX_Control(pDX, IDC_SP_MAT_CASTLE_1, m_Sp_Castle1);
	DDX_Control(pDX, IDC_SP_MAT_CASTLE_BATTLEMENT, m_Sp_CastleBattlement);
	DDX_Control(pDX, IDC_SP_MAT_CASTLE_DOOR, m_Sp_CastleDoor);
	DDX_Control(pDX, IDC_SP_MAT_CASTLE_LADDER, m_Sp_CastleLadder);
	DDX_Control(pDX, IDC_SP_MAT_CASTLE_FLAG, m_Sp_CastleFlag);

	DDX_Text(pDX, IDC_ED_MAT_MARVEL_CONCRETE7, m_Nb_MarvelConcrete7);
	DDV_MinMaxUInt(pDX, m_Nb_MarvelConcrete7, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_MARVEL_CONCRETE2, m_Nb_MarvelConcrete2);
	DDV_MinMaxUInt(pDX, m_Nb_MarvelConcrete2, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_MARVEL_CONCRETE1, m_Nb_MarvelConcrete1);
	DDV_MinMaxUInt(pDX, m_Nb_MarvelConcrete1, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_MARVEL_ASPHALT7, m_Nb_MarvelAsphalt7);
	DDV_MinMaxUInt(pDX, m_Nb_MarvelAsphalt7, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_MARVEL_ASPHALT2, m_Nb_MarvelAsphalt2);
	DDV_MinMaxUInt(pDX, m_Nb_MarvelAsphalt2, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_MARVEL_ASPHALT1, m_Nb_MarvelAsphalt1);
	DDV_MinMaxUInt(pDX, m_Nb_MarvelAsphalt1, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_MARVEL_RUIN6, m_Nb_MarvelRuin6);
	DDV_MinMaxUInt(pDX, m_Nb_MarvelRuin6, 0, 999);

	DDX_Control(pDX, IDC_SP_MAT_MARVEL_CONCRETE7, m_Sp_MarvelConcrete7);
	DDX_Control(pDX, IDC_SP_MAT_MARVEL_CONCRETE2, m_Sp_MarvelConcrete2);
	DDX_Control(pDX, IDC_SP_MAT_MARVEL_CONCRETE1, m_Sp_MarvelConcrete1);
	DDX_Control(pDX, IDC_SP_MAT_MARVEL_ASPHALT7, m_Sp_MarvelAsphalt7);
	DDX_Control(pDX, IDC_SP_MAT_MARVEL_ASPHALT2, m_Sp_MarvelAsphalt2);
	DDX_Control(pDX, IDC_SP_MAT_MARVEL_ASPHALT1, m_Sp_MarvelAsphalt1);
	DDX_Control(pDX, IDC_SP_MAT_MARVEL_RUIN6, m_Sp_MarvelRuin6);

	DDX_Text(pDX, IDC_ED_MAT_SWAMP24, m_Nb_Swamp24);
	DDV_MinMaxUInt(pDX, m_Nb_Swamp24, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_SWAMP7, m_Nb_Swamp7);
	DDV_MinMaxUInt(pDX, m_Nb_Swamp7, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_SWAMP3, m_Nb_Swamp3);
	DDV_MinMaxUInt(pDX, m_Nb_Swamp3, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_SWAMP2, m_Nb_Swamp2);
	DDV_MinMaxUInt(pDX, m_Nb_Swamp2, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_SWAMP1, m_Nb_Swamp1);
	DDV_MinMaxUInt(pDX, m_Nb_Swamp1, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_SWAMP_WATER1, m_Nb_SwampWater1);
	DDV_MinMaxUInt(pDX, m_Nb_SwampWater1, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_SWAMP_HIVE6, m_Nb_SwampHive6);
	DDV_MinMaxUInt(pDX, m_Nb_SwampHive6, 0, 999);

	DDX_Control(pDX, IDC_SP_MAT_SWAMP24, m_Sp_Swamp24);
	DDX_Control(pDX, IDC_SP_MAT_SWAMP7, m_Sp_Swamp7);
	DDX_Control(pDX, IDC_SP_MAT_SWAMP3, m_Sp_Swamp3);
	DDX_Control(pDX, IDC_SP_MAT_SWAMP2, m_Sp_Swamp2);
	DDX_Control(pDX, IDC_SP_MAT_SWAMP1, m_Sp_Swamp1);
	DDX_Control(pDX, IDC_SP_MAT_SWAMP_WATER1, m_Sp_SwampWater1);
	DDX_Control(pDX, IDC_SP_MAT_SWAMP_HIVE6, m_Sp_SwampHive6);

	DDX_Text(pDX, IDC_ED_MAT_TICALLAPALM, m_Nb_TicallaPalm);
	DDX_Text(pDX, IDC_ED_MAT_TICALLAGRASS, m_Nb_TicallaGrass);
	
	DDX_Control(pDX, IDC_SP_MAT_TICALLAPALM, m_Sp_TicallaPalm);
	DDX_Control(pDX, IDC_SP_MAT_TICALLAGRASS, m_Sp_TicallaGrass);

	DDX_Text(pDX, IDC_ED_MAT_DUNGEON24, m_Nb_Dungeon24);
	DDV_MinMaxUInt(pDX, m_Nb_Dungeon24, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_DUNGEON7, m_Nb_Dungeon7);
	DDV_MinMaxUInt(pDX, m_Nb_Dungeon7, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_DUNGEON3, m_Nb_Dungeon3);
	DDV_MinMaxUInt(pDX, m_Nb_Dungeon3, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_DUNGEON2, m_Nb_Dungeon2);
	DDV_MinMaxUInt(pDX, m_Nb_Dungeon2, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_DUNGEON1, m_Nb_Dungeon1);
	DDV_MinMaxUInt(pDX, m_Nb_Dungeon1, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_DUNGEON_SHADOW1, m_Nb_Shadow1);
	DDV_MinMaxUInt(pDX, m_Nb_Shadow1, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_DUNGEON_OUTCROP3, m_Nb_Outcrop3);
	DDV_MinMaxUInt(pDX, m_Nb_Outcrop3, 0, 999);
	DDX_Text(pDX, IDC_ED_MAT_DUNGEON_OUTCROP1, m_Nb_Outcrop1);
	DDV_MinMaxUInt(pDX, m_Nb_Outcrop1, 0, 999);

	DDX_Control(pDX, IDC_SP_MAT_DUNGEON24, m_Sp_Dungeon24);
	DDX_Control(pDX, IDC_SP_MAT_DUNGEON7, m_Sp_Dungeon7);
	DDX_Control(pDX, IDC_SP_MAT_DUNGEON3, m_Sp_Dungeon3);
	DDX_Control(pDX, IDC_SP_MAT_DUNGEON2, m_Sp_Dungeon2);
	DDX_Control(pDX, IDC_SP_MAT_DUNGEON1, m_Sp_Dungeon1);
	DDX_Control(pDX, IDC_SP_MAT_DUNGEON_SHADOW1, m_Sp_Shadow1);
	DDX_Control(pDX, IDC_SP_MAT_DUNGEON_OUTCROP3, m_Sp_Outcrop3);
	DDX_Control(pDX, IDC_SP_MAT_DUNGEON_OUTCROP1, m_Sp_Outcrop1);
}

BEGIN_MESSAGE_MAP(CMaterialEdit, CDialog)
	ON_BN_CLICKED(IDC_BT_ERASE_ALL, &CMaterialEdit::OnBnClickedBtEraseAll)
	ON_BN_CLICKED(IDC_BT_ADD_MASTER_SET, &CMaterialEdit::OnBnClickedBtAddMasterSet)
	ON_BN_CLICKED(IDC_BT_ADD_FORGOTTEN_FOREST, &CMaterialEdit::OnBnClickedBtAddForgottenForest)
	ON_BN_CLICKED(IDC_BT_ADD_VOLCAREN_WASTELAND, &CMaterialEdit::OnBnClickedBtAddVolcarenWasteland)
	ON_BN_CLICKED(IDC_BT_ADD_TUNDRA, &CMaterialEdit::OnBnClickedBtAddTundra)
	ON_BN_CLICKED(IDC_BT_ADD_TERRAIN, &CMaterialEdit::OnBnClickedBtAddTerrain)
	ON_BN_CLICKED(IDC_BT_ADD_CASTLE, &CMaterialEdit::OnBnClickedBtAddCastle)
	ON_BN_CLICKED(IDC_BT_SAVE_COLLECTION, &CMaterialEdit::OnBnClickedBtSaveCollection)
	ON_BN_CLICKED(IDC_BT_LOAD_COLLECTION2, &CMaterialEdit::OnBnClickedBtLoadCollection2)
	ON_BN_CLICKED(IDC_BT_ADD_MARVEL, &CMaterialEdit::OnBnClickedBtAddMarvel)
	ON_BN_CLICKED(IDC_BT_ADD_SWARM, &CMaterialEdit::OnBnClickedBtAddSwarm)
	ON_BN_CLICKED(IDC_BT_ADD_TICALLA_JUNGLE, &CMaterialEdit::OnBnClickedBtAddTicallaJungle)
	ON_BN_CLICKED(IDC_BT_ADD_DUNGEON, &CMaterialEdit::OnBnClickedBtAddDungeon)
END_MESSAGE_MAP()

// The dialog is initialising
//
BOOL CMaterialEdit::OnInitDialog()
{
	// Call the base class
	CDialog::OnInitDialog();

	m_Sp_Grass24.SetRange(0,999);
	m_Sp_Grass7.SetRange(0,999);
	m_Sp_Grass3.SetRange(0,999);
	m_Sp_Grass2.SetRange(0,999);
	m_Sp_Grass1.SetRange(0,999);

	m_Sp_Rock24.SetRange(0,999);
	m_Sp_Rock7.SetRange(0,999);
	m_Sp_Rock3.SetRange(0,999);
	m_Sp_Rock2.SetRange(0,999);
	m_Sp_Rock1.SetRange(0,999);

	m_Sp_Sand7.SetRange(0,999);
	m_Sp_Sand3.SetRange(0,999);
	m_Sp_Sand2.SetRange(0,999);
	m_Sp_Sand1.SetRange(0,999);

	m_Sp_Tree15.SetRange(0,999);
	m_Sp_Tree12.SetRange(0,999);
	m_Sp_Tree11.SetRange(0,999);
	m_Sp_Tree10.SetRange(0,999);

	m_Sp_Glacier6.SetRange(0,999);
	m_Sp_Glacier4.SetRange(0,999);
	m_Sp_Glacier3.SetRange(0,999);
	m_Sp_Glacier1.SetRange(0,999);

	m_Sp_LavaField7.SetRange(0,999);
	m_Sp_LavaField2.SetRange(0,999);
	m_Sp_LavaField1.SetRange(0,999);

	m_Sp_Wall4.SetRange(0,999);

	m_Sp_Road5.SetRange(0,999);
	m_Sp_Road2.SetRange(0,999);
	m_Sp_Road1.SetRange(0,999);

	m_Sp_Water1.SetRange(0,999);
	m_Sp_Lava1.SetRange(0,999);
	m_Sp_Ice1.SetRange(0,999);
	
	m_Sp_Snow2.SetRange(0,999);
	m_Sp_Snow1.SetRange(0,999);

	m_Sp_Ruin3.SetRange(0,999);
	m_Sp_Ruin2.SetRange(0,999);

	m_Sp_GlyphA.SetRange(0,999);
	m_Sp_GlyphG.SetRange(0,999);
	m_Sp_GlyphI.SetRange(0,999);
	m_Sp_GlyphV.SetRange(0,999);
	m_Sp_GlyphD.SetRange(0,999);
	m_Sp_GlyphB.SetRange(0,999);
	m_Sp_GlyphK.SetRange(0,999);
	m_Sp_GlyphE.SetRange(0,999);
	m_Sp_GlyphM.SetRange(0,999);
	m_Sp_GlyphL.SetRange(0,999);
	m_Sp_GlyphS.SetRange(0,999);
	m_Sp_GlyphR.SetRange(0,999);
	m_Sp_GlyphJ.SetRange(0,999);
	m_Sp_GlyphW.SetRange(0,999);
	m_Sp_GlyphP.SetRange(0,999);
	m_Sp_GlyphO.SetRange(0,999);
	m_Sp_GlyphN.SetRange(0,999);
	m_Sp_GlyphC.SetRange(0,999);
	m_Sp_GlyphT.SetRange(0,999);
	m_Sp_GlyphU.SetRange(0,999);

	m_Sp_CastleBaseCorner.SetRange(0,999);
	m_Sp_CastleBaseStraight.SetRange(0,999);
	m_Sp_CastleBaseEnd.SetRange(0,999);
	m_Sp_CastleWallCorner.SetRange(0,999);
	m_Sp_CastleWallStraight.SetRange(0,999);
	m_Sp_CastleWallEnd.SetRange(0,999);
	m_Sp_Castle9.SetRange(0,999);
	m_Sp_Castle7.SetRange(0,999);
	m_Sp_Castle1.SetRange(0,999);
	m_Sp_CastleBattlement.SetRange(0,999);
	m_Sp_CastleDoor.SetRange(0,999);
	m_Sp_CastleLadder.SetRange(0,999);
	m_Sp_CastleFlag.SetRange(0,999);

	m_Sp_MarvelConcrete7.SetRange(0,999);
	m_Sp_MarvelConcrete2.SetRange(0,999);
	m_Sp_MarvelConcrete1.SetRange(0,999);
	m_Sp_MarvelAsphalt7.SetRange(0,999);
	m_Sp_MarvelAsphalt2.SetRange(0,999);
	m_Sp_MarvelAsphalt1.SetRange(0,999);
	m_Sp_MarvelRuin6.SetRange(0,999);

	m_Sp_Swamp24.SetRange(0,999);
	m_Sp_Swamp7.SetRange(0,999);
	m_Sp_Swamp3.SetRange(0,999);
	m_Sp_Swamp2.SetRange(0,999);
	m_Sp_Swamp1.SetRange(0,999);
	m_Sp_SwampWater1.SetRange(0,999);
	m_Sp_SwampHive6.SetRange(0,999);

	m_Sp_TicallaPalm.SetRange(0,999);
	m_Sp_TicallaGrass.SetRange(0,999);

	m_Sp_Dungeon24.SetRange(0,999);
	m_Sp_Dungeon7.SetRange(0,999);
	m_Sp_Dungeon3.SetRange(0,999);
	m_Sp_Dungeon2.SetRange(0,999);
	m_Sp_Dungeon1.SetRange(0,999);
	m_Sp_Shadow1.SetRange(0,999);
	m_Sp_Outcrop3.SetRange(0,999);
	m_Sp_Outcrop1.SetRange(0,999);

	return TRUE;
}

// The user want erase all the data
//
void CMaterialEdit::OnBnClickedBtEraseAll()
{
	m_Nb_Grass24 = 0;
	m_Nb_Grass7 = 0;
	m_Nb_Grass3 = 0;
	m_Nb_Grass2 = 0;
	m_Nb_Grass1 = 0;
	m_Nb_Rock24 = 0;
	m_Nb_Rock7 = 0;
	m_Nb_Rock3 = 0;
	m_Nb_Rock2 = 0;
	m_Nb_Rock1 = 0;
	m_Nb_Sand7 = 0;
	m_Nb_Sand3 = 0;
	m_Nb_Sand2 = 0;
	m_Nb_Sand1 = 0;
	m_Nb_Tree15 = 0;
	m_Nb_Tree12 = 0;
	m_Nb_Tree11 = 0;
	m_Nb_Tree10 = 0;
	m_Nb_Glacier6 = 0;
	m_Nb_Glacier4 = 0;
	m_Nb_Glacier3 = 0;
	m_Nb_Glacier1 = 0;
	m_Nb_LavaField7 = 0;
	m_Nb_LavaField2 = 0;
	m_Nb_LavaField1 = 0;
	m_Nb_Wall4 = 0;
	m_Nb_Road5 = 0;
	m_Nb_Road2 = 0;
	m_Nb_Road1 = 0;
	m_Nb_Water1 = 0;
	m_Nb_Lava1 = 0;
	m_Nb_Ice1 = 0;
	m_Nb_Snow2 = 0;
	m_Nb_Snow1 = 0;
	m_Nb_Ruin3 = 0;
	m_Nb_Ruin2 = 0;
	m_Nb_GlyphA = 0;
	m_Nb_GlyphG = 0;
	m_Nb_GlyphI = 0;
	m_Nb_GlyphV = 0;
	m_Nb_GlyphD = 0;
	m_Nb_GlyphB = 0;
	m_Nb_GlyphK = 0;
	m_Nb_GlyphE = 0;
	m_Nb_GlyphM = 0;
	m_Nb_GlyphL = 0;
	m_Nb_GlyphR = 0;
	m_Nb_GlyphS = 0;
	m_Nb_GlyphJ = 0;
	m_Nb_GlyphW = 0;
	m_Nb_GlyphP = 0;
	m_Nb_GlyphO = 0;
	m_Nb_GlyphN = 0;
	m_Nb_GlyphC = 0;
	m_Nb_GlyphT = 0;
	m_Nb_GlyphU = 0;
	m_Nb_CastleBaseCorner = 0;
	m_Nb_CastleBaseStraight = 0;
	m_Nb_CastleBaseEnd = 0;
	m_Nb_CastleWallCorner = 0;
	m_Nb_CastleWallStraight = 0;
	m_Nb_CastleWallEnd = 0;
	m_Nb_Castle9 = 0;
	m_Nb_Castle7 = 0;
	m_Nb_Castle1 = 0;
	m_Nb_CastleBattlement = 0;
	m_Nb_CastleDoor = 0;
	m_Nb_CastleLadder = 0;
	m_Nb_CastleFlag = 0;
	m_Nb_MarvelConcrete7 = 0;
	m_Nb_MarvelConcrete2 = 0;
	m_Nb_MarvelConcrete1 = 0;
	m_Nb_MarvelAsphalt7 = 0;
	m_Nb_MarvelAsphalt2 = 0;
	m_Nb_MarvelAsphalt1 = 0;
	m_Nb_MarvelRuin6 = 0;
	m_Nb_Swamp24 = 0;
	m_Nb_Swamp7 = 0;
	m_Nb_Swamp3 = 0;
	m_Nb_Swamp2 = 0;
	m_Nb_Swamp1 = 0;
	m_Nb_SwampWater1 = 0;
	m_Nb_SwampHive6 = 0;
	m_Nb_TicallaPalm = 0;
	m_Nb_TicallaGrass = 0;
	m_Nb_Dungeon24 = 0;
	m_Nb_Dungeon7 = 0;
	m_Nb_Dungeon3 = 0;
	m_Nb_Dungeon2 = 0;
	m_Nb_Dungeon1 = 0;
	m_Nb_Shadow1 = 0;
	m_Nb_Outcrop3 = 0;
	m_Nb_Outcrop1 = 0;

	UpdateData( FALSE );
}

// The user want add a master set
//
void CMaterialEdit::OnBnClickedBtAddMasterSet()
{
	UpdateData( TRUE );

	m_Nb_Grass24 += 6;
	m_Nb_Grass7 += 5;
	m_Nb_Grass3 += 5;
	m_Nb_Grass2 += 5;
	m_Nb_Grass1 += 16;
	m_Nb_Rock24 += 2;
	m_Nb_Rock7 += 3;
	m_Nb_Rock3 += 3;
	m_Nb_Rock2 += 3;
	m_Nb_Rock1 += 6;
	m_Nb_Sand7 += 2;
	m_Nb_Sand3 += 2;
	m_Nb_Sand2 += 2;
	m_Nb_Sand1 += 4;
	m_Nb_Water1 += 21;
	m_Nb_Ruin3 += 1;
	m_Nb_Ruin2 += 1;
	m_Nb_GlyphA += 1;
	m_Nb_GlyphG += 1;
	m_Nb_GlyphI += 1;
	m_Nb_GlyphV += 1;
	m_Nb_GlyphD += 1;
	m_Nb_GlyphB += 2;
	m_Nb_GlyphK += 1;
	m_Nb_GlyphE += 1;
	m_Nb_GlyphM += 1;

	UpdateData( FALSE );
}

// The user want add a Forgetten forest
//
void CMaterialEdit::OnBnClickedBtAddForgottenForest()
{
	UpdateData( TRUE );

	m_Nb_Tree15 += 1;
	m_Nb_Tree12 += 1;
	m_Nb_Tree11 += 2;
	m_Nb_Tree10 += 1;
	m_Nb_Wall4 += 2;
	m_Nb_Road5 += 1;
	m_Nb_Road2 += 8;
	m_Nb_Road1 += 8;

	UpdateData( FALSE );
}

// The user want add a Volcaren wasteland
//
void CMaterialEdit::OnBnClickedBtAddVolcarenWasteland()
{
	UpdateData( TRUE );

	m_Nb_LavaField7 += 4;
	m_Nb_LavaField2 += 5;
	m_Nb_LavaField1 += 5;
	m_Nb_Lava1 += 11;

	UpdateData( FALSE );
}

// The user want add a Thaelenk Tundra
//
void CMaterialEdit::OnBnClickedBtAddTundra()
{
	m_Nb_Glacier1 += 3;
	m_Nb_Glacier3 += 1;
	m_Nb_Glacier4 += 1;
	m_Nb_Glacier6 += 1;
	m_Nb_Snow2 += 12;
	m_Nb_Snow1 += 12;
	m_Nb_Ice1 += 21;

	UpdateData( FALSE );
}

// The user want add a terrain set
//
void CMaterialEdit::OnBnClickedBtAddTerrain()
{
	UpdateData( TRUE );

	m_Nb_Grass24 += 6;
	m_Nb_Grass7 += 5;
	m_Nb_Grass3 += 5;
	m_Nb_Grass2 += 5;
	m_Nb_Grass1 += 16;
	m_Nb_Rock24 += 2;
	m_Nb_Rock7 += 3;
	m_Nb_Rock3 += 3;
	m_Nb_Rock2 += 3;
	m_Nb_Rock1 += 6;
	m_Nb_Sand7 += 2;
	m_Nb_Sand3 += 2;
	m_Nb_Sand2 += 2;
	m_Nb_Sand1 += 4;

	UpdateData( FALSE );
}

// The user want add the caste extension
//
void CMaterialEdit::OnBnClickedBtAddCastle()
{
	UpdateData( TRUE );

	m_Nb_CastleBaseCorner += 10;
	m_Nb_CastleBaseStraight += 7;
	m_Nb_CastleBaseEnd += 4;
	m_Nb_CastleWallCorner += 10;
	m_Nb_CastleWallStraight += 7;
	m_Nb_CastleWallEnd += 4;
	m_Nb_Castle9 += 1;
	m_Nb_Castle7 += 1;
	m_Nb_Castle1 += 21;
	m_Nb_CastleBattlement += 50;
	m_Nb_CastleDoor += 1;
	m_Nb_CastleLadder += 22;
	m_Nb_CastleFlag += 1;

	UpdateData( FALSE );
}

// The user want save the collection
//
void CMaterialEdit::OnBnClickedBtSaveCollection()
{
	UpdateData( TRUE );

	CFileDialog fd( FALSE, _T("*.vsc"), 0, 4|2, _T("Collection VirtualScape (*.vsc)|*.vsc||") );

	if( fd.DoModal()==IDOK )
 	{
		CString Str;
		Str.Format( _T("%i"), m_Nb_Grass24 );
		WritePrivateProfileString( _T("Collection"), _T("Grass24"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Grass7 );
		WritePrivateProfileString( _T("Collection"), _T("Grass7"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Grass3 );
		WritePrivateProfileString( _T("Collection"), _T("Grass3"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Grass2 );
		WritePrivateProfileString( _T("Collection"), _T("Grass2"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Grass1 );
		WritePrivateProfileString( _T("Collection"), _T("Grass1"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Rock24 );
		WritePrivateProfileString( _T("Collection"), _T("Rock24"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Rock7 );
		WritePrivateProfileString( _T("Collection"), _T("Rock7"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Rock3 );
		WritePrivateProfileString( _T("Collection"), _T("Rock3"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Rock2 );
		WritePrivateProfileString( _T("Collection"), _T("Rock2"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Rock1 );
		WritePrivateProfileString( _T("Collection"), _T("Rock1"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Sand7 );
		WritePrivateProfileString( _T("Collection"), _T("Sand7"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Sand3 );
		WritePrivateProfileString( _T("Collection"), _T("Sand3"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Sand2 );
		WritePrivateProfileString( _T("Collection"), _T("Sand2"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Sand1 );
		WritePrivateProfileString( _T("Collection"), _T("Sand1"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Tree15 );
		WritePrivateProfileString( _T("Collection"), _T("Tree15"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Tree12 );
		WritePrivateProfileString( _T("Collection"), _T("Tree12"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Tree11 );
		WritePrivateProfileString( _T("Collection"), _T("Tree11"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Tree10 );
		WritePrivateProfileString( _T("Collection"), _T("Tree10"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Glacier6 );
		WritePrivateProfileString( _T("Collection"), _T("Glacier6"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Glacier4 );
		WritePrivateProfileString( _T("Collection"), _T("Glacier4"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Glacier3 );
		WritePrivateProfileString( _T("Collection"), _T("Glacier3"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Glacier1 );
		WritePrivateProfileString( _T("Collection"), _T("Glacier1"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_LavaField7 );
		WritePrivateProfileString( _T("Collection"), _T("LavaField7"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_LavaField2 );
		WritePrivateProfileString( _T("Collection"), _T("LavaField2"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_LavaField1 );
		WritePrivateProfileString( _T("Collection"), _T("LavaField1"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Wall4 );
		WritePrivateProfileString( _T("Collection"), _T("Wall4"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Road5 );
		WritePrivateProfileString( _T("Collection"), _T("Road5"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Road2 );
		WritePrivateProfileString( _T("Collection"), _T("Road2"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Road1 );
		WritePrivateProfileString( _T("Collection"), _T("Road1"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Water1 );
		WritePrivateProfileString( _T("Collection"), _T("Water1"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Lava1 );
		WritePrivateProfileString( _T("Collection"), _T("Lava1"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Ice1 );
		WritePrivateProfileString( _T("Collection"), _T("Ice1"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Snow2 );
		WritePrivateProfileString( _T("Collection"), _T("Snow2"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Snow1 );
		WritePrivateProfileString( _T("Collection"), _T("Snow1"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Ruin3 );
		WritePrivateProfileString( _T("Collection"), _T("Ruin3"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Ruin2 );
		WritePrivateProfileString( _T("Collection"), _T("Ruin2"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_GlyphA );
		WritePrivateProfileString( _T("Collection"), _T("GlyphA"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_GlyphG );
		WritePrivateProfileString( _T("Collection"), _T("GlyphG"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_GlyphI );
		WritePrivateProfileString( _T("Collection"), _T("GlyphI"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_GlyphV );
		WritePrivateProfileString( _T("Collection"), _T("GlyphV"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_GlyphD );
		WritePrivateProfileString( _T("Collection"), _T("GlyphD"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_GlyphB );
		WritePrivateProfileString( _T("Collection"), _T("GlyphB"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_GlyphK );
		WritePrivateProfileString( _T("Collection"), _T("GlyphK"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_GlyphE );
		WritePrivateProfileString( _T("Collection"), _T("GlyphE"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_GlyphM );
		WritePrivateProfileString( _T("Collection"), _T("GlyphM"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_GlyphL );
		WritePrivateProfileString( _T("Collection"), _T("GlyphL"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_GlyphS );
		WritePrivateProfileString( _T("Collection"), _T("GlyphS"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_GlyphR );
		WritePrivateProfileString( _T("Collection"), _T("GlyphR"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_GlyphJ );
		WritePrivateProfileString( _T("Collection"), _T("GlyphJ"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_GlyphW );
		WritePrivateProfileString( _T("Collection"), _T("GlyphW"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_GlyphP );
		WritePrivateProfileString( _T("Collection"), _T("GlyphP"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_GlyphO );
		WritePrivateProfileString( _T("Collection"), _T("GlyphO"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_GlyphN );
		WritePrivateProfileString( _T("Collection"), _T("GlyphN"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_GlyphC );
		WritePrivateProfileString( _T("Collection"), _T("GlyphC"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_GlyphT );
		WritePrivateProfileString( _T("Collection"), _T("GlyphT"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_GlyphU );
		WritePrivateProfileString( _T("Collection"), _T("GlyphU"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_CastleBaseCorner );
		WritePrivateProfileString( _T("Collection"), _T("CastleBaseCorner"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_CastleBaseStraight );
		WritePrivateProfileString( _T("Collection"), _T("CastleBaseStraight"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_CastleBaseEnd );
		WritePrivateProfileString( _T("Collection"), _T("CastleBaseEnd"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_CastleWallCorner );
		WritePrivateProfileString( _T("Collection"), _T("CastleWallCorner"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_CastleWallStraight );
		WritePrivateProfileString( _T("Collection"), _T("CastleWallStraight"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_CastleWallEnd );
		WritePrivateProfileString( _T("Collection"), _T("CastleWallEnd"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Castle9 );
		WritePrivateProfileString( _T("Collection"), _T("Castle9"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Castle7 );
		WritePrivateProfileString( _T("Collection"), _T("Castle7"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Castle1 );
		WritePrivateProfileString( _T("Collection"), _T("Castle1"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_CastleBattlement );
		WritePrivateProfileString( _T("Collection"), _T("CastleBattlement"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_CastleDoor );
		WritePrivateProfileString( _T("Collection"), _T("CastleDoor"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_CastleLadder );
		WritePrivateProfileString( _T("Collection"), _T("CastleLadder"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_CastleFlag );
		WritePrivateProfileString( _T("Collection"), _T("CastleFlag"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_MarvelConcrete7 );
		WritePrivateProfileString( _T("Collection"), _T("MarvelConcrete7"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_MarvelConcrete2 );
		WritePrivateProfileString( _T("Collection"), _T("MarvelConcrete2"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_MarvelConcrete1 );
		WritePrivateProfileString( _T("Collection"), _T("MarvelConcrete1"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_MarvelAsphalt7 );
		WritePrivateProfileString( _T("Collection"), _T("MarvelAsphalt7"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_MarvelAsphalt2 );
		WritePrivateProfileString( _T("Collection"), _T("MarvelAsphalt2"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_MarvelAsphalt1 );
		WritePrivateProfileString( _T("Collection"), _T("MarvelAsphalt1"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_MarvelRuin6 );
		WritePrivateProfileString( _T("Collection"), _T("MarvelRuin6"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Swamp24 );
		WritePrivateProfileString( _T("Collection"), _T("Swamp24"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Swamp7 );
		WritePrivateProfileString( _T("Collection"), _T("Swamp7"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Swamp3 );
		WritePrivateProfileString( _T("Collection"), _T("Swamp3"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Swamp2 );
		WritePrivateProfileString( _T("Collection"), _T("Swamp2"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Swamp1 );
		WritePrivateProfileString( _T("Collection"), _T("Swamp1"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_SwampWater1 );
		WritePrivateProfileString( _T("Collection"), _T("SwampWater1"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_SwampHive6 );
		WritePrivateProfileString( _T("Collection"), _T("SwampHive6"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_TicallaPalm );
		WritePrivateProfileString( _T("Collection"), _T("TicallaPalm"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_TicallaGrass );
		WritePrivateProfileString( _T("Collection"), _T("TicallaGrass"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Dungeon24 );
		WritePrivateProfileString( _T("Collection"), _T("Dungeon24"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Dungeon7 );
		WritePrivateProfileString( _T("Collection"), _T("Dungeon7"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Dungeon3 );
		WritePrivateProfileString( _T("Collection"), _T("Dungeon3"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Dungeon2 );
		WritePrivateProfileString( _T("Collection"), _T("Dungeon2"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Dungeon1 );
		WritePrivateProfileString( _T("Collection"), _T("Dungeon1"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Shadow1 );
		WritePrivateProfileString( _T("Collection"), _T("Shadow1"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Outcrop3 );
		WritePrivateProfileString( _T("Collection"), _T("Outcrop3"), Str, fd.GetPathName());
		Str.Format( _T("%i"), m_Nb_Outcrop1 );
		WritePrivateProfileString( _T("Collection"), _T("Outcrop1"), Str, fd.GetPathName());
	}
}

// The user want load a collection
//
void CMaterialEdit::OnBnClickedBtLoadCollection2()
{
	CFileDialog fd( TRUE, _T("*.vsc"), 0, 4|2, _T("Collection VirtualScape (*.vsc)|*.vsc||") );

	if( fd.DoModal()==IDOK )
 	{
		CString Str;
		m_Nb_Grass24 = GetPrivateProfileInt( _T("Collection"), _T("Grass24"), 0, fd.GetPathName());
		m_Nb_Grass7 = GetPrivateProfileInt( _T("Collection"), _T("Grass7"), 0, fd.GetPathName());
		m_Nb_Grass3 = GetPrivateProfileInt( _T("Collection"), _T("Grass3"), 0, fd.GetPathName());
		m_Nb_Grass2 = GetPrivateProfileInt( _T("Collection"), _T("Grass2"), 0, fd.GetPathName());
		m_Nb_Grass1 = GetPrivateProfileInt( _T("Collection"), _T("Grass1"), 0, fd.GetPathName());
		m_Nb_Rock24 = GetPrivateProfileInt( _T("Collection"), _T("Rock24"), 0, fd.GetPathName());
		m_Nb_Rock7 = GetPrivateProfileInt( _T("Collection"), _T("Rock7"), 0, fd.GetPathName());
		m_Nb_Rock3 = GetPrivateProfileInt( _T("Collection"), _T("Rock3"), 0, fd.GetPathName());
		m_Nb_Rock2 = GetPrivateProfileInt( _T("Collection"), _T("Rock2"), 0, fd.GetPathName());
		m_Nb_Rock1 = GetPrivateProfileInt( _T("Collection"), _T("Rock1"), 0, fd.GetPathName());
		m_Nb_Sand7 = GetPrivateProfileInt( _T("Collection"), _T("Sand7"), 0, fd.GetPathName());
		m_Nb_Sand3 = GetPrivateProfileInt( _T("Collection"), _T("Sand3"), 0, fd.GetPathName());
		m_Nb_Sand2 = GetPrivateProfileInt( _T("Collection"), _T("Sand2"), 0, fd.GetPathName());
		m_Nb_Sand1 = GetPrivateProfileInt( _T("Collection"), _T("Sand1"), 0, fd.GetPathName());
		m_Nb_Tree15 = GetPrivateProfileInt( _T("Collection"), _T("Tree15"), 0, fd.GetPathName());
		m_Nb_Tree12 = GetPrivateProfileInt( _T("Collection"), _T("Tree12"), 0, fd.GetPathName());
		m_Nb_Tree11 = GetPrivateProfileInt( _T("Collection"), _T("Tree11"), 0, fd.GetPathName());
		m_Nb_Tree10 = GetPrivateProfileInt( _T("Collection"), _T("Tree10"), 0, fd.GetPathName());
		m_Nb_Glacier6 = GetPrivateProfileInt( _T("Collection"), _T("Glacier6"), 0, fd.GetPathName());
		m_Nb_Glacier4 = GetPrivateProfileInt( _T("Collection"), _T("Glacier4"), 0, fd.GetPathName());
		m_Nb_Glacier3 = GetPrivateProfileInt( _T("Collection"), _T("Glacier3"), 0, fd.GetPathName());
		m_Nb_Glacier1 = GetPrivateProfileInt( _T("Collection"), _T("Glacier1"), 0, fd.GetPathName());
		m_Nb_LavaField7 = GetPrivateProfileInt( _T("Collection"), _T("LavaField7"), 0, fd.GetPathName());
		m_Nb_LavaField2 = GetPrivateProfileInt( _T("Collection"), _T("LavaField2"), 0, fd.GetPathName());
		m_Nb_LavaField1 = GetPrivateProfileInt( _T("Collection"), _T("LavaField1"), 0, fd.GetPathName());
		m_Nb_Wall4 = GetPrivateProfileInt( _T("Collection"), _T("Wall4"), 0, fd.GetPathName());
		m_Nb_Road5 = GetPrivateProfileInt( _T("Collection"), _T("Road5"), 0, fd.GetPathName());
		m_Nb_Road2 = GetPrivateProfileInt( _T("Collection"), _T("Road2"), 0, fd.GetPathName());
		m_Nb_Road1 = GetPrivateProfileInt( _T("Collection"), _T("Road1"), 0, fd.GetPathName());
		m_Nb_Water1 = GetPrivateProfileInt( _T("Collection"), _T("Water1"), 0, fd.GetPathName());
		m_Nb_Lava1 = GetPrivateProfileInt( _T("Collection"), _T("Lava1"), 0, fd.GetPathName());
		m_Nb_Ice1 = GetPrivateProfileInt( _T("Collection"), _T("Ice1"), 0, fd.GetPathName());
		m_Nb_Snow2 = GetPrivateProfileInt( _T("Collection"), _T("Snow2"), 0, fd.GetPathName());
		m_Nb_Snow1 = GetPrivateProfileInt( _T("Collection"), _T("Snow1"), 0, fd.GetPathName());
		m_Nb_Ruin3 = GetPrivateProfileInt( _T("Collection"), _T("Ruin3"), 0, fd.GetPathName());
		m_Nb_Ruin2 = GetPrivateProfileInt( _T("Collection"), _T("Ruin2"), 0, fd.GetPathName());
		m_Nb_GlyphA = GetPrivateProfileInt( _T("Collection"), _T("GlyphA"), 0, fd.GetPathName());
		m_Nb_GlyphG = GetPrivateProfileInt( _T("Collection"), _T("GlyphG"), 0, fd.GetPathName());
		m_Nb_GlyphI = GetPrivateProfileInt( _T("Collection"), _T("GlyphI"), 0, fd.GetPathName());
		m_Nb_GlyphV = GetPrivateProfileInt( _T("Collection"), _T("GlyphV"), 0, fd.GetPathName());
		m_Nb_GlyphD = GetPrivateProfileInt( _T("Collection"), _T("GlyphD"), 0, fd.GetPathName());
		m_Nb_GlyphB = GetPrivateProfileInt( _T("Collection"), _T("GlyphB"), 0, fd.GetPathName());
		m_Nb_GlyphK = GetPrivateProfileInt( _T("Collection"), _T("GlyphK"), 0, fd.GetPathName());
		m_Nb_GlyphE = GetPrivateProfileInt( _T("Collection"), _T("GlyphE"), 0, fd.GetPathName());
		m_Nb_GlyphM = GetPrivateProfileInt( _T("Collection"), _T("GlyphM"), 0, fd.GetPathName());
		m_Nb_GlyphL = GetPrivateProfileInt( _T("Collection"), _T("GlyphL"), 0, fd.GetPathName());
		m_Nb_GlyphS = GetPrivateProfileInt( _T("Collection"), _T("GlyphS"), 0, fd.GetPathName());
		m_Nb_GlyphR = GetPrivateProfileInt( _T("Collection"), _T("GlyphR"), 0, fd.GetPathName());
		m_Nb_GlyphJ = GetPrivateProfileInt( _T("Collection"), _T("GlyphJ"), 0, fd.GetPathName());
		m_Nb_GlyphW = GetPrivateProfileInt( _T("Collection"), _T("GlyphW"), 0, fd.GetPathName());
		m_Nb_GlyphP = GetPrivateProfileInt( _T("Collection"), _T("GlyphP"), 0, fd.GetPathName());
		m_Nb_GlyphO = GetPrivateProfileInt( _T("Collection"), _T("GlyphO"), 0, fd.GetPathName());
		m_Nb_GlyphN = GetPrivateProfileInt( _T("Collection"), _T("GlyphN"), 0, fd.GetPathName());
		m_Nb_GlyphC = GetPrivateProfileInt( _T("Collection"), _T("GlyphC"), 0, fd.GetPathName());
		m_Nb_GlyphT = GetPrivateProfileInt( _T("Collection"), _T("GlyphT"), 0, fd.GetPathName());
		m_Nb_GlyphU = GetPrivateProfileInt( _T("Collection"), _T("GlyphU"), 0, fd.GetPathName());
		m_Nb_CastleBaseCorner = GetPrivateProfileInt( _T("Collection"), _T("CastleBaseCorner"), 0, fd.GetPathName());
		m_Nb_CastleBaseStraight = GetPrivateProfileInt( _T("Collection"), _T("CastleBaseStraight"), 0, fd.GetPathName());
		m_Nb_CastleBaseEnd = GetPrivateProfileInt( _T("Collection"), _T("CastleBaseEnd"), 0, fd.GetPathName());
		m_Nb_CastleWallCorner = GetPrivateProfileInt( _T("Collection"), _T("CastleWallCorner"), 0, fd.GetPathName());
		m_Nb_CastleWallStraight = GetPrivateProfileInt( _T("Collection"), _T("CastleWallStraight"), 0, fd.GetPathName());
		m_Nb_CastleWallEnd = GetPrivateProfileInt( _T("Collection"), _T("CastleWallEnd"), 0, fd.GetPathName());
		m_Nb_Castle9 = GetPrivateProfileInt( _T("Collection"), _T("Castle9"), 0, fd.GetPathName());
		m_Nb_Castle7 = GetPrivateProfileInt( _T("Collection"), _T("Castle7"), 0, fd.GetPathName());
		m_Nb_Castle1 = GetPrivateProfileInt( _T("Collection"), _T("Castle1"), 0, fd.GetPathName());
		m_Nb_CastleBattlement = GetPrivateProfileInt( _T("Collection"), _T("CastleBattlement"), 0, fd.GetPathName());
		m_Nb_CastleDoor = GetPrivateProfileInt( _T("Collection"), _T("CastleDoor"), 0, fd.GetPathName());
		m_Nb_CastleLadder = GetPrivateProfileInt( _T("Collection"), _T("CastleLadder"), 0, fd.GetPathName());
		m_Nb_CastleFlag = GetPrivateProfileInt( _T("Collection"), _T("CastleFlag"), 0, fd.GetPathName());
		m_Nb_MarvelConcrete7 = GetPrivateProfileInt( _T("Collection"), _T("MarvelConcrete7"), 0, fd.GetPathName());
		m_Nb_MarvelConcrete2 = GetPrivateProfileInt( _T("Collection"), _T("MarvelConcrete2"), 0, fd.GetPathName());
		m_Nb_MarvelConcrete1 = GetPrivateProfileInt( _T("Collection"), _T("MarvelConcrete1"), 0, fd.GetPathName());
		m_Nb_MarvelAsphalt7 = GetPrivateProfileInt( _T("Collection"), _T("MarvelAsphalt7"), 0, fd.GetPathName());
		m_Nb_MarvelAsphalt2 = GetPrivateProfileInt( _T("Collection"), _T("MarvelAsphalt2"), 0, fd.GetPathName());
		m_Nb_MarvelAsphalt1 = GetPrivateProfileInt( _T("Collection"), _T("MarvelAsphalt1"), 0, fd.GetPathName());
		m_Nb_MarvelRuin6 = GetPrivateProfileInt( _T("Collection"), _T("MarvelRuin6"), 0, fd.GetPathName());
		m_Nb_Swamp24 = GetPrivateProfileInt( _T("Collection"), _T("Swamp24"), 0, fd.GetPathName());
		m_Nb_Swamp7 = GetPrivateProfileInt( _T("Collection"), _T("Swamp7"), 0, fd.GetPathName());
		m_Nb_Swamp3 = GetPrivateProfileInt( _T("Collection"), _T("Swamp3"), 0, fd.GetPathName());
		m_Nb_Swamp2 = GetPrivateProfileInt( _T("Collection"), _T("Swamp2"), 0, fd.GetPathName());
		m_Nb_Swamp1 = GetPrivateProfileInt( _T("Collection"), _T("Swamp1"), 0, fd.GetPathName());
		m_Nb_SwampWater1 = GetPrivateProfileInt( _T("Collection"), _T("SwampWater1"), 0, fd.GetPathName());
		m_Nb_SwampHive6 = GetPrivateProfileInt( _T("Collection"), _T("SwampHive6"), 0, fd.GetPathName());
		m_Nb_TicallaPalm = GetPrivateProfileInt( _T("Collection"), _T("TicallaPalm"), 0, fd.GetPathName());
		m_Nb_TicallaGrass = GetPrivateProfileInt( _T("Collection"), _T("TicallaGrass"), 0, fd.GetPathName());
		m_Nb_Dungeon24 = GetPrivateProfileInt( _T("Collection"), _T("Dungeon24"), 0, fd.GetPathName());
		m_Nb_Dungeon7 = GetPrivateProfileInt( _T("Collection"), _T("Dungeon7"), 0, fd.GetPathName());
		m_Nb_Dungeon3 = GetPrivateProfileInt( _T("Collection"), _T("Dungeon3"), 0, fd.GetPathName());
		m_Nb_Dungeon2 = GetPrivateProfileInt( _T("Collection"), _T("Dungeon2"), 0, fd.GetPathName());
		m_Nb_Dungeon1 = GetPrivateProfileInt( _T("Collection"), _T("Dungeon1"), 0, fd.GetPathName());
		m_Nb_Shadow1 = GetPrivateProfileInt( _T("Collection"), _T("Shadow1"), 0, fd.GetPathName());
		m_Nb_Outcrop3 = GetPrivateProfileInt( _T("Collection"), _T("Outcrop3"), 0, fd.GetPathName());
		m_Nb_Outcrop1 = GetPrivateProfileInt( _T("Collection"), _T("Outcrop1"), 0, fd.GetPathName());

		UpdateData( FALSE );
	}
}

// The user want add the marvel set
//
void CMaterialEdit::OnBnClickedBtAddMarvel()
{
	UpdateData( TRUE );

	m_Nb_MarvelConcrete1 += 4;
	m_Nb_MarvelConcrete2 += 7;
	m_Nb_MarvelConcrete7 += 3;
	m_Nb_MarvelAsphalt1 += 3;
	m_Nb_MarvelAsphalt2 += 8;
	m_Nb_MarvelAsphalt7 += 3;
	m_Nb_Grass1 += 2;
	m_Nb_Grass2 += 8;

	UpdateData( FALSE );
}

// The user want add the swarm of the marro set
//
void CMaterialEdit::OnBnClickedBtAddSwarm()
{
	UpdateData( TRUE );

	m_Nb_Rock7 += 1;
	m_Nb_Rock3 += 1;
	m_Nb_Rock2 += 1;
	m_Nb_Rock1 += 1;
	m_Nb_Sand7 += 5;
	m_Nb_Sand3 += 2;
	m_Nb_Sand2 += 1;
	m_Nb_Sand1 += 1;
	m_Nb_SwampWater1 += 34;
	m_Nb_SwampHive6 += 1;
	m_Nb_Water1 += 8;
	m_Nb_Swamp24 += 2;
	m_Nb_Swamp7 += 10;
	m_Nb_Swamp3 += 2;
	m_Nb_Swamp2 += 2;
	m_Nb_Swamp1 += 2;
	m_Nb_Grass2 += 1;
	m_Nb_Grass1 += 1;
	m_Nb_GlyphW += 1;
	m_Nb_GlyphP += 1;
	m_Nb_GlyphO += 1;
	m_Nb_GlyphN += 1;
	m_Nb_GlyphC += 1;
	m_Nb_GlyphT += 1;
	m_Nb_GlyphU += 1;
	m_Nb_GlyphB += 1;

	UpdateData( FALSE );
}

// The user want add the ticalla jungle set
//
void CMaterialEdit::OnBnClickedBtAddTicallaJungle()
{
	UpdateData( TRUE );

	m_Nb_TicallaPalm += 3;
	m_Nb_TicallaGrass += 6;

	UpdateData( FALSE );
}

// The user want add a dungeon master set
//
void CMaterialEdit::OnBnClickedBtAddDungeon()
{
	UpdateData( TRUE );

	m_Nb_Sand7 += 3;
	m_Nb_Sand2 += 1;
	m_Nb_Sand1 += 1;
	m_Nb_Grass3 += 1;
	m_Nb_Grass2 += 1;
	m_Nb_Grass1 += 1;
	m_Nb_Rock7 += 3;
	m_Nb_Rock3 += 2;
	m_Nb_Rock2 += 1;
	m_Nb_Rock1 += 1;
	m_Nb_Water1 += 12;
	m_Nb_Dungeon24 += 2;
	m_Nb_Dungeon7 += 3;
	m_Nb_Dungeon3 += 2;
	m_Nb_Dungeon2 += 2;
	m_Nb_Dungeon1 += 2;
	m_Nb_Shadow1 += 8;
	m_Nb_Outcrop3 += 1;
	m_Nb_Outcrop1 += 3;

	UpdateData( FALSE );
}
