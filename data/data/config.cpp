//
// Created by jorge on 17/12/2022.
//

#include "config.h"



imgr::Config::Config(const filesystem::path &config_file) : m_config_file(config_file) {
    // Try to read configuration file
    m_data_tree = YAML::LoadFile(config_file.string());

    // Read the directory listing
    auto search_directories = m_data_tree["search_directories"];
    for (const auto &dir: search_directories) {
        m_search_directories.emplace_back(dir.as<std::string>());
    }

    // Read connection parameters
    auto connection_parameters = m_data_tree["database"];
    for(const auto &param: connection_parameters){
        m_connection_parameters[param.first.as<std::string>()] = param.second.as<std::string>();
    }
}

const std::vector<imgr::filesystem::path> &imgr::Config::get_search_directories() const {
    return m_search_directories;
}

const std::map<std::string, std::string> &imgr::Config::get_connection_parameters() const {
    return m_connection_parameters;
}

