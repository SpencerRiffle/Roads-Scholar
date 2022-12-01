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
			cout << text[i].first << " " << text[i].second << endl;
		}
		cout << endl;
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