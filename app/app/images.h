#ifndef IMAGE_MANAGER_IMAGES_H
#define IMAGE_MANAGER_IMAGES_H

#include <wx/image.h>
#include <data/photo_store.h>

namespace imgr {

class Image{
public:
    /// Creates the image from a thumbnail
    /// \param thumbnail
    /// \return
    static std::unique_ptr<wxImage> create_image(const PhotoStore::ThumbnailCPtr& thumbnail);
};

} // imgr

#endif //IMAGE_MANAGER_IMAGES_H
