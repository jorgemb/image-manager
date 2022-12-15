///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui/gui.h"

///////////////////////////////////////////////////////////////////////////
using namespace imgr;

ImageManager::ImageManager( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxGridBagSizer* m_sizer_top_level;
	m_sizer_top_level = new wxGridBagSizer( 0, 0 );
	m_sizer_top_level->SetFlexibleDirection( wxBOTH );
	m_sizer_top_level->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_tree_albums = new wxDataViewTreeCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_sizer_top_level->Add( m_tree_albums, wxGBPosition( 0, 0 ), wxGBSpan( 2, 1 ), wxALL|wxEXPAND|wxFIXED_MINSIZE, 5 );

	m_panel_image = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* m_sizer_image;
	m_sizer_image = new wxBoxSizer( wxVERTICAL );

	m_media_main = new wxMediaCtrl( m_panel_image, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize);
	m_media_main->SetPlaybackRate(1);
	m_media_main->SetVolume(1);

	m_media_main->Stop();
	m_sizer_image->Add( m_media_main, 1, wxALL|wxEXPAND, 5 );


	m_panel_image->SetSizer( m_sizer_image );
	m_panel_image->Layout();
	m_sizer_image->Fit( m_panel_image );
	m_sizer_top_level->Add( m_panel_image, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxEXPAND | wxALL, 5 );

	m_panel_gallery = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_panel_gallery->SetScrollRate( 5, 5 );
	m_sizer_top_level->Add( m_panel_gallery, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxEXPAND | wxALL, 5 );


	m_sizer_top_level->AddGrowableCol( 1 );
	m_sizer_top_level->AddGrowableRow( 0 );

	this->SetSizer( m_sizer_top_level );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_ACTIVATE_APP, wxActivateEventHandler( ImageManager::ImageManagerOnActivateApp ) );
}

ImageManager::~ImageManager()
{
	// Disconnect Events
	this->Disconnect( wxEVT_ACTIVATE_APP, wxActivateEventHandler( ImageManager::ImageManagerOnActivateApp ) );

}
