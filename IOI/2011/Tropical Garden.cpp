/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n, m, p,q;
vector<int> oedj[150000];
int edj[300000];
vector<int> revEdj[300000];
int d[2][300000];
int ans[2][1000000];

int getCycleLen(int start) {
	int c = edj[start];
	for (int i = 1; i <= n*2; ++i) {
		if (c == start) return i;
		c = edj[c];
	}
	return -1;
}

void bfs(int start, int* dis) {
	dis[start] = 0;
	queue<int> qu;
	qu.push(start);
	while (qu.size()) {
		int u = qu.front();
		qu.pop();
		for (int v : revEdj[u]) {
			if (dis[v] == -1) {
				dis[v] = dis[u] + 1;
				qu.push(v);
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m >> p;
	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		oedj[u].push_back(v);
		oedj[v].push_back(u);
	}

	for (int i = 0; i < n; ++i) {
		if (oedj[oedj[i][0]][0] == i) edj[i] = oedj[i][0] + n;
		else edj[i] = oedj[i][0];
		if (oedj[i].size() == 1) edj[i + n] = edj[i];
		else {
			if (oedj[oedj[i][1]][0] == i) edj[i+n] = oedj[i][1] + n;
			else edj[i+n] = oedj[i][1];
		}
		revEdj[edj[i]].push_back(i);
		revEdj[edj[i + n]].push_back(i + n);
		d[0][i] = d[1][i] = d[0][i + n]  = d[1][i+n] = -1;
	}
	int len0 = getCycleLen(p);
	int len1 = getCycleLen(p + n);
	bfs(p, d[0]);
	bfs(p + n, d[1]);
	for (int i = 0; i < n; ++i) {
		if (d[0][i] != -1) {
			ans[0][d[0][i]]++;

		}
		if (d[1][i] != -1) {
			ans[1][d[1][i]]++;
		}
	}
	if (len0 != -1) {
		for (int i = len0; i <6 * n; ++i) {
			ans[0][i] += ans[0][i - len0];
		}
	}
	if (len1 != -1) {
		for (int i = len1; i < 6 * n; ++i) {
			ans[1][i] += ans[1][i - len1];
		}
	}
	cin >> q;
	for (int i = 0; i < q; ++i) {
		int k;
		cin >> k;
		int f = k;
		int res = 0;
		if (k > n*2) {
			if (len0 == -1) k = 3 * n;
			else k = ((n*2) / len0)*len0 + len0 + k % len0;
		}
		res = ans[0][k];
		if (f > n * 2) {
			if (len1 == -1) f = 3 * n;
			else f = ((n * 2) / len1)*len1 + len1 + f % len1;
		}
		res += ans[1][f];
		cout << res << ' ';
	}
}
