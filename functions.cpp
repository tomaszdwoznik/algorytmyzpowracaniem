#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <list>
#include <iterator>

using namespace std;

void generateHamiltonianCycle(vector<vector<int>>& graph, int n) {
    vector<int> cycle(n);
    iota(cycle.begin(), cycle.end(), 0);
    random_shuffle(cycle.begin(), cycle.end());

    for (int i = 0; i < n; ++i) {
        int u = cycle[i];
        int v = cycle[(i + 1) % n];
        graph[u][v] = graph[v][u] = 1;
    }
}

void addEdgesForSaturation(vector<vector<int>>& graph, int n, int saturation) {
    int maxEdges = n * (n - 1) / 2;
    int currentEdges = 0;

    for (const auto& row : graph) {
        currentEdges += accumulate(row.begin(), row.end(), 0);
    }
    currentEdges /= 2;

    int targetEdges = maxEdges * saturation / 100;

    while (currentEdges < targetEdges) {
        int u = rand() % n;
        int v = rand() % n;
        if (u != v && graph[u][v] == 0) {
            graph[u][v] = graph[v][u] = 1;
            currentEdges++;
        }
    }
}

void ensureEvenDegrees(vector<vector<int>>& graph, int n) {
    vector<int> degrees(n, 0);
    for (int i = 0; i < n; ++i) {
        degrees[i] = accumulate(graph[i].begin(), graph[i].end(), 0);
    }

    for (int i = 0; i < n; ++i) {
        if (degrees[i] % 2 != 0) {
            for (int j = 0; j < n; ++j) {
                if (i != j && graph[i][j] == 0) {
                    graph[i][j] = graph[j][i] = 1;
                    degrees[i]++;
                    degrees[j]++;
                    break;
                }
            }
        }
    }
}

vector<vector<int>> createHamiltonianGraph(int n, int saturation) {
    vector<vector<int>> graph(n, vector<int>(n, 0));
    generateHamiltonianCycle(graph, n);
    addEdgesForSaturation(graph, n, saturation);
    ensureEvenDegrees(graph, n);
    return graph;
}

vector<vector<int>> createNonHamiltonianGraph(int n, int saturation) {
    vector<vector<int>> graph = createHamiltonianGraph(n, saturation);

    int isolateVertex = rand() % n;
    for (int i = 0; i < n; ++i) {
        graph[isolateVertex][i] = graph[i][isolateVertex] = 0;
    }

    return graph;
}

void printMatrix(const vector<vector<int>>& graph) {
    int nodes = graph.size();
    cout << "Macierz sąsiedztwa:" << endl;
    for (int i = 0; i < nodes; ++i) {
        cout << i + 1 << "> ";
        for (int j = 0; j < nodes; ++j) {
            cout << graph[i][j] << " ";
        }
        cout << "\n";
    }
}


bool isEulerian(const vector<vector<int>>& graph) {
    for (const auto& row : graph) {
        int degree = accumulate(row.begin(), row.end(), 0);
        if (degree % 2 != 0) {
            return false;
        }
    }
    return true;
}

vector<int> findEulerianCycle(vector<vector<int>> graph) {
    int n = graph.size();
    vector<int> cycle;
    if (!isEulerian(graph)) {
        return cycle;
    }

    stack<int> currentPath;
    list<int> circuit;

    currentPath.push(0);
    int currentVertex = 0;

    while (!currentPath.empty()) {
        if (accumulate(graph[currentVertex].begin(), graph[currentVertex].end(), 0) != 0) {
            currentPath.push(currentVertex);
            for (int nextVertex = 0; nextVertex < n; ++nextVertex) {
                if (graph[currentVertex][nextVertex] != 0) {
                    graph[currentVertex][nextVertex] = 0;
                    graph[nextVertex][currentVertex] = 0;
                    currentVertex = nextVertex;
                    break;
                }
            }
        } 
        else {
            circuit.push_front(currentVertex);
            currentVertex = currentPath.top();
            currentPath.pop();
        }
    }

    for (int vertex : circuit) {
        cycle.push_back(vertex + 1);
    }
    return cycle;
}

bool isSafe(int v, const vector<vector<int>>& graph, vector<int>& path, int pos) {
    if (graph[path[pos - 1]][v] == 0) {
        return false;
    }
    for (int i = 0; i < pos; i++) {
        if (path[i] == v) {
            return false;
        }
    }
    return true;
}

bool hamiltonianCycleUtil(vector<vector<int>>& graph, vector<int>& path, int pos) {
    int n = graph.size();
    if (pos == n) {
        if (graph[path[pos - 1]][path[0]] == 1) {
            return true;
        }
        return false;
    }
    for (int v = 1; v < n; v++) {
        if (isSafe(v, graph, path, pos)) {
            path[pos] = v;
            if (hamiltonianCycleUtil(graph, path, pos + 1)) {
                return true;
            }
            path[pos] = -1;
        }
    }
    return false;
}

vector<int> findHamiltonianCycle(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> path(n, -1);
    path[0] = 0;
    if (!hamiltonianCycleUtil(graph, path, 1)) {
        return vector<int>();
    }
    return path;
}

void printDegrees(const vector<vector<int>>& graph) {
    for (int i = 0; i < graph.size(); ++i) {
        int degree = accumulate(graph[i].begin(), graph[i].end(), 0);
        cout << "Wierzchołek " << i + 1 << " ma stopień " << degree << "\n";
    }
}

void printHelp(){
    cout << "\nhelp: wyświetlenie tej informacji\n";
    cout << "print: wypisanie grafu\n";
    cout << "euler: znajdowanie cyklu Eulera w grafie\n";
    cout << "hamilton: znajdowanie cyklu Hamiltona w grafie\n";
    cout << "exit: opuszczenie programu\n\n";
}