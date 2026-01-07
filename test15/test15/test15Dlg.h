
// test15Dlg.h : header file
//

#pragma once

#include <vector>

#include <boost/smart_ptr.hpp>

#include "fifteen.hpp"

// Ctest15Dlg dialog
class Ctest15Dlg : public CDialog
{
// Construction
public:
	Ctest15Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TEST15_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
  typedef std::vector< boost::shared_ptr< CImage > > images;
private:
  void pv_redraw();
  void pv_animation_rect( const unsigned int& f_from, const unsigned int& f_to,
    const fifteen::direction f_direction );
private:
	CMenu pv_menu;
	images pv_images;
  boost::scoped_ptr< fifteen > pv_game;
  unsigned int pv_piece_width;
  unsigned int pv_piece_height;
  unsigned int pv_iter_count;
  unsigned int pv_from;
  unsigned int pv_to;
  fifteen::direction pv_direct;
  int pv_picture_select;
//  int pv_increment;
  CRect pv_anime;
private:
	static const unsigned int pv_max_images = 15;
public:
	afx_msg void OnNew();

  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnExit();
};
