#ifndef IMAGE_MANAGER_STORE_H
#define IMAGE_MANAGER_STORE_H

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <odb/core.hxx>

namespace imgr {
namespace model {

/// ID type to use for all items
using ID_TYPE = uint64_t;

/// Type to be used when storing raw data
using RawData = std::vector<uint8_t>;
PRAGMA_DB(value(RawData) type("BLOB"))

class Photo;

/// Represents an album object, modeled as a folder in the filesystem
PRAGMA_DB(object pointer(std::shared_ptr))

class Album {
public:
    using id_type = ID_TYPE;

    /// Initializer constructor
    /// \param absolute_path
    /// \param name
    /// \param parent_album
    Album(std::string absolute_path, std::string name, std::shared_ptr<const Album> parent_album = nullptr)
            : m_absolute_path(std::move(absolute_path)),
              m_name(std::move(name)),
              m_parent_album(std::move(parent_album)) {}

    /// Getter for ID
    /// \return
    id_type get_id() const { return m_id; }

    /// Getter for absolute path
    /// \return
    const std::string &get_absolute_path() const { return m_absolute_path; }

    /// Getter for album name
    /// \return
    const std::string &get_name() const {
        return m_name;
    }

    /// Getter for album parent
    const std::shared_ptr<const Album> &get_parent_album() const {
        return m_parent_album;
    }

    bool operator==(const Album &rhs) const {
        return m_id == rhs.m_id;
    }

    bool operator!=(const Album &rhs) const {
        return !(rhs == *this);
    }

private:
    /// Allow setting of private members
    friend class odb::access;

    /// Default constructor
    Album() = default;

    /// ID of the album
    PRAGMA_DB(id auto)
    id_type m_id = 0;

    /// Absolute path in the disk
    PRAGMA_DB(unique)
    std::string m_absolute_path;

    /// Name of the album (normally the same as the directory name)
    std::string m_name;

    /// Pointer to parent, if available
    std::shared_ptr<const Album> m_parent_album;
};

/// Represents a single photo object that is part of an album. Captures the relative
/// filename within the album and the thumbnail.
PRAGMA_DB(object pointer(std::shared_ptr))

class Photo {
public:
    using id_type = ID_TYPE;

    /// Initializer constructor
    /// \param filename
    /// \param width
    /// \param height
    /// \param album
    Photo(std::string filename, uint16_t width, uint16_t height, const std::shared_ptr<Album> &album)
            : m_filename(std::move(filename)), m_width(width), m_height(height), m_album(album) {
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
    const std::shared_ptr<const Album> &get_album() const {
        return m_album;
    }

    /// Returns the ID of the photo
    /// \return
    id_type get_id() const {
        return m_id;
    }

    bool operator==(const Photo &rhs) const {
        return m_id == rhs.m_id;
    }

    bool operator!=(const Photo &rhs) const {
        return !(rhs == *this);
    }

private:
    /// Allow access to private members
    friend class odb::access;

    /// Default constructor
    Photo() = default;

    PRAGMA_DB(id auto)
    id_type m_id = 0;

    std::string m_filename;

    uint16_t m_width{}, m_height{};

    PRAGMA_DB(not_null)
    std::shared_ptr<const Album> m_album;
};

/// Contains the thumbnail for a photo
PRAGMA_DB(object pointer(std::shared_ptr))

class PhotoThumbnail {
public:
    using id_type = ID_TYPE;

    /// Constructor that copies the buffer
    /// \param width
    /// \param height
    /// \param thumbnail
    /// \param photo
    PhotoThumbnail(uint16_t width, uint16_t height, uint8_t channels, RawData thumbnail,
                   const std::shared_ptr<const Photo> &photo) : m_width(width), m_height(height), m_channels(channels),
                                                          m_thumbnail(std::move(thumbnail)),
                                                          m_photo(photo) {

    }

    /// Returns the ID of the thumbnail
    /// \return
    id_type get_id() const {
        return m_id;
    }

    /// Returns the thumbnail vector
    /// \return
    const RawData &get_data() const {
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
    const std::shared_ptr<const Photo> &get_photo() const {
        return m_photo;
    }

    bool operator==(const PhotoThumbnail &rhs) const {
        return m_id == rhs.m_id;
    }

    bool operator!=(const PhotoThumbnail &rhs) const {
        return !(rhs == *this);
    }

private:
    friend class odb::access;

    /// Default constructor
    PhotoThumbnail() = default;

    /// ID
    PRAGMA_DB(id auto)
    id_type m_id = 0;

    uint16_t m_width{}, m_height{};
    uint8_t m_channels{};

    RawData m_thumbnail;

    PRAGMA_DB(not_null unique)
    std::shared_ptr<const Photo> m_photo;
};

}
}

#endif //IMAGE_MANAGER_STORE_H
