//
// Created by jorge on 01/01/2023.
//

#include "album_manager.h"

#include <data/config.h>

#include <string>


namespace imgr {
AlbumManager::AlbumManager(const Config &config) {
    // Create the PhotoStore
    const auto &params = config.get_connection_parameters();
    m_store = std::make_unique<PhotoStore>(params.at("file"));
}

AlbumManager::AlbumPtr AlbumManager::add_root_album(const filesystem::path &absolute_path) {
    // Verify if the album already exists
    if (m_store->get_album(absolute_path)) {
        return false;
    }

    // Create the album and return
    AlbumPtr album = create_album(DirectoryTree{absolute_path}, nullptr);

    return album;
}

std::vector<AlbumManager::AlbumPtr> AlbumManager::get_root_albums() {
    return m_store->get_root_albums();
}

AlbumManager::AlbumList AlbumManager::get_sub_albums(AlbumId id) {
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
    for (const auto &subdirectory: tree.get_subdirectories()) {
        create_album(subdirectory, album);
    }

    return album;
}

AlbumIterator AlbumManager::begin() {
    return AlbumIterator(this);
}

AlbumIterator AlbumManager::end() {
    return {};
}

/// ALBUM ITERATOR ///

AlbumIterator::AlbumPtr &AlbumIterator::operator*() {
    if (!m_visit_queue.empty()) {
        return m_visit_queue.front();
    } else {
        throw std::logic_error("Dereference to invalid value in AlbumIterator");
    }
}

AlbumIterator::AlbumPtr AlbumIterator::operator->() {
    if (!m_visit_queue.empty()) {
        return m_visit_queue.front();
    } else {
        return nullptr;
    }
}

bool AlbumIterator::operator==(const AlbumIterator &rhs) const {
    // Check trivial case
    bool both_empty = m_visit_queue.empty() && rhs.m_visit_queue.empty();
    if (both_empty) return true;

    // Check same manager
    bool same_manager = m_manager == rhs.m_manager;
    if (!same_manager) return false;

    // If both are not empty, then the queues must hold the same elements
    return m_visit_queue == rhs.m_visit_queue;
}

AlbumIterator &AlbumIterator::operator++() {
    if (!m_visit_queue.empty()) {
        // Retrieve element
        auto album = m_visit_queue.front();
        m_visit_queue.pop_front();

        // Add children to the queue
        auto sub_albums = m_manager->get_sub_albums(album->get_id());
        std::copy(sub_albums.begin(), sub_albums.end(), std::back_inserter(m_visit_queue));
    }

    return *this;
}

AlbumIterator::AlbumIterator(AlbumManager *manager) : m_manager(manager) {
    auto root_albums = manager->get_root_albums();
    std::copy(root_albums.begin(), root_albums.end(), std::back_inserter(m_visit_queue));
}

} // imgr