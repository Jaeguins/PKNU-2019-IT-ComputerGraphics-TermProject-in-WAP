#pragma once
#include "gl_vectors.hpp"
namespace advanced_gl {
    //ī�޶� Ŭ����
    class gl_camera {
    public:
        gl_vec_3f Position = gl_vec_3f(0, 0, 0);
        float magnify=1.f;
        float xAngle;
        float yAngle;
        void cameraMove() const;
    };
}