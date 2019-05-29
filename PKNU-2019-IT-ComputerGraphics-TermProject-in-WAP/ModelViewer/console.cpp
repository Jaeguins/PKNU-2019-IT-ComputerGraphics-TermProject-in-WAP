#include "console.hpp"
#include <vector>
#include "viewport.hpp"
#include "obj_viewer.hpp"
#include "string_split.h"

namespace model_viewer
{
    void console::input(const unsigned char in)
    {
        if(in==8)if(input_buffer->size()>1)input_buffer->pop_back();
        else if (in == 13)process();
        else (*input_buffer) += in;
    }
    void console::process()
    {
        string t=*input_buffer;
        output_buffer->push_back(t);
        removal_buffer->push_back(removal_time);
        input_buffer->clear();
        vector<string> args = std::split(*input_buffer, ' ');
        //TODO args에 따라 명령 처리
    }

    void console::render()
    {
        float WinPosY = .9, diff = .1f;
        view->drawText(-1, WinPosY, input_buffer->c_str());
        WinPosY -= diff;
        auto strit = output_buffer->rbegin();
        for (int i = 0; i < output_buffer->size(); i++)
        {
            view->drawText(-1, WinPosY, strit->c_str());
            WinPosY -= diff;
            ++strit;
        }
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
