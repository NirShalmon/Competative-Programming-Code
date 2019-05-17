/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<algorithm>

#define pos(u) (u).first][(u).second

using namespace std;

int l, o;

int d[2005][2005];
long long ansa, ansb;

void side(int ds) {
	if (ds >= 0 && ds < l) {
		int s = l - ds;
		int even = s / 2;
		int odd = (s + 1) / 2;
		if (ds & 1) swap(even, odd);
		ansa += even;
		ansb += odd;
	}
}

void corner(int ds) {
	if (ds >= 0 && ds < l) {
		int s = l - ds;
		long long evenn = s / 2;
		long long oddn = (s + 1) / 2;
		long long even = (2 * 3 + (evenn - 1) * 2)*evenn / 2;
		long long odd = (2 * 2 + (oddn - 1) * 2)*oddn / 2;
		if (ds & 1) swap(even, odd);
		ansa += even;
		ansb += odd;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin >> o >> l;
	for (size_t i = 0; i < 2005; i++) {
		for (size_t j = 0; j < 2005; j++) {
			d[i][j] = -1;
		}
	}
	for (size_t i = 0; i < o; i++) {
		int x, y;
		cin >> x >> y;
		d[x + 1001][y + 1001] = -2;
	}
	queue<pair<int, int>> q;
	d[1001][1001] = 0;
	q.push({ 1001,1001 });
	while (!q.empty()) {
		auto u = q.front();
		q.pop();
		if (d[pos(u)] <= l) {
			if (d[pos(u)] & 1)++ansb;
			else ++ansa;
		}
		vector<pair<int, int>> edj = { { u.first - 1,u.second },{ u.first + 1,u.second },{ u.first,u.second - 1 },{ u.first,u.second + 1 } };
		for (auto v : edj) {
			if (v.first >= 0 && v.first <= 2002 && v.second >= 0 && v.second <= 2002 && d[pos(v)] == -1) {
				q.push(v);
				d[pos(v)] = d[pos(u)] + 1;
			}
		}
	}
	for (int i = 1; i < 2002; ++i) {
		side(d[0][i]);
		side(d[2002][i]);
		side(d[i][0]);
		side(d[i][2002]);
	}
	corner(d[0][0]);
	corner(d[2002][0]);
	corner(d[0][2002]);
	corner(d[2002][2002]);
	cout << ansa << ' ' << ansb;
}