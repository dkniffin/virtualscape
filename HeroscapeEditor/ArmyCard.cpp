#include "StdAfx.h"

#include "ArmyCard.h"
#include "FigureObject.h"
#include "HeroscapeEditor.h"
#include "Marquer.h"
#include "Resource.h"
#include "StaticGraphicalLib.h"

// The constructor
//
CArmyCard::CArmyCard()
{
	m_pBits = NULL;
	// The figure are not placed on the battlefield
	m_FigureArePlaced = false;
}

// The destructor
//
CArmyCard::~CArmyCard(void)
{
	for( int i=0; i<m_Figures.GetCount(); )
	{
		delete (CFigureObject*) m_Figures.GetAt(i);
		m_Figures.RemoveAt(i);
	}

	ResetMarquer();
}

// Draw this card on a square
//
void CArmyCard::Draw( CDC* pDC, int XOffset, int YOffset, int Width, int Height, bool IsSelected, int DisplayPlayerIndex )
{
	CString Str;

	// Draw Bitmap of the card
	if( m_pBits==NULL )
		if( !LoadBitmap() )
			return;

	BITMAPINFO bi;

	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = 256;
	bi.bmiHeader.biHeight = 256;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 24;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = 0;
	bi.bmiHeader.biXPelsPerMeter = 1;
	bi.bmiHeader.biYPelsPerMeter = 1;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;

	SetStretchBltMode( pDC->m_hDC, HALFTONE );
	StretchDIBits( pDC->m_hDC, XOffset, YOffset, Width-50, Height-22, 0, 0, 256, 256, m_pBits, &bi, DIB_RGB_COLORS, SRCAND);


	CFont f;
	f.CreateFontW( 12, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial") );
	CFont* pOldFont = pDC->SelectObject( &f );

	// Draw name of the card
	if( theApp.m_GameType==CGameDoc::GAMETYPE_EXPERT )
		Str.Format( _T("%s (%i)"), m_Name, m_ExpertCostPoint );
	else
		Str = m_Name;
	pDC->DrawText( Str, CRect( XOffset, YOffset+Height-20, XOffset+Width, YOffset+Height), DT_CENTER|DT_VCENTER );

	CDC MemoryDC;
	MemoryDC.CreateCompatibleDC( pDC );

	if( theApp.m_GameType==CGameDoc::GAMETYPE_BASIC )
	{
		// Basic mode

		// Draw Movement of the card
		Str.Format( _T("%d"), m_BasicMovementSpace );
		pDC->DrawText( Str, CRect( XOffset+Width-30, YOffset+5, XOffset+Width-5, YOffset+25), DT_RIGHT|DT_VCENTER );
		// Draw Range of the card
		Str.Format( _T("%d"), m_BasicRangeSpace );
		pDC->DrawText( Str, CRect( XOffset+Width-30, YOffset+25+5, XOffset+Width-5, YOffset+50), DT_RIGHT|DT_VCENTER );
		// Draw attack of the card
		Str.Format( _T("%d"), m_BasicAttackDice );
		pDC->DrawText( Str, CRect( XOffset+Width-30, YOffset+50+5, XOffset+Width-5, YOffset+75), DT_RIGHT|DT_VCENTER );
		// Draw Defense of the card
		Str.Format( _T("%d"), m_BasicDefenseDice );
		pDC->DrawText( Str, CRect( XOffset+Width-30, YOffset+75+5, XOffset+Width-5, YOffset+100), DT_RIGHT|DT_VCENTER );

		// Draw bitmap of the movement
		CBitmap bmp;
		bmp.LoadBitmapW(IDB_MOVEMENT);
		MemoryDC.SelectObject( &bmp );
		pDC->BitBlt( XOffset+Width-40, YOffset, 25, 25, &MemoryDC, 0, 0, SRCAND );

		// Draw bitmap of the range
		CBitmap bmp2;
		bmp2.LoadBitmapW(IDB_RANGE);
		MemoryDC.SelectObject( &bmp2 );
		pDC->BitBlt( XOffset+Width-40, YOffset+25, 25, 25, &MemoryDC, 0, 0, SRCAND );

		// Draw bitmap of the attack
		CBitmap bmp3;
		bmp3.LoadBitmapW(IDB_ATTACK);
		MemoryDC.SelectObject( &bmp3 );
		pDC->BitBlt( XOffset+Width-40, YOffset+50, 25, 25, &MemoryDC, 0, 0, SRCAND );

		// Draw bitmap of the shield
		CBitmap bmp4;
		bmp4.LoadBitmapW(IDB_SHIELD);
		MemoryDC.SelectObject( &bmp4 );
		pDC->BitBlt( XOffset+Width-40, YOffset+75, 25, 25, &MemoryDC, 0, 0, SRCAND );
	}
	else if( theApp.m_GameType==CGameDoc::GAMETYPE_EXPERT )
	{
		// Expert mode

		// Draw Movement of the card
		Str.Format( _T("%d"), m_ExpertMovementSpace );
		pDC->DrawText( Str, CRect( XOffset+Width-30, YOffset+5, XOffset+Width-5, YOffset+25), DT_RIGHT|DT_VCENTER );
		// Draw Range of the card
		Str.Format( _T("%d"), m_ExpertRangeSpace );
		pDC->DrawText( Str, CRect( XOffset+Width-30, YOffset+25+5, XOffset+Width-5, YOffset+50), DT_RIGHT|DT_VCENTER );
		// Draw attack of the card
		Str.Format( _T("%d"), m_ExpertAttackDice );
		pDC->DrawText( Str, CRect( XOffset+Width-30, YOffset+50+5, XOffset+Width-5, YOffset+75), DT_RIGHT|DT_VCENTER );
		// Draw Defense of the card
		Str.Format( _T("%d"), m_ExpertDefenseDice );
		pDC->DrawText( Str, CRect( XOffset+Width-30, YOffset+75+5, XOffset+Width-5, YOffset+100), DT_RIGHT|DT_VCENTER );
		// Draw Life of the card
		Str.Format( _T("%d"), m_CurrentLifePoint );
		pDC->DrawText( Str, CRect( XOffset, YOffset+10+1, XOffset+13, YOffset+100), DT_CENTER|DT_TOP );

		// Draw bitmap of the movement
		CDC MemoryDC;
		MemoryDC.CreateCompatibleDC( pDC );
		CBitmap bmp;
		bmp.LoadBitmapW(IDB_MOVEMENT);
		MemoryDC.SelectObject( &bmp );
		pDC->BitBlt( XOffset+Width-40, YOffset, 25, 25, &MemoryDC, 0, 0, SRCAND );

		// Draw bitmap of the range
		CBitmap bmp2;
		bmp2.LoadBitmapW(IDB_RANGE);
		MemoryDC.SelectObject( &bmp2 );
		pDC->BitBlt( XOffset+Width-40, YOffset+25, 25, 25, &MemoryDC, 0, 0, SRCAND );

		// Draw bitmap of the attack
		CBitmap bmp3;
		bmp3.LoadBitmapW(IDB_ATTACK);
		MemoryDC.SelectObject( &bmp3 );
		pDC->BitBlt( XOffset+Width-40, YOffset+50, 25, 25, &MemoryDC, 0, 0, SRCAND );

		// Draw bitmap of the shield
		CBitmap bmp4;
		bmp4.LoadBitmapW(IDB_SHIELD);
		MemoryDC.SelectObject( &bmp4 );
		pDC->BitBlt( XOffset+Width-40, YOffset+75, 25, 25, &MemoryDC, 0, 0, SRCAND );

		// Draw bitmap of the life
		CBitmap bmp5;
		bmp5.LoadBitmapW(IDB_LIFE);
		MemoryDC.SelectObject( &bmp5 );
		pDC->BitBlt( XOffset+1, YOffset+1, 10, 10, &MemoryDC, 0, 0, SRCAND );

		// Draw bitmap of the predicted play if necessary
		for( int i=0; i<m_MarquerList.GetCount(); i++ )
		{
			CMarquer* pMarquer = (CMarquer*) m_MarquerList.GetAt(i);
			CBitmap bmp6;
			CBitmap bmp7;
			switch( pMarquer->m_Value )
			{
			case 0:
				if( pMarquer->m_IsShow )
					bmp6.LoadBitmapW(IDB_PREDICTEDPLAYSHOWX);
				else if(DisplayPlayerIndex==theApp.m_pGameDoc->m_PlayerIndex )
					bmp6.LoadBitmapW(IDB_PREDICTEDPLAYHIDEX);
				else
					bmp6.LoadBitmapW(IDB_PREDICTEDPLAYHIDE);
				break;
			case 1:
				if( pMarquer->m_IsShow )
					bmp6.LoadBitmapW(IDB_PREDICTEDPLAYSHOW1);
				else if(DisplayPlayerIndex==theApp.m_pGameDoc->m_PlayerIndex )
					bmp6.LoadBitmapW(IDB_PREDICTEDPLAYHIDE1);
				else
					bmp6.LoadBitmapW(IDB_PREDICTEDPLAYHIDE);
				break;
			case 2:
				if( pMarquer->m_IsShow )
					bmp6.LoadBitmapW(IDB_PREDICTEDPLAYSHOW2);
				else if(DisplayPlayerIndex==theApp.m_pGameDoc->m_PlayerIndex )
					bmp6.LoadBitmapW(IDB_PREDICTEDPLAYHIDE2);
				else
					bmp6.LoadBitmapW(IDB_PREDICTEDPLAYHIDE);
				break;
			case 3:
				if( pMarquer->m_IsShow )
					bmp6.LoadBitmapW(IDB_PREDICTEDPLAYSHOW3);
				else if(DisplayPlayerIndex==theApp.m_pGameDoc->m_PlayerIndex )
					bmp6.LoadBitmapW(IDB_PREDICTEDPLAYHIDE3);
				else
					bmp6.LoadBitmapW(IDB_PREDICTEDPLAYHIDE);
				break;
			}
			bmp7.LoadBitmapW(IDB_PREDICTEDPLAYMASK);
			MemoryDC.SelectObject( &bmp7 );
			pDC->BitBlt( XOffset+i*25, YOffset+87, 20, 20, &MemoryDC, 0, 0, SRCAND );
			MemoryDC.SelectObject( &bmp6 );
			pDC->BitBlt( XOffset+i*25, YOffset+87, 20, 20, &MemoryDC, 0, 0, SRCPAINT );
		}
	}

	if( IsSelected )
	{
		// Draw bitmap of selected
		CBitmap bmp3;
		bmp3.LoadBitmapW(IDB_VALIDATE);
		MemoryDC.SelectObject( &bmp3 );
		pDC->BitBlt( XOffset, YOffset+Height-25, 25, 25, &MemoryDC, 0, 0, SRCAND );
	}

	pDC->SelectObject( pOldFont );
	f.DeleteObject();
}

// Load the bitmap
//
bool CArmyCard::LoadBitmap()
{
	CString Language;
	Language.LoadStringW( IDS_LANGUAGE );

	m_pBits = CStaticGraphicalLib::LoadBitmap( theApp.m_CurrentDir+_T("\\ArmyCard\\Images\\Basic\\")+Language+_T("\\")+m_BitmapFileName+_T(".bmp") );

	if( m_pBits==NULL )
		return false;

	return true;
}

// Get the figures list
//
CPtrArray* CArmyCard::GetFiguresList()
{
	return &m_Figures;
}

// Remove all the marquer
//
void CArmyCard::ResetMarquer()
{
	while( m_MarquerList.GetCount()>0 )
	{
		CMarquer* pMarquer = (CMarquer*) m_MarquerList.GetAt(0);
		delete pMarquer;
		m_MarquerList.RemoveAt(0);
	}
}

// Remove a marquer with a particular value
//
void CArmyCard::RemoveMarquer( int Value )
{
	for( int i=0; i<m_MarquerList.GetCount(); i++ )
	{
		CMarquer* pMarquer = (CMarquer*) m_MarquerList.GetAt(i);
		if( pMarquer->m_Value==Value )
		{
			delete pMarquer;
			m_MarquerList.RemoveAt(i);
			return;
		}
	}
}

// Add a marquer with a particular value
//
void CArmyCard::AddMarquer( int Value )
{
	CMarquer* pMarquer = new CMarquer( Value );
	m_MarquerList.Add( pMarquer );
}

// Show a marquer with a particular value
//
void CArmyCard::ShowMarquer( int Value )
{
	for( int i=0; i<m_MarquerList.GetCount(); i++ )
	{
		CMarquer* pMarquer = (CMarquer*) m_MarquerList.GetAt(i);
		if( pMarquer->m_Value==Value )
		{
			pMarquer->m_IsShow = true;
			return;
		}
	}
}

// Return the next hidden marquer or -1
//
int	 CArmyCard::GetNextHidenMarquer()
{
	int NextHiden = -1;
	for( int i=0; i<m_MarquerList.GetCount(); i++ )
	{
		CMarquer* pMarquer = (CMarquer*) m_MarquerList.GetAt(i);
		if( !pMarquer->m_IsShow )
		{
			if( (NextHiden==-1 || NextHiden>pMarquer->m_Value) && pMarquer->m_Value>0 )
				NextHiden = pMarquer->m_Value;
		}
	}

	return NextHiden;
}

