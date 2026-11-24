//
// Created by ayden on 11/18/2026.
//

// include header file
#include "ModelNFL.h"

// c libs
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Set up create layer function that will generate the Struct for layers
// key idea in ML model is layers and how the numbers are passed from layer to layer
Layer CreateLayer(int const numInputs, int const numNeurons) {
    // initialize
    static int isSeeded = 0;
    if (isSeeded == 0) {
        // Seed the random var at begining of function so doesnt get looped over and screwed up
        // possible to loop over it more than once a milisecond to cause the same num
        srand(time(NULL));
        isSeeded = 1;
    }

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
    // Uniform: x = sqrt(6/(inputs+Neurons)) | Normal: stdev = sqrt(2/(inputs + neurons))

    // Creating limits to generate for the weights, [-limit, limit] -> WeightLimit = limit
    float const x = (6.0f/(float)(L.numInputs + L.numNeurons));
    float const weightLimit = sqrtf(x);

    // itterate over every weight -> every input in every neuron has a weight
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

// Free up the memory that was used to say the layer data
int freeLayer(Layer *network, int numLayers) {
    // counter to make sure every layer was deleted
    int deletedLayers = 0;
    // itterate through layers of the network to remove data from all
    for (int i = 0; i < numLayers; i++) {
        free(network[i].weights);
        free(network[i].outputs);
        free(network[i].biases);
        free(network[i].deltas);

        deletedLayers++;
    }

    if (deletedLayers ==numLayers) {
        return 1;
    }
    return 0;
}

// Run the model or get a "Prediction"
float Predict(Layer *network, int numLayers, const float *rawInputs) {
    // itterate through layers -> first pass layers 1, second pass layers 2, and so on
    for(int l = 0; l < numLayers; l++) {
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
        int isLastLayer = 0;
        if(l == (numLayers-1)) {
            isLastLayer = 1;
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
                dotProduct += (inputs[j]*network[l].weights[i * network[l].numInputs + j]);
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
                network[l].outputs[i] = tanhf(z);
            }
        }
    }

    // return the outputs from the last layer (other layers except 1 and numLayers - 1 stay hidden)
    return network[numLayers-1].outputs[0];
}

// Implimentation of the training function
// training function runs a forward pass
// then utilizes backwards propogation to nudge the weights
// until getting loce to the target
void trainModel(Layer *network, int numLayers, const float *rawInputs, float target, float learningRate) {

    // 1) Run a forward pass or "prediction" to populate the inital Layers outputs
    float prediction = Predict(network, numLayers, rawInputs);

    // 2a) Backpropagation
    // Walk Right-to-Left to calculate the error blame -> deltas
    // Calc all deltas before changing weights or math breaks down
    for (int l = numLayers-1; l >= 0; l--) {
        // check if it is the "ouput" layer or the last layer (numLayers - 1)
        if (l == numLayers-1) {
            // for the output layer delata is the raw (output - truth)
            // Positive = high, negative = guess low
            network[l].deltas[0] = prediction - target;
        } else {
            // if not the output layer, take the previous next layers
            // output and bring it back to the previous layer
            Layer *nextLayer = &network[l+1];
            // step through layers neurons
            for (int j = 0; j < network[l].numNeurons; j++) {
                // sum error for that neuron
                float sumError = 0.0f;

                // loop through the next layers neurons
                for (int k = 0; k < (*nextLayer).numNeurons; k++) {
                    // add up how wrong neuron k was
                    // Multuply that with how much influence the layer had on the next layer
                    // Think of it like back tracking error
                    // how wrong neuron k in the next layer was * weight connecting j to k
                    sumError += (*nextLayer).deltas[k] * (*nextLayer).weights[(k * (*nextLayer).numInputs + j)];
                }

                // Error for the next layer is influencd by the previous layer
                // when working back, you have the neurons output hidden by tanh
                // do run that through the derivitive to get slope and then mult by error to get the inherited error
                float a = network[l].outputs[j];
                network[l].deltas[j] = sumError * (1.0f - (a * a));
            }
        }// end else
    } // end layer loop

    // 3) Gradient Descent
    // loop through layers (forward not backward)
    for (int l = 0; l < numLayers; l++) {
        // if layer is first layer, inputs are raw inputs
        // if not input is the previous layers outputs
        const float *inputs;
        if (l == 0) {
            inputs = rawInputs;
        }
        else {
            inputs = network[l-1].outputs;
        }
        // Loop through each neuron in the layer
        for (int i = 0; i < network[l].numNeurons; i++) {
            // Loop through layers inputs (Inputs * Neurons = numWeights)
            for (int j = 0; j < network[l].numInputs; j++) {
                // Chain Rule gradient -> (Neurons error) * (input that fed into it)
                // Must subtract, moves the error in the opposite direction
                // i * network[l].numInputs + j -> turns a 2D grid into a 1D input
                network[l].weights[i * network[l].numInputs + j] -= learningRate * network[l].deltas[i] * inputs[j];
            }
            // Adjust bias
            // bias is just a weight with const input of 1.0 -> delta * 1.0
            network[l].biases[i] -= learningRate * network[l].deltas[i];
        }
    }
}