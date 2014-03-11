// MyListCtrl.cpp : implementation file
//

#include "StdAfx.h"

#include "MyListCtrl.h"
#include "HeroscapeEditorView.h"

// The constructor
//
CMyListCtrl::CMyListCtrl()
{
	m_IsSpecialList = false;
	// No active view
	m_pView = NULL;
}

// The destructor
//
CMyListCtrl::~CMyListCtrl()
{
	DeleteAllDatas();
}

// Set if this is a special list or not
//
void CMyListCtrl::SetSpecialList( bool IsSpecialList )
{
	m_IsSpecialList = IsSpecialList;
}

// The windows message managing
//
BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CMyListCtrl)
	ON_WM_ERASEBKGND()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Draw the item
//
void CMyListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
    CRect rcItem(lpDrawItemStruct->rcItem);
    int nItem = lpDrawItemStruct->itemID;
    CImageList* pImageList;
    
    // Save dc state
    int nSavedDC = pDC->SaveDC();
    
    // Get item image and state info
    LV_ITEM lvi;
    lvi.mask = LVIF_IMAGE | LVIF_STATE;
    lvi.iItem = nItem;
    lvi.iSubItem = 0;
    lvi.stateMask = 0xFFFF;     // get all state flags
    GetItem(&lvi);
    
    // Should the item be highlighted
    BOOL bHighlight =((lvi.state & LVIS_DROPHILITED)
        || ( (lvi.state & LVIS_SELECTED)
        && ((GetFocus() == this)
        || (GetStyle() & LVS_SHOWSELALWAYS)
        )
        )
        );
    
    // Get rectangles for drawing
    CRect rcBounds, rcLabel, rcIcon;
    GetItemRect(nItem, rcBounds, LVIR_BOUNDS);
    GetItemRect(nItem, rcLabel, LVIR_LABEL);
    GetItemRect(nItem, rcIcon, LVIR_ICON);
    CRect rcCol( rcBounds ); 
    
    CString sLabel = GetItemText( nItem, 0 );
    
    // Labels are offset by a certain amount  
    // This offset is related to the width of a space character
    int offset = pDC->GetTextExtent(_T(" "), 1 ).cx*2;
    
    CRect rcHighlight;
    CRect rcWnd;
    rcHighlight = rcBounds;
    rcHighlight.left = rcLabel.left;
    
    // Draw the background color
    if( bHighlight )
    {
        pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
        pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));

        pDC->FillRect(rcHighlight, &CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
        pDC->FillRect(rcIcon, &CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
    }
    else
	{
		if( nItem%2==0 )
		{
	        pDC->FillRect(rcIcon, &CBrush(RGB( 255, 255, 192 )));
	        pDC->FillRect(rcHighlight, &CBrush(RGB( 255, 255, 192 )));
		}
		else
		{
	        pDC->FillRect(rcIcon, &CBrush(RGB( 255, 255, 255 )));
	        pDC->FillRect(rcHighlight, &CBrush(RGB( 255, 255, 255 )));
		}
	}

    // Set clip region
    rcCol.right = rcCol.left + GetColumnWidth(0);
    CRgn rgn;
    rgn.CreateRectRgnIndirect(&rcCol);
    pDC->SelectClipRgn(&rgn);
    rgn.DeleteObject();
    
    // Draw state icon
    if (lvi.state & LVIS_STATEIMAGEMASK)
    {
        int nImage = ((lvi.state & LVIS_STATEIMAGEMASK)>>12) - 1;
        pImageList = GetImageList(LVSIL_STATE);
        if (pImageList)
        {
            pImageList->Draw(pDC, nImage,
                CPoint(rcCol.left, rcCol.top), ILD_TRANSPARENT);
        }
    }
    
    // Draw normal and overlay icon
    pImageList = GetImageList(LVSIL_SMALL);
    if (pImageList)
    {
        UINT nOvlImageMask=lvi.state & LVIS_OVERLAYMASK;
        pImageList->Draw(pDC, lvi.iImage, 
            CPoint(rcIcon.left, rcIcon.top),
            (bHighlight?ILD_BLEND50:0) | ILD_TRANSPARENT | nOvlImageMask );
    }
    
    // Draw item label - Column 0
    rcLabel.left += offset/2;
    rcLabel.right -= offset;
    
    LV_COLUMN lvc;
    lvc.mask = LVCF_FMT | LVCF_WIDTH;
    
	GetColumn(0, &lvc);
	if( (lvc.fmt & LVCFMT_JUSTIFYMASK)==LVCFMT_RIGHT )
	    pDC->DrawText(sLabel,-1,rcLabel, DT_RIGHT | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER | DT_END_ELLIPSIS);
	else
	    pDC->DrawText(sLabel,-1,rcLabel, DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER | DT_END_ELLIPSIS);
    
    // Draw labels for remaining columns
    rcBounds.right = rcHighlight.right > rcBounds.right ? rcHighlight.right :
    rcBounds.right;
    rgn.CreateRectRgnIndirect(&rcBounds);
    pDC->SelectClipRgn(&rgn);
    
    for(int nColumn = 1; GetColumn(nColumn, &lvc); nColumn++)
    {
        rcCol.left = rcCol.right;
        rcCol.right += lvc.cx;
        
        sLabel = GetItemText(nItem, nColumn);
        if (sLabel.GetLength() == 0)
            continue;
        
        // Get the text justification
        UINT nJustify = DT_LEFT;
        switch(lvc.fmt & LVCFMT_JUSTIFYMASK)
        {
        case LVCFMT_RIGHT:
            nJustify = DT_RIGHT;
            break;
        case LVCFMT_CENTER:
            nJustify = DT_CENTER;
            break;
        default:
            break;
        }
        
        rcLabel = rcCol;
        rcLabel.left += offset;
        rcLabel.right -= offset;
        
        pDC->DrawText(sLabel, -1, rcLabel, nJustify | DT_SINGLELINE | 
            DT_NOPREFIX | DT_VCENTER | DT_END_ELLIPSIS);
    }
    
    // Draw focus rectangle if item has focus
    if (lvi.state & LVIS_FOCUSED && (GetFocus() == this))
        pDC->DrawFocusRect(rcHighlight);
    
    // Restore dc
    pDC->RestoreDC( nSavedDC );
}

