#include <iostream>

#include "Reader.h"
#include "TypeList.h"
#include "DummyCharDecompressor.h"
#include "NoneType.h"
#include "DecompressionFunctors.h"

#include <stdio.h>


using namespace std;


void rf(FILE* file, void* dst) {
    fread(dst, 1, 1, file);
}

void rotate(void* buff) {
    ((char*)buff)[0] += 1;
}


int main() {
    cout << "Compilation successful" << endl;

    using TL_Types = TypeList<char, TypeList<char, TypeNull> >;
    using TL_Compresseds = TypeList<NoneType, TypeList<NoneType, TypeNull> >;
    using TL_Decompressors = TypeList<
            TypeList<
                    FirstFunctor<rf>, TypeList<OrdinaryFunctor<rotate>, TypeNull>
            >,
            TypeList<
                    TypeList<
                            FirstFunctor<rf>, TypeList<OrdinaryFunctor<rotate>, TypeNull>
                    >,
                    TypeNull
            >
    >;

    FILE* file = fopen("in", "rb");

    Reader<TL_Types, TL_Compresseds, TL_Decompressors> reader;
    char* chars = (char*)reader.readNextLine(file);
    printf("Chars are: %c%c\n", chars[0], chars[1]);

    free(chars);
    fclose(file);

    return 0;
}
