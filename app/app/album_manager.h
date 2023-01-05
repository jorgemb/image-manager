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

namespace imgr {

/* Forward declarations */
class Config;
class wxImage;

class AlbumManager{
public:
    using PhotoId = PhotoStore::id_type;
    using AlbumId = PhotoStore::id_type;
    using AlbumPtr = PhotoStore::AlbumPtr;

    using PhotoList = PhotoStore::PhotoList;
    using AlbumList = PhotoStore::AlbumList;
    using ImagePtr = std::shared_ptr<wxImage>;

    /// Constructor with access to configuration file
    /// \param config
    explicit AlbumManager(const Config& config);

    /// Add an album root to the manager
    /// \param absolute_path
    /// \return
    AlbumPtr add_root_album(const filesystem::path& absolute_path);

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
    ImagePtr load_photo_thumbnail(PhotoId id);

private:
    /// Photo store
    std::unique_ptr<PhotoStore> m_store;

    /// Creates a new album in the given tree, and recursively adds the subdirectories
    /// \param tree
    /// \param parent
    AlbumPtr create_album(const DirectoryTree& tree, AlbumPtr parent);
};

} // imgr

#endif //IMAGE_MANAGER_ALBUM_MANAGER_H
