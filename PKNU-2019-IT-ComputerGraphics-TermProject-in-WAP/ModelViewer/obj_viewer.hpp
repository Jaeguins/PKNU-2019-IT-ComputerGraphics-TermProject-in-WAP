#pragma once
#include <string>

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
        void log(string);
        obj_viewer(int,char**);
    };
}
