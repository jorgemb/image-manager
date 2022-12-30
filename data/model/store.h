#ifndef IMAGE_MANAGER_STORE_H
#define IMAGE_MANAGER_STORE_H

#include <memory>
#include <string>
#include <vector>

#include <odb/core.hxx>

namespace imgr {

// Set std::shared_ptr as default pointer type
#pragma db namespace pointer(std::shared_ptr)
namespace model {

class Photo;

/// Represents an album object, modeled as a folder in the filesystem
#pragma db object

class Album {
public:
    using id_type = uint64_t;

    explicit Album(const std::string &absolute_path) : m_absolute_path(absolute_path) {}

    /// Getter for ID
    /// \return
    id_type get_id() const { return m_id; }

    /// Getter for absolute path
    /// \return
    const std::string &get_absolute_path() const { return m_absolute_path; }

private:
    // Default constructor
    Album() {}

    friend class odb::access;

#pragma db id auto
    id_type m_id;

    std::string m_absolute_path;

//#pragma db value_not_null inverse(m_album)
//    std::vector<std::weak_ptr<Photo>> m_photos;
};

/// Represents a single photo object that is part of an album. Captures the relative
/// filename within the album and the thumbnail.
#pragma db object

class Photo {
public:
    using id_type = uint64_t;

    Photo(const std::string &filename, unsigned int width, unsigned int height,
          const std::vector<unsigned char> &thumbnail, const std::shared_ptr<Album> &album) : m_filename(filename),
                                                                                              m_width(width),
                                                                                              m_height(height),
                                                                                              m_thumbnail(thumbnail),
                                                                                              m_album(album) {}

    /// Getter for filename
    const std::string &get_filename() const {
        return m_filename;
    }

    /// Returns width of the image
    /// \return
    unsigned int get_width() const {
        return m_width;
    }

    /// Returns height of the image
    /// \return
    unsigned int get_height() const {
        return m_height;
    }

    /// Returns thumbnail for the image
    /// \return
    const std::vector<unsigned char> &get_thumbnail() const {
        return m_thumbnail;
    }

    /// Returns the Album to which this photo belongs
    /// \return
    const std::shared_ptr<Album> &get_album() const {
        return m_album;
    }

    /// Returns the ID of the photo
    /// \return
    id_type get_id() const{
        return m_id;
    }

private:
    /// Private default constructor
    Photo() {}

    friend class odb::access;

#pragma db id auto
    id_type m_id;

    std::string m_filename;

    unsigned int m_width, m_height;

#pragma db type("BYTEA")
    std::vector<unsigned char> m_thumbnail;

#pragma db not_null
    std::shared_ptr<Album> m_album;
};

}
}

#endif //IMAGE_MANAGER_STORE_H