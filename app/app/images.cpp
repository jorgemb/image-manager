//
// Created by jorge on 11/01/2023.
//

#include "images.h"
#include <wx/mstream.h>

#include <utility>

namespace imgr {

std::unique_ptr<wxImage> Image::create_image(const PhotoStore::ThumbnailCPtr &thumbnail) {
    // Create stream from thumbnail data
    auto &data = thumbnail->get_data();
    auto stream = wxMemoryInputStream{data.data(), data.size()};

    // Create new image
    auto image = std::make_unique<wxImage>(stream);
    return image;
}
} // imgr