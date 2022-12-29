//
// Created by jorge on 15/12/2022.
//

#include "directory_tree.h"
#include <utility>
#include <sstream>
#include <algorithm>

namespace imgr {
namespace fs = boost::filesystem;

DirectoryTree::DirectoryTree(filesystem::path root) : m_root(root) {
    refresh();
}

std::string DirectoryTree::str() const {
    std::stringstream ss;
    recursive_str(ss, m_root, 0);

    return ss.str();
}

void DirectoryTree::refresh() {
    for (const auto &dir_entry: fs::recursive_directory_iterator(m_root)) {
        // Ignore root entry and files
        if (dir_entry == m_root || !fs::is_directory(dir_entry)) continue;

        auto path = dir_entry.path();
        auto parent = path.parent_path();

        m_files.insert(std::make_pair(parent, path));
    }
}

void DirectoryTree::recursive_str(std::stringstream &ss, const filesystem::path &current_path, int level) const {
    // Add newline only if we are not in the root
    if (level != 0) ss << '\n';

    // Write current directory
    ss << std::string(level, m_separator) << current_path.filename().string();

    // Follow with each subdirectory

    auto iter_range = m_files.equal_range(current_path);
    for (auto iter = iter_range.first; iter != iter_range.second; ++iter) {
        recursive_str(ss, iter->second, level + 1);
    }
}

std::vector<filesystem::path> DirectoryTree::children_of(const filesystem::path &path) const {
    std::vector<filesystem::path> ret;

    auto iter_range = m_files.equal_range(path);
    std::transform(iter_range.first, iter_range.second, std::back_inserter(ret),
                   [](const auto &iter) { return iter.second; });

    return ret;
}

} // imgr