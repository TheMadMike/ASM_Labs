#include "simd.hpp"

namespace simd {

Vect4f add(Vect4f a, Vect4f b) {
    Vect4f result = {};
    asm volatile (
        "movups %1, %%xmm0 \n"
        "movups %2, %%xmm1 \n"
        "addps %%xmm1, %%xmm0 \n"
        "movups %%xmm0, %0 \n"
        : "=m"(result)
        : "m"(a), "m"(b)
    );

    return result;
}

Vect4f subtract(Vect4f a, Vect4f b) {
    Vect4f result = {};
    asm volatile (
        "movups %1, %%xmm0 \n"
        "movups %2, %%xmm1 \n"
        "subps %%xmm1, %%xmm0 \n"
        "movups %%xmm0, %0 \n"
        : "=m"(result)
        : "m"(a), "m"(b)
    );

    return result;
}

Vect4f multiply(Vect4f a, Vect4f b) {
    Vect4f result = {};
    asm volatile (
        "movups %1, %%xmm0 \n"
        "movups %2, %%xmm1 \n"
        "mulps %%xmm1, %%xmm0 \n"
        "movups %%xmm0, %0 \n"
        : "=m"(result)
        : "m"(a), "m"(b)
    );

    return result;
}

Vect4f divide(Vect4f a, Vect4f b) {
    Vect4f result = {};
    asm volatile (
        "movups %1, %%xmm0 \n"
        "movups %2, %%xmm1 \n"
        "divps %%xmm1, %%xmm0 \n"
        "movups %%xmm0, %0 \n"
        : "=m"(result)
        : "m"(a), "m"(b)
    );

    return result;
}

};