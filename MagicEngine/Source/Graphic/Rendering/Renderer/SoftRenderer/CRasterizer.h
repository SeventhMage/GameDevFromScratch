#ifndef _MAGIC_C_RASTERIZER_H_
#define _MAGIC_C_RASTERIZER_H_

#include "Foundation/Math/Triangle.hpp"
#include "Foundation/Math/Vector4.hpp"
#include "Foundation/Math/Vector2.hpp"
#include "Foundation/Math/Color.hpp"
#include "CSoftShaderProgram.h"

namespace Magic
{
    struct Vertex
    {
        Vector4f position;
    };
    struct VertexPNCT : Vertex
    {
        Vector3f normal;
        Color color;
        Vector2f texCoord0;
    };

    class CRasterizer
    {
    public:
        CRasterizer();
        ~CRasterizer();

        void SetDrawBuffer(unsigned int *pDrawBuffer, int width, int height);
        void SetDepthBuffer(float *pDrawBuffer) { _pDepthBuffer = pDrawBuffer; }
        void SetFProgram(FProgram fProgram, UniformMap *globalUniforms, UniformMap *uniforms, ISampler **_pSamplers);

        void SetTextureInfo(unsigned char *textureData, int width, int height);

        void DrawTriangle(Vector4f p0, Vector4f p1, Vector4f p2, Vector2f t0,
                          Vector2f t1, Vector2f t2, Color c0, Color c1, Color c2);
        void DrawLine(int x0, int y0, int x1, int y1, const Color &c = Color(1, 0, 0, 0));
        void DrawPixel(int x, int y, const Color &c);

        void DrawTriangle(Vector4f positions[3], Vector3f normals[3], Color colors[3], Vector2f texCoords[3]);
    private:
        void DrawTopTriangle(const Vector4f &p0, const Vector2f &t0, const Color &c0,
                             const Vector4f &p1, const Vector2f &t1, const Color &c1,
                             const Vector4f &p2, const Vector2f &t2, const Color &c2);
        void DrawBottomTriangle(const Vector4f &p0, const Vector2f &t0, const Color &c0,
                                const Vector4f &p1, const Vector2f &t1, const Color &c1,
                                const Vector4f &p2, const Vector2f &t2, const Color &c2);
        Color GetInterpolation(const Color &c0, const Color &c1, float rate);

        void FillColor(unsigned int *addr, unsigned int count, const Color &lc, const Color &rc);
        void FillColor(unsigned int *addr, float *zbuffer, unsigned int x0, float z0, float wl, unsigned int x1, float z1, float wr, const Color &lc, const Color &rc);
        void FillColor(unsigned int *addr, float *zbuffer, unsigned int x0, float z0, float wl, unsigned int x1, float z1, float wr, const Color &lc, const Color &rc, const Vector2f &lt, const Vector2f &rt);

        typedef struct 
        {
            unsigned int X;
            float InvW;
            float InvZ;
            Vector3f Normal;
            Color Color;
            Vector2f TexCoords;
        }EdgeBuffer;

        void DrawEdgeBuffer(int i0, int i1, Vector4f positions[3], Vector3f normals[3], Color colors[3], Vector2f texCoords[3], EdgeBuffer *edgeBuffer);
        void FillColor(unsigned int *addr, float *zbuffer, const EdgeBuffer &minEdge, const EdgeBuffer &maxEdge);

    private:
        unsigned int *_pDrawBuffer;
        float *_pDepthBuffer;
        EdgeBuffer *_pMinEdgeBuffer;
        EdgeBuffer *_pMaxEdgeBuffer;
        int _bufferWidth;
        int _bufferHeight;


        FProgram _OnFProgram;
        UniformMap *_pGlobalUniforms;
        UniformMap *_pUniforms;
        ISampler **_pSamplers;
    };
}

#endif