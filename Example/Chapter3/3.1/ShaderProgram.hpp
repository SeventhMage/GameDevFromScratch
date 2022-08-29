#include "Foundation/Math/Vector4.hpp"
#include "Foundation/Math/Vector3.hpp"
#include "Foundation/Math/Vector2.hpp"
#include "Foundation/Math/Color.hpp"
#include "Foundation/Math/Matrix4x4.hpp"
#include "Graphic/Rendering/SoftShaderMCR.h"

#define IN
#define OUT
#define UNIFORM

namespace Magic
{
    static void VertexShader(const void *globalUniforms, const void *uniforms, const void *datas, unsigned char *out)
    {
        typedef map<string, vector<float>> UniformMap;
        UniformMap globalU = *((UniformMap *)globalUniforms);
        UniformMap u = *((UniformMap *)uniforms);
        Matrix4x4f mvpMat4(globalU["mvpMat"].data());

        const Vector3f &inPosition = *(Vector3f *)(datas);
        const Vector3f &inColor = *(Vector3f *)(&inPosition + 1);

        Vector4f &outPosition = *(Vector4f *)out;
        Vector3f &outColor = *(Vector3f *)(&outPosition + 1);
        outPosition = mvpMat4 * Vector4f(inPosition.x, inPosition.y, inPosition.z, 1.0f);
        outColor = inColor;
    }

    IMPLEMENT_VPROGRAM(VertexShader);
    REGISTER_VPROGRAM(VertexShader);

    static Color FragmentShader(const void *uniforms, ISampler **samplers, const void *datas)
    {
        Vector3f inColor;
        // Vector2f inUV;
        // memcpy(inColor.v, datas, sizeof(inColor.v));
        // memcpy(inUV.v, (unsigned char *)datas + sizeof(inColor.v), sizeof(inUV.v));

        // ISampler *sampeler1 = samplers[0];
        // ISampler *sampeler2 = samplers[1];
        // Color tex1 = sampeler1->Sample(inUV);
        // Color tex2 = sampeler2->Sample(inUV);

        return Color(1.0f, inColor.x, inColor.y, inColor.z);
    }

    IMPLEMENT_FPROGRAM(FragmentShader);
    REGISTER_FPROGRAM(FragmentShader);

}
