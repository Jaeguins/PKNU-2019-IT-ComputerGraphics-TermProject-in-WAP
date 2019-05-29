#pragma once
#include<vector>
#include "gl_vectors.hpp"

namespace advanced_gl {
    //오브젝트 하나에 대한 클래스
    class gl_object {
    public:
        //위치
        gl_vec_3f Position = gl_vec_3f(0, 0, 0);
        //크기
        gl_vec_3f Scale = gl_vec_3f(1, 1, 1);
        //색상
        gl_vec_3f Color = gl_vec_3f(1, 1, 1);
        //회전정보
        Quaternion Rotation;
        int isText = false;
        gl_object();
        //하위 오브젝트들
        std::vector<gl_object*> subObjects;
        //렌더링 함수 - 오버라이드 필요
        void(*draw)(gl_object* obj);
        //렌더링 실행함수
        void render();
        //글자 렌더링 함수 - 오버라이드 필요
        void(*drawText)(gl_object* obj);
        //글 내용
        std::string str;
    };
}
