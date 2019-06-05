#pragma once
#include "gl_vectors.hpp"
#include <string>
#include <vector>
using namespace advanced_gl;
using namespace std;
struct material {//��Ƽ���� �ϳ��� ���� ���
    string name;//��Ƽ���� �̸�
    gl_vec_3f ambient, diffuse, specular;
    //ȯ��ݻ緮,�⺻�ݻ緮,����ݻ緮�� ���� ���Ͱ�
};
class material_controller {
public:
    material_controller();//�⺻������,�ʿ������ ���ּ���
    ~material_controller();//�Ҹ���, �޸� ������(Ȥ�ó� ������ ���Ǳ� �ؼ�)
    vector<material> materials;//��Ƽ����� �������
    material get_material(string name);//��Ƽ���� �˻��Լ�
    string tex_diffuse, tex_specular, tex_ambient, tex_bump;//�ؽ��� ��ε�
    void load(string path);//�ش� ��� mtl �ε�
};
