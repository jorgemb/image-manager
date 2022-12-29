//
// Created by jorge on 29/12/2022.
//

#include "photo_store.h"

namespace imgr {
PhotoStore::PhotoStore(const std::string &user, const std::string &password, const std::string &db,
                       const std::string &host, uint16_t port) {
    m_database = std::make_unique<database>(user, password, db, host, port);
}
} // imgr