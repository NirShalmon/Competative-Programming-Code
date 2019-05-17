/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n, m;
vector<int> edj[10000];
int k[10000];
int h[10000];
int p[10000];
bool vis[10000];
vector<vector<int>> cmp;

bool cmpv(const vector<int> &a, const vector<int> &b) {
	return a[0] < b[0];
}

vector<int> dfs(int u) {
	k[u] = h[u];
	vector<int> tmp = { u };
	for (int v : edj[u]) {
		if (!vis[v]) {
			h[v] = h[u] + 1;
			vis[v] = true;
			p[v] = u;
			auto q = dfs(v);
			k[u] = min(k[u],k[v]);
			if (k[v] >= h[v]) {
				cmp.push_back(q);
			} else for (int f : q)tmp.push_back(f);
		} else if(v != p[u]){
			k[u] = min(k[u], h[v]);
		}
	}
	return tmp;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n>>m;
	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		edj[--u].push_back(--v);
		edj[v].push_back(u);
	}
	for (int i = 0; i < n; ++i) k[i] = -1, vis[i] = false;
	for (int i = 0; i < n; ++i) {
		if (!vis[i]) {
			vis[i] = true;
			cmp.push_back(dfs(i));
		}
	}
	for (int i = 0; i < cmp.size(); ++i) {
		sort(cmp[i].begin(), cmp[i].end());
	}
	sort(cmp.begin(), cmp.end(), cmpv);
	for (auto v : cmp) {
		for (auto x : v) {
			cout << x+1 << ' ';
		}
		cout << endl;
	}
}