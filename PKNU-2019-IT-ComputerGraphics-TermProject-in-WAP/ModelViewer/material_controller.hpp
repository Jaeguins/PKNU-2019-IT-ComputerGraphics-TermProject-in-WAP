#pragma once
#include "gl_vectors.hpp"
#include <string>
#include <vector>
using namespace advanced_gl;
using namespace std;
struct material {//머티리얼 하나가 가진 요소
    string name;//머티리얼 이름
    gl_vec_3f ambient, diffuse, specular;
    //환경반사량,기본반사량,조명반사량에 대한 벡터값
};
class material_controller {
public:
    material_controller();//기본생성자,필요없으면 없애세요
    ~material_controller();//소멸자, 메모리 해제용(혹시나 포인터 쓰실까 해서)
    vector<material> materials;//머티리얼들 저장공간
    material get_material(string name);//머티리얼 검색함수
    string tex_diffuse, tex_specular, tex_ambient, tex_bump;//텍스쳐 경로들
    void load(string path);//해당 경로 mtl 로드
};
