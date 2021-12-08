#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double DegreesToRadians(double degrees) {
    return degrees * pi / 180.0;
}

inline double RandomDouble(){
    return rand() / (RAND_MAX + 1.0); 
}

inline double RandomDouble(double min, double max){
    return min + (max-min)*RandomDouble();
}

inline double Clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

#endif