/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>
#include<queue>
#include<functional>
#include<map>
#include<stack>

using namespace std;

int n, m;
vector<pair<int, int>> edj[1500];
pair<int, long long> d[1500][1500];
long long from[1500][1500];
const long long mod = 1000000007;
bool v[1500];
vector<pair<int, int>> g;
int ww[1500][1500];

void f(int s) {
	for (int i = 0; i < n; ++i) {
		v[i] = false;
		from[s][i] = 1;
	}
	priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> q;
	d[s][s] = make_pair(0, 1);
	q.push(make_pair(0, make_pair(s, -1)));
	stack<pair<int, int>> fq;
	while (!q.empty()) {
		pair<int, pair<int, int>> t = q.top();
		q.pop();
		int du = t.first;
		int u = t.second.first;
		if (du == d[s][u].first) {
			if (t.second.second != -1) {
				d[s][u].second += d[s][t.second.second].second;
				d[s][u].second %= mod;
				fq.push({ t.second.second,u });
			}
			if (!v[u]) {
				for (int i = 0; i < edj[u].size(); ++i) {
					int v = edj[u][i].first;
					int w = edj[u][i].second;
					if (du + w <= d[s][v].first) {
						d[s][v].first = du + w;
						q.push(make_pair(du + w, make_pair(v, u)));
					}
				}
			}
			v[u] = true;
		}
	}
	while (!fq.empty()) {
		auto tp = fq.top();
		fq.pop();
		from[s][tp.first] += from[s][tp.second];
		from[s][tp.first] %= mod;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			ww[i][j] = 2000000000;
		}
	}
	for (int i = 0; i < m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		g.push_back(make_pair(u - 1, edj[u - 1].size()));
		edj[--u].push_back(make_pair(--v, w));
		ww[u][v] = min(ww[u][v], w);
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			d[i][j] = make_pair(1000000000, 0);
		}
	}
	for (int i = 0; i < n; ++i) {
		f(i);
		/*for(int j = 0; j < edj[2].size(); ++j){
		cout<<(edj[2][j].first)<<endl;
		}
		cout<<endl;*/
	}
	for (int u = 0; u < n; ++u) {
		for (int i = 0; i < edj[u].size(); ++i) {
			long long eda = 0;
			long long eba = 0;
			int v = edj[u][i].first;
			if (edj[u][i].second == ww[u][v]) {
				for (int a = 0; a < n; ++a) {
					if (d[a][u].first + ww[u][v] == d[a][v].first) {
						eda += d[a][u].second * from[a][v];
						eda %= mod;
					}
					/*for (int b = 0; b < n; ++b) {
						if (d[a][u].first + edj[u][i].second + d[v][b].first == d[a][b].first) {
							eba = (eba + (d[a][u].second * d[v][b].second) % mod) % mod;
						}
					}*/
				}
			}
			/*if (eda != eba) {
				cout << "duck";
			}*/
			edj[u][i].second = eda;
		}
	}
	/*for (int i = 0; i < n; ++i) {
	for (int j = 0; j < n; ++j) {
	cout << i << ' ' << j << ' ' << d[i][j].first << ' ' << d[i][j].second << endl;
	}
	}*/
	for (int i = 0; i < g.size(); ++i) {
		cout << edj[g[i].first][g[i].second].second << endl;
	}
}
