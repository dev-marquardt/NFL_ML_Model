//
// Created by ayden on 11/18/2026.
//

#ifndef CFD_ML_MODELCFD_H
#define CFD_ML_MODELCFD_H

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

Layer CreateLayer(int numInputs, int numNeurons);

// Layer pointer to array -> this is the network, array of layers
float Predict(Layer *network, int numLayers, const float *rawInputs);


#endif //CFD_ML_MODELCFD_H
