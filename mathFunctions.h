//
// Created by Ayden Marquardt on 11/24/26.
//

#ifndef CFD_ML_MATHFUNCTIONS_H
#define CFD_ML_MATHFUNCTIONS_H

float mean(float *data, int length);

float stdev(float *data, float mean, int length);

float zScore(float x, float mean, float stdev);

#endif //CFD_ML_MATHFUNCTIONS_H
