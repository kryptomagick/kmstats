struct kmstatsState {
    float e;
    float ic;
    float mean;
    double chi;
    double serial;
    float pi;
    int count[256];
};

void kmstatsInit(struct kmstatsState *state) {
    memset(state->count, 0, 256*(sizeof(int)));
    state->e = 0.0;
    state->ic = 0.0;
    state->mean = 256.0;
}

float avgPerGroup(struct kmstatsState *state, uint8_t *in, int inLen, int groupLen) {
    int score = 0;
    int groups = inLen / groupLen;
    float avg = 0.0;
    int c = 0;
    for (int x = 0; x < groups; x++) {
        for (int y = 0; y < groupLen; y++) {
            avg += in[c];
            c += 1;
        }
        avg = avg / groupLen;
    }
    return avg;
}

void countAll(struct kmstatsState *state, uint8_t *in, int inLen) {
   int i;
   double t0;
   double t1;
   double tv;
   uint8_t lag = 16;
   double mean = 127.0;
   for (i = 0; i < inLen; i++) {
       state->count[in[i]] += 1;
       tv = (in[(i-lag) % inLen] * in[i]);
       t0 = (in[(i-lag) % inLen] - (mean * in[(i-lag) % inLen]));
       t1 = (in[i] - (mean * in[i]));
       state->serial += (t0 * t1) / lag;
       
   }
   for (i = 0; i < 256; i++) {
       state->ic += ((state->count[i] / (inLen / 256)) * ((state->count[i] - 1) / (inLen / 256)));
       state->mean += state->count[i];
       state->e += state->count[i] / 256.0;
       state->chi += (state->count[i] * state->count[i]);
   }
   state->ic = (256.0 * state->ic) / inLen;
   state->mean = (inLen / state->mean) * 127.5;
   state->e = 8.0 - (8.0 / state->e);
   state->chi = (inLen / state->chi);
   state->serial = 1 - (state->serial / inLen / (256 * 256)) / 256;
}
