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
        read_object = new obj_reader(view,filename.c_str());
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
    void obj_viewer::log(string data,float time)
    {
        consoleIO->log(data,time);
    }

    void obj_viewer::try_load_tex(string path) {
        if (read_object != nullptr)
            read_object->load_main_tex(path);
        else
            log("Model not found, this command is only work when you load model first.");
    }

    obj_viewer::obj_viewer(int argc, char** argv)
    {
        view = viewport::GetInstance(this,argc, argv);
        consoleIO = new console(this);

    }


}
