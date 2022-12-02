#pragma once

#include "Sign.h"

// Insertion sort based on distance, then name, then arrival time

int Sign::getSource() {
	return source;
}

int Sign::getDest()
{
	return dest;
}

double Sign::getDist()
{
	return dist;
}

vector<pair<string, int>> Sign::getText()
{
	return text;
}

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

ostream& operator<<(ostream&, Sign& sign)
{
	vector<pair<string, int>> text = sign.getText();
	for (int i = 0; i < text.size(); i++) {
		cout << text[i].first << text[i].second << endl;
	}
	return cout;
}