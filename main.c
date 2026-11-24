#include "ModelNFL.h"
#include "RawDataInput.h"

#include <stdio.h>

int main(void) {

    // 1) Load clean data from CSV file (refer to python scripts)
    const char *inputPath = "../PythonScripts_DataClean/pbpCleanInput.csv";
    const char *targetPath = "../PythonScripts_DataClean/pbpCleanTarget.csv";

    printf("Loading Dataset\n\n");
    Dataset data = loadData(inputPath, targetPath);
    printf("Rows: %d | Cols: %d",data.numRows, data.numCols);

    return 0;
}
