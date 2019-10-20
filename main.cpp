#include <iostream>
#include<fstream>

using namespace std;
int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Error: Input file not specified or too many arguments" << endl << "Usage: Program FileName" << endl;
        return -1;
    }
    ifstream fin(argv[1]);
    // Check if file has been opened properly
    if (!fin.is_open()) {
        cout << "Error: input file cannot be opened" << endl;
        return -1;
    }
    int budget, buyTypeQty, modelCount;
    fin >> budget >> buyTypeQty;
    int modelsCounts[100];
    int table[100][100];
    int group = 0;
    while (fin >> modelCount) {
        //vector<int> models(modelCount); // array element of table
        modelsCounts[group] = modelCount;
        for (int modelIndex = 0; modelIndex < modelCount; modelIndex++) {
            int price;
            fin >> price;
            table[group][modelIndex] = price;
        }
        group++;
    }
    int results[100000] = {0};
    for (int i = 0; i < group; i++) {
        for (int j = budget; j >= 0; j--) {
            for (int k = 0; k < modelsCounts[i]; k++) {
                if (j >= table[i][k]) {
                    results[j] = max (results[j], results[j - table[i][k]] + table[i][k]);
                }
            }
        }
    }
    cout << results[budget] <<endl;
    return 0;
}