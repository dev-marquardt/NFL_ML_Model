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

// set function for dataset loading
Dataset loadData(const char *inputFilePath, const char *targetFilePath);

void freeDataset(Dataset *dataset);

#endif //CFD_ML_RAWDATAINPUT_H
