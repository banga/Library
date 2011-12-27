/* 
 * Activity Selection problem 
 */
#include <string>
#include <iostream>
#include <vector>

using namespace std;

typedef struct {
	int Ts, Te; // Start, End times
	string description;
} Activity;

int main() {
	int n;
	vector<Activity> activities;

	cout << "Number of activities:";
	cin >> n;

	for(int i = 0; i < n; i++) {
		cout << "Enter Ts, Te and description of activity " << (1+i) << ":" << endl;
		Activity a;
		cin >> a.Ts >> a.Te;
		getline(cin, a.description);
		activities.push_back(a);
	}

	vector<Activity> selected;
	selected.push_back(activities[0]);
	for(vector<Activity>::iterator it = activities.begin()+1; it < activities.end(); it++) {
		if(selected[selected.size()-1].Te <= it->Ts)
			selected.push_back(*it);
	}

	cout << "Selected activities:" << endl;
	for(vector<Activity>::iterator it = selected.begin(); it < selected.end(); it++) {
		cout << it->Ts << '\t' << it->Te << '\t' << it->description << endl;
	}
	return 0;
}
