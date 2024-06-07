#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype> 
#include <chrono>
#include "functions.cpp"

using namespace std;
int main(int argc, char* argv[]){
    if (argc != 2) {
        cerr << "Użycie: " << argv[0] << " --hamilton (-h) albo " << argv[0] << " --non-hamilton (-nh)\n";
        return 1;
    }

    int nodes;
    double saturation;
    vector<vector<int>> graph;
    string mode = argv[1];
    string action;

    transform(mode.begin(), mode.end(), mode.begin(), [](unsigned char c){ return tolower(c); });

    if (mode == "--hamilton" || mode == "-h") {
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
    else if(mode == "--non-hamilton" || mode == "-nh") {
        cout << "Podaj liczbę wierzchołków: ";
        if (!(cin >> nodes) || nodes <= 0){
            cerr << "Błędna liczba wierzchołków.\n";
            return 1;
        }

        cout << "Podaj nasycenie (w procentach): ";
        if (!(cin >> saturation) || saturation < 0 || saturation > 100) {
            cerr << "Błędne nasycenie.\n";
            return 1;
        }

        graph = createNonHamiltonianGraph(nodes, saturation);
    }

    else{
        cerr << "Użycie: " << argv[0] << " --hamilton (-h) albo --non-hamilton (-nh)\n";
        return 1;
    }
    
    printHelp();

    while (true) {
        cout << "\naction> ";
        cin >> action;

        if (action == "print") {
            printMatrix(graph);
            cout << endl;
            tikz(graph);
        } 
        
        else if (action == "euler") {
            vector<int> eulerianCycle = findEulerianCycle(graph);
            if (!eulerianCycle.empty()) {
                cout << "Cykl Eulera: ";
                for (int v : eulerianCycle) {
                    cout << v << " ";
                }
                cout << "\n";
            } 
            else {
                cout << "Nie znaleziono cyklu Eulera.\n";
            }
        } 
        
        else if (action == "hamilton") {
            vector<int> hamiltonianCycle = findHamiltonianCycle(graph);
            if (!hamiltonianCycle.empty()) {
                cout << "Cykl Hamiltona: ";
                for (int v : hamiltonianCycle) {
                    cout << v + 1 << " ";
                }
                cout << "\n";
            } 
            else {
                cout << "Nie znaleziono cyklu Hamiltona.\n";
            }
        } 
        
        else if (action == "help") {
            printHelp();
        } 
        
        else if (action == "exit") {
            break;
        } 
        
        else {
            cout << "Nieznana komenda. Wpisz 'help' aby uzyskać pomoc.\n";
        }
    }

    return 0;
}