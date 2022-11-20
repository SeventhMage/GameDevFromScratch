#include "Scene/CCamera.h"

namespace Magic
{
    CCamera::CCamera(const CameraTypeParam &param)
        : _CameraTypeParam(param), _NeedUpdateView(true), _NeedUpdateProj(true)
    {
    }

    CCamera::~CCamera()
    {
    }

    void CCamera::Update()
    {
        if (_NeedUpdateView)
        {
            _ViewMatrix.BuildCameraLookAtMatrix(_Position, _Direction, _Up);
            /*				CMatrix4 mat4;
                            BuildFrustumMatrix(mat4);
                            m_frustum.Transform(mat4);	*/
        }

        if (_NeedUpdateProj)
        {
            if (_CameraTypeParam.cameraType == CameraType::Orthogonal)
            {
                _ProjMatrix.BuildProjectionMatrixOrthoRH(_CameraTypeParam.width, _CameraTypeParam.height, _CameraTypeParam.nearClip, _CameraTypeParam.farClip);
            }
            else
            {
                _ProjMatrix.BuildProjectionMatrixPerspectiveFovRH(_CameraTypeParam.fov, _CameraTypeParam.aspect, _CameraTypeParam.nearClip, _CameraTypeParam.farClip);
                _Frustum.Create(_CameraTypeParam.fov, _CameraTypeParam.aspect, _CameraTypeParam.nearClip, _CameraTypeParam.farClip);
            }
        }

        if (_NeedUpdateProj || _NeedUpdateView)
        {
            _ViewProjMatrix = _ProjMatrix * _ViewMatrix;
            // frustum更新

            //
            _NeedUpdateProj = false;
            _NeedUpdateView = false;
        }
    }
    const Vector3f &CCamera::GetPosition() const
    {
        return _Position;
    }
    const Vector3f &CCamera::GetDirection() const
    {
        return _Direction;
    }
    const Vector3f &CCamera::GetUp() const
    {
        return _Up;
    }
    const CameraTypeParam &CCamera::GetCameraTypeParam() const
    {
        return _CameraTypeParam;
    }
    CameraTypeParam &CCamera::GetCameraTypeParam()
    {
        return _CameraTypeParam;
    }
    void CCamera::SetCameraTypeParam(const CameraTypeParam &camTypeParam)
    {
        _CameraTypeParam = camTypeParam;
    }
    Matrix4x4f &CCamera::GetViewMatrix()
    {
        return _ViewMatrix;
    }
    Matrix4x4f &CCamera::GetProjectionMatrix()
    {
        return _ProjMatrix;
    }
    const Matrix4x4f &CCamera::GetViewProjectionMatrix() const
    {
        return _ViewProjMatrix;
    }
    const Frustumf &CCamera::GetFrustum() const
    {
        return _Frustum;
    }

    void CCamera::SetPosition(const Vector3f &position)
    {
        _Position = position;
        _NeedUpdateView = true;
    }
    void CCamera::SetDirection(const Vector3f &direction)
    {
        _Direction = direction;
        _NeedUpdateView = true;
    }
    void CCamera::SetUp(const Vector3f &up)
    {
        _Up = up;
        _NeedUpdateView = true;
    }
}