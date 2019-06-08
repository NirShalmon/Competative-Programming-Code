/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

class uf {
public:
	int n;
	vector<int> p;
	vector<int> rank;

	uf() {}

	uf(int N) {
		n = N;
		p.resize(n);
		rank.resize(n);
		for (size_t i = 0; i < n; i++) {
			p[i] = i;
			rank[i] = 0;
		}
	}

	int root(int v) {
		while (p[v] != v) {
			p[v] = p[p[v]];
			v = p[v];
		}
		return v;
	}

	void unite(int u, int v) {
		int x = root(u);
		int y = root(v);
		if (x == y) return;
		if (rank[x] < rank[y]) {
			p[x] = y;
		} else if (rank[y] < rank[x]) p[y] = x;
		else {
			p[x] = y;
			++rank[y];
		}
	}
};

int n, l;
vector<int> edj[1000000];
int score[1000000];
int reqScore = 0;
int ans;
uf fulluf;
vector<pair<int, uf>> can;
int state = 0;

void scoreNear(int u) {
	ans = 0;
	++reqScore;
	for (int v : edj[u]) {
		if (++score[v] == reqScore) ++ans;
	}
	if (++score[u] == reqScore) ++ans;
}

void rankScore(int u) {
	if (edj[u].size() == 3) scoreNear(u);
	else if (edj[u].size() == 4) {
		if (++score[u] == ++reqScore) ans = 1;
		else ans = 0;
	}
}

int countCycleEdges[1000000];
int h[1000000];

int dfs(int u) {
	int w = h[u];
	for (int v : edj[u]) {
		if (h[v] == -1) {
			h[v] = h[u] + 1;
			int b = dfs(v);
			w = min(b, w);
			if (b <= h[u]) {
				countCycleEdges[u]++;
				countCycleEdges[v]++;
			}
		} else if (h[v] < h[u] - 1) {
			w = min(w, h[v]);
			countCycleEdges[u]++;
			countCycleEdges[v]++;
		}
	}
	return w;
}

void doCount() {
	for (size_t i = 0; i < n; i++) {
		countCycleEdges[i] = 0;
		h[i] = -1;
	}
	for (size_t i = 0; i < n; i++) {
		if (h[i] == -1) {
			h[i] = 0;
			dfs(i);
		}
	}
}


void fillUf(uf &uf, int u) {
	for (size_t i = 0; i < n; i++) {
		if (i != u) {
			for (int v : edj[i]) {
				if (v != u) {
					uf.unite(i, v);
				}
			}
		}
	}
}

void addEdge(int u, int v) {
	edj[u].push_back(v);
	edj[v].push_back(u);
	rankScore(u);
	rankScore(v);
	if (state == 0) { //no cycles yet
		if (fulluf.root(u) == fulluf.root(v)) { //first cycle
			doCount();
			++reqScore;
			ans = 0;
			for (int i = 0; i < n; ++i) {
				if (countCycleEdges[i] == 2) {
					if (++score[i] == reqScore) ++ans;
				}
			}
			state = 1;
		}else fulluf.unite(u, v);
	} else if (state == 1) { //one cycle
		if (fulluf.root(u) == fulluf.root(v)) { //second cycle
			doCount();
			++reqScore;
			ans = 0;
			for (int i = 0; i < n; ++i) {
				if (countCycleEdges[i] >= 3) {
					if (++score[i] == reqScore) {
						++ans;
						can.push_back({ i, uf(n) });
						fillUf(can.back().second,i);
					}
				}
			}
			state = 2;
		}else fulluf.unite(u, v);
	} else {
		for (int i = 0; i < can.size(); ++i) {
			if (u != can[i].first && v != can[i].first) {
				if (can[i].second.root(u) == can[i].second.root(v)) {
					--score[can[i].first];
					ans = 0;
					for (size_t j = 0; j < can.size(); j++) {
						if (score[can[j].first] == reqScore)++ans;
					}
				} else can[i].second.unite(u, v);
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> l;
	ans = n;
	fulluf = uf(n);
	for (size_t i = 0; i < l; i++) {
		int u, v;
		cin >> u;
		if (u == -1) {
			cout << ans << '\n';
		} else {
			cin >> v;
			addEdge(u, v);
		}
	}
}
