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
        Matrix4x4f mvpMat4(u["mvpMat"].data());

        const Vector3f &inPosition = *(Vector3f *)(datas);
        const Vector2f &inUV = *(Vector2f *)(&inPosition + 1);

        Vector4f &outPosition = *(Vector4f *)out;
        Vector2f &outUV = *(Vector2f *)(&outPosition + 1);
        outPosition = mvpMat4 * Vector4f(inPosition.x, inPosition.y, inPosition.z, 1.0f);
        outUV = inUV;
    }

    REGISTER_VPROGRAM(VertexShader);

    static Color FragmentShader(const void *globalUniforms, const void *uniforms, ISampler **samplers, const void *datas)
    {
        Vector2f &inUV = V2F_UV(datas);

        ISampler *sampler1 = samplers[0];
        Color albedo = sampler1->Sample(inUV);
        return albedo;
    }

    REGISTER_FPROGRAM(FragmentShader);

}
