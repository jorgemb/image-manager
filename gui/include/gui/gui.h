///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/dataview.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/mediactrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/scrolwin.h>
#include <wx/gbsizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

namespace imgr
{

	///////////////////////////////////////////////////////////////////////////////
	/// Class ImageManager
	///////////////////////////////////////////////////////////////////////////////
	class ImageManager : public wxFrame
	{
		private:

		protected:
			wxDataViewTreeCtrl* m_tree_albums;
			wxPanel* m_panel_image;
			wxMediaCtrl* m_media_main;
			wxScrolledWindow* m_panel_gallery;

			// Virtual event handlers, override them in your derived class
			virtual void ImageManagerOnActivateApp( wxActivateEvent& event ) { event.Skip(); }


		public:

			ImageManager( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Image Manager"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1024,768 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

			~ImageManager();

	};

} // namespace imgr

