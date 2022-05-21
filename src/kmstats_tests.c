void runICTest(struct kmstatsState *state) {
    if (state->ic < 0.1) {
        printf("Pass (IC)\n");
    }
    else {
        printf("Fail (IC)\n");
    }
}

void runEntropyTest(struct kmstatsState *state) {
    if (state->e > 7.99) {
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
    runAvgPerGroup(state, in, inLen, 256);
}
