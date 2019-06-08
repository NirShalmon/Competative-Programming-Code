/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n;
int a[1000000];
vector<pair<int, int>> edj[1000000];

int dfs(int u, int k) {
	if (edj[u][k].second != -1) {
		return edj[u][k].second;
	}
	int v = edj[u][k].first;
	edj[u][k].second = a[v];
	for (int i = 0; i < edj[v].size(); ++i) {
		if (edj[v][i].first != u) {
			if(edj[v][i].second == -1)
				edj[u][k].second += dfs(v, i);
			else edj[u][k].second += edj[v][i].second;
		}
	}
	return edj[u][k].second;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (size_t i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (size_t i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;
		edj[a].push_back({ b,-1 });
		edj[b].push_back({ a,-1 });
	}
	int bestCost = 2010000000;
	int best = 0;
	for (size_t i = 0; i < n; i++) {
		int cost = 0;
		for (int j = 0; j < edj[i].size(); ++j) {
			cost = max(dfs(i, j),cost);
		}
		if (cost < bestCost) {
			bestCost = cost;
			best = i;
		}
	}
	cout << best;
}
