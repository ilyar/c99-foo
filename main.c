#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float *w;
    float *x;
    float *b;
    float *h;
    float *o;
    int bSize;
    int wSize;
    int inSize;
    int hSize;
    int outSize;
}
        Foo;

void xtprint(const float *arr, const int size) {
    for (int i = 0; i < size; i++)
        printf("%.18f ", arr[i]);
    printf("\n");
}


static float frand() {
    return rand() / (float) RAND_MAX;
}

static void shuffle(const Foo t) {
    for (int i = 0; i < t.wSize; i++) {
        t.w[i] = frand() - 0.5f;
    }

    for (int i = 0; i < t.bSize; i++) {
        t.b[i] = frand() - 0.5f;
    }
}

Foo fBuild(const int inSize, const int outSize, const int hSize, const int bSize) {
    Foo f;
    f.bSize = bSize;
    f.wSize = hSize * (inSize + outSize);
    f.w = (float *) calloc(f.wSize, sizeof(*f.w));
    f.x = f.w + hSize * inSize;
    f.b = (float *) calloc(f.bSize, sizeof(*f.b));
    f.h = (float *) calloc(hSize, sizeof(*f.h));
    f.o = (float *) calloc(outSize, sizeof(*f.o));
    f.inSize = inSize;
    f.hSize = hSize;
    f.outSize = outSize;
    shuffle(f);
    return f;
}

int main() {
    srand(0);
    const Foo f = fBuild(256, 10, 28, 2);

    printf("Foo:w\n");
    xtprint(f.w, f.wSize);
    printf("Foo:b\n");
    xtprint(f.b, f.bSize);
    printf("Foo:x\n");
    xtprint(f.x, f.wSize - f.hSize * f.inSize);
    return 0;
}