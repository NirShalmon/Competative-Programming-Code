/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

unordered_set<int> points;

int pos(int x, int y) {
	return x * 5000 + y;
}

pair<int,int> dePos(int p) {
	return { p / 5000, p % 5000 };
}

int main() {
	ios::sync_with_stdio(false);
	int w, h,n;
	cin >> w >> h>>n;
	for (size_t i = 0; i < n; i++) {
		int x,y;
		cin >> x >> y;
		--x;
		--y;
		points.insert(pos(x,y));
	}
	int best = 0;
	for (auto a : points) {
		auto u = dePos(a);
		for (auto b : points) {
			auto v = dePos(b);
			int dx = v.first - u.first;
			int dy = v.second - u.second;
			if (dx > 0 && u.first - dx < 0 || u.second - dy < 0) {
				int s = 2;
				int x = v.first + dx;
				int y = v.second + dy;
				while (x < w && x >= 0 && y >= 0 && y < h) {
					if (points.find(pos(x,y)) == points.end()){
						s = 0;
						break;
					}
					s++;
					x += dx;
					y += dy;
				}
				best = max(s, best);
			}
		}
	}
	cout << (best > 2 ? best : 0);
}
