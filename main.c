#include "ModelCFD.h"

#include <stdio.h>

int main(void) {
    Layer l = CreateLayer(5, 5);

    int length = sizeof(l.weights);

    printf("Length = %d\n", length);

    for(int i = 0; i < length; i++) {
        printf("\n%f ", l.weights[i]);
    }

    return 0;
}
