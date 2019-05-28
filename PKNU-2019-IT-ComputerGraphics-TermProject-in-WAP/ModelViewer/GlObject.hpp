#pragma once
#include<GL/glut.h>
#include<iostream>
#include<vector>

struct Gl3dVector {
    GLfloat x, y, z;
    Gl3dVector(GLfloat x, GLfloat y, GLfloat z);
    Gl3dVector operator+(Gl3dVector t);
    Gl3dVector operator-(Gl3dVector t);
    Gl3dVector normalize();
    Gl3dVector operator-();
    Gl3dVector operator*(GLfloat t);
    Gl3dVector operator/(GLfloat t);
    static Gl3dVector zero;
};

struct Quaternion {
    Gl3dVector vect=Gl3dVector(0,1,0);
    float angle=0.0f;
};
class GlCamera {
public:
    Gl3dVector Position = Gl3dVector(0, 0, 0);
    float xAngle;
    float yAngle;
    void cameraMove();
};
class GlObject {
public:
    Gl3dVector Position= Gl3dVector(0, 0, 0);
    Gl3dVector Scale= Gl3dVector(1, 1, 1);
    Gl3dVector Color = Gl3dVector(1, 1, 1);
    Quaternion Rotation;
    int isText=false;
    GlObject();
    std::vector<GlObject*> subObjects;
    void (*draw)(GlObject* obj);
    void render();
    void (*drawText)(GlObject* obj);
    std::string str;
};