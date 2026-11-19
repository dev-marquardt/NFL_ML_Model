#include "ModelCFD.h"

#include <stdio.h>

int main(void) {
    Layer l = CreateLayer(5, 5);

    for(int i = 0; i < 25; i++) {
        printf("\n%f ", l.weights[i]);
    }

    return 0;
}
