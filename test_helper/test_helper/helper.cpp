//
// Created by jorge on 05/01/2023.
//

#include "helper.h"

namespace imgr {
std::string random_string(std::size_t size) {
    const std::string characters("abcdefghijklmnopqrstuvwxyz0123456789_");

    // Random parameters
    std::random_device device;
    std::default_random_engine generator(device());
    std::uniform_int_distribution<std::size_t> distribution(0, characters.size() - 1);

    // Return string
    std::string ret(size, '-');
    std::transform(ret.begin(), ret.end(), ret.begin(), [&](auto &val) {
        return characters[distribution(generator)];
    });

    return ret;
}

bool create_test_image(const fs::path &path, uint32_t width, uint32_t height) {
    // Fill buffer with data
    OIIO::ImageSpec spec(width, height, 3, OIIO::TypeDesc::FLOAT);
    OIIO::ImageBuf buffer(spec);
    float dark[3] = {0.1, 0.1, 0.1};
    float light[3] = {0.8, 0.8, 0.8};
    OIIO::ImageBufAlgo::checker(buffer, 64, 64, 1, dark, light);

    return buffer.write(path.string());
}
} // imgr