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
float Predict(Layer layer, float *inputs, float *outputs);


#endif //CFD_ML_MODELCFD_H
