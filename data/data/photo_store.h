#ifndef IMAGE_MANAGER_PHOTO_STORE_H
#define IMAGE_MANAGER_PHOTO_STORE_H

#include <odb/database.hxx>
#include <odb/session.hxx>
#include <odb/sqlite/database.hxx>

#include <model/store.h>
#include <model/store-odb.hxx>

#include <memory>
#include <string>

#include <boost/filesystem.hpp>

//#define IMGR_ENABLE_TRACING

namespace imgr {
namespace filesystem = boost::filesystem;

/// Class for managing access to photos
class PhotoStore {
public:
    using id_type = model::ID_TYPE;
    using AlbumPtr = odb::object_traits<model::Album>::pointer_type;
    using PhotoPtr = odb::object_traits<model::Photo>::pointer_type;
    using PhotoList = std::vector<PhotoPtr>;
    using ThumbnailPtr = odb::object_traits<model::PhotoThumbnail>::pointer_type;
    using DatabaseType = odb::sqlite::database;

    using Dimension = uint16_t;

    /// Creates a new PhotoStore and connects to DB
    /// \param db_path Path to where to store the database
    /// \param recreate True to delete the database and create anew
    explicit PhotoStore(const filesystem::path& db_path, bool recreate = false);

    /// Retrieves an album given an absolute path
    /// \param album_path
    /// \return
    AlbumPtr get_album(const filesystem::path &album_path);

    /// Creates a new album and, if specified, creates entry for all the photos within
    /// \param album_path
    /// \param load_images
    /// \return
    AlbumPtr create_album(const filesystem::path &album_path, bool load_images = true);

    /// Returns a list of the photos in the album
    /// \param album_id
    /// \return
    PhotoList get_album_photos(model::Album::id_type album_id);

    /// Returns the thumbnail from a photo
    /// \param photo
    /// \return
    ThumbnailPtr get_photo_thumbnail(model::Photo::id_type photo_id);

    /// Calculates the dimensions that keep the aspect ratio and where the largest one equals target_max
    /// \param width
    /// \param height
    /// \param target_max
    /// \return pair(Width, Height)
    static std::pair<Dimension, Dimension>
    calculate_dimensions(Dimension width, Dimension height, Dimension target_max) {
        if (width > height) {
            Dimension new_width = target_max;
            Dimension new_height = height * new_width / width;
            return std::make_pair(new_width, new_height);
        } else {
            Dimension new_height = target_max;
            Dimension new_width = width * new_height / height;
            return std::make_pair(new_width, new_height);
        }
    }

private:
    /// Enable tracing for the current transaction
    /// \param t
    inline void do_trace(odb::transaction &t) {
#ifdef IMGR_ENABLE_TRACING
        t.tracer(odb::stderr_tracer);
#endif
    }

    DatabaseType m_database;

    odb::session m_session;

    /* CONSTANTS */
    const Dimension THUMBNAIL_SIZE = 128;
    const std::string THUMBNAIL_NAME = "thumbnail.jpg";

    /* DEFINITIONS */
    using AlbumQuery = odb::query<imgr::model::Album>;
    using AlbumResult = odb::result<imgr::model::Album>;
    using PhotoQuery = odb::query<imgr::model::Photo>;
    using PhotoResult = odb::result<imgr::model::Photo>;
    using ThumbnailQuery = odb::query<imgr::model::PhotoThumbnail>;
};

} // imgr

#endif //IMAGE_MANAGER_PHOTO_STORE_H
