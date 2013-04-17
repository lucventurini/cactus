/*
 * Copyright (C) 2009-2011 by Benedict Paten (benedictpaten@gmail.com)
 *
 * Released under the MIT license, see LICENSE.txt
 */

/*
 * MERGE POTENTIALLY OVERLAPPING FASTA FILES GENERATED BY
 * cactus_batch_chunkSequences INTO A SINGLE FASTA FILE
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <float.h>
#include <ctype.h>
#include <errno.h>

#include "bioioC.h"
#include "commonC.h"

static FILE* outputFile = NULL;

/* Read fasta sequence from file into the "cur" variables.
 * Then merge into the outputFile
 */
static void readFastaCallback(const char *fastaHeader, const char *sequence, int64_t length) {
    stList *attributes = fastaDecodeHeader(fastaHeader);
    int64_t offset;
    int64_t i = sscanf(stList_peek(attributes), "%" PRIi64 "", &offset);
    (void) i;
    assert(i == 1);
    assert(offset >= 0);
    if (offset == 0) {
        free(stList_pop(attributes));
        char *cA = fastaEncodeHeader(attributes);
        fprintf(outputFile, ">%s\n", cA);
        free(cA);
    }
    stList_destruct(attributes);
    fprintf(outputFile, "%s\n", sequence);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr,
                "USAGE: %s <output> <input>xN\n \
		        <output>: target fasta file\n \
				<input>xN: list of chunk files\n \\n\n",
                argv[0]);
        return -1;
    }

    /* the + is so we can use fseek() */
    outputFile = fopen(argv[1], "w+");

    if (!outputFile) {
        fprintf(stderr, "ERROR: cannot open %s for writing\n", argv[1]);
        return -1;
    }

    for (int64_t chunkFileIndex = 2; chunkFileIndex < argc; chunkFileIndex++) {
        FILE* chunkFile = fopen(argv[chunkFileIndex], "r");
        fastaReadToFunction(chunkFile, readFastaCallback);
        fclose(chunkFile);
    }

    fclose(outputFile);
    return 0;
}
