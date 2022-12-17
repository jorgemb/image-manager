//
// Created by jorge on 17/12/2022.
//

#include <data/config.h>



imgr::Config::Config(const std::filesystem::path &config_file) : m_config_file(config_file) {
    // Try to read configuration file
    m_data_tree = YAML::LoadFile(config_file.string());
}

