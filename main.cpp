
#include <iostream>
#include <fstream>

#include "RTWeekend.h"
#include "HittableList.h"
#include "Material.h"
#include "Sphere.h"
#include "Camera.h"
#include "Color.h"

//Cmake: Configure : à chaque fois qu'on rajoute un fichier
//CMake: Build : pour générer le .Exe
//CMake:Clean : pour clean le dossier debug

//Launch programme = F5

//file PPM = ce qui va determiner la couleur de chacun des pixels de l'image

// https://raytracing.github.io/books/RayTracingInOneWeekend.html
// j'en suis à 6.4

//utiliser Git:
// Local change >< Local Copy >< Remote copy(repo)
// creer un repository sur github pour stocker le projet
// il faut le logiciel git sur son ordi 
// copy adresse ssh du repo
// git clone [adresse ssh] (mais il faut que l'ordi ait le droit de se connecter ssh, donc generer clée ssh sur ordi avec gitbash, voir la docu ou la video)
// copier la clé publique > coller sur notre compte github and GPG Key
// git status : dit où on en est sur le projet
// git add [.] = tout / [main.cpp] = main.cpp : add sur la liste de fichiers à commit
// git commit -m"message" : commit tous les change sur le local copy avec un petit message d'explication
// git push origin main : envoyer le local copy sur le remote copy (repo), sur la branche main
// git pull -- rebase : git fetch + git rebase
// git flow feature start MYFEATURE puis git flow feature finish MYFEATURE : créer une brnche puis la merge avec la branche develop

color RayColor(const Ray& r, const Hittable& world, int depth) {
    
    HitRecord rec; 

    //si + de rebond que le nombre limite, plus de lumière (donc du noir)
    if (depth <= 0) return color(0,0,0);

    if(world.Hit(r, 0.001, infinity, rec)){
        Ray scattered;
        color attenuation;
        if(rec.matPtr->Scatter(r, rec, attenuation, scattered)){
            return attenuation * RayColor(scattered, world, depth-1);
        }
        else{
        return color(0,0,0);
        }
    }
    Vec3 unitDirection = UnitVector(r.direction());
    double t = 0.5*(unitDirection.y() + 1.0);
    return (1.0 - t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);

    return color(0.0,0.0,0.0);
}

int main(){
    //image
    const double aspectRatio = 16.0/9.0;
    const int iWidth = 300;
    const int iHeight = (iWidth/aspectRatio);
    int samplePerPixel = 100;
    const int maxDepth = 50;

    //world
    double R = cos(pi/4);
    HittableList world;

    auto groundMat = make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    auto centerMat = make_shared<Lambertian>(color(0.1, 0.2, 0.5));
    auto leftMat   = make_shared<Dielectric>(1.5);
    auto rightMat  = make_shared<Metal>(color(0.8, 0.6, 0.2), 0.0);

    world.Add(make_shared<Sphere>(point3( 0.0, -100.5, -1.0), 100.0, groundMat));
    world.Add(make_shared<Sphere>(point3( 0.0,    0.0, -1.0),   0.5, centerMat));
    world.Add(make_shared<Sphere>(point3(-1.0,    0.0, -1.0),   0.5, leftMat));
    world.Add(make_shared<Sphere>(point3(-1.0,    0.0, -1.0), -0.45, leftMat));
    world.Add(make_shared<Sphere>(point3( 1.0,    0.0, -1.0),   0.5, rightMat));

    //camera
    //Camera camera(point3(-2,2,1), point3(0,0,-1), Vec3(0,1,0), 90, aspectRatio);
    Camera camera(point3(-2,2,1), point3(0,0,-1), Vec3(0,1,0), 20, aspectRatio);

    // Render
    std::ofstream output;
    output.open("output.ppm");

    output <<"P3\n" << iWidth << " " << iHeight << " \n255\n";

    for(int j = iHeight-1; j>=0; --j){
        //cerr = la ligne va se mettre à jour plutôt que de s'écrire des dizaines de fois
        
        std::cerr << "\rScanlines remaining (j) : " << j << " " << std::flush; 
        for (int i = 0; i < iWidth; ++i) {
            color pixelColor(0,0,0);
            for(int s = 0; s < samplePerPixel; s++){
               double u = (i + RandomDouble()) / (iWidth-1);
               double v = (j + RandomDouble()) / (iHeight-1);
               Ray r = camera.GetRay(u, v);
               pixelColor += RayColor(r, world, maxDepth);
           }
           WriteColor(output, pixelColor, samplePerPixel);
        }
    }
    std::cerr << "\nDone.\n";
    output.close();
    return 0 ;
}