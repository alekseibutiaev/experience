
// test15Dlg.cpp : implementation file
//

#include "stdafx.h"

#include <atlimage.h>

#include <algorithm>
#include <iterator>

#include "array_help.hpp"

#include "test15.h"
#include "test15Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#define FILE

namespace {

#if defined( FILE )
	const char* img_id[] = {
		"res/bitmap1.bmp", "res/bitmap2.bmp", "res/bitmap3.bmp", "res/bitmap4.bmp",
		"res/bitmap5.bmp", "res/bitmap6.bmp", "res/bitmap7.bmp", "res/bitmap8.bmp",
		"res/bitmap9.bmp", "res/bitmap10.bmp", "res/bitmap11.bmp", "res/bitmap12.bmp",
		"res/bitmap13.bmp", "res/bitmap14.bmp", "res/bitmap15.bmp"
	};
#else
	const unsigned int img_id[] = {
		IDB_BITMAP1, IDB_BITMAP2, IDB_BITMAP3, IDB_BITMAP4,
		IDB_BITMAP5, IDB_BITMAP6, IDB_BITMAP7, IDB_BITMAP8,
		IDB_BITMAP9, IDB_BITMAP10, IDB_BITMAP11, IDB_BITMAP12,
		IDB_BITMAP13, IDB_BITMAP14, IDB_BITMAP15
	};
#endif /* FILE */

	class create_img_from_file {
	public:
		boost::shared_ptr< CImage > operator()( const char* f_name ) const {
			boost::shared_ptr< CImage > result( new CImage() );
			result->Load( f_name );
			return result;
		}
	};
#if 0
  CImage myImage;

HINSTANCE hInstance;

TCHAR FileName[256];
GetModuleFileName( NULL, FileName, 255 );
hInstance =  (HINSTANCE) GetModuleHandle( FileName );

myImage.LoadFromResource(hInstance, MAKEINTRESOURCE(IDR_GIF1));
#endif
	class create_img_from_resource {
	public:
    create_img_from_resource() {
      TCHAR fname[ pv_buf_size ];
      GetModuleFileName( NULL, fname, pv_buf_size );
      pv_handle = static_cast< HINSTANCE >( GetModuleHandle( fname ) );
    }
		boost::shared_ptr< CImage > operator()( const unsigned int f_id ) const {
			boost::shared_ptr< CImage > result( new CImage() );
      result->LoadFromResource( pv_handle, f_id );
			return result;
		}
  private:
    HINSTANCE pv_handle;
  private:
    static const unsigned int pv_buf_size = 256;

	};

#if defined( FILE )
  typedef create_img_from_file create_img;
#else
  typedef create_img_from_resource create_img;
#endif /* FILE */


  class check_size {
  public:
    check_size() : pv_width( pv_uninit ), pv_height( pv_uninit ) {
    }
    bool operator()( const boost::shared_ptr< CImage >& f_value ) {
      if( pv_uninit == pv_width && pv_uninit == pv_width ) {
        pv_width = f_value->GetWidth();
        pv_height = f_value->GetHeight();
        return false;
      }
      return pv_width != f_value->GetWidth() || pv_width != f_value->GetHeight();
    }
  private:
    unsigned int pv_width;
    unsigned int pv_height;
  private:
    static const unsigned int pv_uninit = static_cast< unsigned int >( -1 );
  };


} /* namespace */

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD) {
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// Ctest15Dlg dialog




Ctest15Dlg::Ctest15Dlg(CWnd* pParent /*=NULL*/) : CDialog( Ctest15Dlg::IDD, pParent ),
    pv_picture_select( fifteen::unused_cell ), pv_iter_count( 0 ) {
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctest15Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Ctest15Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_NEW, &Ctest15Dlg::OnNew)
  ON_WM_LBUTTONDOWN()
  ON_WM_MOUSEMOVE()
  ON_COMMAND(ID_EXIT, &Ctest15Dlg::OnExit)
END_MESSAGE_MAP()


// Ctest15Dlg message handlers

BOOL Ctest15Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	if( !pv_menu.LoadMenuA( IDR_MENU1 ) )
    return FALSE;
	SetMenu( &pv_menu );
	// Add "About..." menu item to system menu.
	std::transform( array_begin( img_id ), array_end( img_id ),
    std::back_inserter( pv_images ), create_img() );
  images::iterator i = std::find_if( pv_images.begin(), pv_images.end(), check_size() );
  if( pv_images.end() != i )
    return FALSE;
  pv_piece_width = pv_images[ 0 ]->GetWidth();
  pv_piece_height = pv_images[ 0 ]->GetHeight();

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
  CRect r;
  GetClientRect( &r );

  unsigned int w = pv_piece_width * 4 + 6;
  unsigned int h = pv_piece_height * 4 + 52;
  CRect rect( 0, 0, w, h );
  MoveWindow( rect, TRUE );

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
  OnNew();

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Ctest15Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Ctest15Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
	else {
    pv_redraw();
	}
}

