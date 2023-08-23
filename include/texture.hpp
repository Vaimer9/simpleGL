#pragma once

#include "vbo.hpp"
#include <string>
#include <GL/glew.h>
#include <vector>
#include <iostream>

namespace sgl {

/// This class has nothing to do with openGL or graphics, it only handles loading images
class Image
{
    std::string path_;
    int width_, height_, channels_;
    unsigned char* data_ = nullptr;

public:
    Image() {};
    Image(std::string path);
    ~Image();
    unsigned char* data();
    int width();
    int height();
    void load();
};


/// Class for handling Texture Coordinates and TexCoord vertex attribute upload
class TextureBuffer
{
    Image* image_;
    std::vector<float> vertices_;
    unsigned int texture_handle_;

public:
    TextureBuffer();
    ~TextureBuffer() {};
    TextureBuffer(Image* image);
    void load_image(Image* image);
    void bind();
    void unbind();

    // Dumb util functions
    std::vector<float> vertices();
    void set_vertices(std::vector<float> = {});
};

} // namespace sgl
