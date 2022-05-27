struct kmstatsState {
    double e;
    double ed;
    double ic;
    double mean;
    double chi;
    double pr;
    double pdf;
    double serial;
    double pi;
    double cpi;
    long sum;
    int count[256];
};

void kmstatsInit(struct kmstatsState *state) {
    memset(state->count, 0, 256*(sizeof(int)));
    state->e = 0.0;
    state->ic = 0.0;
    state->mean = 256.0;
    state->pi = 3.14159265359;
    state->cpi = 3.14159265359;
    state->pr = 0.0;
    state->pdf = 0.0;
    state->ed = 0.0;
    state->sum = 0;
}

double avgPerGroup(struct kmstatsState *state, uint8_t *in, int inLen, int groupLen) {
    int score = 0;
    int groups = inLen / groupLen;
    double avg = 0.0;
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
   state->ed = log(inLen) * 256;
   int i;
   double t0;
   double t1;
   double tv;
   uint8_t lag = 16;
   double mean = 127.5;
   double area = (acosl(-1.0L));
   int k = 8;
   for (i = 0; i < inLen; i++) {
       state->count[in[i]] += 1;
       tv = (in[(i-lag) % inLen] * in[i]);
       t0 = (in[(i-lag) % inLen] - (mean * in[(i-lag) % inLen]));
       t1 = (in[i] - (mean * in[i]));
       state->serial += (t0 * t1) / lag;
       state->pr += ((in[i]) * (256 * 0.5)) / (0.5 * 256);
       double a = 0.5 * fabs(in[i]);
       state->chi += ((a * a) * 256) - i;
       state->pdf += (pow((in[i]), ((k / 2) - 1)) * exp(-(in[i] / 2))) / (pow(2, (k / 2)) * (k / 2));
       state->e += (in[i] * log(256));
       state->sum += in[i];
       
   }
   for (i = 0; i < 256; i++) {
       state->ic += ((state->count[i] / (inLen / 256)) * ((state->count[i] - 1) / (inLen / 256)));
       state->mean += state->count[i];
   }
   state->pi = (4 - ((((state->cpi * (state->sum / 2)) / (inLen)) / 256) * state->cpi)) * 2;
   //state->pi = ((state->cpi * ((state->sum / 2) * (state->sum / 2))) / (inLen * inLen) / (256 * 256) / (log(256) * log(256)) / state->cpi) + (log(state->cpi) - 1);
   state->ic = (256.0 * state->ic) / inLen;
   state->mean = (inLen / state->mean) * 127.5;
   state->e = state->e / inLen / log(256) / 8 / 2;
   state->pr = 2 - (127.5 / (state->pr / inLen));
   state->pdf = ((state->pdf / 256) / (log(256) * log(256)));
   state->chi = (state->chi / (inLen * inLen) / log(256));
   state->serial = 1 - (state->serial / inLen / (256 * 256)) / 256;
}
