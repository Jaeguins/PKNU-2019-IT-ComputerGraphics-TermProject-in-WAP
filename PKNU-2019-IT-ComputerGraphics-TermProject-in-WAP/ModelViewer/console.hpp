#pragma once
#include <string>
#include <list>


namespace model_viewer
{
    class obj_viewer;
    class viewport;
    
    using namespace std;
    class console
    {
    public:
        //뷰포트
        viewport* view;
        //뷰어
        obj_viewer* parent;
        //사라지는 시간
        int removal_time;
        //입력 버퍼
        string* input_buffer;
        //출력 버퍼
        list<string>* output_buffer;
        //출력 대기시간 버퍼
        list<float>* removal_buffer;
        //타이머에서 계산하는 함수
        void refresh();
        //입력 처리 함수
        void process();
        //한글자 입력함수
        void input(unsigned char in);
        //출력함수
        void log(string data,float time=-1);
        //콘솔 그리는 함수
        void render();
        console(obj_viewer* parent);
        ~console();
    };
}
