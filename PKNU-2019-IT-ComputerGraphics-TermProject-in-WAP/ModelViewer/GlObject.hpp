#pragma once
#include<GL/glut.h>
#include<iostream>
#include<vector>
namespace GlVector {
    //3���� ���� ����ü
    struct GlVec3f {
        GLfloat x, y, z;
        GlVec3f(GLfloat x, GLfloat y, GLfloat z);
        GlVec3f operator+(GlVec3f t) const;
        GlVec3f operator-(GlVec3f t) const;
        //ũ�⸦ 1�� ��źȭ
        GlVec3f normalize() const;
        GlVec3f operator-() const;
        GlVec3f operator*(GLfloat t) const;
        GlVec3f operator/(GLfloat t) const;
        GlVec3f();
        //(0,0,0)
        static GlVec3f zero;
    };
    //2���� ���� ����ü
    struct GlVec2f {
        GLfloat x, y;
        GlVec2f(GLfloat x, GLfloat y);
        GlVec2f operator+(GlVec2f t) const;
        GlVec2f operator-(GlVec2f t) const;
        //ũ�⸦ 1�� ��źȭ
        GlVec2f normalize() const;
        GlVec2f operator-() const;
        GlVec2f operator*(GLfloat t) const;
        GlVec2f operator/(GLfloat t) const;
        GlVec2f();
        //(0,0)
        static GlVec2f zero;
    };
    //�鿡 ���� ����ü
    struct GlFace
    {
        //������ ��
        GlVec3f vertices[3];
        //uv ��ǥ
        GlVec2f uvs[3];
        //��������
        GlVec3f normals[3];
        GlFace();
    };

    //ȸ�� ����ü
    struct Quaternion {
        GlVec3f vect = GlVec3f(0, 1, 0);
        float angle = 0.0f;
    };
    //ī�޶� Ŭ����
    class GlCamera {
    public:
        GlVec3f Position = GlVec3f(0, 0, 0);
        float xAngle;
        float yAngle;
        void cameraMove() const;
    };
    //������Ʈ �ϳ��� ���� Ŭ����
    class GlObject {
    public:
        //��ġ
        GlVec3f Position = GlVec3f(0, 0, 0);
        //ũ��
        GlVec3f Scale = GlVec3f(1, 1, 1);
        //����
        GlVec3f Color = GlVec3f(1, 1, 1);
        //ȸ������
        Quaternion Rotation;
        int isText = false;
        GlObject();
        //���� ������Ʈ��
        std::vector<GlObject*> subObjects;
        //������ �Լ� - �������̵� �ʿ�
        void(*draw)(GlObject* obj);
        //������ �����Լ�
        void render();
        //���� ������ �Լ� - �������̵� �ʿ�
        void(*drawText)(GlObject* obj);
        //�� ����
        std::string str;
    };
}