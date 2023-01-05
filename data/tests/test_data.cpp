#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>

#include "data/directory_tree.h"
#include "data/photo_store.h"
#include "data/config.h"

#include <test_helper/helper.h>

#include <iostream>
#include <memory>

#include <boost/filesystem.hpp>

#include <OpenImageIO/filesystem.h>

namespace fs = boost::filesystem;

// Used to do tests that write to disk
//#define WRITE_TO_DISK_TESTS

/// Sets up the directory environment for tests
class EnvironmentSetup : public Catch::EventListenerBase {
public:
    explicit EnvironmentSetup(const Catch::IConfig *config) : EventListenerBase(config) {}

    void testRunStarting(const Catch::TestRunInfo &testRunInfo) override {
        // Create temp root directory
        temp_root = fs::temp_directory_path() / imgr::random_string(20);
        fs::create_directories(temp_root);
        fs::current_path(temp_root);

        // Create directory structure
        fs::create_directories("sandbox/1/1");
        fs::create_directories("sandbox/1/2");
        fs::create_directories("sandbox/2/1");
        fs::create_directories("sandbox/2/2");

        // Create yaml file for testing
        std::ofstream yaml_test("test.yml");
        yaml_test << fmt::format("# Test files\nsearch_directories:\n - {}\n - {}\n",
                                 fs::current_path().string(),
                                 (fs::current_path() / "sandbox").string())
                  << fmt::format("database:\n host: localhost\n db: database\n port: 1234\n")
                  << std::endl;

        // Create images
        fs::path sandbox = temp_root / "sandbox";
        imgr::create_test_image(sandbox / "1.jpg", 512, 512);
        imgr::create_test_image(sandbox / "2.png", 256, 512);
        imgr::create_test_image(sandbox / "3.bmp", 512, 256);

        // Invalid image that should not be loaded
        std::ofstream not_an_image((sandbox / "not_image.jpg").string());
        not_an_image << "This is not an image\n";
    }

    void testRunEnded(const Catch::TestRunStats &testRunStats) override {
        fs::current_path(fs::temp_directory_path());
        fs::remove_all(temp_root);
    }

private:
    fs::path temp_root;
};

CATCH_REGISTER_LISTENER(EnvironmentSetup)


TEST_CASE("File tree", "[DirectoryTree]") {
    using namespace Catch::Matchers;
    using imgr::DirectoryTree;

    // Initial tree
    fs::path root_directory = fs::current_path() / "sandbox";
    std::cout << "Using directory: " << root_directory;
    DirectoryTree tree(root_directory);

    REQUIRE(tree.get_path() == root_directory);

    // Check that we have the expected subdirectories
    std::vector<DirectoryTree> subdirs{
        DirectoryTree(root_directory / "1"),
        DirectoryTree(root_directory / "2")
    };
    REQUIRE_THAT(tree.get_subdirectories(), UnorderedEquals(subdirs));

    // Get files
    auto files = tree.get_files();
    REQUIRE_THAT(files, Contains(root_directory / "not_image.jpg"));
}

TEST_CASE("Config file read", "[Config]") {
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

        REQUIRE_THAT(expected_paths, UnorderedEquals(paths));
    }

    SECTION("Connection parameters") {
        std::map<std::string, std::string> expected_params{
                {"host", "localhost"},
                {"db",   "database"},
                {"port", "1234"}
        };

        REQUIRE(expected_params == config.get_connection_parameters());
    }
}

TEST_CASE("Check photo store calculations", "[PhotoStore]") {
    SECTION("Square image") {
        int width = 1024, height = 1024;
        std::tie(width, height) = imgr::PhotoStore::calculate_dimensions(width, height, 128);

        REQUIRE(width == 128);
        REQUIRE(height == 128);
    }

    SECTION("Vertical image") {
        int width = 512, height = 1024;
        std::tie(width, height) = imgr::PhotoStore::calculate_dimensions(width, height, 128);
        REQUIRE(width == 64);
        REQUIRE(height == 128);
    }

    SECTION("Horizontal image") {
        int width = 1024, height = 256;
        std::tie(width, height) = imgr::PhotoStore::calculate_dimensions(width, height, 128);
        REQUIRE(width == 128);
        REQUIRE(height == 32);
    }
}

TEST_CASE("Check database connection", "[PhotoStore]") {
    imgr::PhotoStore store(fs::current_path() / "test.db");

    fs::path album_path = fs::current_path() / "sandbox";
    SECTION("Creates the album") {
        // Album shouldn't exist in the database
        auto album = store.get_album(album_path);
        REQUIRE_FALSE(album);

        // Create the new album
        album = store.create_album(album_path);
        REQUIRE(album);
    }

    SECTION("Retrieve existing album") {
        auto album = store.get_album(album_path);
        REQUIRE(album);

        // Three photos should be created on startup
        auto photos = store.get_album_photos(album->get_id());
        REQUIRE(photos.size() == 3);

        // Every photo should have a thumbnail
        for (auto &p: photos) {
            auto thumbnail = store.get_photo_thumbnail(p->get_id());

            REQUIRE(thumbnail);

#ifdef WRITE_TO_DISK_TESTS
            // Try to write the thumbnail to disk
            fs::path filename(p->get_filename());
            fs::path dest =
                    fs::current_path() / "sandbox" / fmt::format(".thumbnail.{}.jpg", filename.stem().string());

            // Read the image
            auto thumbnail_data = OIIO::Filesystem::IOMemReader(thumbnail->get_data());
            auto reader = OIIO::ImageInput::open(dest.filename().string(), nullptr, &thumbnail_data);

            size_t size = thumbnail->get_width() * thumbnail->get_height() * thumbnail->get_channels();
            std::vector<uint8_t> pixels(size);
            reader->read_image(OIIO::TypeDesc::UINT8, pixels.data());
            reader->close();

            // Write the image
            auto out = OIIO::ImageOutput::create(dest.string());
            out->open(dest.string(),
                      OIIO::ImageSpec{thumbnail->get_width(), thumbnail->get_height(), thumbnail->get_channels()});
            out->write_image(OIIO::TypeDesc::UINT8, pixels.data());
            out->close();
#endif
        }
    }
}