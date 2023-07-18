#include <logger.hpp>
#include "vbo.hpp"
#include <texture.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace sgl {

Image::Image(std::string path)
{
    data_ = stbi_load(path.data(), &width_, &height_, &channels_, 0);
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

TextureBuffer::TextureBuffer()
{
    glGenTextures(1, &handle_);
}

TextureBuffer::TextureBuffer(Image image)
{
    glGenTextures(1, &handle_); 
    this->load_image(image);
}

void Texture::set_vertices(std::vector<float> vertices = {})
{
    vertices_ = vertices;
}

void TextureBuffer::load_image(Image image)
{
    image_ = image;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_.width(), image_.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.data());
    glGenerateMipmap(GL_TEXTURE_2D);
}

void TextureBuffer::bind()
{
    glBindTexture(GL_TEXTURE_2D, handle_);
}

void TextureBuffer::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

}
