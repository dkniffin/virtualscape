#ifndef _GLOBALIHM_H_
#define _GLOBALIHM_H_

class CGlobalIHM
{
//************
// The methods
//************

public:
	// Draw a button with a specified color
	void static DrawColorButton( LPDRAWITEMSTRUCT lpDrawItemStruct, COLORREF Color );
	// Draw a button with a specified bitmap
	void static DrawBitmapButton( LPDRAWITEMSTRUCT lpDrawItemStruct, HBITMAP hBmp );
	// Create a column liste
	void static CreateColumnListCtrl( CListCtrl* lstCtrl, const CString& Chaine );
	// Add Item at the position index in a CListCtrl with the image NoImage
	int static	AddListItem( CListCtrl* pList, const CString& Str , const int Index, const int NoImage);
	// Set Item at the position index in a CListCtrl with the image NoImage
	int static	SetListItem( CListCtrl* pList, const CString& Str , const int Index, const int NoImage);
	// Change color of bitmap
	void static ChangeColorForToolBarButton( CBitmap* pBitmap );
};

#endif // #ifndef _GLOBALIHM_H_
