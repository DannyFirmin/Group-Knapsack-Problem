#include <iostream>
#include<fstream>
#include<string>
#include <list>
#include <unordered_map>

using namespace std;
struct Model {
    int group;
    int index;
    int price;
};
unordered_map<int, list<Model>> table;

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
    string i;
    fin >> budget >> buyTypeQty;

    int group = 0;
    while (fin >> modelCount) {
        group++;
        list<Model> models;
        for (int modelIndex = 1; modelIndex <= modelCount; modelIndex++) {
            int price;
            fin >> price;
            Model currentModel = {group, modelIndex, price};
            models.push_back(currentModel);
        }
        table[group] = models;
    }
    list<Model>::iterator it;
    for(it = table[25].begin(); it != table[25].end(); ++it)
        cout << it -> price << " ";
    return 0;
}