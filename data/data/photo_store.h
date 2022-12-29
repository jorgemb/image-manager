#ifndef IMAGE_MANAGER_PHOTO_STORE_H
#define IMAGE_MANAGER_PHOTO_STORE_H

#include <odb/database.hxx>
#include <odb/pgsql/database.hxx>

#include <memory>
#include <string>

namespace imgr {
using database = odb::pgsql::database;

/// Class for managing access to photos
class PhotoStore {
public:
    PhotoStore(const std::string &user, const std::string &password, const std::string &db,
               const std::string &host, uint16_t port);

private:
    std::unique_ptr<database> m_database;
};

} // imgr

#endif //IMAGE_MANAGER_PHOTO_STORE_H
