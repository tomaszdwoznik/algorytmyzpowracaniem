#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
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

        graph = createNonHamiltonianGraph(nodes, 50);
    }

    else{
        cerr << "Użycie: " << argv[0] << " --hamilton (-h) albo --non-hamilton (-nh)\n";
        return 1;
    }
    
    printHelp();

    if(mode == "--hamilton" || mode == "-h"){
        while (true) {
            cout << "action> ";
            cin >> action;
            if (action == "print") {
                printMatrix(graph);
            }

            else if (action == "help"){
                printHelp();
            }

            else if (action == "euler") {
                vector<int> cycle = findEulerianCycle(graph);
                if (cycle.empty()) {
                    cout << "Graf nie posiada cyklu Eulera.\n";
                } 
                else {
                    cout << "Cykl Eulera: ";
                    for (int node : cycle) {
                        cout << node << " ";
                    }
                    cout << "\n";
                }
            }

            else if (action == "exit"){
                cout << "Opuszczanie programu...\n";
                return 1;
            }
        }
    }        

    else if(mode == "--non-hamilton" || mode == "-nh"){
        while (true) {
            cout << "action> ";
            cin >> action;
            if (action == "print") {
                printMatrix(graph);
            }

            else if (action == "help"){
                printHelp();
            }
            
            else if (action == "euler") {
                vector<int> cycle = findEulerianCycle(graph);
                if (cycle.empty()) {
                    cout << "Graf nie posiada cyklu Eulera.\n";
                } 
                else {
                    cout << "Cykl Eulera: ";
                    for (int node : cycle) {
                        cout << node << " ";
                    }
                    cout << "\n";
                }
            }

            else if (action == "exit"){
                cout << "Opuszczanie programu...\n";
                return 1;
            }
        }
    }



    return 0;
}
