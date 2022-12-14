//
// Created by jorge on 29/12/2022.
//

#include <data/photo_store.h>

#include <odb/query.hxx>
#include <odb/schema-catalog.hxx>
#include <odb/sqlite/database.hxx>

#include <OpenImageIO/imageio.h>
#include <OpenImageIO/filter.h>
#include <OpenImageIO/imagebuf.h>
#include <OpenImageIO/imagebufalgo.h>
#include <OpenImageIO/filesystem.h>


namespace imgr {

/// Class to do query transactions that commits on destruction
class AutoTransaction {
public:
    AutoTransaction(odb::transaction_impl *impl) : m_transaction(impl) {}

    ~AutoTransaction() { m_transaction.commit(); }

    odb::transaction &get_transaction() { return m_transaction; }

private:
    odb::transaction m_transaction;
};


PhotoStore::PhotoStore(const filesystem::path &db_path, bool recreate)
        : m_database(db_path.string(), SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE) {

    if (!filesystem::exists(db_path) || recreate) {
        odb::transaction t(m_database.begin());
        odb::schema_catalog::create_schema(m_database, "", recreate);
        t.commit();
    }
}

PhotoStore::AlbumCPtr PhotoStore::get_album(const filesystem::path &album_path) {
    // Search for the album in the database
    AutoTransaction t(m_database.begin());
    do_trace(t.get_transaction());

    AlbumPtr album = m_database.query_one<model::Album>(AlbumQuery::absolute_path == album_path.string());
    return album;
}

PhotoStore::AlbumCPtr PhotoStore::get_album(model::Album::id_type album_id) {
    // Search for the album in the database
    AutoTransaction t(m_database.begin());
    do_trace(t.get_transaction());

    AlbumPtr album = m_database.query_one<model::Album>(AlbumQuery::id == album_id);
    return album;
}

PhotoStore::AlbumList PhotoStore::get_root_albums() {
    AutoTransaction t(m_database.begin());

    auto result = m_database.query<model::Album>(AlbumQuery::parent_album.is_null());
    AlbumList root_albums;
    for (auto iter = result.begin(); iter != result.end(); ++iter) {
        root_albums.emplace_back(iter.load());
    }

    return root_albums;
}

PhotoStore::AlbumList PhotoStore::get_children_albums(model::Album::id_type album_id) {
    AutoTransaction t(m_database.begin());

    auto result = m_database.query<model::Album>(AlbumQuery::parent_album->id == album_id);
    AlbumList children_albums;
    for (auto iter = result.begin(); iter != result.end(); ++iter) {
        children_albums.emplace_back(iter.load());
    }

    return children_albums;
}

PhotoStore::AlbumCPtr
PhotoStore::create_album(const filesystem::path &album_path, bool load_images, const AlbumCPtr &parent) {
    odb::transaction t(m_database.begin());
    do_trace(t);

    // Create the new album
    AlbumPtr album = std::make_shared<model::Album>(album_path.string(), album_path.filename().string(), parent);
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


        }
    }

    t.commit();

    return album;
}

PhotoStore::PhotoList PhotoStore::get_album_photos(model::Album::id_type album_id) {
    AutoTransaction t(m_database.begin());

    // Retrieve all the photos
    PhotoList album_photos;
    PhotoResult photos(m_database.query<model::Photo>(PhotoQuery::album->id == album_id));

    for (auto iter = photos.begin(); iter != photos.end(); ++iter) {
        album_photos.push_back(iter.load());
    }

    return album_photos;
}

PhotoStore::ThumbnailCPtr PhotoStore::get_photo_thumbnail(model::Photo::id_type photo_id) {
    AutoTransaction t(m_database.begin());

    // Get the thumbnail for the current photo
    auto thumbnail = m_database.query_one<model::PhotoThumbnail>(ThumbnailQuery::photo->id == photo_id);
    if(thumbnail){
        return thumbnail;
    } else {
        auto photo = m_database.query_one<model::Photo>(PhotoQuery::id == photo_id);
        return create_thumbnail(photo);
    }
}

PhotoStore::ThumbnailCPtr PhotoStore::create_thumbnail(const PhotoCPtr &photo) {
    // Load image from file
    auto &album = photo->get_album();
    auto image_path = filesystem::path(album->get_absolute_path()) / photo->get_filename();
    auto image = OIIO::ImageBuf(image_path.string());

    // Create thumbnail
    Dimension width, height;
    int channels = 3;
    std::tie(width, height) = calculate_dimensions(
            photo->get_width(),
            photo->get_height(),
            THUMBNAIL_SIZE);

    auto thumbnail_spec = OIIO::ImageSpec{width, height, channels, OIIO::TypeDesc::UINT8};
    OIIO::ImageBuf image_thumbnail(thumbnail_spec);
    image_thumbnail.make_writable();

    bool ok = OIIO::ImageBufAlgo::resize(image_thumbnail, image, "box");
    // TODO: Handle failure of resize

    // .. copy to buffer
    std::vector<uint8_t> buffer;
    OIIO::Filesystem::IOVecOutput out_buffer(buffer);

    auto out = OIIO::ImageOutput::create(THUMBNAIL_NAME, &out_buffer);
    out->open(THUMBNAIL_NAME, thumbnail_spec);
    image_thumbnail.write(out.get());
    out->close();

    // Create Thumbnail
    auto photo_thumbnail = std::make_shared<model::PhotoThumbnail>(width,
                                                                   height, channels,
                                                                   std::move(buffer),
                                                                   photo);
    m_database.persist(photo_thumbnail);

    return photo_thumbnail;
}

} // imgr