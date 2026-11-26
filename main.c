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
    // set up datasets for injection into model
    Dataset trainData = loadData(trainInputPath, trainTargetPath);
    Dataset testData = loadData(testInputPath, testTargetPath);
    Dataset valData = loadData(valInputPath, valTargetPath);

    // normolize the datasets
    NormilizationFit normFit = normalizeFit(&trainData, &valData);
    applyNormalization(&trainData, &normFit);
    applyNormalization(&valData, &normFit);
    applyNormalization(&testData, &normFit);

    // Validate that the data was imported correctly -> problem with data breaks the model
    printf("\nTraining Data: Rows: %d | Cols: %d\n",trainData.numRows, trainData.numCols);
    printf("\nTest Data: Rows: %d | Cols: %d\n",testData.numRows, testData.numCols);
    printf("\nValidation Data: Rows: %d | Cols: %d\n",valData.numRows, valData.numCols);

    // Building the Neural network
    // network arr (Layer arr) is the model itself
    const int numLayers = 3;
    Layer net[3];
    net[0] = createLayer(trainData.numCols, 64);
    net[1] = createLayer(64, 32);
    net[2] = createLayer(32, 1);

    // Training the network
    const int numEpochs = 3;
    const float learningRate = 0.01f;
    trainNetwork(net, numLayers, numEpochs, &trainData, learningRate);

    // Fine tuning on modern plays (2023-2025)
    const int tuneEpochs = 2;
    const float tuneLearningRate = 0.001f;
    trainNetwork(net, numLayers, tuneEpochs, &valData, tuneLearningRate);

    // Test Model -> Test data loaded and is from 2026 (this curr year)
    benchmarkNetwork(net, numLayers, &testData, &normFit);

    // Clean
    freeLayer(net, numLayers);
    freeDataset(&trainData);
    freeDataset(&testData);
    freeDataset(&valData);
    freeNormilizationFit(&normFit);

    return 0;
}