// Erase the background
//
BOOL CMyListCtrl::OnEraseBkgnd(CDC* pDC) 
{
	CRect	Rect;
	GetClientRect( &Rect );

	pDC->FillSolidRect( Rect, GetSysColor( 15 ) );
	
	return 1;
}

// The user right clic on the list
//
void CMyListCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if( m_IsSpecialList )
	{
		int Index = HitTest( point );

		CPoint point2( point );
		ClientToScreen( &point2 );

		//theApp.SendRightClicOnSpecialList( point2, Index );
	}

	// Call the base class
	CListCtrl::OnRButtonDown(nFlags, point);
}

// The user dbl clic on the list
//
void CMyListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// Inform the document about this
	int Index = HitTest( point );
	if( Index>=0 )
	{
		CHeroscapeEditorDoc::InformationDatas* pDatas = (CHeroscapeEditorDoc::InformationDatas*) m_ArrayDatas.GetAt(Index);
		if( pDatas->z>=0 )
		{
			if( m_pView!=NULL )
				((CHeroscapeEditorView*) m_pView)->CenterOnPosAndBlink( pDatas->x, pDatas->y, pDatas->z );
		}
	}

	// Call the base class
	CListCtrl::OnLButtonDblClk(nFlags, point);
}

// Delete all the item datas
//
void CMyListCtrl::DeleteAllDatas()
{
	for( int i=0; i<m_ArrayDatas.GetCount(); i++ )
		free( m_ArrayDatas.GetAt(i) );
	
	m_ArrayDatas.RemoveAll();
}

// Add informations
//
void CMyListCtrl::AddInformationDatas( void* pDatas )
{
	m_ArrayDatas.Add( pDatas );
}
