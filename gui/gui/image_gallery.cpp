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

void wxImageGallery::SetImagesPath(const filesystem::path &images_path) {
    namespace fs = filesystem;

    // Create the gallery
    auto sizer_gallery = new wxBoxSizer(wxHORIZONTAL);

    // Iterate through the folder
    std::vector<fs::directory_entry> directory_paths;
    std::copy(fs::directory_iterator(images_path), fs::directory_iterator(), std::back_inserter(directory_paths));
    std::sort(directory_paths.begin(), directory_paths.end());

    for (const auto &path: directory_paths) {
        if (fs::is_directory(path) || !fs::exists(path)) continue;

        // Try to load image
        try {
            auto panel = new wxImagePanel(this, path);
            sizer_gallery->Add(panel, 0, wxALL | wxEXPAND);
        } catch (const InvalidImageException &ex) {
            // Log
            wxLogWarning("Couldn't load image: %s", wxString(ex.what()));
        } catch (...) {
            wxLogWarning("Unknown exception");
        }
    }

//        for (int i: std::ranges::iota_view(1, 5)) {
//            auto filename = wxString::Format("C:\\Users\\jorge\\Desktop\\test\\%d.bmp", i);
//            sizer_gallery->Add(new wxImagePanel(this, filename.ToStdString()), 0,
//                               wxALL |  wxEXPAND );
//        }
    SetSizer(sizer_gallery);
    Layout();
    sizer_gallery->FitInside(this);
}
} // imgr