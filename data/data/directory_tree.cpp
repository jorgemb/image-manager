//
// Created by jorge on 15/12/2022.
//

#include "directory_tree.h"
#include <utility>
#include <sstream>
#include <algorithm>

namespace imgr {
namespace fs = boost::filesystem;

DirectoryTree::DirectoryTree(filesystem::path path) : m_path(std::move(path)) {}

std::vector<DirectoryTree> DirectoryTree::get_subdirectories() const {
    std::vector<DirectoryTree> directories;
    for(auto dir = filesystem::directory_iterator(m_path); dir != filesystem::directory_iterator(); ++dir){
        if(filesystem::is_directory(*dir)){
            directories.emplace_back(dir->path());
        }
    }

    return directories;
}

std::vector<filesystem::path> DirectoryTree::get_files() const {
    std::vector<filesystem::path> files;
    for(auto dir = filesystem::directory_iterator(m_path); dir != filesystem::directory_iterator(); ++dir){
        if(filesystem::is_regular_file(*dir)){
            files.emplace_back(dir->path());
        }
    }

    return files;
}

const filesystem::path &DirectoryTree::get_path() const {
    return m_path;
}

std::string DirectoryTree::get_name() const {
    return m_path.filename().string();
}

std::ostream &operator<<(std::ostream &os, const DirectoryTree &tree) {
    os << "path: " << tree.m_path;
    return os;
}


} // imgr