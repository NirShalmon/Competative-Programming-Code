/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

vector<pair<int, int>> edj[100000];
int d[100000];
int p[100000];

int main() {
	ios::sync_with_stdio(false);
	int n, m, s;
	cin >> n >> m;
	for (size_t i = 0; i < n; i++) {
		edj[i].clear();
	}
	for (size_t i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		edj[--u].push_back({ --v,w });
		edj[v].push_back({ u,w });
	}
	cin >> s;
	--s;
	fill(d, d + n, 1000000001);
	fill(p, p + n, -2);
	d[s] = 0;
	p[s] = s;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	q.push({ 0,s });
	while (!q.empty()) {
		auto r = q.top();
		q.pop();
		int u = r.second;
		int du = r.first;
		if (du == d[u]) {
			for (auto e : edj[u]) {
				int v = e.first;
				int w = e.second;
				if (du + w < d[v]) {
					d[v] = du + w;
					p[v] = u;
					q.push({ d[v],v });
				}
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		cout << (d[i] == 1000000001 ? -1 : d[i]) << ' ';
	}
	cout << endl;
	for (int i = 0; i < n; ++i) {
		cout << p[i] + 1 << ' ';
	}
}