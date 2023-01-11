#ifndef IMAGE_MANAGER_IMAGE_PANEL_H
#define IMAGE_MANAGER_IMAGE_PANEL_H

#include <wx/wx.h>

#include <memory>

namespace imgr {

class wxImagePanel : public wxPanel {
public:
    /// Default constructor with parent and path
    /// \param parent
    /// \param image_path
    wxImagePanel(wxWindow *parent, const wxImage *image);

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

    // Image to show
    const wxImage *m_image;
    wxImage m_image_resized;
    int m_last_width = -1, m_last_height = -1;

    const int TARGET_MIN_HEIGHT = 100;
};

} // imgr

#endif //IMAGE_MANAGER_IMAGE_PANEL_H
