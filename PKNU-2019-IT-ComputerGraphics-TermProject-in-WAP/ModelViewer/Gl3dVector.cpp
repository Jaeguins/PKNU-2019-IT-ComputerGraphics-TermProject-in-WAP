#include <GL/glut.h>
#include <math.h>
#include "GlObject.hpp"


Gl3dVector::Gl3dVector(GLfloat x, GLfloat y, GLfloat z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Gl3dVector Gl3dVector::operator+(Gl3dVector t) {
    return Gl3dVector(x + t.x, y + t.y, z + t.z);
}

Gl3dVector Gl3dVector::operator*(GLfloat t) {
    return Gl3dVector(x*t, y*t, z*t);
}

Gl3dVector Gl3dVector::operator/(GLfloat t) {
    return Gl3dVector(x, y, z)*(1 / t);
}

Gl3dVector Gl3dVector::operator-() {
    return Gl3dVector(x, y, z)*-1;
}

Gl3dVector Gl3dVector::operator-(Gl3dVector a) {
    return Gl3dVector(x,y,z)+(a*-1);
}

Gl3dVector Gl3dVector::normalize() {
    GLfloat t = sqrt(x * x + y * y + z * z);
    return Gl3dVector(x, y, z) / t;
}

