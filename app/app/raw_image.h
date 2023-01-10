#ifndef IMAGE_MANAGER_RAW_IMAGE_H
#define IMAGE_MANAGER_RAW_IMAGE_H

#include <model/store.h>

#include <odb/traits.hxx>

#include <vector>

namespace imgr {

/// Represent an image raw information to be used for the GUI
class RawImage {
public:
    /// Get width
    /// \return
    virtual unsigned int get_width() const = 0;

    /// Get height
    /// \return
    virtual unsigned int get_height() const = 0;

    /// Get internal bit information
    /// \return
    virtual const uint8_t *get_data() const = 0;
};

class RawImage_Thumbnail : public RawImage {
public:
    using ThumbnailPtr = odb::object_traits<model::PhotoThumbnail>::const_pointer_type;

    /// Gets a reference to the thumbnail
    /// \param thumbnail
    explicit RawImage_Thumbnail(ThumbnailPtr thumbnail);

    unsigned int get_width() const override;

    unsigned int get_height() const override;

    const uint8_t *get_data() const override;

private:
    ThumbnailPtr m_thumbnail;
};

} // imgr

#endif //IMAGE_MANAGER_RAW_IMAGE_H
