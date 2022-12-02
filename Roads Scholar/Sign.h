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
	int getSource() { return source; }
	int getDest() { return dest; }
	double getDist() { return dist; }
	vector<pair<string, int>> getText() { return text; }

	// Modifiers
	void insert(string name, double dist);
	friend ostream& operator<<(ostream&, Sign& sign)
	{
		vector<pair<string, int>> text = sign.getText();
		for (int i = 0; i < text.size(); i++) {
			cout << text[i].first << text[i].second << endl;
		}
		return cout;
	}

private:
	int source;
	int dest;
	double dist;
	vector<pair<string, int>> text;
};

// Insertion sort based on distance, then name, then arrival time
void Sign::insert(string name, double dist) {
	int miles = round(dist);
	pair<string, int> temp = pair<string, int>("", NULL);
	pair<string, int> hold = pair<string, int>(name, miles);

	for (int i = 0; i < text.size(); i++) {
		// Sort numerically
		if (hold.second < text[i].second) {
			temp = text[i];
			text[i] = hold;
			hold = temp;
		}
		// Sort alphabetically
		else if (hold.second == text[i].second) {
			if (hold.first.compare(text[i].first) < 0) {
				temp = text[i];
				text[i] = hold;
				hold = temp;
			}
		}
	}
	text.push_back(hold);
}