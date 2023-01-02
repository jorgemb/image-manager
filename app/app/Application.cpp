//
// Created by jorge on 18/12/2022.
//

#include <app/application.h>

#include <gui/image_panel.h>

namespace imgr {
    class AlbumTreeData : public wxTreeItemData {
    public:
        /// Default constructor with path
        explicit AlbumTreeData(const filesystem::path &path) : m_path(path) {}

        /// Returns the path associated to the item
        /// \return
        const filesystem::path &get_path() const {
            return m_path;
        }

    private:
        filesystem::path m_path;
    };

    void ImageManagerWindow::TreeAlbums_OnTreeSelChanged(wxTreeEvent &event) {
        auto selected_item = event.GetItem();
        auto *item_data = dynamic_cast<AlbumTreeData *>(tree_albums->GetItemData(selected_item));

        if (item_data) {
            bar_status->SetStatusText(item_data->get_path().string());
            panel_gallery->SetImagesPath(item_data->get_path());
        } else {
            bar_status->SetStatusText("");
        }
    }

void ImageManagerWindow::refresh_tree(const wxTreeItemId &parent_item, const filesystem::path &current_path,
                                      DirectoryTree &current_tree) {
    // Add current
    auto current_item = tree_albums->AppendItem(parent_item, current_path.filename().string(),
                                                -1, -1, new AlbumTreeData(current_path));
    bool ok = current_item.IsOk();

    // Add children
    for (auto &path: current_tree.children_of(current_path)) {
        refresh_tree(current_item, path, current_tree);
    }
    }

void ImageManagerWindow::add_directory_root(const filesystem::path &tree_root) {
    // Add the new root
    m_tree_roots.emplace_back(tree_root);
}

    void ImageManagerWindow::refresh_full_tree() {
        tree_albums->DeleteAllItems();
        // Create root item
        auto root_item = tree_albums->AppendItem(
                tree_albums->GetRootItem(),
                "Albums");

        // Iterate through all the roots
        for (auto &directory_tree: m_tree_roots) {
            refresh_tree(root_item, directory_tree.get_root(), directory_tree);
        }
    }

    bool ImageManagerApp::OnInit() {
        // Load configuration file
        m_config = std::make_unique<Config>("config.yml");

        // Load all image handlers
        wxInitAllImageHandlers();

        // Create main window
        auto *main_window = new ImageManagerWindow(nullptr);
        for (const auto &root_dir: m_config->get_search_directories()) {
            main_window->add_directory_root(root_dir);
        }
        main_window->refresh_full_tree();

        // .. show main window
        main_window->Show(true);

        return true;
    }
} // imgr

wxIMPLEMENT_APP(imgr::ImageManagerApp);
