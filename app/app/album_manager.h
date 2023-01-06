//
// Created by jorge on 01/01/2023.
//

#ifndef IMAGE_MANAGER_ALBUM_MANAGER_H
#define IMAGE_MANAGER_ALBUM_MANAGER_H

#include <data/photo_store.h>
#include <data/directory_tree.h>
#include <model/store.h>

#include <memory>
#include <vector>
#include <iterator>
#include <deque>

namespace imgr {

/* Forward declarations */
class Config;
class AlbumIterator;

/// Represent the album structure
class AlbumManager : public std::enable_shared_from_this<AlbumManager> {
public:
    using PhotoId = PhotoStore::id_type;
    using AlbumId = PhotoStore::id_type;
    using AlbumPtr = PhotoStore::AlbumPtr;

    using PhotoList = PhotoStore::PhotoList;
    using AlbumList = PhotoStore::AlbumList;

    /// Allows the creation of a new AlbumManager via shared pointer interface
    /// \param config
    /// \return
    [[nodiscard]]
    static std::shared_ptr<AlbumManager> create(const Config &config) {
        return std::shared_ptr<AlbumManager>(new AlbumManager(config));
    }

    /// Returns a shared pointer from this
    /// \return
//    std::shared_ptr<AlbumManager> get_ptr() { return shared_from_this(); }

    /// Add an album root to the manager
    /// \param absolute_path
    /// \return
    AlbumPtr add_root_album(const filesystem::path &absolute_path);

    /// Returns a list with the root albums
    /// \return
    AlbumList get_root_albums();

    /// Returns a list of the sub-albums of the current album
    /// \param id
    /// \return
    AlbumList get_sub_albums(AlbumId id);

    /// Returns the photos that belong to the given Album
    /// \param id
    /// \return
    PhotoList get_album_photos(AlbumId id);

    /// Loads the thumbnail of a given photo
    /// \param id
    /// \return
//    ImagePtr load_photo_thumbnail(PhotoId id);

    /// Returns an iterator for the AlbumManager starting from the provided album
    /// \param root
    /// \return
    AlbumIterator begin();

    /// Returns an end iterator
    /// \return
    AlbumIterator end();

private:
    /// Constructor with access to configuration file
    /// \param config
    explicit AlbumManager(const Config &config);

    /// Photo store
    std::unique_ptr<PhotoStore> m_store;

    /// Creates a new album in the given tree, and recursively adds the subdirectories
    /// \param tree
    /// \param parent
    AlbumPtr create_album(const DirectoryTree &tree, AlbumPtr parent);
};

/// Allows lazy breadth-first iteration of albums
class AlbumIterator : public std::iterator<std::input_iterator_tag, AlbumManager::AlbumPtr> {
public:
    using AlbumPtr = AlbumManager::AlbumPtr;
    /// Default constructor. Creates an END iterator.
    AlbumIterator() = default;

    /* OPERATORS */

    AlbumPtr &operator*();

    AlbumPtr operator->();

    bool operator==(const AlbumIterator &rhs) const;

    bool operator!=(const AlbumIterator &rhs) const {
        return !(rhs == *this);
    }

    // Continues to the next element in the iteration
    AlbumIterator& operator++();

    // Creates the album iterator
    static AlbumIterator create_iterator(const std::shared_ptr<AlbumManager> &manager);

private:
    std::shared_ptr<AlbumManager> m_manager;
    std::deque<value_type> m_visit_queue;
};


} // imgr

#endif //IMAGE_MANAGER_ALBUM_MANAGER_H
