#ifndef IMAGE_MANAGER_HELPER_H
#define IMAGE_MANAGER_HELPER_H

#include <string>
#include <random>
#include <forward_list>

#include <boost/filesystem.hpp>

#include <OpenImageIO/imageio.h>
#include <OpenImageIO/imagebuf.h>
#include <OpenImageIO/imagebufalgo.h>

namespace imgr {

namespace fs = boost::filesystem;

/// Creates a random string for the root file
/// \param size
/// \return
std::string random_string(std::size_t size);

/// Creates a random image and saves it to the specified
/// \param path
/// \param width
/// \param height
/// \param channels
/// \return
bool create_test_image(const fs::path &path, uint32_t width, uint32_t height);

/// Returns a random element from the vector
/// \tparam T
/// \param options
/// \return
template<class T>
T& random_uniform_choice(std::vector<T>& options){
    // Create distribution
    std::default_random_engine generator(std::random_device{}());
    std::vector<double> weights(options.size(), 1.0);
    std::discrete_distribution<size_t> distribution(weights.begin(), weights.end());

    // Get index and return
    auto index = distribution(generator);
    return options.at(index);
}

} // imgr

#endif //IMAGE_MANAGER_HELPER_H
