//
// Created by jorge on 17/12/2022.
//

#include "config.h"



imgr::Config::Config(const std::filesystem::path &config_file) : m_config_file(config_file) {
    // Try to read configuration file
    m_data_tree = YAML::LoadFile(config_file.string());

    // Read the directory listing
    auto search_directories = m_data_tree["search_directories"];
    for(const auto& dir: search_directories){
        m_search_directories.emplace_back(dir.as<std::string>());
    }
}

