#pragma once
#include <string>
#include <vector>

namespace advanced_gl {
    class gl_object;
}

namespace model_viewer
{
    class viewport;
    class obj_reader;

    using namespace advanced_gl;
    using namespace std;

    class console;

    class obj_viewer
    {
    public:
        viewport* view;
        obj_reader* read_object;
        console* consoleIO;
        void load(string filename);
        void clear() const;
        void log(string data,float time=-1);
        void try_load_tex(string cs);
        obj_viewer(int,char**);
    };
}
