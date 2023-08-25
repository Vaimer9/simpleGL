#include <texture.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <logger.hpp>

namespace sgl {

Image::Image(std::string path):
    path_(path)
{
    this->load(path_);
}

Image::~Image()
{
    stbi_image_free(this->data);
}

void Image::load(std::string path)
{
    this->data = stbi_load(path.data(), &width_, &height_, &channels_, 0);
    
    if (!data)
    {
        log_error("Could not load image `" + path + "` properly");
    }
}

int Image::width()
{
    return width_;
}

int Image::height()
{
    return height_;
}

Texture::Texture(Image* image):
    image_(image)
{
    glGenTextures(1, &handle_);
    this->load_image();
}

void Texture::load_image()
{
    this->bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0 ,GL_RGB, image_->width(), image_->height(), 0, GL_BGR, GL_UNSIGNED_BYTE, image_->data);
    this->unbind();
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, handle_);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

std::vector<float> Texture::vertices()
{
    return vertices_;
}

void Texture::set_vertices(std::vector<float> vertices)
{
    vertices_ = vertices;
}

} // namespace sgl
