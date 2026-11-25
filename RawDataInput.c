//
// Created by Ayden Marquardt on 11/19/26.
//

#include "RawDataInput.h"
#include "mathFunctions.h"

#include <stdio.h>
#include <stdlib.h>

void freeDataset(Dataset *dataset) {
    free((*dataset).rawPBPData);
    free((*dataset).rawTargetData);
    (*dataset).rawPBPData = NULL;
    (*dataset).rawTargetData = NULL;
    (*dataset).numRows = 0;
    (*dataset).numCols = 0;
}

void freeNormilizationFit(NormilizationFit *normFit) {
    free((*normFit).trainingMean);
    free((*normFit).trainingStdev);
    (*normFit).trainingMean = NULL;
    (*normFit).trainingStdev = NULL;

    (*normFit).numDataCols = 0;
    (*normFit).numRows = 0;
    (*normFit).targetMean = 0.0f;
    (*normFit).targetStdev = 0.0f;
}

Dataset loadData(const char *inputFilePath, const char *targetFilePath) {
    Dataset data;

    FILE *inputFile = fopen(inputFilePath, "r");
    FILE *targetFile = fopen(targetFilePath, "r");

    int currChar = 0;
    int numInputColunms = 1; // Start at 1 becasue it counts commas. Last element doesnt have an ending comma
    // loop through first line of data file and count the num of , to determine num inputs
    // Basically counts the number of columns
    while ((currChar = fgetc(inputFile)) != EOF && currChar != 0x0A) {
        // 0x2C binary code for ','
        if (currChar == 0x2C) {
            numInputColunms++;
        }
    }

    // loop through rest of file to find data rows
    int numInputRows = 0;
    int prevCharr = 0x0A; // Hex code for '\n'
    currChar = 0; // reset the currChar data point
    while ((currChar = fgetc(inputFile)) != EOF) {
        // if currChar is \n (End of line) and the prev char was not end of line, add a row
        if (currChar == 0x0A && prevCharr != 0x0A) {
            numInputRows++;
        }
        // save current char as prev for next run
        prevCharr = currChar;
    }
    // catch final row incase last line doesnt end in \n
    if (prevCharr != 0x0A) {
        numInputRows++;
    }

    // Set memory foot-print for dataset struct
    int totalInputs = numInputColunms * numInputRows;

    data.numRows = numInputRows;
    data.numCols = numInputColunms;
    data.rawPBPData = calloc(totalInputs, sizeof(float));
    data.rawTargetData = calloc(numInputRows, sizeof(float));

    // Rewind sets cursor back to the begining of the file
    rewind(inputFile); // -> optimized way to do this check "Effective C" book
    currChar = 0;

    while ((currChar = fgetc(inputFile)) != EOF && currChar != 0x0A) {} // Skip headers for the data file

    for (int i = 0; i < totalInputs; i++) {
        if (fscanf(inputFile, "%f,", &data.rawPBPData[i]) != 1) {
            // Put error logs here
        }
    }

    currChar = 0;
    while ((currChar = fgetc(targetFile)) != EOF && currChar != 0x0A) {} // Skip headers for the data file

    for (int i = 0; i < numInputRows; i++) {
        if (fscanf(targetFile, "%f", &data.rawTargetData[i]) != 1) {
            // Put error logs here
        }
    }

    fclose(inputFile);
    fclose(targetFile);

    return data;
}

NormilizationFit normalizeFit(Dataset *trainingDataset, Dataset *valDataset) {
    NormilizationFit fit;
    fit.numDataCols = (*trainingDataset).numCols;
    fit.numRows = (*trainingDataset).numRows + (*valDataset).numRows;

    fit.trainingMean = calloc(fit.numDataCols, sizeof(float));
    fit.trainingStdev = calloc(fit.numDataCols, sizeof(float));

    float *allData = calloc(fit.numRows * fit.numDataCols, sizeof(float));
    float *allTarget = calloc(fit.numRows, sizeof(float));
    float *dataCol = malloc(fit.numRows * sizeof(float));

    float *rawTrainingData = (*trainingDataset).rawPBPData;
    float *rawTrainingTarget = (*trainingDataset).rawTargetData;

    float *rawTestData = (*valDataset).rawPBPData;
    float *rawTestTarget = (*valDataset).rawTargetData;

    // merging data arrs to have 1 data arr to then get
    //stastical numbers from
    int arr1 = (*trainingDataset).numRows * fit.numDataCols;
    int arr2 = (*valDataset).numRows * fit.numDataCols;

    for (int i = 0; i < arr1; i++) {
        allData[i] = rawTrainingData[i];
    }
    for (int i = 0; i < arr2; i++) {
        allData[arr1 + i] = rawTestData[i];
    }

    // merging target arrs to have 1 target arr to then get
    //stastical numbers from
    arr1 = (*trainingDataset).numRows;
    arr2 = (*valDataset).numRows;

    for (int i = 0; i < arr1; i++) {
        allTarget[i] = rawTrainingTarget[i];
    }
    for (int i = 0; i < arr2; i++) {
        allTarget[arr1 + i] = rawTestTarget[i];
    }

    for (int c = 0; c < fit.numDataCols; c++) {
        for (int r = 0; r < fit.numRows; r++) {
            dataCol[r] = allData[r * fit.numDataCols + c];
        }

        float average = mean(dataCol, fit.numRows);
        float standardDev = stdev(dataCol, average, fit.numRows);

        fit.trainingMean[c] = average;
        fit.trainingStdev[c] = standardDev;
    }

    fit.targetMean = mean(allTarget, fit.numRows);
    fit.targetStdev = stdev(allTarget, fit.targetMean, fit.numRows);

    free(allData);
    free(dataCol);
    free(allTarget);

    return fit;
}

void applyNormalization(Dataset *data, NormilizationFit *normFit) {
    for (int c = 0; c < (*data).numCols; c++) {
        for (int r = 0; r < (*data).numRows; r++) {
            (*data).rawPBPData[r * (*normFit).numDataCols + c] = zScore((*data).rawPBPData[r * (*normFit).numDataCols + c], (*normFit).trainingMean[c], (*normFit).trainingStdev[c]);
        }
    }

    for (int r = 0; r < (*data).numCols; r++) {
        (*data).rawTargetData[r] = zScore((*data).rawTargetData[r], (*normFit).targetMean, (*normFit).targetStdev);
    }
}


