#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Sign {
public:
	// Constructors
	Sign(int source, int dest, double dist) : source(source), dest(dest), dist(dist) {}

	// Getters
	int getSource();
	int getDest();
	double getDist();
	vector<pair<string, int>> getText();

	// Modifiers
	void insert(string name, double dist);
	friend ostream& operator<<(ostream&, Sign& sign);

private:
	int source;
	int dest;
	double dist;
	vector<pair<string, int>> text;
};

