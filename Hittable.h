#ifndef HITTABLE_H
#define HITTABLE_H

#include "Vec3.h"
#include "Ray.h"

class Material;

// container 
// permet de stoquer les infos liées à la façon de gerer un hit, permet de les envoyer de façon groupée

struct HitRecord {
    point3 p;
    Vec3 normal;
    shared_ptr<Material> matPtr;
    double t;
    bool frontFace;

    inline void SetFaceNormal(const Ray& r, const Vec3& outwardNormal){
        frontFace = dot(r.direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal :-outwardNormal;
    }
};

class Hittable {
    public:
        virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};

#endif