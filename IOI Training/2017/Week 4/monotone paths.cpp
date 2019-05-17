/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int bp[120000];
vector<pair<int, pair<int, int>>> edj;

int main() {
	ios::sync_with_stdio(false);
	int n,m;
	cin >> n>>m;
	int ans = 0;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		edj.push_back({ w,{--u,--v} });
	}
	sort(edj.begin(), edj.end());
	for (auto e : edj) {
		int w = e.first;
		auto nds = e.second;
		int t = bp[nds.first];
		ans = max(ans, max(t, bp[nds.second]) + 1);
		bp[nds.first] = max(bp[nds.first], bp[nds.second] + 1);
		bp[nds.second] = max(bp[nds.second], t + 1);
	}
	cout << ans;
}

