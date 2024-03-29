#include <cmath>
#include "color.hpp"

namespace sgl {

Tint::Tint(float r, float g, float b)
{
    this->set_r(r);
    this->set_g(g);
    this->set_b(b);
}

// Default Color is white
Tint::Tint() 
{
    this->set_r(255.f);
    this->set_g(255.f);
    this->set_b(255.f);
}

std::tuple<float, float, float> Tint::values()
{
    return {r_, g_, b_};
}

void Tint::set_r(float value)
{
    if (value > 255) value = 255;
    r_ = value;
}

void Tint::set_g(float value)
{
    if (value > 255) value = 255;
    g_ = value;
}

void Tint::set_b(float value)
{
    if (value > 255) value = 255;
    b_ = value;
}

float Tint::get_r()
{
    return r_;
}

float Tint::get_g()
{
    return g_;
}

float Tint::get_b()
{
    return b_;
}

} // namespace sgl
