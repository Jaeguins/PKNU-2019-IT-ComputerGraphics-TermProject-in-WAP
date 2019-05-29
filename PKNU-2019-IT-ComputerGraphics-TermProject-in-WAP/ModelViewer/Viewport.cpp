#include <GL/glut.h>
#include "gl_object.hpp"
#include "viewport.hpp"
#include <vector>
#include <functional>
#include "gl_camera.hpp"
#include "console.hpp"
#include "obj_viewer.hpp"


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
        if(mousePosFunc!=nullptr)
        mousePosFunc(x, y);
    }

    void viewport::baseKeyFunc(unsigned char key, int x, int y) {
        parent->consoleIO->input(key);
        if(keyFunc!=nullptr)
        keyFunc(key, x, y);
    }

    void viewport::baseMouseButtonFunc(int button, int state, int x, int y) {
        if(mouseButtonFunc!=nullptr)
        mouseButtonFunc(button, state, x, y);
    }

    void viewport::baseTimerFunc(int prior) {

        parent->consoleIO->refresh();

        if(timerFunc!=nullptr)
        timerFunc(prior);


        glutTimerFunc(millis,
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

        parent->consoleIO->render();

        glutSwapBuffers();
        glutPostRedisplay();
    }

    void viewport::start() {
        components.reserve(100);
        Camera = new gl_camera();
    }

    viewport* viewport::GetInstance(obj_viewer* parent,int argc, char **argv)
    {
        if (instance == NULL)
        {
            instance = new viewport(parent,argc, argv);
        }
        return instance;
    }

    void viewport::drawText(float WinPosX, float WinPosY, const char* strMsg, gl_vec_3f color, void* font)
    {
        double FontWidth = 0.02;
        glColor3f(color.x,color.y,color.z);

        int len = (int)strlen(strMsg);
        glRasterPos2f(WinPosX,WinPosY);
        for (int i = 0; i < len; ++i)
        {
            glutBitmapCharacter(font, strMsg[i]);
        }
    }


    viewport::viewport(obj_viewer* parent,int argc, char **argv)
    {
        this->parent=parent;
        millis=30;
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
    }
}