#include <gui/gui.h>
#include <wx/wx.h>

class ImageManagerWindow: public imgr::ImageManager{
public:
    ImageManagerWindow(wxWindow *parent) : ImageManager(parent) {}

protected:
    void ImageManagerOnActivateApp(wxActivateEvent &event) override {
        ImageManager::ImageManagerOnActivateApp(event);
    }
};

class ImageManagerApp: public wxApp{
public:
    bool OnInit() override {
        auto* main_window = new ImageManagerWindow(nullptr);
        main_window->Show(true);

        return true;
    }
};

wxIMPLEMENT_APP(ImageManagerApp);