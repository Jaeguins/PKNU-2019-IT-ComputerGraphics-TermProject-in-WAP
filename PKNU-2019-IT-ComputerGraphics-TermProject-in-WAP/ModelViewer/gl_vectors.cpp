#include <cmath>
#include "gl_Vectors.hpp"

namespace advanced_gl {
    gl_vec_3f::gl_vec_3f()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    gl_vec_3f::gl_vec_3f(GLfloat x, GLfloat y, GLfloat z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    gl_vec_3f gl_vec_3f::operator+(gl_vec_3f t) const
    {
        return gl_vec_3f(x + t.x, y + t.y, z + t.z);
    }

    gl_vec_3f gl_vec_3f::operator*(GLfloat t) const
    {
        return gl_vec_3f(x*t, y*t, z*t);
    }

    gl_vec_3f gl_vec_3f::operator/(GLfloat t) const
    {
        return gl_vec_3f(x, y, z)*(1 / t);
    }

    gl_vec_3f gl_vec_3f::operator-() const
    {
        return gl_vec_3f(x, y, z)*-1;
    }

    gl_vec_3f gl_vec_3f::operator-(gl_vec_3f a) const
    {
        return gl_vec_3f(x, y, z) + (a*-1);
    }

    gl_vec_3f gl_vec_3f::normalize() const
    {
        GLfloat t = sqrt(x * x + y * y + z * z);
        return gl_vec_3f(x, y, z) / t;
    }

    gl_vec_3f gl_vec_3f::zero = gl_vec_3f(0, 0, 0);

    gl_vec_2f::gl_vec_2f()
    {
        x = 0;
        y = 0;
    }

    gl_vec_2f::gl_vec_2f(GLfloat x, GLfloat y) {
        this->x = x;
        this->y = y;
    }

    gl_vec_2f gl_vec_2f::operator+(gl_vec_2f t) const
    {
        return gl_vec_2f(x + t.x, y + t.y);
    }

    gl_vec_2f gl_vec_2f::operator*(GLfloat t) const
    {
        return gl_vec_2f(x*t, y*t);
    }

    gl_vec_2f gl_vec_2f::operator/(GLfloat t) const
    {
        return gl_vec_2f(x, y)*(1 / t);
    }

    gl_vec_2f gl_vec_2f::operator-() const
    {
        return gl_vec_2f(x, y)*-1;
    }

    gl_vec_2f gl_vec_2f::operator-(gl_vec_2f a) const
    {
        return gl_vec_2f(x, y) + -a;
    }

    gl_vec_2f gl_vec_2f::normalize() const
    {
        GLfloat t = sqrt(x * x + y * y);
        return gl_vec_2f(x, y) / t;
    }

    gl_vec_2f gl_vec_2f::zero = gl_vec_2f(0, 0);

    void glVertexVector(gl_vec_3f vec){
        glVertex3f(vec.x,vec.y,vec.z);
    }

    void glVertexVector(gl_vec_2f vec){
        glVertex2f(vec.x,vec.y);
    }

    void glFace(gl_face face){
        for(int i=0;i<3;i++)
            glVertexVector(face.vertices[i]);
    }
}