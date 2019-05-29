#include <stdio.h>
#include <GL/glut.h>
#include "GlObject.hpp"
#include "Viewport.hpp"
#include <vector>
#include <functional>

extern "C"
using namespace std;
using namespace viewport;

void timerCallback(int prior)
{
    Viewport::instance->baseTimerFunc(prior);
}
void renderCallback()
{
    Viewport::instance->render();
}
void mousePosCallback(int x,int y)
{
    Viewport::instance->baseMousePosFunc(x,y);
}
void keyCallback(unsigned char key,int x,int y)
{
    Viewport::instance->baseKeyFunc(key, x, y);
}
void mouseButtonCallback(int button, int state, int x, int y)
{
    Viewport::instance->baseMouseButtonFunc(button, state, x, y);
}

Viewport* Viewport::instance=nullptr;

void Viewport::baseMousePosFunc(int x, int y) {
    {
        Camera->xAngle += ((x - postX)) / (resolutionX / 2.0) * 90;
        Camera->yAngle += ((postY - y)) / (resolutionY / 2.0) * 90;
        postX = x;
        postY = y;
    }
    mousePosFunc(x,y);
}

void Viewport::baseKeyFunc(unsigned char key, int x, int y) {
    switch (key) {
    case 'a':
        Camera->Position.x -= .01f;
        break;
    case 'd':
        Camera->Position.x += .01f;
        break;
    case 'q':
        Camera->Position.y -= .01f;
        break;
    case 'e':
        Camera->Position.y += .01f;
        break;
    case 'w':
        Camera->Position.z -= .01f;
        break;
    case 's':
        Camera->Position.z += .01f;
        break;
    }
    keyFunc(key,x,y);
}

void Viewport::baseMouseButtonFunc(int button, int state, int x, int y) {
    mouseButtonFunc(button,state,x,y);
}

void Viewport::baseTimerFunc(int prior) {


    timerFunc(prior);


    glutTimerFunc(30,
        timerCallback,
        1);
}


void Viewport::render() {
    glLoadIdentity();
    Camera->cameraMove();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_LINES);
    glLineWidth(.3);
    glColor3f(1, 0, 0);
    glVertex3f(-10, 0, 0);
    glVertex3f(10, 0, 0);
    glColor3f(0, 10, 0);
    glVertex3f(0, -10, 0);
    glVertex3f(0, 10, 0);
    glColor3f(0, 0, 10);
    glVertex3f(0, 0, -10);
    glVertex3f(0, 0, 10);
    glEnd();

    for(GlObject* t :components)
    {
        t->render();
    }

    glutSwapBuffers();
    glutPostRedisplay();
}

void Viewport::start() {
    components.reserve(100);
    Camera = new GlCamera();
}

Viewport* Viewport::GetInstance(int argc, char **argv)
{
    if (instance == NULL)
    {
        instance = new Viewport(argc, argv);
    }
    return instance;
}

Viewport::Viewport(int argc, char **argv)
{
    start();
    this->Camera=new GlCamera();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(resolutionX, resolutionY);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("example");
    glutKeyboardFunc(keyCallback);
    glutMotionFunc(mousePosCallback);
    glutMouseFunc(mouseButtonCallback);
    glutTimerFunc(30, timerCallback, 1);
    glutDisplayFunc(renderCallback);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -10.0, 10.0);
    glutMainLoop();
}