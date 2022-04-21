#ifndef SIMD_HPP
#define SIMD_HPP

#include "vect4f.hpp"

namespace simd {

Vect4f add(Vect4f a, Vect4f b);
Vect4f subtract(Vect4f a, Vect4f b);
Vect4f multiply(Vect4f a, Vect4f b);
Vect4f divide(Vect4f a, Vect4f b);

};

#endif //SIMD_HPP