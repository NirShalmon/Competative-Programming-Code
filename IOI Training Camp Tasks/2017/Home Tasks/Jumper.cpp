/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n,k;
pair<int, int> p[100000];
map<int, set<int>> x, y;
string st;

int main() {
	ios::sync_with_stdio(false);
	cin >> n>>k;
	cin >> st;
	for (int i = 0; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		p[i] = { a + b, b - a };
		if (i != 0) {
			x[p[i].first].insert(p[i].second);
			y[p[i].second].insert(p[i].first);
		}
	}
	int cx = p[0].first,cy = p[0].second;
	for (char c : st) {
		if (c == 'A') {
			auto f = y[cy].upper_bound(cx);
			if (f != y[cy].end()) {
				int nx = *f;
				x[nx].erase(cy);
				y[cy].erase(f);
				cx = nx;
			}
		} else if (c == 'D') {
			auto f = y[cy].upper_bound(cx);
			if (f != y[cy].begin() && y[cy].size() > 0) {
				--f;
				int nx = *f;
				x[nx].erase(cy);
				y[cy].erase(f);
				cx = nx;
			}
		}else if (c == 'C') {
			auto f = x[cx].upper_bound(cy);
			if (f != x[cx].end()) {
				int ny = *f;
				y[ny].erase(cx);
				x[cx].erase(f);
				cy = ny;
			}
		} else if (c == 'B') {
			auto f = x[cx].upper_bound(cy);
			if (f != x[cx].begin() && x[cx].size() > 0) {
				--f;
				int ny = *f;
				y[ny].erase(cx);
				x[cx].erase(f);
				cy = ny;
			}
		}
	}
	cout << (cx - cy) / 2 << ' ' << (cx + cy) / 2;
}