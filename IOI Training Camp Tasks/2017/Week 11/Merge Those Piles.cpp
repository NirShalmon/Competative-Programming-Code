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

int m;
const int inf = 1000000000;
int ind[1000000],beg[1000000],sz[1000000];
int arr[2000000];
int bkp[2000000];
int t[12][2000000];
int lg[2000005];
vector<int> cnt[2000000];
int ts;
int k;

bool cmp1(const int &a, const int &b) {
	return arr[a] < arr[b];
}

bool cmp2(const int &a, const int &b) {
	if (t[k - 1][a] < t[k - 1][b]) return true;
	if (t[k - 1][a] > t[k - 1][b]) return false;
	return t[k - 1][a + (1 << (k - 1))] < t[k - 1][b + (1 << (k - 1))];
}

struct cmps {
	bool operator()(const int &a, const int &b) {
		int s1 = beg[a] + ind[a], s2 = beg[b] + ind[b];
		//int e1 = beg[a] + sz[a], e2 = beg[b] + sz[b];
		int l = min(sz[a] - ind[a], sz[b] - ind[b]);
		int lk = lg[l];
		if (t[lk][s1] > t[lk][s2]) return true;
		if (t[lk][s1] < t[lk][s2]) return false;
		if (t[lk][s1 + l - (1 << lk)] > t[lk][s2 + l - (1 << lk)]) return true;
		if (t[lk][s1 + l - (1 << lk)] < t[lk][s2 + l - (1 << lk)]) return false;
		return sz[a] - ind[a] < sz[b] - ind[b];
	}
};

void srt1(int n) {
	for (int i = 0; i < ts; ++i) cnt[i].clear();
	for (int i = 0; i < n; ++i) cnt[t[k - 1][bkp[i] + (1 << (k - 1))]].push_back(bkp[i]);
	int p = 0;
	for (int i = 0; i < ts; ++i){
		for (int v : cnt[i]) {
			bkp[p++] = v;
		}
	}
}

void srt2(int n) {
	for (int i = 0; i < ts; ++i) cnt[i].clear();
	for (int i = 0; i < n; ++i) cnt[t[k - 1][bkp[i]]].push_back(bkp[i]);
	int p = 0;
	for (int i = 0; i < ts; ++i)
		for (int v : cnt[i]) bkp[p++] = v;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> m;
	int ms = 0;
	for (size_t i = 0; i < m; i++) {
		cin >> sz[i];
		beg[i] = 0;
		if (i > 0) beg[i] = beg[i - 1] + sz[i-1] + 1;
		for (int j = beg[i]; j < beg[i] + sz[i]; ++j) cin >> arr[j];
		arr[beg[i] + sz[i]] = inf;
		ms = max(ms, sz[i]);
	}
	ts = beg[m - 1] + sz[m - 1];
	for (int i = 0; i < ts; ++i) bkp[i] = i;
	sort(bkp, bkp + ts,cmp1);
	t[0][bkp[0]] = 0;
	int p = 0;
	lg[0] = 0;
	for (size_t i = 1; 1<<i < 2000005; i++) {
		lg[1 << i] = 1;
	}
	for (size_t i = 1; i < 2000005; i++) {
		lg[i] += lg[i - 1];
	}
	for (int i = 1; i < ts; ++i) {
		if (arr[bkp[i]] != arr[bkp[i - 1]]) ++p;
		t[0][bkp[i]] = p;
	}
	for (k = 1; (1 << k) <= ms; ++k) {
		for (int i = 0; i + (1<<k) - 1 < ts; ++i) bkp[i] = i;
		srt1(ts - (1 << k) + 1);
		srt2(ts - (1 << k) + 1);
		p = 0;
		t[k][bkp[0]] = 0;
		for (int i = 1; i + (1 << k)-1 < ts; ++i) {
			if (cmp2(bkp[i - 1], bkp[i]))++p;
			t[k][bkp[i]] = p;
		}
	}
	priority_queue<int, vector<int>, cmps> q;
	for (size_t i = 0; i < m; i++) {
		q.push(i);
	}
	while (!q.empty()) {
		int t = q.top();
		q.pop();
		cout << arr[beg[t] + ind[t]++]<<' ';
		if (ind[t] < sz[t]) q.push(t);
	}
}