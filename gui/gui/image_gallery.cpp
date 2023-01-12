//
// Created by jorge on 27/12/2022.
//

#include "image_gallery.h"
#include <gui/image_panel.h>
#include <gui/exceptions.h>

#include <wx/sizer.h>

#include <boost/filesystem/directory.hpp>

namespace imgr {
wxImageGallery::wxImageGallery(wxWindow *parent, wxWindowID winid, const wxPoint &pos, const wxSize &size,
                               long style) : wxScrolledWindow(parent, winid, pos, size, style) {}

void wxImageGallery::SetImages(const wxImageGallery::ImageList &images) {
    // Create the gallery
    auto sizer_gallery = new wxBoxSizer(wxHORIZONTAL);

    for (int i = 0; i < images.size(); ++i) {
        auto panel = new wxImagePanel(this, images[i].get());
        sizer_gallery->Add(panel, 0, wxALL | wxEXPAND );

        // TODO: Use i to create event for handling click
    }

    // Create the new sizer
    SetSizer(sizer_gallery, true);
    Layout();
    sizer_gallery->FitInside(this);

    // Clear all
    Refresh();
    Update();
}

} // imgr