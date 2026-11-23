//
// Created by Ayden Marquardt on 11/19/26.
//

#import "RawDataInput.h"
#include <stdio.h>

Dataset loadData(const char *inputFilePath, const char *targetFilePath) {
    Dataset data;

    FILE *inputFile = fopen(inputFilePath, "r");
    FILE *targetFile = fopen(targetFilePath, "r");

    int currChar;
    int numInputFeatures;
    // loop through first line of data file and count the num of , to determine num inputs
    // Basically counts the number of columns
    while ((currChar = fgetc(inputFile)) != EOF && currChar != '\n') {
        // 0x2C binary code for ','
        if (currChar == 0x2C) {
            numInputFeatures++;
        }
    }

    // loop through rest of file to find data rows
    int numInputRows;
    int prevCharr = 0x0A; // Hex code for '\n'
    currChar = 0; // reset the currChar data point
    while ((currChar = fgetc(inputFile)) != EOF) {
        // if currChar is \n (End of line) and the prev char was not end of line, add a row
        if (currChar == 0x2c && prevCharr != 0x0A) {
            numInputRows++;
        }
        // save current char as prev for next run
        prevCharr = currChar;
    }
    // catch final row incase last line doesnt end in \n
    if (prevCharr != 0x0A) {
        numInputRows++;
    }



}
