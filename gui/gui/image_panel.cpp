//
// Created by jorge on 18/12/2022.
//

#include "image_panel.h"

#include <filesystem>

namespace imgr {
    wxImagePanel::wxImagePanel(wxWindow *parent, std::filesystem::path image_path)
            : wxPanel(parent, wxID_ANY), m_image_path(image_path),
              m_last_width(-1), m_last_height(-1) {
        m_image.LoadFile(image_path.string());

        // Calculate minimum size
        auto image_size = m_image.GetSize();
        int min_width = wxRound( 1.0 * image_size.GetWidth() / image_size.GetHeight() * TARGET_MIN_HEIGHT );
        SetInitialSize(wxSize(min_width, TARGET_MIN_HEIGHT));

        // Bind events
        Bind(wxEVT_PAINT, &wxImagePanel::OnPaint, this);
        Bind(wxEVT_SIZE, &wxImagePanel::OnResize, this);

        Bind(wxEVT_ENTER_WINDOW, [this](auto &evt) { SetBackgroundColour((255, 0, 0)); });
        Bind(wxEVT_LEAVE_WINDOW, [this](auto &evt) { SetBackgroundColour((0, 255, 0)); });
    }

    void wxImagePanel::OnPaint(wxPaintEvent &evt) {
        wxPaintDC dc(this);
        render(dc);
    }

    void wxImagePanel::OnResize(wxSizeEvent &evt) {
        evt.Skip();

        // Calculate new size based on the aspect ratio of the image
        auto image_size = m_image.GetSize();
        auto new_size = evt.GetSize();
        new_size.SetWidth(wxRound(1.0 * new_size.GetHeight() * image_size.GetWidth() / image_size.GetHeight()));

        // Update the control with the new size
//        SetMinSize(wxSize(new_size.GetWidth(), -1));
//        SetMaxSize(wxSize(new_size.GetWidth(), -1));
        SetClientSize(new_size);

        // Force repaint
        Refresh();
    }

    void wxImagePanel::paint_now() {
        wxClientDC dc(this);
        render(dc);
    }

    void wxImagePanel::render(wxDC &dc) {
        int new_width, new_height;
        dc.GetSize(&new_width, &new_height);

        if (new_width != m_last_width || new_height != m_last_height) {
            m_image_resized = m_image.Scale(new_width, new_height);
            m_last_width = new_width;
            m_last_height = new_height;
        }
        dc.DrawBitmap(m_image_resized, 0, 0, false);
    }

    wxSize wxImagePanel::DoGetBestClientSize() const {
        return wxWindowBase::DoGetBestClientSize();
    }

} // imgr