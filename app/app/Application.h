//
// Created by jorge on 18/12/2022.
//

#ifndef IMAGE_MANAGER_APPLICATION_H
#define IMAGE_MANAGER_APPLICATION_H

#include <gui/gui.h>
#include <data/directory_tree.h>
#include <data/config.h>

#include <filesystem>
#include <utility>

#include <wx/wx.h>

namespace imgr {
    class ImageManagerWindow: public imgr::ImageManager{
    public:
        ImageManagerWindow(wxWindow *parent) : ImageManager(parent) {}

        /// Adds a tree root to the Window
        /// \param tree_root
        /// \return
        void add_directory_root(const std::filesystem::path &tree_root);

        /// Refreshes the full tree of the albums
        void refresh_full_tree();
    protected:
        /// Called when the selection changes
        /// \param event
        void TreeAlbums_OnTreeSelChanged(wxTreeEvent &event) override;

    private:
        // Contains all the tree roots of images
        std::vector<imgr::DirectoryTree> m_tree_roots;

        /// Refreshes the directory tree
        void refresh_tree(const wxTreeItemId& parent_item, const std::filesystem::path& current_path, imgr::DirectoryTree& current_tree);

        /// Refreshes the thumbnail list using the images in the directory path
        /// \param directory_path Root of the directory path to load images from
        void refresh_thumbnail_list(const std::filesystem::path& directory_path);
    };

    /// Class to manage the application
    class ImageManagerApp: public wxApp{
    public:
        /// Entry point of the application
        /// \return
        bool OnInit() override;

    private:
        // Configuration data for the application
        std::unique_ptr<Config> m_config;
    };

    wxDECLARE_APP(ImageManagerApp);

} // imgr

#endif //IMAGE_MANAGER_APPLICATION_H
