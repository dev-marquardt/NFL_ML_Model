#include "ModelNFL.h"
#include "RawDataInput.h"

#include <stdio.h>

int main(void) {

    // 1) Load clean data from CSV file (refer to python scripts)
    const char *trainInputPath = "../PythonScripts_DataClean/trainInput.csv";
    const char *trainTargetPath = "../PythonScripts_DataClean/trainTarget.csv";

    const char *testInputPath = "../PythonScripts_DataClean/testInput.csv";
    const char *testTargetPath = "../PythonScripts_DataClean/testTarget.csv";

    const char *valInputPath = "../PythonScripts_DataClean/valInput.csv";
    const char *valTargetPath = "../PythonScripts_DataClean/valTarget.csv";

    printf("Loading Dataset\n\n");
    Dataset trainData = loadData(trainInputPath, trainTargetPath);
    Dataset testData = loadData(testInputPath, testTargetPath);
    Dataset valData = loadData(valInputPath, valTargetPath);

    printf("\nTraining Data: Rows: %d | Cols: %d",trainData.numRows, trainData.numCols);
    printf("\nTest Data: Rows: %d | Cols: %d",testData.numRows, testData.numCols);
    printf("\nValidation Data: Rows: %d | Cols: %d",valData.numRows, valData.numCols);

    // Building the Neural network
    int numLayers = 3;


    // Clean
    freeDataset(&trainData);
    freeDataset(&testData);
    freeDataset(&valData);

    return 0;
}
