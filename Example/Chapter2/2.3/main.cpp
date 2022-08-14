#include "../../../MagicEngine/Include/Math/Vector3.hpp"
#include "../../../MagicEngine/Include/Math/Quaternion.hpp"

using namespace Magic;

int main(int argc, char *argv[])
{

    Quaterniond q1;
    cout << PI_DIV_3 << endl;
    q1.FromEulerAngle(PI_DIV_3, PI_DIV_3, PI_DIV_3);
    cout << q1 << endl << q1.ToEulerAngle() << endl;
    Quaterniond q2;
    q2.MakeRotateByX(PI_DIV_2);
    Quaterniond q3;
    q3.MakeRotateByAxis(Vector3d(1, 1, 1), PI_DIV_6);
    //q2 = q3 * q2;
    cout << q3.GetRotationAngle() << " " << q3.GetRotationAxis() << endl;
    Quaterniond q4;
    q4.MakeRotateByX(PI_DIV_2);
    Vector3d v(0, 1, 0);
    cout << q4 * q2 * v << endl;
    cout << q4 * (q2 * v) << endl;
    return 0;
}
