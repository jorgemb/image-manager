//
// Created by jorge on 15/12/2022.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>

#include <filesystem>
#include <iostream>
#include <random>
#include <fstream>
#include <format>
#include <ranges>

#include "../data/directory_tree.h"
#include "../data/config.h"

namespace fs = std::filesystem;

/// Creates a random string for the root file
/// \param size
/// \return
std::string random_string(std::size_t size){
    const std::string characters("abcdefghijklmnopqrstuvwxyz0123456789_");

    // Random parameters
    std::random_device device;
    std::default_random_engine generator(device());
    std::uniform_int_distribution<std::size_t> distribution(0, characters.size()-1);

    // Return string
    std::string ret(size, '-');
    std::transform(ret.begin(), ret.end(), ret.begin(), [&](auto& val){
        return characters[distribution(generator)];
    });

    return ret;
}

/// Sets up the directory environment for tests
class EnvironmentSetup: public Catch::EventListenerBase{
public:
    explicit EnvironmentSetup(const Catch::IConfig *config) : EventListenerBase(config) {}

    void testRunStarting(const Catch::TestRunInfo &testRunInfo) override {
        // Create temp root directory
        temp_root = fs::temp_directory_path() / random_string(20);
        fs::create_directories(temp_root);
        fs::current_path(temp_root);

        // Create directory structure
        fs::create_directories("sandbox/1/1");
        fs::create_directories("sandbox/1/2");
        fs::create_directories("sandbox/2/1");
        fs::create_directories("sandbox/2/2");

        // Create yaml file for testing
        std::ofstream yaml_test("test.yml");
        yaml_test << std::format("# Test files\nsearch_directories:\n - {}\n - {}",
                                 fs::current_path().string(),
                                 (fs::current_path()/"sandbox").string())
                                 << std::endl;

    }

    void testRunEnded(const Catch::TestRunStats &testRunStats) override {
        fs::current_path(fs::temp_directory_path());
        fs::remove_all(temp_root);
    }

private:
    fs::path temp_root;
};
CATCH_REGISTER_LISTENER(EnvironmentSetup)


TEST_CASE("File tree", "[DirectoryTree]"){
    using namespace Catch::Matchers;

    // Initial tree
    fs::path root_directory = fs::current_path() / "sandbox";
    std::cout << "Using directory: " << root_directory;
    imgr::DirectoryTree tree(root_directory);

    SECTION("Basic tests") {
        REQUIRE(tree.get_root() == root_directory);

        // Compare trees
        std::string expected_tree = "sandbox\n-1\n--1\n--2\n-2\n--1\n--2";
        REQUIRE(tree.str() == expected_tree);

        // Get single children
        std::vector<fs::path> expected_children = {root_directory / "1", root_directory / "2"};
        REQUIRE(tree.children_of(root_directory) == expected_children);
    }
}

TEST_CASE("Config file read", "[Config]"){
    using namespace Catch::Matchers;

    // Load the initial file
    imgr::Config config("test.yml");

    SECTION("Directory list") {
        // Get the directory list
        std::vector<fs::path> expected_paths{
                fs::current_path(),
                fs::current_path() / "sandbox"
        };
        auto paths = config.get_search_directories();

        REQUIRE(std::ranges::mismatch(expected_paths, paths).in1 == std::ranges::end(expected_paths));
    }

}