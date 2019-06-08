/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int n, r,me;
vector<int> ranks;
int p[3][600000];
int a[3];
bool filled[200000];

pair<int, int> sim(int s) {
	ranks.insert(ranks.begin() + 2 * s, 1);
	int loops = 0;
	pair<int,int> ans;
	if (me <= n + 1) {
		for (size_t i = 0; i < 3; i++) {
			for (size_t j = 0; j < 3*n; j++) {
				p[i][j] = 0;
			}
			a[i] = 0;
		}
		int in = ranks[0];
		p[ranks[1]][0]++;
		for (int i = 1; i < n; ++i) {
			p[ranks[2 * i]][i]++;
			p[ranks[2 * i + 1]][i]++;
		}
		int lastPass = -1;
		for (int i = 0; i < 3*n; i++) {
			int k = 3;
			while (k--) a[k] += p[k][i];
			k = 3;
			while (k--) {
				if (a[k]) break;
			}
			--a[k];
			if (i < 2 * n) p[min(k,in)][i + n]++;
			if (min(k,in) == 1) {
				++loops;
				lastPass = i;
			}
			in = max(k, in);
		}
		if (lastPass < 2 * n + (r%n)) ans = { loops,(n -1- (2 * n + r%n - ++lastPass)) % n };
		else ans = { loops-1,lastPass - 2 * n - r%n};
	} else {
		a[0] = 0;
		a[1] = 0;
		filled[0] = true;
		for (size_t i = 1; i < n; i++) {
			filled[i] = false;
		}
		a[ranks[0]]++;
		a[ranks[1]]++;
		if (a[1])loops++;
		for (int x = n - 1; x > 0; --x) {
			a[ranks[2 * x]]++;
			a[ranks[2 * x+1]]++;
			if (a[0]) {
				--a[0];
				filled[x] = true;
			} else if (a[1]) {
				ans = { loops,x };
				goto end;
			}
		}
		if (a[1])loops++;
		for (int x = n - 1; x > 0; --x) {
			if (!filled[x]) {
				if (a[0]) {
					--a[0];
					filled[x] = true;
				} else if (a[1]) {
					ans = { loops,x };
					goto end;
				}
			}
		}
	}
	end:
	ranks.erase(ranks.begin() + 2 * s);
	return ans;
}

pair<int,int> search(int l, int r) {
	int v = sim(l).second;
	--r;
	while (l < r) {
		int mid = (l + r+1) / 2;
		if (sim(mid).second == v) l = mid;
		else r = mid - 1;
	}
	return{ v,l };
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> r >> me;
	ranks = vector<int>(2 * n);
	for (int i = 0; i < 2 * n - 1; ++i) {
		cin >> ranks[i];
		ranks[i] = ranks[i] < me ? 2 : 0;
	}
	if (me == 1) {
		cout << n;
		return 0;
	}
	int mn = sim(n - 1).first;
	int mx = sim(0).first;
	int best = n + 1;
	int bs = 0;
	vector<int> v;
	for (int i = mx; i >= mn; i--) {
		int lo = 0;
		int hi = n - 1;
		while (lo < hi) {
			int mid = (lo + hi) / 2;
			if (sim(mid).first > i) lo = mid + 1;
			else hi = mid;
		}
		v.push_back(lo);
	}
	v.push_back(n);
	for (size_t i = 0; i < v.size()-1; i++) {
		auto tt = search(v[i], v[i + 1]);
		if (tt.first <= best) {
			best = tt.first;
			bs = tt.second;
		}
	}
	cout << bs + 1;
}
