#ifndef MATERIAL_H
#define MATERIAL_H

#include "RTWeekend.h"
#include "HittableList.h"

class Material {
    public:
        virtual bool Scatter(
            const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered
        ) const = 0;
};

class Lambertian : public Material{
    public :
    Lambertian(const color& a) : mAlbedo(a) {}

    virtual bool Scatter( const Ray& RIn, const HitRecord& rec, color& attenuation, Ray& scattered)const override {
        Vec3 scatterDirection = rec.normal + RandomUnitVector();

        // attrape des disperssions qui servent à rien
        if(scatterDirection.nearZero()){
            scatterDirection = rec.normal;
        }

        scattered = Ray(rec.p, scatterDirection);
        attenuation = mAlbedo;
        return true;
    }

    public:
    color mAlbedo;
};

class Metal : public Material {
    public:
        Metal(const color& a, double f) : mAlbedo(a) , mFuzz(f < 1 ? f : 1){}

        virtual bool Scatter( const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const override {
            Vec3 reflected = Reflect(UnitVector(r_in.direction()), rec.normal);
            scattered = Ray(rec.p, reflected + mFuzz*RandomInUnitSphere());
            attenuation = mAlbedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }

    public:
        color mAlbedo;
        double mFuzz;
};


class Dielectric : public Material {
    public:
        Dielectric(double indexOfRefraction) : ir(indexOfRefraction) {}

        virtual bool Scatter(const Ray& rIn, const HitRecord& rec, color& attenuation, Ray& scattered) const override {
            attenuation = color(1.0, 1.0, 1.0);
            double refractionRatio = rec.frontFace ? (1.0/ir) : ir;

            Vec3 unitDirection = UnitVector(rIn.direction());
            double cosTheta = fmin(dot(-unitDirection, rec.normal), 1.0);
            double sinTheta = sqrt(1.0 - cosTheta*cosTheta);

            bool cannot_refract = refractionRatio * sinTheta > 1.0;
            Vec3 direction;

            if (cannot_refract || Reflectance(cosTheta, refractionRatio) > RandomDouble())
                direction = Reflect(unitDirection, rec.normal);
            else
                direction = Refract(unitDirection, rec.normal, refractionRatio);

            scattered = Ray(rec.p, direction);
            return true;

        }

    public:
        double ir; // Index of Refraction

    private:
        static double Reflectance(double cosine, double refIdx) {
            // Use Schlick's approximation for reflectance.
            auto r0 = (1-refIdx) / (1+refIdx);
            r0 = r0*r0;
            return r0 + (1-r0)*pow((1 - cosine),5);
        }
};


#endif