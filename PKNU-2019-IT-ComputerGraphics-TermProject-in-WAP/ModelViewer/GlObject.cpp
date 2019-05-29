#include <GL/glut.h>
#include "GlObject.hpp"
namespace GlVector {
    void GlObject::render() {
        glPushMatrix();
        glTranslatef(Position.x, Position.y, Position.z);
        glRotatef(Rotation.angle, Rotation.vect.x, Rotation.vect.y, Rotation.vect.z);
        glScalef(Scale.x, Scale.y, Scale.z);
        glColor3f(Color.x, Color.y, Color.z);
        this->draw(this);
        for (std::vector<GlObject*>::size_type i = 0; i < subObjects.size(); i++) {
            subObjects[i]->render();
        }
        if (isText)this->drawText(this);
        glPopMatrix();
    }
    GlObject::GlObject() {
        subObjects = std::vector<GlObject*>();
        subObjects.reserve(10);
        drawText = [](GlObject* obj)->void {
            int i = 0;
            glPushMatrix();
            glRasterPos3f(obj->Position.x, obj->Position.y, obj->Position.z);
            while (obj->str[i] != '\0' && i < 100)
            {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, obj->str[i++]);
            }
            glPopMatrix();
        };
        draw = [](GlObject* obj)->void {};
    }
}

