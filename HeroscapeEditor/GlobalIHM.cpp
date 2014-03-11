// GlobalIHM.cpp : implementation file
//

#include "stdafx.h"

#include "GlobalIHM.h"

// Draw a button with a specified color
//
void CGlobalIHM::DrawColorButton( LPDRAWITEMSTRUCT lpDrawItemStruct, COLORREF Color )
{
	CDC* pDC = CDC::FromHandle( lpDrawItemStruct->hDC );

	CPen WhitePen( PS_SOLID, 1, RGB(255,255,255) );
	CPen BlackPen( PS_SOLID, 1, RGB(128,128,128) );
	CPen* pOldPen = pDC->SelectObject( &BlackPen );

	if( Color!=0xff000000 )
	{
		pDC->FillSolidRect(0,0,lpDrawItemStruct->rcItem.right,lpDrawItemStruct->rcItem.bottom,Color);
	}
	else
	{
		pDC->FillSolidRect(0,0,lpDrawItemStruct->rcItem.right,lpDrawItemStruct->rcItem.bottom,RGB(192,192,192));
		pDC->MoveTo(0,0);
		pDC->LineTo(lpDrawItemStruct->rcItem.right-1,lpDrawItemStruct->rcItem.bottom-1);
		pDC->MoveTo(lpDrawItemStruct->rcItem.right-1,0);
		pDC->LineTo(0,lpDrawItemStruct->rcItem.bottom-1);
	}
	pDC->MoveTo( 0, lpDrawItemStruct->rcItem.bottom );
	pDC->LineTo( 0, 0 );
	pDC->LineTo( lpDrawItemStruct->rcItem.right-1, 0 );
	pDC->SelectObject( &WhitePen );
	pDC->LineTo( lpDrawItemStruct->rcItem.right-1, lpDrawItemStruct->rcItem.bottom-1 );
	pDC->LineTo( 0, lpDrawItemStruct->rcItem.bottom-1 );
	pDC->SelectObject( pOldPen );
}

// Draw a button with a specified bitmap
//
void CGlobalIHM::DrawBitmapButton( LPDRAWITEMSTRUCT lpDrawItemStruct, HBITMAP hBmp )
{
	CDC* pDC = CDC::FromHandle( lpDrawItemStruct->hDC );

	CBitmap* pBitmap = CBitmap::FromHandle( hBmp );

	ChangeColorForToolBarButton( pBitmap );

	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = dcMemory.SelectObject( pBitmap );

	pDC->BitBlt(0,0,lpDrawItemStruct->rcItem.right,lpDrawItemStruct->rcItem.bottom,&dcMemory,0,0, SRCCOPY );

	dcMemory.SelectObject( pOldBitmap );
}

// Change color of bitmap
//
void CGlobalIHM::ChangeColorForToolBarButton( CBitmap* pBitmap )
{
	DWORD ColorFace = ::GetSysColor(COLOR_BTNFACE);
	DWORD ColorShadow = ::GetSysColor(COLOR_BTNSHADOW);
	DWORD ColorHiLight = ::GetSysColor(COLOR_BTNHILIGHT);
	DWORD* pBuff = (DWORD*) malloc(22*22*sizeof(DWORD));
	int Current = 0;
	pBitmap->GetBitmapBits( 22*22*sizeof(DWORD), pBuff );
	for( int y=0; y<22; y++ )
	{
		for( int x=0; x<22; x++ )
		{
			if( pBuff[Current]==0x00efebde )
				pBuff[Current]=GetBValue(ColorFace)+GetGValue(ColorFace)*256+GetRValue(ColorFace)*256*256;
			else if( pBuff[Current]==0x00ecd59d )
				pBuff[Current]=0; //GetBValue(ColorShadow)+GetGValue(ColorShadow)*256+GetRValue(ColorShadow)*256*256;
			else if( pBuff[Current]==0x00adaa9c )
				pBuff[Current]=GetBValue(ColorShadow)+GetGValue(ColorShadow)*256+GetRValue(ColorShadow)*256*256;
			else if( pBuff[Current]==0x00ffffff )
				pBuff[Current]=GetBValue(ColorHiLight)+GetGValue(ColorHiLight)*256+GetRValue(ColorHiLight)*256*256;
			Current++;
		}
	}
	pBitmap->SetBitmapBits( 22*22*sizeof(DWORD), pBuff );
	free( pBuff );
}

