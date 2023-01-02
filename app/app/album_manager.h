//
// Created by jorge on 01/01/2023.
//

#ifndef IMAGE_MANAGER_ALBUM_MANAGER_H
#define IMAGE_MANAGER_ALBUM_MANAGER_H

#include <data/photo_store.h>
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

    using PhotoList = PhotoStore::PhotoList;
    using ImagePtr = std::shared_ptr<wxImage>;

    /// Constructor with access to configuration file
    /// \param config
    explicit AlbumManager(const Config& config);

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
};

} // imgr

#endif //IMAGE_MANAGER_ALBUM_MANAGER_H
