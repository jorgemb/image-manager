//
// Created by jorge on 27/12/2022.
//

#ifndef IMAGE_MANAGER_EXCEPTIONS_H
#define IMAGE_MANAGER_EXCEPTIONS_H

#include <stdexcept>

namespace imgr {

    /// Exception thrown when trying to load an invalid image
    class InvalidImageException: public std::invalid_argument{
    public:
        explicit InvalidImageException(const std::string &message) : invalid_argument(message) {}
    };

} // imgr

#endif //IMAGE_MANAGER_EXCEPTIONS_H
