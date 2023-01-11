//
// Created by jorge on 27/12/2022.
//

#ifndef IMAGE_MANAGER_IMAGE_GALLERY_H
#define IMAGE_MANAGER_IMAGE_GALLERY_H

#include <wx/scrolwin.h>

#include <boost/filesystem.hpp>

namespace imgr {
namespace filesystem = boost::filesystem;
    /// Displays a
    class wxImageGallery : public wxScrolledWindow {
    public:
        using ImageList = std::vector<std::unique_ptr<wxImage>>;

        /// Provided constructor
        /// \param parent
        /// \param winid
        /// \param pos
        /// \param size
        /// \param style
        wxImageGallery(wxWindow *parent, wxWindowID winid, const wxPoint &pos, const wxSize &size, long style);

        /// Sets the image
        /// \param images
        void SetImages(const ImageList& images);
    };

} // imgr

#endif //IMAGE_MANAGER_IMAGE_GALLERY_H
