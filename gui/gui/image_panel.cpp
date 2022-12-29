//
// Created by jorge on 18/12/2022.
//

#include "image_panel.h"
#include <gui/exceptions.h>

namespace imgr {
    wxImagePanel::wxImagePanel(wxWindow *parent, filesystem::path image_path)
            : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxDOUBLE_BORDER),
              m_image_path(image_path),
              m_last_width(-1), m_last_height(-1) {
        // Load image and check if successful
        bool image_loaded = m_image.LoadFile(image_path.string());
        if (!image_loaded) {
            throw InvalidImageException(image_path.string());
        }

        // Calculate minimum size
        auto image_size = m_image.GetSize();
        int min_width = wxRound(1.0 * image_size.GetWidth() / image_size.GetHeight() * TARGET_MIN_HEIGHT);
        SetInitialSize(wxSize(min_width, TARGET_MIN_HEIGHT));

        // Bind events
        Bind(wxEVT_PAINT, &wxImagePanel::OnPaintEvent, this);
        Bind(wxEVT_SIZE, &wxImagePanel::OnResize, this);
    }

    void wxImagePanel::OnPaintEvent(wxPaintEvent &evt) {
        wxPaintDC dc(this);
        Render(dc);
    }

    void wxImagePanel::OnResize(wxSizeEvent &evt) {
        evt.Skip();
        DoResize(evt.GetSize());
    }

    void wxImagePanel::PaintNow() {
        wxClientDC dc(this);
        Render(dc);
    }

    void wxImagePanel::Render(wxDC &dc) {
        int new_width, new_height;
        dc.GetSize(&new_width, &new_height);

        if (new_width != m_last_width || new_height != m_last_height) {
            m_image_resized = m_image.Scale(new_width, new_height);
            m_last_width = new_width;
            m_last_height = new_height;
        }
        dc.DrawBitmap(m_image_resized, 0, 0, false);
    }

    void wxImagePanel::DoResize(const wxSize &expected_size) {
        // Calculate new size based on the aspect ratio of the image
        auto image_size = m_image.GetSize();
        int width = wxRound(1.0 * expected_size.GetHeight() * image_size.GetWidth() / image_size.GetHeight());

        // Update the control with the new size
        SetMinSize(wxSize(width, -1));
        SetMaxSize(wxSize(width, -1));
//        SetClientSize(new_size);

        // Force repaint
        Refresh();
    }
} // imgr