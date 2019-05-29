#pragma once
#include<vector>
#include "gl_vectors.hpp"

namespace advanced_gl {
    //������Ʈ �ϳ��� ���� Ŭ����
    class gl_object {
    public:
        //��ġ
        gl_vec_3f Position = gl_vec_3f(0, 0, 0);
        //ũ��
        gl_vec_3f Scale = gl_vec_3f(1, 1, 1);
        //����
        gl_vec_3f Color = gl_vec_3f(1, 1, 1);
        //ȸ������
        Quaternion Rotation;
        int isText = false;
        gl_object();
        //���� ������Ʈ��
        std::vector<gl_object*> subObjects;
        //������ �Լ� - �������̵� �ʿ�
        void(*draw)(gl_object* obj);
        //������ �����Լ�
        void render();
        //���� ������ �Լ� - �������̵� �ʿ�
        void(*drawText)(gl_object* obj);
        //�� ����
        std::string str;
    };
}
