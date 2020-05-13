#include <iostream>
#include <fstream>
// u6611178 Danny, 2019, Australia
// Knapsack with selection from distinct groups solved by brute force - COMP3600 Assignment 3
// Combinations finding (line 56-66) inspired by: https://www.geeksforgeeks.org/combinations-from-n-arrays-picking-one-element-from-each-array/
// The code for file reading (line 10-19) credits to COMP3600 Assignment 2 provided code
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
    int M, buyTypeQty, modelCount;
    fin >> M >> buyTypeQty;
    int modelsCounts[100];
    int table[100][100];
    int T = 0;
    while (fin >> modelCount) {
        //vector<int> models(modelCount); // array element of table
        modelsCounts[T] = modelCount;
        for (int modelIndex = 0; modelIndex < modelCount; modelIndex++) {
            int price;
            fin >> price;
            table[T][modelIndex] = price;
        }
        T++;
    }
    int n = T;
    // track next element in each type
    int *indexMask = new int[n];
    for (int i = 0; i < n; i++)
        indexMask[i] = 0;
    int bestCost = 0;
    int selectedIndex[n];
    int tmpSelectedIndex[n];
    while (true) {
        int tempCost = 0;
        for (int i = 0; i < n; i++) {
            // table[i][indexMask[i]] is the current combination
            tempCost += table[i][indexMask[i]];
            tmpSelectedIndex[i] = indexMask[i];
        }
        if (tempCost <= M && tempCost > bestCost) {
            // pick the best combination
            bestCost = tempCost;
            for (int i = 0; i < n; i++)
                selectedIndex[i] = tmpSelectedIndex[i];
        }
        // from the last type check if it has model left, if yes, move to the next model
        int next = n - 1;
        // keep moving left to check all type, until next < 0, means we are done
        while (next >= 0 && (indexMask[next] + 1 >= modelsCounts[next]))
            next--;
        if (next < 0)
            break;
        // move to next model in that type
        indexMask[next]++;

        for (int i = next + 1; i < n; i++)
            indexMask[i] = 0;
    }
    cout << bestCost << " ";
    for (int i = 0; i < n; i++)
        cout << selectedIndex[i] + 1 << " ";
    cout << endl;
    return 0;
}