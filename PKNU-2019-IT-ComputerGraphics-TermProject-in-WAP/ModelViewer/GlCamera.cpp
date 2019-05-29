#include "GlObject.hpp"
#include <GL/glut.h>
using namespace GlVector;
void GlCamera::cameraMove() const
{
    glRotatef(yAngle, 1, 0, 0);
    glRotatef(xAngle, 0, -1, 0);
    glTranslatef(Position.x, Position.y, Position.z);
}
