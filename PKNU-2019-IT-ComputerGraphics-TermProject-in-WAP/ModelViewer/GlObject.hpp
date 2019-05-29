#pragma once
#include<GL/glut.h>
#include<iostream>
#include<vector>
namespace GlVector {
    //3차원 벡터 구조체
    struct GlVec3f {
        GLfloat x, y, z;
        GlVec3f(GLfloat x, GLfloat y, GLfloat z);
        GlVec3f operator+(GlVec3f t) const;
        GlVec3f operator-(GlVec3f t) const;
        //크기를 1로 평탄화
        GlVec3f normalize() const;
        GlVec3f operator-() const;
        GlVec3f operator*(GLfloat t) const;
        GlVec3f operator/(GLfloat t) const;
        GlVec3f();
        //(0,0,0)
        static GlVec3f zero;
    };
    //2차원 벡터 구조체
    struct GlVec2f {
        GLfloat x, y;
        GlVec2f(GLfloat x, GLfloat y);
        GlVec2f operator+(GlVec2f t) const;
        GlVec2f operator-(GlVec2f t) const;
        //크기를 1로 평탄화
        GlVec2f normalize() const;
        GlVec2f operator-() const;
        GlVec2f operator*(GLfloat t) const;
        GlVec2f operator/(GLfloat t) const;
        GlVec2f();
        //(0,0)
        static GlVec2f zero;
    };
    //면에 대한 구조체
    struct GlFace
    {
        //폴리곤 점
        GlVec3f vertices[3];
        //uv 좌표
        GlVec2f uvs[3];
        //법선벡터
        GlVec3f normals[3];
        GlFace();
    };

    //회전 구조체
    struct Quaternion {
        GlVec3f vect = GlVec3f(0, 1, 0);
        float angle = 0.0f;
    };
    //카메라 클래스
    class GlCamera {
    public:
        GlVec3f Position = GlVec3f(0, 0, 0);
        float xAngle;
        float yAngle;
        void cameraMove() const;
    };
    //오브젝트 하나에 대한 클래스
    class GlObject {
    public:
        //위치
        GlVec3f Position = GlVec3f(0, 0, 0);
        //크기
        GlVec3f Scale = GlVec3f(1, 1, 1);
        //색상
        GlVec3f Color = GlVec3f(1, 1, 1);
        //회전정보
        Quaternion Rotation;
        int isText = false;
        GlObject();
        //하위 오브젝트들
        std::vector<GlObject*> subObjects;
        //렌더링 함수 - 오버라이드 필요
        void(*draw)(GlObject* obj);
        //렌더링 실행함수
        void render();
        //글자 렌더링 함수 - 오버라이드 필요
        void(*drawText)(GlObject* obj);
        //글 내용
        std::string str;
    };
}