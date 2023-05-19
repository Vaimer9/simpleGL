#pragma once

#include "mesh.hpp"
#include <glm/vec2.hpp>
#include <glm/fwd.hpp>

namespace sgl {

class Rectangle : public Mesh
{
public:
    Rectangle(glm::vec2 center, float width, float height, Tint tint = Tint());
};

class Triangle : public Mesh
{
public:
    Triangle(glm::vec2 first, glm::vec2 second, glm::vec2 third, Tint tint = Tint());
};

class Circle : public Mesh
{
public:
    Circle(glm::vec2 center, float radius, int precision = 160, Tint tint = Tint());
};

class Line : public Mesh
{
public:
    Line(glm::vec2 start, glm::vec2 end, Tint tint = Tint());
};

}
