#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"

class Sphere : public Hittable {
    public:
        Sphere() {}
        Sphere(point3 cen, double r, shared_ptr<Material> m) : mCenter(cen), mRadius(r), mMatPtr(m) {};

        virtual bool Hit(
            const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

    public:
        point3 mCenter;
        double mRadius;
        shared_ptr<Material> mMatPtr;
};

bool Sphere::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    Vec3 oc = r.origin() - mCenter;
    double a = r.direction().length_squared();
    double halfB = dot(oc, r.direction());
    double c = oc.length_squared() - mRadius*mRadius;

    double discriminant = halfB*halfB - a*c;
    if (discriminant < 0) return false;
    double sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    double root = ( -halfB - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-halfB + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    Vec3 outwardNormal = (rec.p - mCenter) / mRadius;
    rec.SetFaceNormal(r, outwardNormal);
    rec.matPtr = mMatPtr;
    
    return true;
}

#endif