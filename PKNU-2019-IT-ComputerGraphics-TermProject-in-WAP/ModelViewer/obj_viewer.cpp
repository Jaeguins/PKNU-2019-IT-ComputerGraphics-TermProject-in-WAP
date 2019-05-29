#include "obj_viewer.hpp"
#include "obj_reader.hpp"
#include "viewport.hpp"
#include "console.hpp"
#include "gl_object.hpp"

namespace model_viewer
{
    using namespace advanced_gl;
    void obj_viewer::load(string filename)
    {
        clear();
        read_object = new obj_reader(filename.c_str());
        view->components.push_back(static_cast<gl_object*>(read_object));
    }
    void obj_viewer::clear() const
    {
        auto itr = view->components.begin();
        for (int i = 0; i < view->components.size(); i++)
        {
            if (*itr == static_cast<gl_object*>(read_object))itr = view->components.erase(itr);
            else ++itr;
        }
        delete(read_object);
    }
    obj_viewer::obj_viewer(int argc, char** argv)
    {
        view = viewport::GetInstance(this,argc, argv);
        consoleIO = new console(this);

    }


}
