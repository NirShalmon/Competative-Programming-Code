/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n, m;
int w[2000];
int position[2000];
int rate[100];
queue<int> waiting;
long long ans;
set<int> open;

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 0; i < n; ++i) cin >> rate[i],open.insert(i);
	for (int i = 0; i < m; ++i) cin >> w[i];
	for (int i = 0; i < 2 * m; ++i) {
		int p;
		cin >> p;
		if (p > 0) {
			--p;
			waiting.push(p);
		}
		else {
			p = -p - 1;
			open.insert(position[p]);
		}
		if (open.size() && waiting.size()) {
			int place = *open.begin();
			int car = waiting.front();
			open.erase(place);
			waiting.pop();
			ans += w[car] * (rate[place]);
			position[car] = place;
		}
	}
	cout << ans;
}
