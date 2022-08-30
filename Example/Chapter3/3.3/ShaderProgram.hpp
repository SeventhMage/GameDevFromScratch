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

    typedef map<string, vector<float>> UniformMap;

    static void VertexShader(const void *globalUniforms, const void *uniforms, const void *datas, unsigned char *out)
    {
        UniformMap globalU = *((UniformMap *)globalUniforms);
        UniformMap u = *((UniformMap *)uniforms);
        Matrix4x4f mvpMat4(globalU["mvpMat"].data());

        const Vector3f &inPosition = *(Vector3f *)(datas);
        const Vector3f &inColor = *(Vector3f *)(&inPosition + 1);

        Vector4f &outPosition = *(Vector4f *)out;
        Color &outColor = *(Color *)(&outPosition + 1);
        outPosition = mvpMat4 * Vector4f(inPosition.x, inPosition.y, inPosition.z, 1.0f);
        outColor = Color(1.f, inColor.x, inColor.y, inColor.z);
    }

    REGISTER_VPROGRAM(VertexShader);

    static Color FragmentShader(const void *globalUniforms, const void *uniforms, ISampler **samplers, const void *datas)
    {
        Color &inColor = *((Color *)datas);
        //Vector2f &inUV = *(Vector2f *)(&inColor + 1);

        // ISampler *sampeler1 = samplers[0];
        // Color albedo = sampeler1->Sample(inUV);

        // return Color(albedo.a, albedo.r * inColor.x, albedo.g * inColor.y, albedo.b * inColor.z);
        return inColor;
    }

    REGISTER_FPROGRAM(FragmentShader);

}
