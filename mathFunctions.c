//
// Created by Ayden Marquardt on 11/24/26.
//

#include "mathFunctions.h"
#include <math.h>

float mean(float *data, int length) {
    float sum = 0.0f;
    float mean = 0.0f;

    for (int i = 0; i < length; i++) {
        sum += data[i];
    }

    mean = (sum / (float)length);

    return mean;
}

float stdev(float *data, float mean, int length) {
    float stdev = 0.0f;

    for (int i = 0; i < length; i++) {
        stdev += (data[i] - mean) * (data[i] - mean);
    }
    stdev = (stdev / (float)length);
    stdev = sqrt(stdev);

    return stdev;
}

float zScore(float x, float mean, float stdev) {
    float z = 0.0f;

    z = (x - mean) / stdev;

    return z;
}