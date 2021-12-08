#ifndef CAMERA_H
#define CAMERA_H

#include "RTWeekend.h"
#include "Vec3.h"
#include "Ray.h"

class Camera {
    public:
        Camera(point3 lookFrom, point3 lookAt, Vec3 vup,double vFov /* vertical field of view */, double aspectRatio) {
            

            double theta = DegreesToRadians(vFov);
            auto h = tan(theta/2);
            auto viewportHeight = 2.0 * h;
            auto viewportWidth = aspectRatio * viewportHeight;

            Vec3 w = UnitVector(lookFrom - lookAt);
            auto u = UnitVector(cross(vup, w));
            auto v = cross(w, u);

            origin = lookFrom;
            horizontal = viewportWidth * u;
            vertical = viewportHeight * v;
            lowerLeftCorner = origin - horizontal/2 - vertical/2 - w;
        }

        Ray GetRay(double s, double t) const {
            return Ray(origin, lowerLeftCorner + s*horizontal + t*vertical - origin);
        }

    private:
        point3 origin;
        point3 lowerLeftCorner;
        Vec3 horizontal;
        Vec3 vertical;
};
#endif