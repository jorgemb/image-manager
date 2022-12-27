//
// Created by jorge on 18/12/2022.
//

#ifndef IMAGE_MANAGER_IMAGE_PANEL_H
#define IMAGE_MANAGER_IMAGE_PANEL_H

#include <filesystem>

#include <wx/wx.h>

namespace imgr {

    class wxImagePanel: public wxPanel{
    public:
        /// Default constructor with parent and path
        /// \param parent
        /// \param image_path
        wxImagePanel(wxWindow *parent, std::filesystem::path image_path);

        /// On paint event
        /// \param evt
        void OnPaint(wxPaintEvent &evt);

        /// On Resize event
        /// \param evt
        void OnResize(wxSizeEvent &evt);

    protected:
        wxSize DoGetBestClientSize() const override;

    public:

        /// Repaints the control
        void paint_now();

        /// Renders using the device context
        /// \param dc
        void render(wxDC& dc);

    private:
        // Path to the image
        std::filesystem::path m_image_path;

        // Image data
        wxImage m_image, m_image_resized;
        int m_last_width, m_last_height;

        const int TARGET_MIN_HEIGHT = 100;
    };

} // imgr

#endif //IMAGE_MANAGER_IMAGE_PANEL_H
