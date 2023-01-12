//
// Created by jorge on 18/12/2022.
//

#include <app/application.h>
#include <app/images.h>

#include <gui/image_panel.h>

#include <wx/image.h>

namespace imgr {

wxIMPLEMENT_APP(ImageManagerApp);

void ImageManagerWindow::TreeAlbums_OnTreeSelChanged(wxTreeEvent &event) {
    auto selected_item = event.GetItem();
    auto item_data = dynamic_cast<AlbumTreeData *>(tree_albums->GetItemData(selected_item));

    if (item_data) {
        // Get album and display information
        auto &album = item_data->get_album();
        bar_status->SetStatusText(album->get_absolute_path());

        // Create the list of images
        auto &album_manager = wxGetApp().GetAlbumManager();
        auto album_photos = album_manager.get_album_photos(album->get_id());
        ImageList images;
        std::transform(album_photos.begin(), album_photos.end(), std::back_inserter(images),
                       [&album_manager](auto &photo){
            auto thumbnail = album_manager.load_photo_thumbnail(photo->get_id());
            return Image::create_image(thumbnail);
        });
        panel_gallery->SetImages(std::move(images));

        // Copy the new album photos
    } else {
        bar_status->SetStatusText("");
    }
}

void ImageManagerWindow::refresh_full_tree() {
    tree_albums->DeleteAllItems();
    // Create root item
    auto root_item = tree_albums->AppendItem(
            tree_albums->GetRootItem(),
            "Albums");

    // Iterate through all the items
    std::map<AlbumManager::AlbumId, decltype(root_item)> album_map;
    for (auto &album: wxGetApp().GetAlbumManager()) {
        auto id = album->get_id();
        auto parent_album = album->get_parent_album();

        // Get the parent item on the tree
        bool is_root = parent_album == nullptr;
        auto parent_item = !is_root ? album_map.at(parent_album->get_id()) : root_item;
        auto item = tree_albums->AppendItem(parent_item, album->get_name(), -1, -1,
                                            new AlbumTreeData(album));

        // Add to the map
        album_map[id] = item;
    }

}

bool ImageManagerApp::OnInit() {
    // Load configuration file
    m_config = std::make_unique<Config>("config.yml");

    // Create album manager
    m_album_manager = std::make_unique<AlbumManager>(*m_config);

    // Load all image handlers
    wxInitAllImageHandlers();

    // Create main window
    auto *main_window = new ImageManagerWindow(nullptr);
    main_window->refresh_full_tree();

    // .. show main window
    main_window->Show(true);

    return true;
}

AlbumManager &ImageManagerApp::GetAlbumManager() {
    return *m_album_manager;
}
} // imgr

