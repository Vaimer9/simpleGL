#pragma once

#include "vbo.hpp"
#include <string>
#include <GL/glew.h>
#include <vector>
#include <iostream>

namespace sgl {

class Image
{
    std::string path;
    int width_, height_, channels_;
    unsigned char* data_ = nullptr;

public:
    Image();
    Image(std::string path);
    ~Image();
    unsigned char* data();
    int width();
    int height();
    void load();
};

class Texture {
    Image image_;
    unsigned int handle_;
    std::vector<float> vertices_;

public:
    Texture();
    Texture(Image image);
    void load(std::string path);
    void free_data();
    void set_vertices(std::vector<float> vertices);
    void bind();
    void unbind();
};

class TextureBuffer : public ArrayBuffer
{
    Image image_;

public:
    TextureBuffer();
    TextureBuffer(Image image);
    void gen_buffers() override;
    void bind() override;
    void unbind() override;
    void load_image(Image image);
};

} // namespace sgl
