#ifndef MIPT_METAPROG_DECOMPRESSOR_H
#define MIPT_METAPROG_DECOMPRESSOR_H

#include <stdlib.h>
#include <stdio.h>

#include "NoneType.h"


template<class Compressed, class Decompressor>
class ProcessorDecompression;


/**
 * Construct a decompression processor that invokes decompress() function of compressed element
 *
 * @tparam Compressed a compressed element.
 * decompress() must be a member function with signature
 * <any_return_type> .decompress(void* destination);
 */
template<class Compressed>
class ProcessorDecompression<Compressed, NoneType>
{
public:
    /**
     * Decompress a given element src (of type Compressed) into dst
     */
    static void decompress(FILE* file, void* dst) {
        void* compressed = malloc(sizeof(Compressed));
        fread(compressed, sizeof(Compressed), 1, file);
        ((Compressed)compressed).decompress(dst);
        free(compressed);
    }
};


/**
 * Construct a decompression processor that invokes decompress() function of a decompressor
 *
 * @tparam Decompressor a decompressor. decompress() must be a static function with signature
 * <any_return_type> .decompress(const void* src, void* destination);
 */
template<class Decompressor>
class ProcessorDecompression<NoneType, Decompressor>
{
public:
    /**
     * Decompress a given element src into dst using Decompressor::decompress
     */
    static void decompress(FILE* file, void* dst) {
        Decompressor::decompress(file, dst);
    }
};


#endif //MIPT_METAPROG_DECOMPRESSOR_H
