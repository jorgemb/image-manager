//
// Created by jorge on 18/12/2022.
//

#ifndef IMAGE_MANAGER_IMAGE_PANEL_H
#define IMAGE_MANAGER_IMAGE_PANEL_H

#include <filesystem>

#include <wx/wx.h>

namespace imgr {
    class wxImagePanel : public wxPanel {
    public:
        /// Default constructor with parent and path
        /// \param parent
        /// \param image_path
        wxImagePanel(wxWindow *parent, std::filesystem::path image_path);

        /// On paint event
        /// \param evt
        void OnPaintEvent(wxPaintEvent &evt);

        /// On Resize event
        /// \param evt
        void OnResize(wxSizeEvent &evt);


        /// Repaints the control
        void PaintNow();

        /// Renders using the device context
        /// \param dc
        void Render(wxDC &dc);

    private:
        /// Does the actual resize of the panel
        /// \param expected_size
        void DoResize(const wxSize &expected_size);

        // Path to the image
        std::filesystem::path m_image_path;

        // Image data
        wxImage m_image, m_image_resized;
        int m_last_width, m_last_height;

        const int TARGET_MIN_HEIGHT = 100;
    };

} // imgr

#endif //IMAGE_MANAGER_IMAGE_PANEL_H
