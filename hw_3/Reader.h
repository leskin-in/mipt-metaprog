#ifndef MIPT_METAPROG_READER_H
#define MIPT_METAPROG_READER_H

#include <stdio.h>
#include <stdlib.h>

#include "TypeList.h"
#include "ProcessorDecompression.h"
#include "ProcessorAdvancedDecompression.h"


/* Base class */

template<class TypesTL, class CompressedTL=TypeNull, class DecompressorsTL=TypeNull>
class Reader;



/* End recursion */

template<>
class Reader<TypeNull, TypeNull, TypeNull>
{
public:
    static void readNextElem(FILE *file, void* dst) {}
};



/* No decompression */

template<
        class TypeH, class TypeT
>
class Reader<TypeList<TypeH, TypeT>, TypeNull, TypeNull>
{
public:
    /**
     * Read elements from file, decompress them and store into dst
     *
     * @param file descriptor of an already opened (in binary read mode) file
     * @param dst
     */
    static void readNextElem(FILE *file, void* dst) {
        // Read current element
        fread(dst, sizeof(TypeH), 1, file);
        dst = (void*)(((TypeH*)dst) + 1);
        // Call next Reader
        Reader<TypeT, TypeNull, TypeNull>::readNextElem(file, dst);
    }

    /**
     * Read next line from file
     *
     * @param file descriptor of an ALREADY OPENED (in binary read mode) file
     * @return pointer pointer to malloc'ed memory with line content
     * @note The caller's responsibility is to clean up allocated memory
     */
    void* readNextLine(FILE *file) {
        void* result = malloc(TL_Sizeof<TypeList<TypeH, TypeT> >::result);
        readNextElem(file, result);
        return result;
    }
};



/* List of decompression functions (functors) */

template<
        class TypeH, class TypeT,
        class CompressedH, class CompressedT,
        class DecompressorsListH, class DecompressorsListT, class DecompressorT
>
class Reader<
        TypeList<TypeH, TypeT>,
        TypeList<CompressedH, CompressedT>,
        TypeList<TypeList<DecompressorsListH, DecompressorsListT>, DecompressorT>
>
{
public:
    /**
     * Read elements from file, decompress them and store into dst
     *
     * @param file descriptor of an already opened (in binary read mode) file
     * @param dst
     */
    static void readNextElem(FILE *file, void* dst) {
        // Read current element
        ProcessorAdvancedDecompression<CompressedH, TypeList<DecompressorsListH, DecompressorsListT> >::decompress(file, dst);
        dst = (void*)(((TypeH*)dst) + 1);
        // Call next Reader
        Reader<TypeT, CompressedT, DecompressorT>::readNextElem(file, dst);
    }

    /**
     * Read next line from file
     *
     * @param file descriptor of an ALREADY OPENED (in binary read mode) file
     * @return pointer pointer to malloc'ed memory with line content
     * @note The caller's responsibility is to clean up allocated memory
     */
    void* readNextLine(FILE *file) {
        void* result = malloc(TL_Sizeof<TypeList<TypeH, TypeT> >::result);
        readNextElem(file, result);
        return result;
    }
};


#endif //MIPT_METAPROG_READER_H
