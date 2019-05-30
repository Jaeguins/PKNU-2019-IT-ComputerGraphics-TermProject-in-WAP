#pragma once
#include <GL/glut.h>

namespace advanced_gl
{
    //3차원 벡터 구조체
    struct gl_vec_3f {
        GLfloat x, y, z;
        gl_vec_3f(GLfloat x, GLfloat y, GLfloat z);
        gl_vec_3f operator+(gl_vec_3f t) const;
        gl_vec_3f operator-(gl_vec_3f t) const;
        //크기를 1로 평탄화
        gl_vec_3f normalize() const;
        gl_vec_3f operator-() const;
        gl_vec_3f operator*(GLfloat t) const;
        gl_vec_3f operator/(GLfloat t) const;
        gl_vec_3f();
        //(0,0,0)
        static gl_vec_3f zero;
    };
    //2차원 벡터 구조체
    struct gl_vec_2f {
        GLfloat x, y;
        gl_vec_2f(GLfloat x, GLfloat y);
        gl_vec_2f operator+(gl_vec_2f t) const;
        gl_vec_2f operator-(gl_vec_2f t) const;
        //크기를 1로 평탄화
        gl_vec_2f normalize() const;
        gl_vec_2f operator-() const;
        gl_vec_2f operator*(GLfloat t) const;
        gl_vec_2f operator/(GLfloat t) const;
        gl_vec_2f();
        //(0,0)
        static gl_vec_2f zero;
    };
    //면에 대한 구조체
    struct gl_face
    {
        //폴리곤 점
        gl_vec_3f vertices[3];
        //uv 좌표
        gl_vec_2f uvs[3];
        //법선벡터
        gl_vec_3f normals[3];

    };
    
    void glVertexVector(gl_vec_3f);
    void glVertexVector(gl_vec_2f);
    void glFace(gl_face);
    //회전 구조체
    struct Quaternion {
        gl_vec_3f vect = gl_vec_3f(0, 1, 0);
        float angle = 0.0f;
    };
}
