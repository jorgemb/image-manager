//
// Created by jorge on 17/12/2022.
//

#ifndef IMAGE_MANAGER_CONFIG_H
#define IMAGE_MANAGER_CONFIG_H

#include <vector>

#include "yaml-cpp/yaml.h"

#include "boost/filesystem.hpp"

namespace imgr {
namespace filesystem = boost::filesystem;

class Config {
public:
    /// Constructs a Config object using the specified configuration file
    /// \param config_file
    explicit Config(const filesystem::path &config_file);

    /// Returns a view of the search directories
    /// \return Read only view of the search directories
    const std::vector<filesystem::path> &get_search_directories() const;

    /// Returns the connection parameters for the database
    /// \return
    const std::map<std::string, std::string> &get_connection_parameters() const;

private:
    // Path to the config file
    const filesystem::path m_config_file;

    // YAML Node
    YAML::Node m_data_tree;

    // Internal data
    std::vector<filesystem::path> m_search_directories;
    std::map<std::string, std::string> m_connection_parameters;
};
}


#endif //IMAGE_MANAGER_CONFIG_H
