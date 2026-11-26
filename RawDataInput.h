//
// Created by Ayden Marquardt on 11/19/26.
//

#ifndef CFD_ML_RAWDATAINPUT_H
#define CFD_ML_RAWDATAINPUT_H

typedef struct {
    float *rawPBPData; // 1D arr -> numRows * numCols
    float *rawTargetData; // 1D arr or target outputs (success rate)
    int numRows;
    int numCols;
} Dataset;

typedef struct {
    int numDataCols;
    int numRows;
    float *trainingMean;
    float *trainingStdev;
    float targetMean;
    float targetStdev;
} NormilizationFit;

void freeDataset(Dataset *dataset);
void freeNormilizationFit(NormilizationFit *normFit);

// set function for dataset loading
Dataset loadData(const char *inputFilePath, const char *targetFilePath);

NormilizationFit normalizeFit(Dataset *trainingDataset, Dataset *valDataset);

void applyNormalization(Dataset *data, NormilizationFit *normFit);

float unNormalize(float z, float mean, float stdev);

#endif //CFD_ML_RAWDATAINPUT_H
