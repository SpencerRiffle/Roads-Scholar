/*********************************************************
* Summary: This program solves the Roads Scholar program, in which
* you are given a list of intersections, cities, and roads, and
* asked to create signs at specific destinations which include only
* cities the shortest distance from the sign's path.
* 
* The Floyd-Warshall algorithm solves a graph of the intersections/
* cities and roads, then the results are used to fill out the signs,
* after which the results are printed.
*
* Author: Seth Campbell, Spencer Riffle
* Created: December 2022
*
* ©Copyright Cedarville University, its Computer Science faculty, and the
* authors. All rights reserved.
********************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include "Sign.h"
using namespace std;

#define NAME_FIELD_SIZE 20

void floydWarshall(vector<vector<double>>& best, vector<vector<double>>& pred, int numInters);
void writeSigns(const vector<vector<double>>& best, const vector<vector<double>>& pred,
                vector<Sign>& signs, const unordered_map<int, string>& cities);

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
        int source;
        int dest;
        double dist;
        cin >> source;
        cin >> dest;
        cin >> dist;
        graph[source][dest] = dist;
        graph[dest][source] = dist;
        pred[source][dest] = source;
    }

    // Collect cities
    for (int i = 0; i < numCities; i++) {
        string name;
        int intersection;
        cin >> intersection;
        cin >> name;
        cities[intersection] = name;
    }
    
    // Collect signs
    cin >> numsigns;
    for (int i = 0; i < numsigns; i++) {
        int source;
        int dest;
        double dist;
        cin >> source;
        cin >> dest;
        cin >> dist;
        signs.push_back(Sign(source, dest, dist));
    }

    // Solve graph
    floydWarshall(graph, pred, numInters);

    // Solve all signs
    writeSigns(graph, pred, signs, cities);

    // Print signs
    for (int i = 0; i < signs.size(); i++) {
        cout << signs[i];
        if (i != signs.size() - 1) {
            cout << endl;
        }
    }
	return 0;
}

 void floydWarshall(vector<vector<double>>& best, vector<vector<double>>& pred, int numInters) {
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

void writeSigns(const vector<vector<double>>& best, const vector<vector<double>>& pred, 
                vector<Sign>& signs, const unordered_map<int, string>& cities) {

    for (int i = 0; i < signs.size(); i++) {
        int source = signs[i].getSource();
        int dest = signs[i].getDest();
        double dist = signs[i].getDist();

        for (auto& city : cities) {
            int lastHop = city.first;
            string cityName = city.second + string((NAME_FIELD_SIZE - city.second.size()), ' ');

            // Check path and record valid city
            while (pred[source][lastHop] != source) {
                lastHop = pred[source][lastHop];
            }
            if (lastHop == dest) {
                signs[i].insert(cityName, best[source][city.first] - dist);
            }
        }
    }
}