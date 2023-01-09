#ifndef IMAGE_MANAGER_RAW_IMAGE_H
#define IMAGE_MANAGER_RAW_IMAGE_H

#include <vector>

namespace imgr {

/// Represent an image raw information to be used for the GUI
class RawImage {
public:
    /// Constructor where data is being copied
    /// \param width
    /// \param height
    /// \param data
    RawImage(unsigned int width, unsigned int height, const std::vector<uint8_t> &data);

    /// Constructor where data is being moved
    /// \param width
    /// \param height
    /// \param data
    RawImage(unsigned int width, unsigned int height, std::vector<uint8_t> &&data);
private:
    unsigned int m_width, m_height;
    std::vector<uint8_t> m_data;
};

} // imgr

#endif //IMAGE_MANAGER_RAW_IMAGE_H
