#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include "Sign.h"
using namespace std;

#define NAME_FIELD_SIZE 20

void Floyd_Warshall(vector<vector<double>>& best, vector<vector<double>>& pred, int numInters);
void WriteSigns(const vector<vector<double>>& best, const vector<vector<double>>& pred,
                vector<Sign>& signs, const unordered_map<int, string>& cities);
template <typename T>
void printMatrix(vector<vector<T>>& v) {
    for (auto row : v) {
        for (auto col : row) {
            cout << col << " ";
        }
        cout << endl;
    }
}

int main() {

    // Data Variables
    int numInters = 0;
    int numRoads = 0;
    int numCities = 0;
    int numsigns = 0;
    vector<vector<double>> graph;
    vector<vector<double>> pred;
    unordered_map<int, string> cities;
    vector<Sign> signs;

    // Temp Variables
    int source = -1;
    int dest = -1;
    int tempDest = -1;
    double dist = 0;
    int intersection = 0;
    string name = "";

    // Collect n, m, k
    cin >> numInters;
    cin >> numRoads;
    cin >> numCities;

    // Initialize graph
    for (int i = 0; i < numInters; i++) {
        vector<double> temp;
        for (int j = 0; j < numInters; j++) {
            if (i == j) {
                temp.push_back(0);
            }
            else {
                temp.push_back(INFINITY);
            }
        }
        graph.push_back(temp);
    }

    // Initialize pred
    for (int i = 0; i < numInters; i++) {
        vector<double> temp;
        for (int j = 0; j < numInters; j++) {
            temp.push_back(i);
        }
        pred.push_back(temp);
    }

    // Collect roads
    for (int i = 0; i < numRoads; i++) {
        cin >> source;
        cin >> dest;
        cin >> dist;
        graph[source][dest] = dist;
        graph[dest][source] = dist;
        pred[source][dest] = source;
    }

    // Collect cities
    for (int i = 0; i < numCities; i++) {
        cin >> intersection;
        cin >> name;
        cities[intersection] = name;
    }
    
    // Collect signs
    cin >> numsigns;
    for (int i = 0; i < numsigns; i++) {
        cin >> source;
        cin >> dest;
        cin >> dist;
        signs.push_back(Sign(source, dest, dist));
    }

    // Solve graph APSP
    Floyd_Warshall(graph, pred, numInters);

    // Solve all signs
    WriteSigns(graph, pred, signs, cities);
    for (int i = 0; i < signs.size(); i++) {
        cout << signs[i];
        if (i != signs.size() - 1) {
            cout << endl;
        }
    }
	return 0;
}

 void Floyd_Warshall(vector<vector<double>>& best, vector<vector<double>>& pred, int numInters) {
     int n = numInters;

     for (int k = 0; k < n; k++) {
         for (int u = 0; u < n; u++) {
             for (int v = 0; v < n; v++) {
                 if ((best[u][k] + best[k][v]) < best[u][v]) {
                     best[u][v] = best[u][k] + best[k][v];
                     best[v][u] = best[u][k] + best[k][v];
                     pred[u][v] = pred[k][v];
                     pred[v][u] = pred[k][v];
                 }
             }
         }
     }
 }

void WriteSigns(const vector<vector<double>>& best, const vector<vector<double>>& pred, 
                vector<Sign>& signs, const unordered_map<int, string>& cities) {
    
    // Solve each sign
    for (int i = 0; i < signs.size(); i++) {

        int source = signs[i].getSource();
        int dest = signs[i].getDest();
        double dist = signs[i].getDist();

        for (auto& city : cities) {
            int lastHop = city.first;
            string cityName = city.second + string((NAME_FIELD_SIZE - city.second.size()), ' ');

            // Check path
            while (pred[source][lastHop] != source) {
                lastHop = pred[source][lastHop];
            }

            // Record city
            if (lastHop == dest) {
                signs[i].insert(cityName, best[source][city.first] - dist);
            }
        }
    }
}