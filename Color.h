#ifndef COLOR_H
#define COLOR_H

//class qui va return quelle couleur afficher
#include "RTWeekend.h"
#include "Vec3.h"

#include <iostream>

void WriteColor(std::ostream &out, color pixelColor, int samplesPerPixel){
    double r = pixelColor.x();
    double g = pixelColor.y();
    double b = pixelColor.z();

    //diviser la couleur par le nombre de samples + gamma correction car sinon c'est de + en + sombre
    double scale = 1.0 / samplesPerPixel;
    r = sqrt(scale *r);
    g = sqrt(scale *g);
    b = sqrt(scale *b);

    //ecrire la couleur
    out << static_cast<int>(256 * Clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Clamp(b, 0.0, 0.999)) << '\n';
}

#endif
