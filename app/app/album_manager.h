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
class RawImage;

/// Represent the album structure
class AlbumManager {
public:
    using PhotoId = PhotoStore::id_type;
    using AlbumId = PhotoStore::id_type;
    using AlbumCPtr = PhotoStore::AlbumCPtr;
    using PhotoCPtr = PhotoStore::PhotoCPtr;
    using ThumbnailCPtr = PhotoStore::ThumbnailCPtr;

    using PhotoList = PhotoStore::PhotoList;
    using AlbumList = PhotoStore::AlbumList;

    /// Constructor with access to configuration file
    /// \param config
    explicit AlbumManager(const Config &config);

    /// Add an album root to the manager
    /// \param absolute_path
    /// \return
    AlbumCPtr add_root_album(const filesystem::path &absolute_path);

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
    ThumbnailCPtr load_photo_thumbnail(PhotoId id);

    /// Loads a photo
    /// \param id
    /// \return
//    std::unique_ptr<RawImage> load_photo(PhotoId id);

    /// Returns an iterator for the AlbumManager starting from the provided album
    /// \param root
    /// \return
    AlbumIterator begin();

    /// Returns an end iterator
    /// \return
    AlbumIterator end();

private:
    /// Photo store
    std::unique_ptr<PhotoStore> m_store;

    /// Creates a new album in the given tree, and recursively adds the subdirectories
    /// \param tree
    /// \param parent
    AlbumCPtr create_album(const DirectoryTree &tree, const AlbumCPtr& parent);
};

/// Allows lazy breadth-first iteration of albums
class AlbumIterator : public std::iterator<std::input_iterator_tag, AlbumManager::AlbumCPtr> {
public:
    using AlbumCPtr = AlbumManager::AlbumCPtr;

    /// Default constructor. Creates an END iterator.
    AlbumIterator() = default;

    /// Creates an album iterator to the given manager
    /// \param manager
    explicit AlbumIterator(AlbumManager *manager);

    /* OPERATORS */

    AlbumCPtr &operator*();

    AlbumCPtr operator->();

    bool operator==(const AlbumIterator &rhs) const;

    bool operator!=(const AlbumIterator &rhs) const {
        return !(rhs == *this);
    }

    // Continues to the next element in the iteration
    AlbumIterator &operator++();

private:
    AlbumManager *m_manager{};
    std::deque<value_type> m_visit_queue;
};


} // imgr

#endif //IMAGE_MANAGER_ALBUM_MANAGER_H
