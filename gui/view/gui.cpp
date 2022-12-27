///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

///////////////////////////////////////////////////////////////////////////
using namespace imgr;

ImageManager::ImageManager( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	bar_status = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
	wxBoxSizer* top_box_hor;
	top_box_hor = new wxBoxSizer( wxHORIZONTAL );

	tree_albums = new wxTreeCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	top_box_hor->Add( tree_albums, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* top_box_ver;
	top_box_ver = new wxBoxSizer( wxVERTICAL );

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
	top_box_ver->Add( panel_image, 2, wxEXPAND | wxALL, 5 );

	panel_gallery = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL );
	panel_gallery->SetScrollRate( 5, 5 );
	top_box_ver->Add( panel_gallery, 1, wxEXPAND | wxALL, 5 );


	top_box_hor->Add( top_box_ver, 2, wxEXPAND, 5 );


	this->SetSizer( top_box_hor );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	tree_albums->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( ImageManager::TreeAlbums_OnTreeSelChanged ), NULL, this );
}

ImageManager::~ImageManager()
{
	// Disconnect Events
	tree_albums->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( ImageManager::TreeAlbums_OnTreeSelChanged ), NULL, this );

}
