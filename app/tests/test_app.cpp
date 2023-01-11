#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>

#include <app/album_manager.h>
#include <data/config.h>
#include <test_helper/helper.h>

#include <iostream>
#include <memory>
#include <set>

#include <boost/filesystem.hpp>

#include <OpenImageIO/filesystem.h>

namespace fs = boost::filesystem;

// Parameters
constexpr int TOTAL_ALBUMS = 5;
constexpr int PHOTOS_PER_ALBUM = 3;

/// Sets up the directory environment for tests
class EnvironmentSetup : public Catch::EventListenerBase {
public:
    explicit EnvironmentSetup(const Catch::IConfig *config) : EventListenerBase(config) {}

    void testRunStarting(const Catch::TestRunInfo &testRunInfo) override {
        std::default_random_engine generator(std::random_device{}());
        std::vector<std::string> image_types{".jpg", ".png", ".bmp"};
        std::vector<int> sizes{64, 128, 256, 512};

        // Create temp root directory
        temp_root = fs::temp_directory_path() / imgr::random_string(20);
        fs::create_directories(temp_root);
        fs::current_path(temp_root);

        // Create album structure
        std::array<std::string, TOTAL_ALBUMS> directories;
        std::for_each(directories.begin(), directories.end(), [](auto &dir) { dir = imgr::random_string(10); });

        // Create photos in each directory
        for (const auto &dir: directories) {
            // Create directory
            fs::path current_album = temp_root / dir;
            fs::create_directory(current_album);

            // Create files
            for (int i = 0; i < PHOTOS_PER_ALBUM; ++i) {
                auto &extension = imgr::random_uniform_choice(image_types);
                fs::path photo_path = current_album / (imgr::random_string(10) + extension);
                imgr::create_test_image(photo_path,
                                        imgr::random_uniform_choice(sizes),
                                        imgr::random_uniform_choice(sizes));
            }
        }

        // Create yaml file for testing
        std::ofstream yaml_test("test.yml");
        yaml_test << fmt::format("# Test files\nsearch_directories:\n - {}\n",
                                 fs::current_path().string())
                  << fmt::format("database:\n file: test.db\n")
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

TEST_CASE("AlbumManager tests", "[AlbumManager]") {

    imgr::Config config("test.yml");
    imgr::AlbumManager manager(config);

    // Add the album root
    auto current_path = fs::current_path();
//    auto root_album = manager.add_root_album(current_path);
//    REQUIRE(root_album);
//    REQUIRE(!root_album->get_parent_album());

    // Check that we are getting the root albums
    auto roots = manager.get_root_albums();
    REQUIRE(roots.size() == 1);

    auto root_album = roots.front();
    REQUIRE(root_album);
    REQUIRE(!root_album->get_parent_album());

    auto root_album_copy = roots.front();
    REQUIRE(root_album->get_id() == root_album_copy->get_id());

    auto root_photos = manager.get_album_photos(root_album->get_id());
    REQUIRE(root_photos.empty());

    // Check that each sub album has only the required amount of photos
    auto root_sub_albums = manager.get_sub_albums(root_album->get_id());
    REQUIRE(root_sub_albums.size() == TOTAL_ALBUMS);

    for (auto sub_album: root_sub_albums) {
        auto photos = manager.get_album_photos(sub_album->get_id());
        REQUIRE(photos.size() == PHOTOS_PER_ALBUM);
    }

    // Check iteration
    std::set<fs::path> expected_iteration{ current_path };
    std::copy_if(fs::recursive_directory_iterator(current_path), fs::recursive_directory_iterator(),
                 std::inserter(expected_iteration, expected_iteration.begin()),
                 [](auto &val) { return fs::is_directory(val); });

    std::set<fs::path> album_iteration;
    std::transform(manager.begin(), manager.end(),
                   std::inserter(album_iteration, album_iteration.begin()),
                   [](auto &val) { return fs::path(val->get_absolute_path()); });
    REQUIRE(expected_iteration == album_iteration);
}