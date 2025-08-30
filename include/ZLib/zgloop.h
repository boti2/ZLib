#pragma once

#include <ZLib/vec.h>

namespace __ZLIB__INTERNAL__ /* Internal Stuff */ {
    namespace ZGL /* Internal ZGL stuff */ {

    }
}

namespace ZGL {
    class Color {
        protected:
            char R = 0, G = 0, B = 0, A = 255;
        public:
            Color(){}
            Color(char r, char g, char b)         : R(r), G(g), B(b)       {}
            Color(char r, char g, char b, char a) : R(r), G(g), B(b), A(a) {}

            char r(){return R;}
            char g(){return G;}
            char b(){return B;}
            char a(){return A;}
    };

    enum class Primitive {
        POINTS,
        LINE_STRIP,
        LINE_LOOP,
        TRIANGLES,
        QUADS,
        POLYGON
    };

    enum class Feature {
        BLEND,
        CULL_FACE,
        DEPTH_TEST,
        DITHER,
        FOG,
        LIGHTING,
        LINE_STIPPLE,
        NORMALIZE,
        SCISSOR_TEST,
        STENCIL_TEST,
        TEXTURE,
        TEXTURE_CUBE_MAP
    };

    void setColor(ZGL::Color);
    void setClearColor(ZGL::Color);

    namespace Imm {
        void begin(ZGL::Primitive);
        void end();
        void vertex(Vec4);
        void texCoord(Vec4);
    }

    void clear();
    void flush();

    void viewport(int x, int y, int width, int height);

    void rotate(float angle, float x, float y, float z);

    void enable(ZGL::Feature);

    enum class WrapMode {
        REPEAT,
        MIRROR,
        EDGE,
        BORDER,
    };

    unsigned int loadTexture(int width, int height, ZGL::WrapMode wrapX, ZGL::WrapMode wrapY, int minFilter, int maxFilter);
}
