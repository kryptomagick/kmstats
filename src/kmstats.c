#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include "kmstats_common.c"
#include "kmstats_display.c"
#include "kmstats_tests.c"

void kmstatsUsage() {
    printf("KryptoMagick Stats v0.1\n\n");
    printf("usage: kmstats <filename>\n");
}

/* KryptoMagick Stats by Karl Zander */
// Inteneded to give statistical insight into the given dataset

int main(int argc, char *argv[]) {
    if (argc < 2) {
        kmstatsUsage();
        exit(1);
    }
    if (access(argv[1], F_OK) == -1 ) {
        printf("%s not found\n", argv[1]);
        exit(1);
    }
    char *filename = argv[1];
    FILE *f;
    f = fopen(filename, "r");
    fseek(f, 0, SEEK_END);
    int fsize = ftell(f);
    fseek(f, 0, 0);
    uint8_t dataset[fsize];
    fread(dataset, 1, fsize, f);
    fclose(f);
    struct kmstatsState state;
    kmstatsInit(&state);
    countAll(&state, dataset, fsize);
    printBanner(&state);
    printAllCounts(&state);
    printIC(&state);
    printEntropy(&state);
    printMean(&state);
    printChi(&state);
    printSerial(&state);
    printPr(&state);
    printPDF(&state);
    runAllTests(&state, dataset, fsize);
}
