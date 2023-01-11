//
// Created by jorge on 18/12/2022.
//

#ifndef IMAGE_MANAGER_APPLICATION_H
#define IMAGE_MANAGER_APPLICATION_H

#include <view/view.h>
#include <data/config.h>
#include <app/album_manager.h>

#include <utility>

#include <wx/wx.h>

#include <boost/filesystem.hpp>

namespace imgr {

/// Main window for the application
class ImageManagerWindow : public imgr::ImageManager {
public:
    explicit ImageManagerWindow(wxWindow *parent) : ImageManager(parent) {}

    /// Refreshes the full tree of the albums
    void refresh_full_tree();

protected:
    /// Called when the selection changes
    /// \param event
    void TreeAlbums_OnTreeSelChanged(wxTreeEvent &event) override;

private:
    using ImageList = wxImageGallery::ImageList;
    ImageList m_thumbnails;
};

/// Represents a node for the album tree data
class AlbumTreeData : public wxTreeItemData {
public:
    explicit AlbumTreeData(AlbumManager::AlbumCPtr album) : m_album(std::move(album)) {}
    const AlbumManager::AlbumCPtr &get_album() const { return m_album; }
private:
    AlbumManager::AlbumCPtr m_album;
};


/// Class to manage the application
class ImageManagerApp : public wxApp {
public:
    /// Entry point of the application
    /// \return
    bool OnInit() override;

    /// Get the album manager from the application
    AlbumManager& GetAlbumManager();

private:
    // Configuration data for the application
    std::unique_ptr<Config> m_config;

    // Album manager
    std::unique_ptr<AlbumManager> m_album_manager;
};

wxDECLARE_APP(ImageManagerApp);

} // imgr

#endif //IMAGE_MANAGER_APPLICATION_H
