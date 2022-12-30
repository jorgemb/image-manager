//
// Created by jorge on 29/12/2022.
//

#include <data/photo_store.h>

#include <model/store-odb.hxx>
#include <odb/query.hxx>

using AlbumQuery = odb::query<imgr::model::Album>;
using AlbumResult = odb::result<imgr::model::Album>;
using PhotoQuery = odb::query<imgr::model::Photo>;
using PhotoResult = odb::result<imgr::model::Photo>;

namespace imgr {
PhotoStore::PhotoStore(const std::string &user, const std::string &password, const std::string &db,
                       const std::string &host, uint16_t port) {
    m_database = std::make_unique<database>(user, password, db, host, port);
    m_session = std::make_unique<odb::session>();
}

PhotoStore::AlbumPtr PhotoStore::get_or_create_album(const filesystem::path &album_path) {
    // Search for the album in the database
    odb::transaction t(m_database->begin());
    trace_on_debug(t);

    AlbumPtr album(m_database->query_one<model::Album>(AlbumQuery::absolute_path == album_path.string()));
    if(!album){
        // Create the new album
        album = std::make_shared<model::Album>(album_path.string());
        m_database->persist(album);

        // TODO: Populate album with photos
    }

    t.commit();

    return album;
}
} // imgr