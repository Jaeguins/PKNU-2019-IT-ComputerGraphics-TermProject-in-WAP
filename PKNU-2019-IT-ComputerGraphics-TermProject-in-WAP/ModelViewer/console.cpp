#include "console.hpp"
#include <vector>
#include <string>
#include "viewport.hpp"
#include "obj_viewer.hpp"
#include "string_split.h"
#include "gl_camera.hpp"
#include "obj_reader.hpp"

namespace model_viewer
{
    void console::input(const unsigned char in)
    {
        if (in == 8) { if (input_buffer->size() > 0)input_buffer->pop_back(); }
        else if (in == 13)process();
        else (*input_buffer) += in;
    }
    void console::log(string content, float time) {
        output_buffer->push_back(content);
        removal_buffer->push_back(time == -1 ? removal_time : time);
    }
    void console::process()
    {
        string t = *input_buffer;
        output_buffer->push_back(t);
        removal_buffer->push_back(removal_time);
        vector<string> args = std::split(input_buffer->c_str(), ' ');
        input_buffer->clear();
        //TODO args에 따라 명령 처리
        switch (args.size()) {
        case 1:
            if (!args[0].compare("identify")) {
                gl_camera* cam = parent->view->camera;
                cam->xAngle = 0;
                cam->yAngle = 0;
                log("Rotation set to default.");
            }else if(!args[0].compare("autosize"))
            {
                parent->read_object->auto_magnify();
            }
            else if (!args[0].compare("help")) {
                float helpShowTime = 10000;
                log("", helpShowTime);
                log("Ctrl + C : Exit program.",helpShowTime);
                log("+ or - : Zoom in/out",helpShowTime);
                log("autosize : Reset zoom to auto-generated magnification",helpShowTime);
                log("identify [] : Reset rotation", helpShowTime);
                log("obj [file path] : Open .obj file", helpShowTime);
                log("tex [file path] : open and apply texture", helpShowTime);
                log("help [] : Show this message", helpShowTime);
                log("", helpShowTime);
                log("Commands :", helpShowTime);
            }
            break;
        case 2:
            if (!args[0].compare("obj")) {
                parent->load(args[1]);
            }else if(!args[0].compare("tex")) {
                parent->try_load_tex(args[1]);
            }
            break;
        case 3:
            break;
        }

    }

    void console::render()
    {
        float WinPosX = -parent->view->resolutionX / 160.f;
        float WinPosY = parent->view->resolutionY / 160.f*.9f, diff = parent->view->resolutionY / 160.f*.05f;
        view->drawText(WinPosX, WinPosY, input_buffer->c_str());
        WinPosY -= diff;
        auto strit = output_buffer->rbegin();
        for (int i = 0; i < output_buffer->size(); i++)
        {
            view->drawText(WinPosX, WinPosY, strit->c_str());
            WinPosY -= diff;
            ++strit;
        }
        if (output_buffer->size() < 1)
            view->drawText(WinPosX, WinPosY, "type 'help' to see commands.");
    }

    void console::refresh()
    {
        int count = output_buffer->size();
        list<string>::iterator strit = output_buffer->begin();
        list<float>::iterator timeit = removal_buffer->begin();
        for (int i = 0; i < count; i++)
        {

            *timeit -= view->millis;
            if (*timeit < 0)
            {
                timeit = removal_buffer->erase(timeit);
                strit = output_buffer->erase(strit);
            }
            else {
                ++timeit;
                ++strit;
            }
        }
    }

    console::console(obj_viewer* parent)
    {
        this->parent = parent;
        view = parent->view;
        removal_time = 2000;
        input_buffer = new string();
        output_buffer = new list<string>;
        removal_buffer = new list<float>;
    }

    console::~console()
    {
        delete(input_buffer);
        delete(output_buffer);
        delete(removal_buffer);
    }

}
