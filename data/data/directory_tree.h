//
// Created by jorge on 15/12/2022.
//

#ifndef IMAGE_MANAGER_FILE_TREE_H
#define IMAGE_MANAGER_FILE_TREE_H

#include <string>
#include <map>
#include <sstream>
#include <vector>

#include <boost/filesystem.hpp>
#include <ostream>

namespace imgr {
namespace filesystem = boost::filesystem;

/// Represents a directory tree in the filesystem
class DirectoryTree{
public:
    /// Creates a new directory tree
    /// \param path
    explicit DirectoryTree(filesystem::path path);

    /// Returns the path of the tree
    /// \return
    const filesystem::path &get_path() const;

    /// Returns the name of the directory
    /// \return
    std::string get_name() const;

    /// Returns a list of sub-directories
    /// \return
    std::vector<DirectoryTree> get_subdirectories() const;

    /// Returns a list of files
    /// \return
    std::vector<filesystem::path> get_files() const;

    bool operator==(const DirectoryTree &rhs) const {
        return m_path == rhs.m_path;
    }

    bool operator!=(const DirectoryTree &rhs) const {
        return !(rhs == *this);
    }

    friend std::ostream &operator<<(std::ostream &os, const DirectoryTree &tree);

private:
    /// Root path of this directory tree
    const filesystem::path m_path;
};

} // imgr

#endif //IMAGE_MANAGER_FILE_TREE_H
