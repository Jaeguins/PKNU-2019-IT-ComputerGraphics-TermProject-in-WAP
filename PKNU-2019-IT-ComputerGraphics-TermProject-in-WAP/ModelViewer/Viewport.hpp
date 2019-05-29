#pragma once
#include <vector>
#include "GlObject.hpp"
namespace viewport {
    using namespace GlVector;
    using namespace std;
    class Viewport {
    public:

        GlCamera* Camera;
        vector<GlObject*> components;
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

        static Viewport* GetInstance(int, char**);
        static Viewport* instance;
    private:
        Viewport(int argc, char **argv);
    };

}