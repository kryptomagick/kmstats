void printBanner(struct kmstatsState *state) {
    printf("kmstats - KryptoMagick Stats\n");
    printf("byte value: occurrence\n");
}

void printAllCounts(struct kmstatsState *state) {
    for (int i = 0; i < 256; i++) {
        printf("%d: %d\n", i, state->count[i]);
    }
}

void printIC(struct kmstatsState *state) {
    printf("Index of Coincidence: %f\n", state->ic);
}

void printEntropy(struct kmstatsState *state) {
    printf("Entropy per byte: %f\n", state->e);
}

void printMean(struct kmstatsState *state) {
    printf("Arithmetic Mean: %f\n", state->mean);
}
