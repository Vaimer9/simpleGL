#include <map>
#include <targets.hpp>

Targets::Targets()
{
    bounded_[GL_ARRAY_BUFFER] = nullptr;
    bounded_[GL_ELEMENT_ARRAY_BUFFER] = nullptr;
    bounded_[GL_ATOMIC_COUNTER_BUFFER] = nullptr;
    bounded_[GL_COPY_READ_BUFFER] = nullptr;
    bounded_[GL_COPY_WRITE_BUFFER] = nullptr;
    bounded_[GL_DISPATCH_INDIRECT_BUFFER] = nullptr;
    bounded_[GL_DRAW_INDIRECT_BUFFER] = nullptr;
    bounded_[GL_ELEMENT_ARRAY_BUFFER] = nullptr;
    bounded_[GL_PIXEL_PACK_BUFFER] = nullptr;
    bounded_[GL_QUERY_BUFFER] = nullptr;
    bounded_[GL_SHADER_STORAGE_BUFFER] = nullptr;
    bounded_[GL_TEXTURE_BUFFER] = nullptr;
    bounded_[GL_TRANSFORM_FEEDBACK_BUFFER] = nullptr;
    bounded_[GL_UNIFORM_BUFFER] = nullptr;
}

Vbo*& Targets::bound(GLenum target)
{
    return bounded_[target];
}

void Targets::bind(GLenum target, Vbo* vbo)
{
    bounded_[target] = vbo;
}
