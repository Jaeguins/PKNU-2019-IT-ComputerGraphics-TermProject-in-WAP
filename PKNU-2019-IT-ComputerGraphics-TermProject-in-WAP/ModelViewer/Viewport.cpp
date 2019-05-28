#include <stdio.h>
#include <GL/glut.h>
#include "GlObject.hpp"
#include <vector>
using namespace std;
int resolutionX = 500, resolutionY = 500;
int postX = resolutionX / 2, postY = resolutionX / 2;
int t = 0;

float r = 1, g = 0, b = 0;
int flag = 0;

GlObject *triangle, *square, *sphere;
GlCamera* Camera;
vector<GlObject*> components;
void keyFunc(unsigned char key, int x, int y) {
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
}
void mousePosFunc(int x, int y) {
    Camera->xAngle += ((x - postX)) / (resolutionX / 2.0) * 90;
    Camera->yAngle += ((postY - y)) / (resolutionY / 2.0) * 90;
    postX = x;
    postY = y;
}
void mouseButtonFunc(int button, int state, int x, int y) {
}
void timerFunc(int prior) {
    t = t >= 360 ? 0 : t += 5;
    triangle->Scale = Gl3dVector(1, 1, 1)*(-abs(t-180) / 180.0);
    square->Rotation.angle = t;
    switch (flag) {
    case 0:
        r -= .001;
        g += .001;
        if (r < 0) {
            r = 0;
            g = 1;
            flag = flag + 1 % 3;
        }
        break;
    case 1:
        g -= .001;
        b += .001;
        if (g < 0) {
            g = 0;
            b = 1;
            flag = flag + 1 % 3;
        }
        break;
    case 2:
        b -= .001;
        r += .001;
        if (b < 0) {
            b = 0;
            r = 1;
            flag = flag + 1 % 3;
        }
        break;
    }

    
    glutTimerFunc(30, timerFunc, 1);
}

void render() {
    glLoadIdentity();
    Camera->cameraMove();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (vector<GlObject>::size_type i = 0; i < components.size(); i++) {
        components[i]->render();
    }
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

    glutSwapBuffers();
    glutPostRedisplay();
}

void TriangleDraw(GlObject* obj) {

    glBegin(GL_TRIANGLE_STRIP);
    
    glColor3f(r,g,b);
    glLineWidth(1);

    glVertex3f(0, .3, 0);
    glVertex3f(-.2, 0, -.2);
    glVertex3f(0, .3, 0);

    glVertex3f(.2, 0, -.2);
    glVertex3f(0, .3, 0);
    glVertex3f(0, 0, .2);

    glVertex3f(-.2, 0, -.2);
    glVertex3f(.2, 0, -.2);
    glVertex3f(.2, 0, -.2);

    glVertex3f(0, 0, .2);
    glVertex3f(0, 0, .2);
    glVertex3f(-.2, 0, -.2);

    glEnd();
}

void CubeDraw(GlObject* obj) {
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1, 0, 0);
    glVertex3f(-.1f, -.1f, -.1f);
    glVertex3f(-.1f, .1f, -.1f);
    glVertex3f(-.1f, -.1f, .1f);
    glVertex3f(-.1f, .1f, .1f);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0, 1, 0);
    glVertex3f(-.1f, .1f, -.1f);
    glVertex3f(-.1f, .1f, .1f);
    glVertex3f(.1f, .1f, -.1f);
    glVertex3f(.1f, .1f, .1f);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0, 0, 1);
    glVertex3f(.1f, -.1f, -.1f);
    glVertex3f(.1f, .1f, -.1f);
    glVertex3f(-.1f, -.1f, -.1f);
    glVertex3f(-.1f, .1f, -.1f);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0, 1, 1);
    glVertex3f(.1f, -.1f, .1f);
    glVertex3f(.1f, .1f, .1f);
    glVertex3f(-.1f, -.1f, .1f);
    glVertex3f(-.1f, .1f, .1f);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1, 0, 1);
    glVertex3f(.1f, -.1f, -.1f);
    glVertex3f(.1f, -.1f, .1f);
    glVertex3f(-.1f, -.1f, -.1f);
    glVertex3f(-.1f, -.1f, .1f);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1, 1, 0);
    glVertex3f(.1f, .1f, -.1f);
    glVertex3f(.1f, .1f, .1f);
    glVertex3f(.1f, -.1f, -.1f);
    glVertex3f(.1f, -.1f, .1f);
    glEnd();

}

void start() {
    triangle = new GlObject();
    triangle->Position = Gl3dVector(.1, .1, .1);
    triangle->Rotation.vect = Gl3dVector(1, 0.0, 0.0);
    triangle->Rotation.angle = 45;
    triangle->draw = TriangleDraw;

    square = new GlObject();
    square->Position = Gl3dVector(-.1, -.1, -.1);
    square->Rotation.vect = Gl3dVector(-1, 1, 1);
    square->draw = CubeDraw;




    components.reserve(100);
    components.push_back(triangle);
    components.push_back(square);
    Camera = new GlCamera();

}

int mainView(int argc, char **argv)
{

    start();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(resolutionX, resolutionY);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("example");
    glutKeyboardFunc(keyFunc);
    glutMotionFunc(mousePosFunc);
    glutMouseFunc(mouseButtonFunc);
    glutTimerFunc(30, timerFunc, 1);
    glutDisplayFunc(render);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glutMainLoop();
    return 1;
}