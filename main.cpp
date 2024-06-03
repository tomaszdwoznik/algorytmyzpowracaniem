#include <unordered_set>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <stack>
#include <algorithm>
#include <queue>
#include "functions.cpp"

using namespace std;
int main(int argc, char* argv[]){
    int nodes;
    double saturation;
    vector<vector<int>> graph;
    string mode = argv[1];
    string action;

    if (argc != 2) {
        cerr << "Użycie: " << argv[0] << " <tryb>\n";
        return 1;
    }

    if (mode == "--hamilton") {
        cout << "Podaj liczbę wierzchołków: ";
        if (!(cin >> nodes) || nodes <= 0) {
            cerr << "Błędna liczba wierzchołków.\n";
            return 1;
        }

        cout << "Podaj nasycenie (w procentach): ";
        if (!(cin >> saturation) || saturation < 0 || saturation > 100) {
            cerr << "Błędne nasycenie.\n";
            return 1;
        }

        graph = createHamiltonianGraph(nodes, saturation);   

    }
    else if(mode == "--nonhamilton") {
        if (!(cin >> nodes) || nodes <= 0){
            cerr << "Błędna liczba wierzchołków.\n";
            return 1;
        }

        // graph = generate NON HAMILTON IN MATRIX
    }

   
    if(mode == "--hamilton"){
        while (true) {
        cout << "action> ";
        cin >> action;
        if (action == "print") {
            printMatrix(graph);
        }
        else if (action == "exit"){
            cout << "Opuszczanie programu...\n";
            return 1;
        }
        }
    }        
    // else if(mode == "--non-hamilton"){

    // }

    return 0;
}
