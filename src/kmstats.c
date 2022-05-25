#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "kmstats_common.c"
#include "kmstats_display.c"
#include "kmstats_tests.c"

/* KryptoMagick Stats by Karl Zander */
// Inteneded to give statistical insight into the given dataset

int main(int argc, char *argv[]) {
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
    runAllTests(&state, dataset, fsize);
}
