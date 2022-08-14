#include <iostream>
#include "../../../MagicEngine/Include/Math/Matrix4x3.hpp"
#include "../../../MagicEngine/Include/Math/Vector3.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    Vector3d a(1.0, 0., 0.);
    Vector3d b(0., 1., 0.);
    Vector3d c(0., 0., 1.);

    cout << a.DotProduct(b) << endl;
    cout << a.CrossProduct(b) << endl;
    cout << a + b << endl;
    cout << a - b << endl;
    cout << a * b << endl;

    cout << a.RotateByZ(3.141592654 * 0.5) << endl; // 0,1,0
    cout << b.RotateByX(3.141592654 * 0.5) << endl; // 0,0,1
    cout << c.RotateByY(3.141592654 * 0.5) << endl; // 1,0,0

    double piDiv2 = 1.5707963267;
    double cs = cos(piDiv2);
    double sn = sin(piDiv2);
    Matrix4x3d mat4x3;
    mat4x3.m00 = cs;
    mat4x3.m01 = -sn;
    mat4x3.m10 = sn;
    mat4x3.m11 = cs;
    cout << mat4x3 * c << endl;

    return 0;
}