//
// Created by jorge on 17/12/2022.
//

#ifndef IMAGE_MANAGER_CONFIG_H
#define IMAGE_MANAGER_CONFIG_H

#include <filesystem>
#include <string_view>
#include <optional>
#include <vector>
#include <ranges>

#include <yaml-cpp/yaml.h>

namespace imgr {

    class Config {
    public:
        /// Constructs a Config object using the specified configuration file
        /// \param config_file
        explicit Config(const std::filesystem::path &config_file);

        /// Returns a view of the search directories
        /// \return Read only view of the search directories
        auto get_search_directories() const{
            return m_search_directories | std::views::all;
        }

    private:
        // Path to the config file
        const std::filesystem::path m_config_file;

        // YAML Node
        YAML::Node m_data_tree;

        // Internal data
        std::vector<std::filesystem::path> m_search_directories;
    };
}


#endif //IMAGE_MANAGER_CONFIG_H
