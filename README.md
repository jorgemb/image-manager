# Image Manager

## Linux dependencies
```
bison
libgtk-3-dev
libgstreamer-plugins-base1.0-dev
```

## ToDo list
* ~~Update album tree management in the GUI~~
* ~~Implement get_thumbnail workflow~~
  * ~~Show thumbnails in the GUI~~
* Implement get_full_image workflow
* Do lazy evaluation for loading images from albums
  * Load metadata of images first
  * Create thumbnails until album is read
  * Add root only reads the album tree. Update photos 
loads the thumbnails.
* Add update_album to re-read the album tree
  * Add metadata to support this in the model
  * Photo (DateCreated, Status[Created, Loaded, Deleted])
  * Album (DateCreated, LastUpdate)
  * PhotoThumbnail (DateCreated)

## Errors
* When an album is selected with many images, some empty size remains at the end of the Gallery