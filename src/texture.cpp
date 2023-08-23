#include <logger.hpp>
#include "vbo.hpp"
#include <texture.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace sgl {

Image::Image(std::string path)
{
    path_ = path;
    this->load();
}

Image::~Image()
{
    stbi_image_free(data_);
}

unsigned char* Image::data()
{
    return data_;
}

int Image::width()
{
    return width_;
}

int Image::height()
{
    return height_;
}

void Image::load()
{
    data_ = stbi_load(path_.data(), &width_, &height_, &channels_, 0);

    if (!data_)
    {
        log_error("Could not load texture file `" + path_ + "`.");
    }
}

TextureBuffer::TextureBuffer()
{
    glGenTextures(1, &texture_handle_);
}

TextureBuffer::TextureBuffer(Image* image)
{
    this->load_image(image);
}

void TextureBuffer::load_image(Image* image)
{
    image_ = image;

    this->bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image_->width(), image_->height(), 0, GL_RGB8, GL_UNSIGNED_BYTE, image_->data());
    this->unbind();
}

void TextureBuffer::bind()
{
    glBindTexture(GL_TEXTURE_2D, texture_handle_);
}

void TextureBuffer::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureBuffer::set_vertices(std::vector<float> vertices)
{
    vertices_ = vertices;
}

std::vector<float> TextureBuffer::vertices()
{
    return this->vertices_;
}

}
