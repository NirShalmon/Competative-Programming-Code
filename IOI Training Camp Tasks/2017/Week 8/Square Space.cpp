/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<set>
#include<map>
#include<algorithm>
#include<vector>

using namespace std;

set<pair<int,int>> s;
pair<int, int> q[40000];
map<int, int> m;
vector<vector<int>> vec;
vector<int> mny;

bool chk(int x, int y) {
	return s.find({ x,y }) != s.end();
}

long long sqr(int a) {
	return a*a;
}

int main() {
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	vec.push_back(vector<int>());
	for (int i = 0; i < n; ++i) {
		cin >> q[i].first >> q[i].second;
		s.insert({ q[i].first,q[i].second });
		if (m[q[i].first] == 0) {
			m[q[i].first] = vec.size();
			vec.push_back({ q[i].second });
		} else vec[m[q[i].first]].push_back(q[i].second);
	}
	for (int i = 0; i < vec.size(); ++i) sort(vec[i].begin(), vec[i].end());
	int ans = 0;
	int mx = (int)sqrt(n)/12;
	for (auto a = m.begin(); a != m.end(); ++a) {
		if (vec[(*a).second].size() <  mx) {
			int x = (*a).first;
			vector<int> v = vec[(*a).second];
			for (int i = 0; i < v.size(); ++i) {
				for (int j = 0; j < v.size(); ++j) {
					if (v[i] < v[j]) {
						int dy = v[j] - v[i];
						ans += chk(x + dy, v[i]) && chk(x + dy, v[j]);
						if (x >= dy && vec[m[x-dy]].size() >= mx) {
							ans += chk(x - dy, v[i]) && chk(x - dy, v[j]);
						}
					}
				}
			}
		} else {
			mny.push_back((*a).first);
		}
	}
	for (int i = 0; i < mny.size(); ++i) {
		int x = mny[i];
		int p = m[x];
		for (int j = 0; j < mny.size(); ++j) {
			if (i == j) continue;
			int xx = mny[j];
			if (x < xx) {
				int dx = xx - x;
				int t = m[xx];
				vector<int> match;
				int e = 0, r = 0;
				while (e < vec[p].size() && r < vec[t].size()) {
					if (vec[p][e] == vec[t][r]) {
						match.push_back(vec[p][e]);
						++e; ++r;
					} else if (vec[p][e] < vec[t][r]) ++e;
					else ++r;
				}
				e = 0;
				r = 1;
				while (r < match.size()) {
					if (match[r] == match[e] + dx) {
						++ans;
						++r; ++e;
					} else if (match[r] < match[e] + dx) ++r;
					else ++e;
				}
			}
		}
	}
	cout << ans;
}