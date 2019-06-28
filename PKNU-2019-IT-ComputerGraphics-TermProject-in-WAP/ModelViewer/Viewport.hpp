#pragma once
#include<gl/glut.h>
#include"gl_vectors.hpp"

namespace advanced_gl {
    class gl_camera;
    class gl_object;
}

namespace model_viewer {
    class obj_viewer;
    using namespace advanced_gl;
    using namespace std;
    class viewport {
    public:
        int millis;
        obj_viewer* parent;
        gl_camera* camera;
        vector<gl_object*> components;
        int resolutionX = 1280, resolutionY = 720;
        int postX = resolutionX / 2, postY = resolutionX / 2;
        void baseKeyFunc(unsigned char key, int x, int y);
        void baseMousePosFunc(int x, int y);
        void baseMouseButtonFunc(int button, int state, int x, int y);
        void baseTimerFunc(int prior);

        void(*mousePosFunc)(int x, int y);
        void(*mouseButtonFunc)(int button, int state, int x, int y);
        void(*keyFunc)(unsigned char key, int x, int y);
        void(*timerFunc)(int prior);
        void drawText(float WinPosX, float WinPosY, const char* strMsg, gl_vec_3f color = gl_vec_3f(1.0f, 1.0f, 1.0f), void* font =
            GLUT_BITMAP_8_BY_13);

        void log(string data,float time=-1);
        void render();
        void start();

        static viewport* GetInstance(obj_viewer* parent, int, char**);
        static viewport* instance;
    private:
        viewport(obj_viewer* parent, int argc, char **argv);
    };

}
