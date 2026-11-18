//
// Created by ayden on 11/18/2026.
//

#include "ModelCFD.h"

#include <stdlib.h>

Layer CreateLayer(int const numInputs, int const numNeurons) {
    // initialize
    Layer L;
    L.numInputs = numInputs;
    L.numNeurons = numNeurons;

    // Set size of the data for each
    L.weights = calloc(numInputs*numNeurons, sizeof(float));
    L.biases = calloc(numNeurons, sizeof(float));
    L.outputs = calloc(numNeurons, sizeof(float));
    L.deltas = calloc(numNeurons, sizeof(float));

    // Sets the weights using Xavier Initialization
    // Also needs to be small enough to make sure that the tanh() non-liner funcation works correctly
    // Uniform: x = sqrt(6/(inputs+outputs)) | Normal: stdev = sqrt(2/(inputs + outputs))


    return L;
}

