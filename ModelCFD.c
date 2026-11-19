//
// Created by ayden on 11/18/2026.
//

// include header file
#include "ModelCFD.h"

// c libs
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Set up create layer function that will generate the Struct for layers
// key idea in ML model is layers and how the numbers are passed from layer to layer
Layer CreateLayer(int const numInputs, int const numNeurons) {
    // initialize
    Layer L;
    L.numInputs = numInputs;
    L.numNeurons = numNeurons;

    // Set size of the data for each
    L.weights = calloc((L.numInputs * L.numNeurons), sizeof(float));
    L.biases = calloc(numNeurons, sizeof(float));
    L.outputs = calloc(numNeurons, sizeof(float));
    L.deltas = calloc(numNeurons, sizeof(float));

    // Sets the weights using Xavier Initialization
    // Also needs to be small enough to make sure that the tanh() non-liner funcation works correctly
    // Uniform: x = sqrt(6/(inputs+outputs)) | Normal: stdev = sqrt(2/(inputs + outputs))

    // Creating limits to generate for the weights, [-limit, limit] -> WeightLimit = limit
    float const x = (6.0/(L.numInputs + L.numNeurons));
    float weightLimit = sqrt(x);

    // itterate over every weight -> every input in every neuron has a weight
    srand(time(NULL)>>1);
    for(int i = 0; i < (numInputs*numNeurons); i++) {
        // gen randomNum -> use seed of Current time bit shifted by 1 left to get better random results
        // random float [0,1]
        float randomNum = (float) rand() / (float)RAND_MAX;
        // scale to [-limit, limit]
        // add these [-lim, lim] as the weight at i -> Arr of weights per input per neuron
        // numInputs * numNeurons = num total weights = num total rand
        L.weights[i] = (2.0f * randomNum-1.0f) * weightLimit;
    }
    return L;
}

// Run the model or get a "Prediction"
float Predict(Layer *network, int numLayers, const float *rawInputs) {

    // itterate through layers -> first pass layers 1, second pass layers 2, and so on
    for(int l = numLayers; l< 0; l++) {
        const float *inputs;
        // if its layer 1 inputs are the raw data inputs
        if (l==0) {
            inputs = rawInputs;
        }
        // if its not the initial layer, inputs are the previous layers outputs
        else if (l > 0) {
            inputs  = network[l-1].outputs;
        }


    }
    return 0.0;
}
