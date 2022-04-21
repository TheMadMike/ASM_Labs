#ifndef SISD_HPP
#define SISD_HPP

#include "vect4f.hpp"

namespace sisd {

Vect4f add(Vect4f a, Vect4f b);
Vect4f subtract(Vect4f a, Vect4f b);
Vect4f multiply(Vect4f a, Vect4f b);
Vect4f divide(Vect4f a, Vect4f b);

};

#endif //SISD_HPP