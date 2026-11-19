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

        // Check if layer is the lasy layer
        int isLastLayer;
        if(l == (numLayers-1)) {
            isLastLayer =1;
        }
        // loop through each neuron in the layer
        for(int i = 0; i < network[l].numNeurons; i++) {
            // pull in that neurons bias -> pull the layer (l) then pull that neurons bias (i)
            float bias = network[l].biases[i];

            // take dot product of weights and inputs (or last layer outputs)
            // Ex: (a,b,c), (d,e,f) -> linear regression equ = (ad + be+ cf) + b
            // dot procut of vectors = (ad) + (be) + (cf)
            // they happen to be the same with how this software is structured
            float dotProduct = 0.0;
            for(int j = 0; j < network[l].numInputs; j++) {
                dotProduct += (inputs[j]*network[l].weights[j]);
            }

            // linear regression output
            float z = dotProduct + bias;

            // if its last layer set that layers output to the linear regresion
            if (isLastLayer) {
                network[l].outputs[i] = z;
            }
            // if its any other layer must turn the linear output into a non-linear output
            // using tanh() to turn each input into a [-1,1] to pass into the next layer
            // if you pass the linear output into the next layers linear equ it will fall apart
            else {
                // tanhf() is tanh() with float output
                network[l].outputs[l] = tanhf(z);
            }
        }
    }

    // return the outputs from the last layer (other layers except 1 and numLayers - 1 stay hidden)
    return network[numLayers-1].outputs[0];
}
