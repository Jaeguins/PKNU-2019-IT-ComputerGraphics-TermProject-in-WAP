#include <GL/glut.h>
#include <math.h>
#include "GlObject.hpp"
namespace GlVector {
    GlVec3f::GlVec3f()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    GlVec3f::GlVec3f(GLfloat x, GLfloat y, GLfloat z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    GlVec3f GlVec3f::operator+(GlVec3f t) const
    {
        return GlVec3f(x + t.x, y + t.y, z + t.z);
    }

    GlVec3f GlVec3f::operator*(GLfloat t) const
    {
        return GlVec3f(x*t, y*t, z*t);
    }

    GlVec3f GlVec3f::operator/(GLfloat t) const
    {
        return GlVec3f(x, y, z)*(1 / t);
    }

    GlVec3f GlVec3f::operator-() const
    {
        return GlVec3f(x, y, z)*-1;
    }

    GlVec3f GlVec3f::operator-(GlVec3f a) const
    {
        return GlVec3f(x, y, z) + (a*-1);
    }

    GlVec3f GlVec3f::normalize() const
    {
        GLfloat t = sqrt(x * x + y * y + z * z);
        return GlVec3f(x, y, z) / t;
    }

    GlVec3f GlVec3f::zero = GlVec3f(0, 0, 0);

    GlVec2f::GlVec2f()
    {
        x = 0;
        y = 0;
    }

    GlVec2f::GlVec2f(GLfloat x, GLfloat y) {
        this->x = x;
        this->y = y;
    }

    GlVec2f GlVec2f::operator+(GlVec2f t) const
    {
        return GlVec2f(x + t.x, y + t.y);
    }

    GlVec2f GlVec2f::operator*(GLfloat t) const
    {
        return GlVec2f(x*t, y*t);
    }

    GlVec2f GlVec2f::operator/(GLfloat t) const
    {
        return GlVec2f(x, y)*(1 / t);
    }

    GlVec2f GlVec2f::operator-() const
    {
        return GlVec2f(x, y)*-1;
    }

    GlVec2f GlVec2f::operator-(GlVec2f a) const
    {
        return GlVec2f(x, y) + -a;
    }

    GlVec2f GlVec2f::normalize() const
    {
        GLfloat t = sqrt(x * x + y * y);
        return GlVec2f(x, y) / t;
    }

    GlVec2f GlVec2f::zero = GlVec2f(0, 0);
}