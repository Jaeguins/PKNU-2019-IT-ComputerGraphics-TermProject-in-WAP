#include "GlObject.hpp"
#include <GL/glut.h>

void GlCamera::cameraMove() {
    glRotatef(yAngle, 1, 0, 0);
    glRotatef(xAngle, 0, -1, 0);
    glTranslatef(Position.x, Position.y, Position.z);
}