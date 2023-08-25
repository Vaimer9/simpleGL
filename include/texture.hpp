#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>

namespace sgl {

// TODO: Remove all the separate load() methods and multiple constructors!

class Image {
    std::string path_;
    int height_, width_, channels_;
public:
    unsigned char* data = nullptr;
    Image() {};
    Image(std::string path);
    ~Image();
    void load(std::string path);
    int height();
    int width();
};

class Texture {
    Image* image_;
    std::vector<float> vertices_;
    unsigned int handle_;
    void gen_handle();

public:
    Texture(Image* image);
    void load_image();
    void bind();
    void unbind();

    std::vector<float> vertices();
    void set_vertices(std::vector<float> = {});
};

} // namespace sgl

