//
// Created by jorge on 09/01/2023.
//

#include "raw_image.h"

namespace imgr {
RawImage::RawImage(unsigned int width, unsigned int height, const std::vector<uint8_t> &data) : m_width(width),
                                                                                                m_height(height),
                                                                                                m_data(data) {}

RawImage::RawImage(unsigned int width, unsigned int height, std::vector<uint8_t> &&data) : m_width(width),
                                                                                           m_height(height),
                                                                                           m_data(std::move(data)) {}
} // imgr