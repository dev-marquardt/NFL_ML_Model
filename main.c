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

    printf("\nTraining Data: Rows: %d | Cols: %d\n",trainData.numRows, trainData.numCols);
    printf("\nTest Data: Rows: %d | Cols: %d\n",testData.numRows, testData.numCols);
    printf("\nValidation Data: Rows: %d | Cols: %d\n",valData.numRows, valData.numCols);

    // Building the Neural network
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
    double testErrSqu = 0.0;
    int correctTestRuns = 0;

    // loop through rows in the test data (how many input cycsles there is)
    for (int r = 0; r < testData.numRows; r++) {
        // format the inputs to predict with the model
        const float *testInputs = &testData.rawPBPData[r * testData.numCols];
        const float testTarget = testData.rawTargetData[r];

        float prediction = Predict(net, numLayers, testInputs);

        // unNormalize the results

        float unNormalizePrediction = unNormalize(prediction, normFit.targetMean, normFit.targetStdev);
        float unNormalizeTarget = unNormalize(testTarget, normFit.targetMean, normFit.targetStdev);

        // calculate the difference from the predicrtion
        float delatTarget = unNormalizePrediction - unNormalizeTarget;
        testErrSqu += (double)(delatTarget * delatTarget);


        // model prediction and target are a floats, need to convery to binary
        int predictionBinary = 0;
        if (unNormalizePrediction >= 0.5f) {
            predictionBinary = 1;
        }
        int targetBinary = 0;
        if (unNormalizeTarget >= 0.5f) {
            targetBinary = 1;
        }

        // check if the binary prediction vs target are the same
        // if so add one to correct test runs to get some accuracy ratings
        if (predictionBinary == targetBinary) {
            correctTestRuns++;
        }
    }

    // get the MSE for the test runs
        double testMSE = testErrSqu / (double)testData.numRows;

        // get the test accuracy
        double testAcc = ((double)correctTestRuns / (double)testData.numRows) * 100.0;

        printf("\n2026 Test | MSE: %.5f | Accuracy: %.2f%%\n", testMSE, testAcc);

    // Clean
    freeLayer(net, numLayers);
    freeDataset(&trainData);
    freeDataset(&testData);
    freeDataset(&valData);
    freeNormilizationFit(&normFit);

    return 0;
}
