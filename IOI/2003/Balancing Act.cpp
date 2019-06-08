/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int n;
int w[200000];
vector<pair<int, int>> edj[200000];

int calc(int u, int q) {
	int v = edj[u][q].first;
	if (edj[u][q].second != -1) return edj[u][q].second;
	int sum = w[v];
	for (int i = 0; i < edj[v].size(); ++i) {
		if (edj[v][i].first != u) {
			sum += calc(v, i);
		}
	}
	edj[u][q].second = sum;
	//cout<<u+1<<' '<<v+1<<": "<<sum<<endl;
	return sum;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; ++i) w[i] = 1;
	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		cin >> u >> v;
		edj[--u].push_back(make_pair(--v, -1));
		edj[v].push_back(make_pair(u, -1));
	}
	int bestmx = 2000000001;
	int besti = 0;
	for (int i = 0; i < n; ++i) {
		int mx = 0;
		for (int j = 0; j < edj[i].size(); ++j) {
			mx = max(mx, calc(i, j));
		}
		if (mx < bestmx) {
			bestmx = mx;
			besti = i;
		}
	}
	cout << besti+1<<' '<<bestmx;
}
