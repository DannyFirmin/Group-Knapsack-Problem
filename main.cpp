#include <iostream>
#include <fstream>
// u6611178 Danny, 2019, Australia
// Knapsack with selection from distinct groups solved by DP - COMP3600 Assignment 3
// Algorithms credit to: https://stackoverflow.com/questions/29729609/knapsack-with-selection-from-distinct-groups https://blog.csdn.net/zhaohaibo_/article/details/86177801
// The code for file reading credits to COMP3600 Assignment 2 provided code
using namespace std;
struct recordElement {
    int index;
    int prevPrice;
};
recordElement dpItems[100][100000];

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
    int M, buyTypeQty, modelCount;
    fin >> M >> buyTypeQty;
    int modelsCounts[100];
    int table[100][100];
    int T = 0;
    while (fin >> modelCount) {
        modelsCounts[T] = modelCount;
        for (int modelIndex = 0; modelIndex < modelCount; modelIndex++) {
            int price;
            fin >> price;
            table[T][modelIndex] = price;
        }
        T++;
    }
    int results[100000] = {0};

    for (int i = 0; i < T; i++) {
        for (int j = M; j >= 0; j--) {
            int tempMax = 0;
            for (int k = 0; k < modelsCounts[i]; k++) {
                if (j >= table[i][k]) {
                    results[j] = max(results[j], results[j - table[i][k]] + table[i][k]);
                    if (results[j] > tempMax) {
                        recordElement item = {k + 1, j - table[i][k]};
                        dpItems[i][j - 1] = item;
                        tempMax = results[j];
                    }
                }
            }
        }
    }
    cout << results[M] << " ";
    int selectedId[T];
    for (int i = T - 1; i >= 0; i--) {
        selectedId[i] = dpItems[i][M - 1].index;
        M = dpItems[i][M - 1].prevPrice;
    }
    for (int i = 0; i < T; i++) {
        cout << selectedId[i] << " ";
    }
    cout << endl;
    return 0;
}