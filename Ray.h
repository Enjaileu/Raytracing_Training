#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray{
public:
    Ray() {}
    Ray(const point3& origin, const Vec3& direction)
    : mOrig(origin), mDir(direction)
    {}

    point3 origin() const { return mOrig;}
    Vec3 direction() const {return mDir;}

    point3 at(double t) const { return mOrig + t*mDir;}

    point3 mOrig;
    Vec3 mDir;

};

#endif