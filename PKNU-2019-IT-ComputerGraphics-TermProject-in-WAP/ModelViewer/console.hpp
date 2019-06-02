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
        //����Ʈ
        viewport* view;
        //���
        obj_viewer* parent;
        //������� �ð�
        int removal_time;
        //�Է� ����
        string* input_buffer;
        //��� ����
        list<string>* output_buffer;
        //��� ���ð� ����
        list<float>* removal_buffer;
        //Ÿ�̸ӿ��� ����ϴ� �Լ�
        void refresh();
        //�Է� ó�� �Լ�
        void process();
        //�ѱ��� �Է��Լ�
        void input(unsigned char in);
        //����Լ�
        void log(string data,float time=-1);
        //�ܼ� �׸��� �Լ�
        void render();
        console(obj_viewer* parent);
        ~console();
    };
}
