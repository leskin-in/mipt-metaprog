#ifndef MIPT_METAPROG_FUNCTOR_H
#define MIPT_METAPROG_FUNCTOR_H

#include <stdio.h>


/**
 * A functor to wrap decompression utilities
 *
 * @tparam F function to wrap
 */
template <void (*F)(void*)>
class OrdinaryFunctor {
public:
    static void call(void* buff) {
        F(buff);
    }
};


/**
 * A functor to wrap file read utility, a.k.a. first decompression function
 *
 * @tparam F function to wrap
 */
template <void (*F)(FILE*, void*)>
class FirstFunctor {
public:
    static void call(FILE* src, void* dst) {
        F(src, dst);
    }
};


#endif //MIPT_METAPROG_FUNCTOR_H
