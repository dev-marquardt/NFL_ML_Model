//
// Created by ayden on 11/18/2026.
//

// include header file
#include "ModelCFD.h"

// c libs
#include <stdlib.h>
#include <math.h>

// Set up create layer function that will generate the Struct for layers
// key idea in ML model is layers and how the numbers are passed from layer to layer
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

    // Creating limits to generate for the weights, [-limit, limit] -> WeightLimit = limit
    float const x = (6.0/(numInputs + numNeurons));
    float weightLimit = sqrt(x);

    // itterate over every weight -> every input in every neuron has a weight
    for(int i = 0; i< numInputs*numNeurons; i++) {
        float rand = 
    }

    return L;
}

