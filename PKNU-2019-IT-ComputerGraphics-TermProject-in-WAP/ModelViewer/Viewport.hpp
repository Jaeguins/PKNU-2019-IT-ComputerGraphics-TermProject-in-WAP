#pragma once
#include <vector>
#include "gl_object.hpp"
#include "gl_Camera.hpp"

namespace model_viewer {
    using namespace advanced_gl;
    using namespace std;
    class viewport {
    public:

        gl_camera* Camera;
        vector<gl_object*> components;
        int resolutionX = 500, resolutionY = 500;
        int postX = resolutionX / 2, postY = resolutionX / 2;

        void baseKeyFunc(unsigned char key, int x, int y);
        void baseMousePosFunc(int x, int y);
        void baseMouseButtonFunc(int button, int state, int x, int y);
        void baseTimerFunc(int prior);

        void(*mousePosFunc)(int x, int y);
        void(*mouseButtonFunc)(int button, int state, int x, int y);
        void(*keyFunc)(unsigned char key, int x, int y);
        void(*timerFunc)(int prior);

        void render();
        void start();

        static viewport* GetInstance(int, char**);
        static viewport* instance;
    private:
        viewport(int argc, char **argv);
    };

}
