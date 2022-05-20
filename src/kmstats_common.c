struct kmstatsState {
    float e;
    float ic;
    float mean;
    int count[256];
};

void kmstatsInit(struct kmstatsState *state) {
    memset(state->count, 0, 256*(sizeof(int)));
    state->e = 0.0;
    state->ic = 0.0;
    state->mean = 256.0;
}

void avgPerGroup(struct kmstatsState *state, uint8_t *in, uint64_t inLen, int groupLen) {
    int score = 0;
    int groups = inLen / groupLen;
    for (int x = 0; x < groups; x++) {
        for (int y = 0; y < groupLen; y++) {
            score += 1;
        }
    }
}

void countAll(struct kmstatsState *state, uint8_t *in, uint64_t inLen) {
   uint64_t i;
   for (i = 0; i < inLen; i++) {
       state->count[in[i]] += 1;
   }
   for (i = 0; i < 256; i++) {
       state->ic += ((state->count[i] / (inLen / 256)) * ((state->count[i] - 1) / (inLen / 256)));
       state->mean += state->count[i];
       state->e += state->count[i] / 256.0;
   }
   state->ic = (256.0 * state->ic) / inLen;
   state->mean = (inLen / state->mean) * 127.5;
   state->e = 8.0 - (8.0 / state->e);
}
