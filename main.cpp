#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
// u6611178 Danny, 2019, Australia
// Knapsack with selection from distinct groups solved by DP - COMP3600 Assignment 3
// The code for file reading credits to COMP3600 Assignment 2 provided code
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
    auto start = std::chrono::system_clock::now();
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
    int prevBudget = 0;
    int selectedId[100] = {0};
    for (int i = 0; i < T; i++) {
        for (int j = M; j >= 0; j--) {
            for (int k = 0; k < modelsCounts[i]; k++) {
                if (j >= table[i][k]) {
                    results[j] = max(results[j], results[j - table[i][k]] + table[i][k]);
                }
            }
        }
        for (int k = 0; k < modelsCounts[i]; k++) {
            if (table[i][k] == results[M] - prevBudget) {
                selectedId[i] = k + 1;
                break;
            }
        }
        prevBudget = results[M];
    }
    cout << results[M] << " ";
    for (int i = 0; i < T; i++) {
        cout << selectedId[i] << " ";
    }
    cout << endl;
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() * 1000 << "ms\n";
    return 0;
}