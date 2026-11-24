//
// Created by Ayden Marquardt on 11/19/26.
//

#include "RawDataInput.h"
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

Dataset loadData(const char *inputFilePath, const char *targetFilePath) {
    Dataset data;

    FILE *inputFile = fopen(inputFilePath, "r");
    FILE *targetFile = fopen(targetFilePath, "r");

    int currChar;
    int numInputColunms = 1; // Start at 1 becasue it counts commas. Last element doesnt have an ending comma
    // loop through first line of data file and count the num of , to determine num inputs
    // Basically counts the number of columns
    while ((currChar = fgetc(inputFile)) != EOF && currChar != '\n') {
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
        if (currChar == 0x0A && prevCharr != 0x0D) {
            numInputRows++;
        }
        // save current char as prev for next run
        prevCharr = currChar;
    }
    // catch final row incase last line doesnt end in \n
    if (prevCharr != 0x0A) {
        numInputRows++;
    }

    // Set memory foot-print
    int totalInputs = numInputColunms * numInputRows;

    data.numRows = numInputRows;
    data.numCols = numInputColunms;
    data.rawPBPData = calloc(totalInputs, sizeof(float));
    data.rawTargetData = calloc(numInputRows, sizeof(float));

    // Rewind sets cursor back to the begining of the file
    rewind(inputFile);
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
