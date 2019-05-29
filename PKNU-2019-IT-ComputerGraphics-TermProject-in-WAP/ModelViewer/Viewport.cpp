#include <stdio.h>
#include <GL/glut.h>
#include "gl_object.hpp"
#include "viewport.hpp"
#include <vector>
#include <functional>
namespace model_viewer {
    extern "C"
        using namespace std;

    void timerCallback(int prior)
    {
        viewport::instance->baseTimerFunc(prior);
    }
    void renderCallback()
    {
        viewport::instance->render();
    }
    void mousePosCallback(int x, int y)
    {
        viewport::instance->baseMousePosFunc(x, y);
    }
    void keyCallback(unsigned char key, int x, int y)
    {
        viewport::instance->baseKeyFunc(key, x, y);
    }
    void mouseButtonCallback(int button, int state, int x, int y)
    {
        viewport::instance->baseMouseButtonFunc(button, state, x, y);
    }

    viewport* viewport::instance = nullptr;

    void viewport::baseMousePosFunc(int x, int y) {
        {
            Camera->xAngle += ((x - postX)) / (resolutionX / 2.0) * 90;
            Camera->yAngle += ((postY - y)) / (resolutionY / 2.0) * 90;
            postX = x;
            postY = y;
        }
        mousePosFunc(x, y);
    }

    void viewport::baseKeyFunc(unsigned char key, int x, int y) {
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
        keyFunc(key, x, y);
    }

    void viewport::baseMouseButtonFunc(int button, int state, int x, int y) {
        mouseButtonFunc(button, state, x, y);
    }

    void viewport::baseTimerFunc(int prior) {


        timerFunc(prior);


        glutTimerFunc(30,
            timerCallback,
            1);
    }


    void viewport::render() {
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

        for (gl_object* t : components)
        {
            t->render();
        }

        glutSwapBuffers();
        glutPostRedisplay();
    }

    void viewport::start() {
        components.reserve(100);
        Camera = new gl_camera();
    }

    viewport* viewport::GetInstance(int argc, char **argv)
    {
        if (instance == NULL)
        {
            instance = new viewport(argc, argv);
        }
        return instance;
    }

    viewport::viewport(int argc, char **argv)
    {
        start();
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
}