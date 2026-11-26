//
// Created by ayden on 11/18/2026.
//

#ifndef CFD_ML_MODELCFD_H
#define CFD_ML_MODELCFD_H

#include "RawDataInput.h"

typedef struct {
    // params for the model
    int numInputs;
    int numNeurons;

    // nums used in the model itself
    float *weights;
    float *biases;

    // Training specific usage, row specific usage
    float *outputs;
    float *deltas;
} Layer;

// Function to create a layer of weights and neurons
Layer createLayer(int numInputs, int numNeurons);

// Function to clear up the memory used by the network
int freeLayer(Layer *network, int numLayers);

// Layer pointer to array -> this is the network, array of layers
float Predict(Layer *network, int numLayers, const float *rawInputs);

// Function to train the model
void trainModel(Layer *network, int numLayers, const float *rawInputs, float target, float learningRate);

// function to train the network
void trainNetwork(Layer *network, int numLayers, int numEpochs, Dataset *data, float learningRate);

//
void benchmarkNetwork(Layer *network, int numLayers, Dataset *data, NormilizationFit *normFit);

#endif //CFD_ML_MODELCFD_H
