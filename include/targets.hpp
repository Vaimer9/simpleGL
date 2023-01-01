#include "vbo.hpp"
#include <GL/glew.h>
#include <map>
#include <vector>

class Targets {
private:
    std::map<GLenum, Vbo*> bounded_;
public:
    Targets();

    Vbo*& bound(GLenum target);
    void bind(GLenum target, Vbo* vbo);
};