// Create a column liste
//
void CGlobalIHM::CreateColumnListCtrl( CListCtrl* lstCtrl, const CString& Chaine )
{
	int		No=0;
	int		l_Width;
	CString	Str;

	Str = Chaine;

	while( lstCtrl->DeleteColumn(0) != 0 );
	
	while( Str.Find(';') != -1 )
	{
		CString	Str2;
		Str2 = Str.SpanExcluding(_T(";"));
		Str = Str.Mid(Str2.GetLength()+1);

		lstCtrl->InsertColumn( No, Str2 );
		l_Width = lstCtrl->GetStringWidth( Str2.GetBuffer(0) );
		lstCtrl->SetColumnWidth( No++,l_Width+20 );
	}
	lstCtrl->InsertColumn( No, Str );
	l_Width = lstCtrl->GetStringWidth( Str.GetBuffer(0) );
	lstCtrl->SetColumnWidth( No,l_Width+20 );
}

// Add Item at the position index in a CListCtrl with the image NoImage
//
int CGlobalIHM::AddListItem( CListCtrl* pList, const CString& Str , const int Index, const int NoImage)
{
	CString	l_String;
	CString	l_String2;
	LV_ITEM	l_LvItem;
	int		l_InsertIndex;
	int		l_Width;
	int		i=0;
	
	if(Index == -1)
	{
		l_InsertIndex = pList->GetItemCount();
	}
	else
	{
		l_InsertIndex = Index;
	}

	memset( &l_LvItem,0, sizeof(LV_ITEM) );

	// Format the string
	l_String = Str;

	// Extract the first column
	l_String2 = l_String.SpanExcluding(_T(";"));
	l_String = l_String.Mid( l_String2.GetLength()+1 );
	l_Width = pList->GetStringWidth( l_String2.GetBuffer(0) );
	if( l_Width+30>pList->GetColumnWidth( 0 ) )
		pList->SetColumnWidth( 0,l_Width+30 );
	if( NoImage<0 )
	{
		l_LvItem.mask = LVIF_TEXT;
 		l_LvItem.pszText = l_String2.GetBuffer(0);
		l_LvItem.iItem = l_InsertIndex;
	}
	else
	{
		l_LvItem.mask = LVIF_TEXT|LVIF_IMAGE;
		l_LvItem.iImage = NoImage;
 		l_LvItem.pszText = l_String2.GetBuffer(0);
		l_LvItem.iItem = l_InsertIndex;
	}
	pList->InsertItem( &l_LvItem );
	while( !l_String.IsEmpty() )
	{
		i++;
		// Extract the next column
		l_String2 = l_String.SpanExcluding(_T(";"));
		if( l_String2 != l_String )
			l_String = l_String.Mid( l_String2.GetLength()+1 );
		else
			l_String = "";
		l_Width = pList->GetStringWidth( l_String2.GetBuffer(0) );
		if( l_Width+15>pList->GetColumnWidth( i ) )
			pList->SetColumnWidth( i, l_Width+15 );
		pList->SetItemText( l_InsertIndex, i, l_String2 );
	}
	return l_InsertIndex;
}

// Set Item at the position index in a CListCtrl with the image NoImage
//
int CGlobalIHM::SetListItem( CListCtrl* pList, const CString& Str , const int Index, const int NoImage)
{
	CString	l_String;
	CString	l_String2;
	LV_ITEM	l_LvItem;
	int		l_Width;
	int		i=0;
	
	memset( &l_LvItem,0, sizeof(LV_ITEM) );

	// Format the string
	l_String = Str;

	// Extract the first column
	l_String2 = l_String.SpanExcluding(_T(";"));
	l_String = l_String.Mid( l_String2.GetLength()+1 );
	l_Width = pList->GetStringWidth( l_String2.GetBuffer(0) );
	if( l_Width+15>pList->GetColumnWidth( 0 ) )
		pList->SetColumnWidth( 0,l_Width+15 );
	if( NoImage<0 )
	{
		l_LvItem.mask = LVIF_TEXT;
 		l_LvItem.pszText = l_String2.GetBuffer(0);
		l_LvItem.iItem = Index;
	}
	else
	{
		l_LvItem.mask = LVIF_TEXT|LVIF_IMAGE;
		l_LvItem.iImage = NoImage;
 		l_LvItem.pszText = l_String2.GetBuffer(0);
		l_LvItem.iItem = Index;
	}
	pList->SetItem( &l_LvItem );
	while( !l_String.IsEmpty() )
	{
		i++;
		// Extract the next column
		l_String2 = l_String.SpanExcluding(_T(";"));
		if( l_String2 != l_String )
			l_String = l_String.Mid( l_String2.GetLength()+1 );
		else
			l_String = "";
		l_Width = pList->GetStringWidth( l_String2.GetBuffer(0) );
		if( l_Width+20>pList->GetColumnWidth( i ) )
			pList->SetColumnWidth( i, l_Width+20 );
		pList->SetItemText( Index, i, l_String2 );
	}
	return Index;
}
