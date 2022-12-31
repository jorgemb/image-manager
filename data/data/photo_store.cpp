//
// Created by jorge on 29/12/2022.
//

#include <data/photo_store.h>

#include <odb/query.hxx>

#include <OpenImageIO/imageio.h>
#include <OpenImageIO/imagebuf.h>
#include <OpenImageIO/imagebufalgo.h>


namespace imgr {

/// Class to do query transactions that commits on destruction
class QueryTransaction {
public:
    QueryTransaction(odb::transaction_impl *impl) : m_transaction(impl) {}

    ~QueryTransaction() { m_transaction.commit(); }

    odb::transaction &get_transaction() { return m_transaction; }

private:
    odb::transaction m_transaction;
};


PhotoStore::PhotoStore(const std::string &user, const std::string &password, const std::string &db,
                       const std::string &host, uint16_t port) :
        m_database(user, password, db, host, port), m_session(true) {
}

PhotoStore::AlbumPtr PhotoStore::get_album(const filesystem::path &album_path) {
    // Search for the album in the database
    QueryTransaction t(m_database.begin());
    do_trace(t.get_transaction());

    AlbumPtr album = m_database.query_one<model::Album>(AlbumQuery::absolute_path == album_path.string());
    return album;
}

PhotoStore::AlbumPtr PhotoStore::create_album(const filesystem::path &album_path, bool load_images) {
    odb::transaction t(m_database.begin());
    do_trace(t);

    // Create the new album
    AlbumPtr album = std::make_shared<model::Album>(album_path.string());
    m_database.persist(album);

    // Handle image creation
    if (load_images) {
        for (filesystem::directory_iterator iter(album_path); iter != filesystem::directory_iterator{}; ++iter) {
            // Skip directories
            filesystem::path photo_path = iter->path();
            if (!filesystem::is_regular_file(photo_path)) continue;

            // Load image information
            OIIO::ImageBuf image(photo_path.string());
            if (!image.initialized()) continue;     // Not a readable image

            auto spec = image.spec();
            auto new_photo = std::make_shared<model::Photo>(photo_path.filename().string(), spec.width, spec.height,
                                                            album);
            m_database.persist(new_photo);

            // Create thumbnail
            Dimension width, height;
            int channels = 3;
            std::tie(width, height) = calculate_dimensions(spec.width, spec.height, THUMBNAIL_SIZE);
            OIIO::ImageBuf image_thumbnail(OIIO::ImageSpec{width, height, channels, OIIO::TypeDesc::UINT8});

            bool ok = OIIO::ImageBufAlgo::resize(image_thumbnail, image);
            // TODO: Handle failure of resize

            // .. copy to buffer
            size_t size = width * height * channels;
            std::vector<uint8_t> buffer;
            buffer.reserve(size);

            // Read all data
            for (OIIO::ImageBuf::ConstIterator<uint8_t> pixel(image_thumbnail); !pixel.done(); ++pixel) {
                for (int c = 0; c < channels; ++c) {
                    buffer.push_back(pixel[c]);
                }
            }

            // Create Thumbnail
            auto photo_thumbnail = std::make_shared<model::PhotoThumbnail>(width,
                                                                           height, std::move(buffer),
                                                                           new_photo);
            m_database.persist(photo_thumbnail);
        }
    }

    t.commit();

    return album;
}

std::vector<PhotoStore::PhotoPtr> PhotoStore::get_album_photos(const AlbumPtr &album) {
    QueryTransaction t(m_database.begin());

    // Retrieve all the photos
    std::vector<PhotoPtr> album_photos;
    PhotoResult photos(m_database.query<model::Photo>(PhotoQuery::album->id == album->get_id()));

    for (auto iter = photos.begin(); iter != photos.end(); ++iter) {
        album_photos.push_back(iter.load());
    }

    return album_photos;
}

PhotoStore::ThumbnailPtr PhotoStore::get_photo_thumbnail(const PhotoStore::PhotoPtr &photo) {
    QueryTransaction t(m_database.begin());

    // Get the thumbnail for the current photo
    auto thumbnail = m_database.query_one<model::PhotoThumbnail>(ThumbnailQuery::photo->id == photo->get_id());

    return thumbnail;
}
} // imgr