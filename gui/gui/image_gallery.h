//
// Created by jorge on 27/12/2022.
//

#ifndef IMAGE_MANAGER_IMAGE_GALLERY_H
#define IMAGE_MANAGER_IMAGE_GALLERY_H

#include <wx/scrolwin.h>

#include <filesystem>

namespace imgr {

    class wxImageGallery : public wxScrolledWindow {
    public:
        /// Provided constructor
        /// \param parent
        /// \param winid
        /// \param pos
        /// \param size
        /// \param style
        wxImageGallery(wxWindow *parent, wxWindowID winid, const wxPoint &pos, const wxSize &size, long style);

        /// Changes the path of the folder to load
        /// \param images_path
        void SetImagesPath(const std::filesystem::path &images_path);

    private:
        /// Current path being displayed
        std::filesystem::path m_current_path;
    };

} // imgr

#endif //IMAGE_MANAGER_IMAGE_GALLERY_H
