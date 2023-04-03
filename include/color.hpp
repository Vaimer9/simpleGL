#pragma once
#include <tuple>
#include <span>

namespace sgl {

class Tint
{
    float r_, g_, b_; // Can't make public so stupid values can't be set

public:
    Tint(float r, float g, float b);
    Tint();

    static const Tint red() { return Tint(255, 0, 0); }
    static const Tint green() { return Tint(0, 255, 0); }
    static const Tint blue() { return Tint(0, 0, 255); }
    static const Tint black() { return Tint(0, 0, 0); }
    static const Tint white() { return Tint(255, 255, 255); }
    static const Tint gray() { return Tint(128, 128, 128); }
    static const Tint orange() { return Tint(255, 128, 0); }
    static const Tint pink() { return Tint(255, 0, 255); }
    static const Tint yellow() { return Tint(255, 255, 0); }
    static const Tint cyan() { return Tint(0, 255, 255); }

    void set_r(float val);
    void set_g(float val);
    void set_b(float val);

    float get_r();
    float get_g();
    float get_b();

    std::tuple<float, float, float> values();
};

} // namespace sgl
