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
    m_store = std::make_unique<PhotoStore>(params.at("user"),
                                           params.at("password"),
                                           params.at("database"),
                                           params.at("host"),
                                           std::stoi(params.at("port").c_str()));

}

AlbumManager::PhotoList AlbumManager::get_album_photos(AlbumManager::AlbumId id) {
    return m_store->get_album_photos(id);
}

AlbumManager::ImagePtr AlbumManager::load_photo_thumbnail(PhotoId id) {
    m_store->get_photo_thumbnail(id);
}

} // imgr