#include <cmath>
#include "gl_vectors.hpp"
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
        return gl_vec_3f(x * t, y * t, z * t);
    }

    gl_vec_3f gl_vec_3f::operator/(GLfloat t) const
    {
        return gl_vec_3f(x, y, z) * (1 / t);
    }

    gl_vec_3f gl_vec_3f::operator%(gl_vec_3f rhs)
    {
        return gl_vec_3f(y * rhs.z - z * rhs.y,
            z * rhs.x - x * rhs.z,
            x * rhs.y - y * rhs.x);
    }

    gl_vec_3f gl_vec_3f::operator-() const
    {
        return gl_vec_3f(x, y, z) * -1;
    }

    gl_vec_3f gl_vec_3f::operator-(gl_vec_3f a) const
    {
        return gl_vec_3f(x, y, z) + (a * -1);
    }

    gl_vec_3f gl_vec_3f::normalize() const
    {
        GLfloat t = sqrt(x * x + y * y + z * z);
        return gl_vec_3f(x, y, z) / t;
    }

    float gl_vec_3f::magnitude() const
    {
        return sqrt(x * x + y * y + z * z);
    }


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
        return gl_vec_2f(x * t, y * t);
    }

    gl_vec_2f gl_vec_2f::operator/(GLfloat t) const
    {
        return gl_vec_2f(x, y) * (1 / t);
    }



    gl_vec_2f gl_vec_2f::operator-() const
    {
        return gl_vec_2f(x, y) * -1;
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

    void glVertexVector(gl_vec_3f vec) {
        glVertex3f(vec.x, vec.y, vec.z);
    }

    void glVertexVector(gl_vec_2f vec) {
        glVertex2f(vec.x, vec.y);
    }
    void glNormalVector(gl_vec_3f vec) {
        glNormal3f(vec.x, vec.y, vec.z);
    }

    gl_vec_3f computePlane(gl_vec_3f A, gl_vec_3f B, gl_vec_3f C)
    {
        return ((A - B) % (B - C)).normalize(); //perform cross product of two lines on plane
    }


    void glFace(gl_face face, GLuint tex_index) {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
        glColor3f(1, 1, 1);
        if (tex_index != 0xffffffff)
            glBindTexture(GL_TEXTURE_2D, tex_index);
        glBegin(face.amount == 3 ? GL_TRIANGLES : GL_QUADS);
        for (int i = 0; i < face.amount; i++) {
            if (face.normals[i].magnitude() == 0)
                glNormalVector(computePlane(face.vertices[0], face.vertices[1], face.vertices[2]));
            else
                glNormalVector(face.normals[i]);
            glTexCoord2f(face.uvs[i].x, 1 - face.uvs[i].y);
            glVertexVector(face.vertices[i]);
        }
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING);
    }

    gl_vec_2f zero2f = gl_vec_2f(0, 0);
    gl_vec_3f zero3f = gl_vec_3f(0, 0, 0);

}