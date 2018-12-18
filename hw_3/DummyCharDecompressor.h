#ifndef MIPT_METAPROG_DUMMYCHARDECOMPRESSOR_H
#define MIPT_METAPROG_DUMMYCHARDECOMPRESSOR_H

#include <stdio.h>


/**
 * A sample decompressor (for char elements)
 *
 * All Decompressor classes must have compatible signature
 */
class DummyCharDecompressor {
public:
    static void decompress(FILE* src, void* dst) {
        fread(dst, 1, 1, src);
    }
};


#endif //MIPT_METAPROG_DUMMYCHARDECOMPRESSOR_H
