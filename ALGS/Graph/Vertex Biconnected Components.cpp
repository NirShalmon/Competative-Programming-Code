/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

typedef struct lst {
	int val;
	lst *nxt;
} lst;

int n, m;
vector<int> edj[10000];
lst cur[10000];
lst* last[10000];
vector<vector<int>> comps;
int h[10000], up[10000];

vector<int> toVec(int id) {
	vector<int> ans;
	for (lst* p = &cur[id]; p; p = p->nxt) ans.push_back(p->val);
	return ans;
}

void dfs(int u,int p) {
	up[u] = h[u];
	for (int v : edj[u]) {
		if (h[v] == 0) {
			h[v] = h[u] + 1;
			dfs(v,u);
			up[u] = min(up[u], up[v]);
			if (up[v] < h[u]) {
				last[u]->nxt = &cur[v];
				last[u] = last[v];
			}
		}
		else up[u] = min(up[u], h[v]);
	}
	if (up[u] == h[u] - 1) {
		auto vec = toVec(u);
		vec.push_back(p);
		sort(vec.begin(), vec.end());
		comps.push_back(vec);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (size_t i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		edj[--u].push_back(--v);
		edj[v].push_back(u);
	}
	for (int i = 0; i < n; ++i) {
		cur[i].val = i;
		last[i] = &cur[i];
	}
	for (int i = 0; i < n; ++i) {
		if (h[i] == 0) {
			h[i] = 1;
			dfs(i,-1);
		}
	}
	sort(comps.begin(), comps.end(), [&](const vector<int> &a, const vector<int> &b) {return a[0] == b[0] ? a[1] < b[1] : a[0] < b[0]; });
	for (int i = 0; i < comps.size(); ++i) {
		for (int v : comps[i]) cout << v+1 << ' ';
		cout << '\n';
	}
}