void Ctest15Dlg::pv_redraw() {
  CPaintDC dc( this ); // device context for painting
  COLORREF backcolor = RGB( 128, 128, 128 );
  CBrush brush_back_ground( backcolor );

  CRect rect;
    GetClientRect( &rect );
    dc.FillRect( &rect, &brush_back_ground );
    int pos = 0;
    for( fifteen::const_iterator i = pv_game->begin(); i != pv_game->end(); ++i ) {
      if( fifteen::unused_cell != *i && pv_picture_select != *i /**/ ) {
        unsigned int px = pv_piece_width * ( pos % 4 );
        unsigned int py = pv_piece_height * ( pos / 4 );
        pv_images[ *i ]->Draw( dc.m_hDC, px, py, pv_piece_width, pv_piece_height );
      }
      ++pos;
    }
    
  if( pv_game->ready() && 0 == pv_iter_count ) {
   if( IDYES != MessageBox( "Game over. Retry?", "Fifteen", MB_YESNO ) )
     OnExit();  
   OnNew();
   return;
  }
#if 1
    if( pv_iter_count ) {
      --pv_iter_count;
      dc.FillRect( &pv_anime, &brush_back_ground );
      CRect anime = pv_anime;
      switch( pv_direct ) {
        case fifteen::e_left :
          anime.left += pv_iter_count;
          anime.right = anime.left + pv_piece_width;
          break;
        case fifteen::e_right :
          anime.left += pv_piece_width - pv_iter_count;
          anime.right = anime.left + pv_piece_width;
          break;
        case fifteen::e_bottom :
          anime.top += pv_piece_height - pv_iter_count;
          anime.bottom = anime.top + pv_piece_height;
          break;
        case fifteen::e_top :
          anime.top += pv_iter_count;
          anime.bottom = anime.top + pv_piece_height;
          break;
      };
      pv_images[ pv_picture_select ]->Draw( dc.m_hDC, anime );
      if( !pv_iter_count )
        pv_picture_select = fifteen::unused_cell;
      Sleep( 5 );
    this->RedrawWindow( pv_anime );
    }
#endif
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Ctest15Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Ctest15Dlg::OnNew() {
  pv_game.reset( new fifteen() );
  this->RedrawWindow();
}

void Ctest15Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
  pv_from = point.x / pv_piece_width +
    fifteen::field_height * ( point.y / pv_piece_height );
  pv_picture_select = pv_game->select( pv_from );
  if( fifteen::unused_cell != pv_picture_select ) {
    for( unsigned int i = fifteen::e_left; i < fifteen::e_COUNT; ++i ) {
      pv_to = pv_game->can_move( static_cast< fifteen::direction >( i ) );
      if( fifteen::max_pieces != pv_to ) {
        pv_game->move( pv_from, pv_to );
        pv_direct = static_cast< fifteen::direction >( i );
        switch( pv_direct ) {
          case fifteen::e_left :
          case fifteen::e_right :
            pv_iter_count = pv_piece_width;
            break;
          case fifteen::e_top :
          case fifteen::e_bottom :
            pv_iter_count = pv_piece_height;
            break;
        }
        pv_animation_rect( pv_from, pv_to, pv_direct );
        this->RedrawWindow();
        return;
      }
    }
  }
  pv_picture_select = fifteen::unused_cell;
}

void Ctest15Dlg::pv_animation_rect( const unsigned int& f_from, const unsigned int& f_to,
    const fifteen::direction f_direction ) {
  CSize size;
  unsigned int from = f_from;
  switch( f_direction ){
    case fifteen::e_left :
      from = f_to;
    case fifteen::e_right:
      size.cx = pv_piece_width * 2;
      size.cy = pv_piece_height;
      pv_iter_count = pv_piece_width;
      break;
    case fifteen::e_top :
      from = f_to;
    case fifteen::e_bottom:
      size.cx = pv_piece_width;
      size.cy = pv_piece_height * 2;
      pv_iter_count = pv_piece_height;
      break;
  }
  CPoint point( ( from % fifteen::field_width ) * pv_piece_width,
    ( from / fifteen::field_width ) * pv_piece_height );
  pv_anime = CRect( point, size );
}

void Ctest15Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
  // TODO: Add your message handler code here and/or call default
}

void Ctest15Dlg::OnExit()
{
  // TODO: Add your command handler code here
  this->EndDialog( 0 );
}
