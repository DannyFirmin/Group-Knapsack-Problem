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
    int n = group;
    int *indexMask = new int[n];
    for (int i = 0; i < n; i++)
        indexMask[i] = 0;
    int bestCost = 0;
    int selectedIndex[n];
    int tmpSelectedIndex[n];
    while (true) {
        int tempCost = 0;
        for (int i = 0; i < n; i++) {
            tempCost += table[i][indexMask[i]];
            tmpSelectedIndex[i] = indexMask[i];
        }
        if (tempCost <= budget && tempCost > bestCost) {
            bestCost = tempCost;
            for (int i = 0; i < n; i++)
                selectedIndex[i] = tmpSelectedIndex[i];
        }

        int next = n - 1;
        while (next >= 0 && (indexMask[next] + 1 >= modelsCounts[next]))
            next--;
        if (next < 0)
            break;
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