#include <iostream>
#include<fstream>
//#include<string>
#include <vector>
//#include <list>
//#include <unordered_map>

using namespace std;
//struct Model {
//    int group;
//    int index;
//    int price;
//};
//unordered_map<int, list<Model>> table;
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
//    string i;
    fin >> budget >> buyTypeQty;
    vector<int> table[buyTypeQty]; // array of vectors
    int group = 0;
    while (fin >> modelCount) {
        vector<int> models(modelCount); // array element of table
        for (int modelIndex = 0; modelIndex < modelCount; modelIndex++) {
            int price;
            fin >> price;
            models[modelIndex] = price;
        }
        table[group] = models;
        group++;
    }

//    int n = group;
//    int* indices = new int[n];
//    for (int i = 0; i < n; i++)
//        indices = 0;
//    while (1) {
//        for (int i = 0; i < n; i++) {
//            list<Model>::iterator it = table[i].begin();
//            advance (it, indices[i]);
//            cout << it->price << " ";
//            cout << endl;
//        }
//
//
//        int next = n - 1;
//        while (next >= 0 && (indices[next] + 1 >= table[next].size()))
//            next --;
//        if (next < 0)
//            break;
//        indices[next]++;
//
//        for (int i = next +1; i < n; i++)
//            indices[i] = 0;
//    }

//    list<Model>::iterator it;
//    for(it = table[25].begin(); it != table[25].end(); ++it)
//        cout << it -> price << " ";
    return 0;
}