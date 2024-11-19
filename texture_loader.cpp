#include <iostream>
#include <stb_image.h>
#include "texture_loader.hpp"
#include <spdlog/spdlog.h>

#include "sbpt_generated_includes.hpp"

void default_texture_callback(int width, int height, int num_components, char *data) {};

// Function to load texture from file and return TextureData
TextureData load_texture_from_file(const std::string &filepath, bool gamma) {
    int width, height, num_components;
    unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &num_components, 0);

    /*if (!data) {*/
    /*    spdlog::get(Systems::asset_loading)*/
    /*        ->error("Unable to load image: {} with error: {}", filepath, stbi_failure_reason());*/
    /*    throw std::runtime_error("Failed to load image data");*/
    /*}*/
    /**/
    /*spdlog::get(Systems::asset_loading)*/
    /*    ->info("Loaded file: {} with width: {}, height: {}, and {} components", filepath, width, height,*/
    /*           num_components);*/

    // Copy the image data into a std::vector
    std::vector<unsigned char> image_data(data, data + (width * height * num_components));

    // Free the dynamically allocated image data
    stbi_image_free(data);

    // Return the texture data encapsulated in a struct
    return {width, height, num_components, std::move(image_data)};
}

void load_texture_from_file_with_callback(const std::string &filepath, bool gamma, TextureCallback texture_callback) {

    int width, height, num_components;
    unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &num_components, 0);

    if (!data) {
        /*spdlog::get(Systems::asset_loading)*/
        /*    ->error("unable to load image: {} with error: {}", filepath, stbi_failure_reason());*/
        /*// throw;*/
    } else {
        /*spdlog::get(Systems::asset_loading)*/
        /*    ->info("loading file: {} with width: {}, height: {}, and has {} components", filepath, width, height,*/
        /*           num_components);*/

        texture_callback(width, height, num_components, data);
    }

    stbi_image_free(data);
}
