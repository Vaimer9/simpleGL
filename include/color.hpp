#pragma once
#include <tuple>
#include <span>

namespace sgl {

class Tint
{
    float r_, g_, b_;

public:
    Tint(float r, float g, float b);
    Tint();

    void set_r(float val);
    void set_g(float val);
    void set_b(float val);

    float get_r();
    float get_g();
    float get_b();

    std::tuple<float, float, float> values();
};

} // namespace sgl
