/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<map>
#include<string>
#include<deque>

using namespace std;

int n, m;
map<string, int> numberer;
pair<int, int> l[2000], r[2000];
unsigned long long hs[2000];
unsigned long long vall[3000],valr[3000];

int num(string &s) {
	if (numberer.find(s) != numberer.end()) {
		return numberer[s];
	} else {
		int ans = numberer.size();
		numberer[s] = ans;
		return ans;
	}
}

void read(int cnt, pair<int, int> *t) {
	numberer.clear();
	for (size_t i = 0; i < cnt; i++) {
		string a, b, c;
		char f;
		cin >> a >> f >> b >> f >> c;
		t[i*2] = { num(a),num(a) };
		t[i * 2 + 1] = { num(b),num(c) };
	}
}

int line(int q,int i, int dx, int dy) {
	if (l[q + dx].first == l[q + dx].second && r[q + dy].first != r[q + dy].second ||
		l[q + dx].first != l[q + dx].second && r[q + dy].first == r[q + dy].second) return -1;
	vall[l[q + dx].first] ^= hs[q];
	if(l[q+dx].second != l[q+dx].first) vall[l[q + dx].second] ^= hs[q];
	valr[r[q + dy].first] ^= hs[q];
	if (r[q + dy].second != r[q + dy].first)valr[r[q + dy].second] ^= hs[q];
	if (vall[l[i + dx].first] == valr[r[i + dy].first] && vall[l[i + dx].second] == valr[r[i + dy].second] ||
		vall[l[i + dx].second] == valr[r[i + dy].first] && vall[l[i + dx].first] == valr[r[i + dy].second]) return 1;
	return 0;
}

int chk(int dx, int dy) {
	for (size_t i = 0; i < 3000; i++) {
		vall[i] = 0;
		valr[i] = 0;
	}
	int ans = 0;
	int i = 0;
	int j = 0;
	vall[l[i+dx].first] = hs[i];
	valr[r[i+dy].first] = hs[i];
	while (i + dx < 2 * n && i+dy < 2 * m) {
		bool rst = false;
		while (true) {
			++i;
			if (i + dx == 2 * n || i + dy == 2 * m) break;
			int v = line(i,i, dx, dy);
			if (v == -1) {
				rst = true;
			}  
			if (v <= 0) break;
		}
		ans = max(ans, i / 2 - (j+1) / 2);
		if (rst) {
			while (j <= i) {
				line(j, i, dx, dy);
				++j;
			}
		} else {
			while (line(j,i, dx, dy) != 1)++j;
			++j;
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m;
	read(n, l);
	read(m, r);
	for (size_t i = 0; i < 2000; i++) {
		for (int j = 0; j < 64; ++j) hs[i] |= (((long long)rand()) & 1) << j;
	}
	int ans = 0;
	for (size_t i = 0; i < n; i++) {
		ans = max(ans, chk(2*i, 0));
	}
	for (size_t i = 1; i < m; i++) {
		ans = max(ans, chk(0, 2*i));
	}
	cout << ans;
}
