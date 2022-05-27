double expectedEntropy(int inLen) {
    double e = inLen / (log(256) * log(256));
    return e;
}

double expectedMean(int inLen) {
    double m = inLen / (log(256) * log(256));
    return m;
}

void runICTest(struct kmstatsState *state) {
    if (state->ic < 0.1) {
        printf("Pass (IC)\n");
    }
    else {
        printf("Fail (IC)\n");
    }
}

void runEntropyTest(struct kmstatsState *state) {
    if (state->e > 7.96) {
        printf("Pass (Entropy)\n");
    }
    else {
        printf("Fail (Entropy)\n");
    }
}

void runMeanTest(struct kmstatsState *state) {
    if (state->mean > 127.4) {
        printf("Pass (Mean)\n");
    }
    else {
        printf("Fail (Mean)\n");
    }
}

void runSerialTest(struct kmstatsState *state) {
    if (state->serial < 0.1) {
        printf("Pass (Serial)\n");
    }
    else {
        printf("Fail (Serial)\n");
    }
}

void runChiTest(struct kmstatsState *state) {
    if ((state->chi < 255) && (state->chi > 209)) {
        printf("Pass (Chi)\n");
    }
    else {
        printf("Fail (Chi)\n");
    }
}

void runAvgPerGroup(struct kmstatsState *state, uint8_t *in, int inLen, int groupLen) {
    float avg = avgPerGroup(state, in, inLen, groupLen);
    if (avg > 127) {
        printf("Pass (AvgPerGroup %f)\n", avg);
    }
    else {
        printf("Fail (AvgPerGroup %f)\n", avg);
    }
}

void runAllTests(struct kmstatsState *state, uint8_t *in, int inLen) {
    runICTest(state);
    runEntropyTest(state);
    runMeanTest(state);
    runSerialTest(state);
    runChiTest(state);
    runAvgPerGroup(state, in, inLen, 256);
}
