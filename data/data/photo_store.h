#ifndef IMAGE_MANAGER_PHOTO_STORE_H
#define IMAGE_MANAGER_PHOTO_STORE_H

#include <odb/database.hxx>
#include <odb/session.hxx>
#include <odb/pgsql/database.hxx>

#include <model/store.h>

#include <memory>
#include <string>

#include <boost/filesystem.hpp>

namespace imgr {
namespace filesystem = boost::filesystem;
using database = odb::pgsql::database;

/// Class for managing access to photos
class PhotoStore {
public:
    using AlbumPtr = std::shared_ptr<model::Album>;
    using PhotoPtr = std::shared_ptr<model::Photo>;

    /// Creates a new PhotoStore and connects to DB
    /// \param user
    /// \param password
    /// \param db
    /// \param host
    /// \param port
    PhotoStore(const std::string &user, const std::string &password, const std::string &db,
               const std::string &host, uint16_t port);

    /// Retrieves an album or creates a new one
    /// \param album_path
    /// \return
    AlbumPtr get_or_create_album(const filesystem::path &album_path);


private:
    inline void trace_on_debug(odb::transaction& t){
#ifdef _DEBUG
        t.tracer(odb::stderr_tracer);
#endif
    }

    std::unique_ptr<database> m_database;
    std::unique_ptr<odb::session> m_session;
};

} // imgr

#endif //IMAGE_MANAGER_PHOTO_STORE_H
