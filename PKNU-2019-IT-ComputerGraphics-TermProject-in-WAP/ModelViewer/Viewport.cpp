#include <GL/glut.h>
#include "gl_object.hpp"
#include "viewport.hpp"
#include <vector>
#include <functional>
#include "gl_camera.hpp"
#include "console.hpp"
#include "obj_viewer.hpp"


namespace model_viewer {
    using namespace std;
    GLfloat lightPos[] = { 8,8,8,1};
    
    GLfloat diffuse[] = { .8,.8,.8,.8 };
    GLfloat ambient[] = { 1,1,1,.5 };
    GLfloat specular[] = { 1,1,1,.8 };
    GLfloat linear_attenutation = .5f;
    GLfloat quadratic_attenutation = 1.8f;
    int timer = 0;
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
            camera->xAngle += ((postX - x)) / (resolutionX / 2.0) * 90;
            camera->yAngle += ((y - postY)) / (resolutionY / 2.0) * 90;
            postX = x;
            postY = y;
        }
        if (mousePosFunc != nullptr)
            mousePosFunc(x, y);
    }


    void viewport::baseKeyFunc(unsigned char key, int x, int y) {
        switch (key)
        {
        case '=':
            camera->magnify += .05f;
            break;
        case '-':
            camera->magnify -= .05f;
            break;
        case '`':
            parent->consoleIO->input_buffer->append("obj ../teddybear.obj");
            break;
        default:
            parent->consoleIO->input(key);
            break;
        }

        if (keyFunc != nullptr)
            keyFunc(key, x, y);
    }

    void viewport::baseMouseButtonFunc(int button, int state, int x, int y) {
        postX = x;
        postY = y;
        if (mouseButtonFunc != nullptr)
            mouseButtonFunc(button, state, x, y);
    }

    float deg2rad(float deg) {
        return deg / 180 * 3.14159;
    }

    void viewport::baseTimerFunc(int prior) {

        parent->consoleIO->refresh();

        timer = (timer + 1) % 360;

        if (timerFunc != nullptr)
            timerFunc(prior);

        glutTimerFunc(millis,
            timerCallback,
            1);
    }


    void viewport::log(string data, float time)
    {
        parent->log(data, time);
    }

    void viewport::render() {

        glLoadIdentity();
        glOrtho(-resolutionX / 160.f, resolutionX / 160.f, -resolutionY / 160.f, resolutionY / 160.f, -100.0, 100.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        parent->consoleIO->render();

        /*Lights*/

        float attenuLin = linear_attenutation / camera->magnify, attenuQuad = quadratic_attenutation / camera->magnify;
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, attenuLin);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, attenuQuad);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDir);

        //LightSphere
        glPushMatrix();
        glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
        glColor3f(1, 0, 0);
        glutWireSphere(.1, 10, 10);
        glPopMatrix();



        camera->cameraMove();
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


        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        //Material

        GLfloat materialDiffuse[] = { .5,.5,.5 };
        GLfloat materialAmbient[] = { 1,1,1 };
        GLfloat materialSpecular[] = { 1,1,1 };
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);


        //Test
        //glColor3f(.5, .5, .5);
        glPushMatrix();
        glTranslatef(0, -2, 0);
        glutSolidSphere(1, 30, 30);
        glPopMatrix();

        for (gl_object* t : components)
        {
            t->render();
        }
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);






        glutSwapBuffers();
        glutPostRedisplay();
    }

    void viewport::start() {
        components.reserve(100);
        camera = new gl_camera();
    }

    viewport* viewport::GetInstance(obj_viewer* parent, int argc, char** argv)
    {
        if (instance == NULL)
        {
            instance = new viewport(parent, argc, argv);
        }
        return instance;
    }

    void viewport::drawText(float WinPosX, float WinPosY, const char* strMsg, gl_vec_3f color, void* font)
    {
        double FontWidth = 0.02;
        glColor3f(color.x, color.y, color.z);

        int len = (int)strlen(strMsg);
        glRasterPos2f(WinPosX, WinPosY);
        for (int i = 0; i < len; ++i)
        {
            glutBitmapCharacter(font, strMsg[i]);
        }
    }


    viewport::viewport(obj_viewer* parent, int argc, char** argv)
    {
        this->parent = parent;
        millis = 30;
        start();
        glutInit(&argc, argv);

        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
        glutInitWindowSize(resolutionX, resolutionY);
        glutInitWindowPosition(250, 250);
        glutCreateWindow("example");
        glutKeyboardFunc(keyCallback);
        glutMotionFunc(mousePosCallback);
        glutMouseFunc(mouseButtonCallback);
        glutTimerFunc(30, timerCallback, 1);
        glShadeModel(GL_SMOOTH);
        glFrontFace(GL_CCW);



        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        //glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180);
        //glLightf(GL_LIGHT0, GL_SHININESS, 0);

        glutDisplayFunc(renderCallback);
        glDepthFunc(GL_LESS);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
    }
}