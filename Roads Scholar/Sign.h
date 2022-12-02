/********************************************************
* This class provides an implementation for the Sign object. 
* Users of this class are provided methods to create a sign
* and insert locations into it. They may also retrieve the
* sign's base values, such as its path's source, destination,
* the sign's distance from its source, and its current text.
* Sign does not inherit from other classes, and is not anticipated to
* be a base class for other classes.
*
* ©Copyright Cedarville University, its Computer Science faculty, and the
* authors. All rights reserved.
* *******************************************************/

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

