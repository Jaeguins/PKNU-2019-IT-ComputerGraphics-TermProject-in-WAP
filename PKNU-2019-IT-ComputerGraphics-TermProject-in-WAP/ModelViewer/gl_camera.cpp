#include "gl_Camera.hpp"
#include <GL/glut.h>
namespace advanced_gl {
    void gl_camera::cameraMove() const
    {
        glRotatef(yAngle, 1, 0, 0);
        glRotatef(xAngle, 0, -1, 0);
        glScalef(magnify,magnify,magnify);
        glTranslatef(Position.x, Position.y, Position.z);
    }
}