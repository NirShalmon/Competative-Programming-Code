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

pair<int, int> p[1000000];

int main() {
	ios::sync_with_stdio(false);
	int n,m;
	cin >> n >> m;
	int h = 0;
	int sz = 0;
	for (size_t i = 0; i < m; i++) {
		int s, e;
		cin >> s>>e;
		h = max(h, max(s, e));
		if (s > e) p[sz++] = { e,s};
	}
	if (sz == 0) {
		cout << h;
		return 0;
	}
	sort(p, p + sz);
	int mxs = p[0].second, mne = p[0].first;
	int ans = 2 * h - p[0].first;
	int prsum = 0;
	for (size_t i = 1; i < sz; i++) {
		if (p[i].first > mxs) {
			prsum += 2 * (mxs - mne);
			ans = min(ans, 2 * h + prsum - p[i].first);
			mxs = p[i].second;
			mne = p[i].first;
		} else {
			mxs = max(mxs, p[i].second);
		}
	}
	prsum += 2 * (mxs - mne);
	ans = min(ans, h + prsum);
	cout << ans;
}