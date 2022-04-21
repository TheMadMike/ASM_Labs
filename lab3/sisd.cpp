#include "sisd.hpp"

namespace sisd {

Vect4f add(Vect4f a, Vect4f b) {
    Vect4f result = {};
    asm volatile(
        "fld %4 \n"
        "fadd %5 \n"
        "fstps %0 \n"
        "fld %6 \n"
        "fadd %7 \n"
        "fstps %1 \n"
        "fld %8 \n"
        "fadd %9 \n"
        "fstps %2 \n"
        "fld %10 \n"
        "fadd %11 \n"
        "fstps %3 \n"
    :	"=m" (result.x),
        "=m" (result.y),
       	"=m" (result.z),
       	"=m" (result.w)
    :   "f" (a.x),"f" (b.x),
        "f" (a.y),"f" (b.y),
        "f" (a.z),"f" (b.z),
        "f" (a.w),"f" (b.w)
    );
    return result;
}

Vect4f subtract(Vect4f a, Vect4f b) {
    Vect4f result = {};
    asm volatile(
        "fld %4 \n"
        "fsub %5 \n"
        "fstps %0 \n"
        "fld %6 \n"
        "fsub %7 \n"
        "fstps %1 \n"
        "fld %8 \n"
        "fsub %9 \n"
        "fstps %2 \n"
        "fld %10 \n"
        "fsub %11 \n"
        "fstps %3 \n"
    :	"=m" (result.x),
        "=m" (result.y),
       	"=m" (result.z),
       	"=m" (result.w)
    :   "f" (a.x),"f" (b.x),
        "f" (a.y),"f" (b.y),
        "f" (a.z),"f" (b.z),
        "f" (a.w),"f" (b.w)
    );
    return result;
}

Vect4f multiply(Vect4f a, Vect4f b) {
    Vect4f result = {};
    asm volatile(
        "fld %4 \n"
        "fmul %5 \n"
        "fstps %0 \n"
        "fld %6 \n"
        "fmul %7 \n"
        "fstps %1 \n"
        "fld %8 \n"
        "fmul %9 \n"
        "fstps %2 \n"
        "fld %10 \n"
        "fmul %11 \n"
        "fstps %3 \n"
    :	"=m" (result.x),
        "=m" (result.y),
       	"=m" (result.z),
       	"=m" (result.w)
    :   "f" (a.x),"f" (b.x),
        "f" (a.y),"f" (b.y),
        "f" (a.z),"f" (b.z),
        "f" (a.w),"f" (b.w)
    );
    return result;
}

Vect4f divide(Vect4f a, Vect4f b) {
    Vect4f result = {};
    asm volatile(
        "fld %4 \n"
        "fdiv %5 \n"
        "fstps %0 \n"
        "fld %6 \n"
        "fdiv %7 \n"
        "fstps %1 \n"
        "fld %8 \n"
        "fdiv %9 \n"
        "fstps %2 \n"
        "fld %10 \n"
        "fdiv %11 \n"
        "fstps %3 \n"
    :	"=m" (result.x),
        "=m" (result.y),
       	"=m" (result.z),
       	"=m" (result.w)
    :   "f" (a.x),"f" (b.x),
        "f" (a.y),"f" (b.y),
        "f" (a.z),"f" (b.z),
        "f" (a.w),"f" (b.w)
    );
    return result;
}


};