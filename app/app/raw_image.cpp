//
// Created by jorge on 09/01/2023.
//

#include "raw_image.h"

namespace imgr {

RawImage_Thumbnail::RawImage_Thumbnail(RawImage_Thumbnail::ThumbnailPtr thumbnail) : m_thumbnail(thumbnail) {}

unsigned int RawImage_Thumbnail::get_width() const {
    return m_thumbnail->get_width();
}

unsigned int RawImage_Thumbnail::get_height() const {
    return m_thumbnail->get_height();
}

const uint8_t *RawImage_Thumbnail::get_data() const {
    return m_thumbnail->get_data().data();
}
} // imgr