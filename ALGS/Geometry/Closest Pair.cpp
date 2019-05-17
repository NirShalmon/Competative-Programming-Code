/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n;
pair<int, int> p[100000];

long long sqr(int t) {
	return ((long long)t) * t;
}

long long d(int a, int b) {
	return sqr(p[b].first - p[a].first) + sqr(p[b].second - p[a].second);
}

long long cp(vector<int> x, vector<int> y) {
	if (x.size() == 1) return 1ll << 62;
	if (x.size() == 2) return d(x[0], x[1]);
	vector<int> ly, ry;
	long long l = 0;
	for (int t : y) {
		if (p[t].first < p[x[x.size() / 2]].first || (p[t].first == p[x[x.size()/2]].first && p[t].second < p[x.size() / 2].second)) ly.push_back(t);
		else ry.push_back(t);
	}
	l = min(cp(vector<int>(x.begin(), x.begin() + x.size() / 2), ly), cp(vector<int>(x.begin()+x.size()/2, x.end()), ry));
	deque<int> stk;
	for (int t : y) {
		if (sqr(p[t].first - p[x[x.size() / 2]].first) <= l) {
			if (stk.size() == 9) stk.pop_front();
			for (int k : stk) l = min(l, d(t, k));
			stk.push_back(t);
		}
	}
	return l;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	vector<int> x,y;
	for (size_t i = 0; i < n; i++) {
		cin >> p[i].first >> p[i].second;
		x.push_back(i);
	}
	y = x;
	sort(x.begin(), x.end(), [](int a, int b) {return p[a].first < p[b].first; });
	sort(y.begin(), y.end(), [](int a, int b) {return p[a].second < p[b].second; });
	cout.precision(4);
	cout << fixed << sqrt((long double)cp(x, y));
}