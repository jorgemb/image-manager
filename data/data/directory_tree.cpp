//
// Created by jorge on 15/12/2022.
//

#include "directory_tree.h"
#include <utility>
#include <sstream>

namespace imgr {
    namespace fs = std::filesystem;

    DirectoryTree::DirectoryTree(std::filesystem::path root): m_root(root) {
        refresh();
    }

    std::string DirectoryTree::str() const {
        std::stringstream ss;
        recursive_str(ss, m_root, 0);

        return ss.str();
    }

    void DirectoryTree::refresh() {
        for(const auto& dir_entry: fs::recursive_directory_iterator(m_root)){
            // Ignore root entry and files
            if(dir_entry == m_root || !dir_entry.is_directory()) continue;

            auto path = dir_entry.path();
            auto parent = path.parent_path();

            m_files.insert(std::make_pair(parent, path));
        }
    }

    void DirectoryTree::recursive_str(std::stringstream &ss, const std::filesystem::path &current_path, int level) const{
        // Add newline only if we are not in the root
        if(level != 0) ss << '\n';

        // Write current directory
        ss << std::string(level, m_separator) << current_path.filename().string();

        // Follow with each subdirectory
        auto [start, end] = m_files.equal_range(current_path);
        for(auto iter=start; iter != end; ++iter){
            recursive_str(ss, iter->second, level+1);
        }
    }

    std::vector<std::filesystem::path> DirectoryTree::children_of(const std::filesystem::path &path) const {
        std::vector<std::filesystem::path> ret;

        auto [start, end] = m_files.equal_range(path);
        std::transform(start, end, std::back_inserter(ret),
                       [](const auto& iter){ return iter.second; });

        return ret;
    }

} // imgr