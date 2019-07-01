#include "gl/glut.h"
#include "gl_object.hpp"
namespace advanced_gl {
    void gl_object::render() {
        glPushMatrix();
        glTranslatef(Position.x, Position.y, Position.z);
        glRotatef(Rotation.angle, Rotation.vect.x, Rotation.vect.y, Rotation.vect.z);
        glScalef(Scale.x, Scale.y, Scale.z);
        glColor3f(Color.x, Color.y, Color.z);
        if (draw != nullptr)
            this->draw(this);
        for (std::vector<gl_object*>::size_type i = 0; i < subObjects.size(); i++) {
            subObjects[i]->render();
        }
        if (isText)this->drawText(this);
        glPopMatrix();
    }
    gl_object::gl_object() {
        subObjects = std::vector<gl_object*>();
        subObjects.reserve(10);
        drawText = [](gl_object* obj)->void {
            int i = 0;
            glPushMatrix();
            glRasterPos3f(obj->Position.x, obj->Position.y, obj->Position.z);
            while (obj->str[i] != '\0' && i < 100)
            {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, obj->str[i++]);
            }
            glPopMatrix();
        };
        draw = [](gl_object* obj)->void {};
    }
}

