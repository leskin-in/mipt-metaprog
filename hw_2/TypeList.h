#ifndef MIPT_METAPROG_TYPELIST_H
#define MIPT_METAPROG_TYPELIST_H

#include <glob.h>

#include "TypeNull.h"


/**
 * Type list (node)
 */
template <class H, class T>
class TypeList {
public:
    typedef H Head;
    typedef T Tail;
};


/* Length of a TypeList */

template <class Type>
struct TL_Length {
    enum {
        Result = 0
    };
};

template<class H, class T>
struct TL_Length<TypeList<H, T> > {
    enum {
        Result = 1 + TL_Length<T>::Result
    };
};


/* Type by index from TypeList */

template <class TypeList, unsigned int index, typename TypeDefault=TypeNull>
struct TL_GetTypeAt {
    typedef TypeDefault Result;
};

template <class H, class T, typename TypeDefault>
struct TL_GetTypeAt<TypeList<H, T>, 0, TypeDefault> {
    typedef H Result;
};

template <class H, class T, unsigned int index, typename TypeDefault>
struct TL_GetTypeAt<TypeList<H, T>, index, TypeDefault> {
    typedef typename TL_GetTypeAt<T, index - 1, TypeDefault>::Result Result;
};


/* Slice by index */

template <class TypeList, unsigned int index, typename TypeDefault=TypeNull>
struct TL_Slice {
    typedef TypeDefault Result;
};

template <class H, class T, typename TypeDefault>
struct TL_Slice<TypeList<H, T>, 0, TypeDefault> {
    typedef TypeList<H, T> Result;
};

template <class H, class T, unsigned int index, typename TypeDefault>
struct TL_Slice<TypeList<H, T>, index, TypeDefault> {
    typedef typename TL_Slice<T, index - 1, TypeDefault>::Result Result;
};


/* sizeof() of all elements in TypeList */

template <class TypeList>
struct TL_Sizeof;

template <class H, class T>
struct TL_Sizeof<TypeList<H, T> > {
    static const size_t result = sizeof(H) + TL_Sizeof<T>::result;
};

template <>
struct TL_Sizeof<TypeNull> {
    static const size_t result = 0;
};


#endif //MIPT_METAPROG_TYPELIST_H
