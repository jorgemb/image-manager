#include <gui/gui.h>
#include <data/directory_tree.h>

#include <wx/wx.h>
#include <iostream>

class AlbumTreeData: public wxTreeItemData{
public:
    /// Default constructor with path
    explicit AlbumTreeData(const std::filesystem::path &path) : m_path(path) {}

    /// Returns the path associated to the item
    /// \return
    const std::filesystem::path &get_path() const {
        return m_path;
    }
private:
    std::filesystem::path m_path;
};

class ImageManagerWindow: public imgr::ImageManager{
public:
    ImageManagerWindow(wxWindow *parent) : ImageManager(parent), m_directory_tree(".") { new char[100]; }

protected:
    void ImageManagerOnActivate(wxActivateEvent &event) override {
        tree_albums->DeleteAllItems();
        auto root_item = tree_albums->GetRootItem();
        refresh_tree(root_item, m_directory_tree.get_root(), m_directory_tree);

        tree_albums->ExpandAll();
    }

    void TreeAlbums_OnTreeSelChanged(wxTreeEvent &event) override {
        auto selected_item = event.GetItem();
        auto *item_data = dynamic_cast<AlbumTreeData*>(tree_albums->GetItemData(selected_item));

        if(item_data){
            bar_status->SetStatusText(item_data->get_path().string());
        }
    }

private:
    imgr::DirectoryTree m_directory_tree;

    /// Refreshes the directory tree
    void refresh_tree(const wxTreeItemId& parent_item, const std::filesystem::path& current_path, imgr::DirectoryTree& current_tree){
        // Add current
        auto current_item = tree_albums->AppendItem(parent_item, current_path.filename().string(),
                                                    -1, -1, new AlbumTreeData(current_path));
        bool ok = current_item.IsOk();

        // Add children
        for(auto& path: current_tree.children_of(current_path)){
            refresh_tree(current_item, path, current_tree);
        }
    }
};

class ImageManagerApp: public wxApp{
public:
    bool OnInit() override {
        auto* main_window = new ImageManagerWindow(nullptr);
        main_window->Show(true);

        return true;
    }
};


wxIMPLEMENT_APP(ImageManagerApp);