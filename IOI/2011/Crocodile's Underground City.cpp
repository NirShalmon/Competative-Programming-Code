/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n, m, k;
vector<pair<int,int>> edj[100000];
bool isEnd[100000];
pair<int, int> d[100000];

void ins(pair<int, int> &p, int val) {
	if (val < p.first) {
		p.second = p.first;
		p.first = val;
	} else if (val < p.second) p.second = val;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m >> k;
	for (size_t i = 0; i < m; i++) {
		int u, v, t;
		cin >> u >> v >> t;
		edj[u].push_back({ v,t });
		edj[v].push_back({ u,t });
	}
	for (size_t i = 0; i < k; i++) {
		int a;
		cin >> a;
		isEnd[a] = true;
	}
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	for (size_t i = 0; i < n; i++) {
		if (!isEnd[i]) {
			d[i] = { 1000000001,1000000001 };
			for (int j = 0; j < edj[i].size(); ++j) {
				if (isEnd[edj[i][j].first]) {
					ins(d[i], edj[i][j].second);
				}
			}
			q.push({ d[i].second,i });
		} else {
			d[i] = { 0,0 };
		}
	}
	while (!q.empty()) {
		auto t = q.top();
		q.pop();
		int u = t.second;
		int ds = t.first;
		if (ds == d[u].second) {
			//if (u == 0) break;
			for (pair<int, int> &o : edj[u]) {
				int v = o.first;
				int w = o.second;
				int prevs = d[v].second;
				ins(d[v], ds + w);
				if (d[v].second != prevs) {
					q.push({ d[v].second,v });
				}
			}
		}
	}
	cout << d[0].second;
}
