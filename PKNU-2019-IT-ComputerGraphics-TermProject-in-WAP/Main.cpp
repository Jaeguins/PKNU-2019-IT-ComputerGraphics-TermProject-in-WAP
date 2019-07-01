
#include"ModelViewer/GL/glut.h"
#include "ModelViewer/obj_viewer.hpp"


int main(int argc,char* argv[])
{
    model_viewer::obj_viewer viewer(argc,argv);
    glutMainLoop();
    system("pause");
}