#include "Math/AABBox.hpp"
#include "Math/Plane.hpp"
#include "Math/Ray.hpp"
#include "Math/Sphere.hpp"
#include "Math/Triangle.hpp"

using namespace Magic;

int main(int argc, char *argv[])
{
    AABBoxf aabb0(Vector3f(-1.0f, -1.0f, -1.0f), Vector3f(1.0f, 1.0f, 1.0f));
    aabb0.Union(Vector3f(2.f, 2.f, 2.f));
    cout << aabb0 << endl;

    Planef plane0(Vector3f::up, 1.f);
    Spheref sphere0(Vector3f(2, 2, 2), 4.f);

    Trianglef tri0(Vector3f(0, 0, 0), Vector3f(1.f, 0.f, 0.f), Vector3f(0.f, 0.f, 1.f));

    Rayf ray(Vector3f(4.f, 4.f, 4.f), Vector3f(-1, -1, -2).Normalize());

    Vector3f point;
    cout << aabb0.Intersect(ray, nullptr, &point) << " " << point << endl;

    cout << sphere0.Intersect(ray, nullptr, &point) << " " << point << endl;

    cout << plane0.Intersect(ray, nullptr, &point) << " " << point << endl;

    cout << tri0.Intersect(ray, nullptr, &point) << " " << point << endl;

    Vector3f out;
    Vector3f in(0.5f, 2.f, 0.1f);
    cout << tri0.BarycentricCoord(in, out) << endl;
    cout << out << " " << out.x * tri0[0] + out.y * tri0[1] + out.z * tri0[2] << endl;

    return 0;
}
