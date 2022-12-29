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

namespace imgr {
namespace filesystem = boost::filesystem;

class DirectoryTree {
private:
    // Definitions
    using file_map = std::multimap<filesystem::path, filesystem::path>;
public:
    using const_iterator = file_map::const_iterator;

    /// Creates a new DirectoryTree from the given root path
    /// \param root
    DirectoryTree(filesystem::path root);

        /// Returns a string representation of the tree
        /// \return
        std::string str() const;

        /// Refreshes the internal representation of the tree
        void refresh();

    /// Returns the absolute path
    filesystem::path get_root() const { return m_root; }

    // Returns the children of a given path
    std::vector<filesystem::path> children_of(const filesystem::path &path) const;

    private:
    // Path to the root of the tree
    const filesystem::path m_root;

        // List of files in the directory in the form [parent] -> [directory]
        file_map m_files;

        // Separator for sub directories
        const char m_separator = '-';

    /// Helper function to recurse through the tree
    /// \param ss
    /// \param current_path
    /// \param level
    void recursive_str(std::stringstream &ss, const filesystem::path &current_path, int level) const;
    };

} // imgr

#endif //IMAGE_MANAGER_FILE_TREE_H
