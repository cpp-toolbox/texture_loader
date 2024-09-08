#ifndef TEXTURE_LOADER_HPP
#define TEXTURE_LOADER_HPP

#include <string>
#include <functional>
#include <vector>

using TextureCallback = std::function<void(int, int, int, unsigned char *)>;

struct TextureData {
    int width;
    int height;
    int num_components;
    std::vector<unsigned char> image_data;
};

void default_texture_callback(int width, int height, int num_components, unsigned char *data);

TextureData load_texture_from_file(const std::string &filepath, bool gamma = false);

void load_texture_from_file_with_callback(const std::string &filepath, bool gamma = false,
                                          TextureCallback texture_callback = default_texture_callback);

#endif // TEXTURE_LOADER_HPP
