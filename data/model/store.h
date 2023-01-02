#ifndef IMAGE_MANAGER_STORE_H
#define IMAGE_MANAGER_STORE_H

#include <memory>
#include <string>
#include <vector>

#include <odb/core.hxx>

namespace imgr {
namespace model {

/// ID type to use for all items
using ID_TYPE = uint64_t;

class Photo;

/// Represents an album object, modeled as a folder in the filesystem
#pragma db object pointer(std::shared_ptr)

class Album {
public:
    using id_type = ID_TYPE;

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

#pragma db unique
    std::string m_absolute_path;
};

/// Represents a single photo object that is part of an album. Captures the relative
/// filename within the album and the thumbnail.
#pragma db object pointer(std::shared_ptr)

class Photo {
public:
    using id_type = ID_TYPE;

    Photo(const std::string &filename, uint16_t width, uint16_t height, const std::shared_ptr<Album> &album)
            : m_filename(filename), m_width(width), m_height(height), m_album(album) {
    }

    /// Getter for filename
    const std::string &get_filename() const {
        return m_filename;
    }

    /// Returns width of the image
    /// \return
    uint16_t get_width() const {
        return m_width;
    }

    /// Returns height of the image
    /// \return
    uint16_t get_height() const {
        return m_height;
    }

    /// Returns the Album to which this photo belongs
    /// \return
    const std::shared_ptr<Album> &get_album() const {
        return m_album;
    }

    /// Returns the ID of the photo
    /// \return
    id_type get_id() const {
        return m_id;
    }

private:
    /// Private default constructor
    Photo() {}

    friend class odb::access;

#pragma db id auto
    id_type m_id;

    std::string m_filename;

    uint16_t m_width, m_height;

#pragma db not_null
    std::shared_ptr<Album> m_album;
};

#pragma db object pointer(std::shared_ptr)

/// Contains the thumbnail for a photo
class PhotoThumbnail {
public:
    using id_type = ID_TYPE;

    /// Constructor that copies the buffer
    /// \param width
    /// \param height
    /// \param thumbnail
    /// \param photo
    PhotoThumbnail(uint16_t width, uint16_t height, uint8_t channels, const std::vector<uint8_t> &thumbnail,
                   const std::shared_ptr<Photo> &photo) : m_width(width), m_height(height), m_channels(channels),
                                                          m_thumbnail(thumbnail),
                                                          m_photo(photo) {

    }

    /// Constructor that allows moving the buffer
    /// \param width
    /// \param height
    /// \param thumbnail
    /// \param photo
    PhotoThumbnail(uint16_t width, uint16_t height, uint8_t channels, std::vector<uint8_t> &&thumbnail,
                   const std::shared_ptr<Photo> &photo) : m_width(width), m_height(height), m_channels(channels),
                                                          m_thumbnail(thumbnail),
                                                          m_photo(photo) {

    }

    /// Returns the ID of the thumbnail
    /// \return
    id_type get_id() const {
        return m_id;
    }

    /// Returns the thumbnail vector
    /// \return
    const std::vector<uint8_t> &get_data() const {
        return m_thumbnail;
    }

    /// Returns the width of the thumbnail
    /// \return
    uint16_t get_width() const {
        return m_width;
    }

    /// Returns the height of the thumbnail
    /// \return
    uint16_t get_height() const {
        return m_height;
    }

    /// Returns the number of channels of the thumbnail
    /// \return
    uint8_t get_channels() const {
        return m_channels;
    }

    /// Returns the photo associated to the thumbnail
    /// \return
    const std::shared_ptr<Photo> &get_photo() const {
        return m_photo;
    }

private:
    /// Private default constructor
    PhotoThumbnail() {};

    friend class odb::access;

#pragma db id auto
    /// ID
    id_type m_id;

    uint16_t m_width, m_height;
    uint8_t m_channels;

#pragma db type("BYTEA")
    std::vector<uint8_t> m_thumbnail;

#pragma db not_null unique
    std::shared_ptr<Photo> m_photo;
};

}
}

#endif //IMAGE_MANAGER_STORE_H
