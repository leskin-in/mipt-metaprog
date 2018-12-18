#ifndef MIPT_METAPROG_PROCESSORADVANCEDDECOMPRESSION_H
#define MIPT_METAPROG_PROCESSORADVANCEDDECOMPRESSION_H

#include <stdio.h>
#include <stdlib.h>

#include "TypeList.h"
#include "NoneType.h"


template<class Compressed, class TypeList>
class ProcessorAdvancedDecompression;


/**
 * End iteration
 */
template<>
class ProcessorAdvancedDecompression<TypeNull, TypeNull>
{
public:
    static void decompress(void* buff) {}
};


/**
 * One step of iteration over decompression functors
 */
template<class Functor, class TLElem>
class ProcessorAdvancedDecompression<TypeNull, TypeList<Functor, TLElem> >
{
public:
    static void decompress(void* buff) {
        Functor::call(buff);
        ProcessorAdvancedDecompression<TypeNull, TLElem>::decompress(buff);
    }
};


/**
 * Entry point: no type Compressed
 */
template<class Functor, class TLElem>
class ProcessorAdvancedDecompression<NoneType, TypeList<Functor, TLElem> >
{
public:
    static void decompress(FILE* file, void* dst) {
        // The first functor reads data from file, and its signature is different
        // XXX: The signature of that functor could be checked, but requires careful template instantiation
        Functor::call(file, dst);
        ProcessorAdvancedDecompression<TypeNull, TLElem>::decompress(dst);
    }
};


/**
 * Entry point: with type Compressed
 */
template<class Compressed, class Functor, class TLElem>
class ProcessorAdvancedDecompression<Compressed, TypeList<Functor, TLElem> >
{
public:
    static void decompress(FILE* file, void* dst) {
        // Decompress file using function in type Compressed
        void* compressed = malloc(sizeof(Compressed));
        fread(compressed, sizeof(Compressed), 1, file);
        ((Compressed)compressed).decompress(dst);
        free(compressed);
        // Decompress file using functors. Note the first one does not read data from file
        ProcessorAdvancedDecompression<TypeNull, TypeList<Functor, TLElem> >::decompress(dst);
    }
};


#endif //MIPT_METAPROG_PROCESSORADVANCEDDECOMPRESSION_H
