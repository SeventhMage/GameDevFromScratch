#include <iostream>
#include "../../../MagicEngine/Include/Math/Matrix4x4.hpp"
#include "../../../MagicEngine/Include/Math/Vector3.hpp"
#include "../../../MagicEngine/Include/Math/Math.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    Vector3d a(1., 0., 0.);
    Vector3d b(1.0, 0., 0.);
    Vector3d c(0., 0., 1.);

    double piDiv2 = 1.5707963267;
    double cs = cos(piDiv2);
    double sn = sin(piDiv2);
    Matrix4x4d mat44;
    mat44.MakeRotation(Vector3d::right, PI_DIV_2);
    cout << mat44.Transform(b) << endl;
    cout << b.RotateByX(PI_DIV_2) << endl;

    mat44.MakeRotation(Vector3d::up, PI_DIV_2);
    cout << mat44.Transform(b) << endl;
    cout << b.RotateByY(PI_DIV_2) << endl;

    mat44.MakeRotation(Vector3d::direction, PI_DIV_2);
    Matrix4x4d mat44_1;
    mat44_1.MakeRotation(Vector3d::right, PI_DIV_2);
    Matrix4x4d mat44_2 = mat44_1 * mat44;
    cout << mat44.Transform(a) << endl;
    cout << mat44_2.Transform(a) << endl;

    mat44_2.MakeTransition(Vector3d(100., 100., 100.));

    cout << mat44_2.Transform(Vector3d::right) << endl;

    Matrix4x4d matReflect;
    matReflect.MakeReflect(Vector3d::up);
    cout << matReflect.Transform(Vector3d(1.0, 1.0, 0.0)) << endl;
    return 0;
}