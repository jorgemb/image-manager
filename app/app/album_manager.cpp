//
// Created by jorge on 01/01/2023.
//

#include "album_manager.h"

#include <data/config.h>

#include <wx/image.h>

#include <string>


namespace imgr {
AlbumManager::AlbumManager(const Config &config) {
    // Create the PhotoStore
    const auto &params = config.get_connection_parameters();
    m_store = std::make_unique<PhotoStore>(params.at("file"));
}

AlbumManager::AlbumPtr AlbumManager::add_root_album(const filesystem::path& absolute_path){
    // Verify if the album already exists
    if(m_store->get_album(absolute_path)){
        return false;
    }

    // Create the album and return
    AlbumPtr album = create_album(DirectoryTree{absolute_path}, nullptr);

    return album;
}

std::vector<AlbumManager::AlbumPtr> AlbumManager::get_root_albums(){
    return m_store->get_root_albums();
}

AlbumManager::AlbumList AlbumManager::get_sub_albums(AlbumId id){
    return m_store->get_children_albums(id);
}

AlbumManager::PhotoList AlbumManager::get_album_photos(AlbumManager::AlbumId id) {
    return m_store->get_album_photos(id);
}

//AlbumManager::ImagePtr AlbumManager::load_photo_thumbnail(PhotoId id) {
//    m_store->get_photo_thumbnail(id);
//}

AlbumManager::AlbumPtr AlbumManager::create_album(const DirectoryTree &tree, AlbumManager::AlbumPtr parent) {
    // Creates the current album
    auto album = m_store->create_album(tree.get_path(), true, parent);

    // Creates the album for the subdirectories
    for(const auto& subdirectory: tree.get_subdirectories()){
        create_album(subdirectory, album);
    }

    return album;
}

} // imgr