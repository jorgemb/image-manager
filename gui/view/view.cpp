///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "view.h"

///////////////////////////////////////////////////////////////////////////
using namespace imgr;

ImageManager::ImageManager( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 800,600 ), wxDefaultSize );

	bar_status = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
	wxBoxSizer* top_box_hor;
	top_box_hor = new wxBoxSizer( wxHORIZONTAL );

	tree_albums = new wxTreeCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	top_box_hor->Add( tree_albums, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* top_box_ver;
	top_box_ver = new wxBoxSizer( wxVERTICAL );

	panel_image = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE|wxTAB_TRAVERSAL );
	top_box_ver->Add( panel_image, 2, wxEXPAND | wxALL, 5 );

	panel_gallery = new wxImageGallery( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxALWAYS_SHOW_SB|wxHSCROLL );
	panel_gallery->SetScrollRate( 5, 5 );
	panel_gallery->SetMinSize( wxSize( -1,200 ) );

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );


	panel_gallery->SetSizer( fgSizer1 );
	panel_gallery->Layout();
	fgSizer1->Fit( panel_gallery );
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
