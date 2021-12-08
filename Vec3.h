#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

#include "RTWeekend.h"

using std::sqrt;

class Vec3 {
    public:
        Vec3() : e{0,0,0} {}
        Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        Vec3& operator+=(const Vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        Vec3& operator*=(const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        Vec3& operator/=(const double t) {
            return *this *= 1/t;
        }

        double length() const {
            return sqrt(length_squared());
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        //return un point random
        inline static Vec3 Random(){
            return Vec3(RandomDouble(), RandomDouble(), RandomDouble());
        }

        //return un point random selon le max et le min 
        inline static Vec3 Random(double min, double max){
            return Vec3(RandomDouble(min,max), RandomDouble(min,max), RandomDouble(min,max));
        }

        bool nearZero() const{
            //return true si le vector est proche de 0 sur les 3 axes
            const double s = 1e-8;
            return(fabs(e[0] < s) && fabs(e[1] < s) && fabs(e[2] < s));
        }
        
    public:
        double e[3];

        
};
// vec3 Utility Functions

inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator*(double t, const Vec3 &v) {
    return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline Vec3 operator*(const Vec3 &v, double t) {
    return t * v;
}

inline Vec3 operator/(Vec3 v, double t) {
    return (1/t) * v;
}

//produit scalaire
inline double dot(const Vec3 &u, const Vec3 &v) {
    return u.e[0] * v.e[0]
        + u.e[1] * v.e[1]
        + u.e[2] * v.e[2];
}

//produit vectoriel
inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vec3 UnitVector(Vec3 v) {
    return v / v.length();
}

//return position random pour une sphere
inline Vec3 RandomInUnitSphere(){
    while(true){
        Vec3 p = Vec3::Random(-1, 1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

Vec3 RandomUnitVector(){
    return UnitVector(RandomInUnitSphere()); 
}

Vec3 RandomInHemisphere(const Vec3& normal){
    Vec3 inUnitSphere = RandomInUnitSphere();
    // if in the same hemisphere as the normal
    if(dot(inUnitSphere, normal) > 0.0) {
        return inUnitSphere;
    }
    else{
        return - inUnitSphere;
    }
}
// return une version miroire du param 1 par rapport au param2(surface reflechissante)
Vec3 Reflect(const Vec3& v, const Vec3& n) {
    return v - 2*dot(v,n)*n;
}

Vec3 Refract(const Vec3& uv, const Vec3& n, double etai_over_etat) {
    double cosTheta = fmin(dot(-uv, n), 1.0);
    Vec3 rOutPerp =  etai_over_etat * (uv + cosTheta*n);
    Vec3 rOutParallel = -sqrt(fabs(1.0 - rOutPerp.length_squared())) * n;
    return rOutPerp + rOutParallel;
}

// Type aliases for vec3
using point3 = Vec3;   // 3D point
using color = Vec3;    // RGB color


#endif
