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

	wxGridBagSizer* sizer_top_level;
	sizer_top_level = new wxGridBagSizer( 0, 0 );
	sizer_top_level->SetFlexibleDirection( wxBOTH );
	sizer_top_level->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	tree_albums = new wxTreeCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	tree_albums->SetMinSize( wxSize( 300,-1 ) );

	sizer_top_level->Add( tree_albums, wxGBPosition( 0, 0 ), wxGBSpan( 2, 1 ), wxALL|wxEXPAND, 5 );

	panel_image = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* sizer_image;
	sizer_image = new wxBoxSizer( wxVERTICAL );

	media_main = new wxMediaCtrl( panel_image, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize);
	media_main->SetPlaybackRate(1);
	media_main->SetVolume(1);

	media_main->Stop();
	sizer_image->Add( media_main, 1, wxALL|wxEXPAND, 5 );


	panel_image->SetSizer( sizer_image );
	panel_image->Layout();
	sizer_image->Fit( panel_image );
	sizer_top_level->Add( panel_image, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxEXPAND | wxALL, 5 );

	panel_gallery = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	panel_gallery->SetScrollRate( 5, 5 );
	panel_gallery->SetMinSize( wxSize( -1,200 ) );

	sizer_top_level->Add( panel_gallery, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxEXPAND | wxALL, 5 );


	sizer_top_level->AddGrowableCol( 1 );
	sizer_top_level->AddGrowableRow( 0 );

	this->SetSizer( sizer_top_level );
	this->Layout();
	bar_status = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_ACTIVATE, wxActivateEventHandler( ImageManager::ImageManagerOnActivate ) );
	tree_albums->Connect( wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( ImageManager::TreeAlbums_OnTreeItemActivated ), NULL, this );
	tree_albums->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( ImageManager::TreeAlbums_OnTreeSelChanged ), NULL, this );
}

ImageManager::~ImageManager()
{
	// Disconnect Events
	this->Disconnect( wxEVT_ACTIVATE, wxActivateEventHandler( ImageManager::ImageManagerOnActivate ) );
	tree_albums->Disconnect( wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( ImageManager::TreeAlbums_OnTreeItemActivated ), NULL, this );
	tree_albums->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( ImageManager::TreeAlbums_OnTreeSelChanged ), NULL, this );

}
