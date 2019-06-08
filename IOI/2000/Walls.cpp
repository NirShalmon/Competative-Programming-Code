/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

#define at min(cur, prev)][max(cur, prev)

vector<int> st;
vector<int> areas[250];
vector<int> edj[250];
int mp[250][250];
int d[30][250];

int main() {
	ios::sync_with_stdio(false);
	int m,n,l;
	cin >> m>>n>>l;
	st = vector<int>(l);
	for (int i = 0; i < l; ++i) {
		cin >> st[i];
		--st[i];
	}
	for (size_t i = 0; i < m; i++) {
		int sz,prev,cur,f;
		cin >> sz>>f;
		cur = f;
		areas[--cur].push_back(i);
		for (size_t j = 1; j < sz; j++) {
			prev = cur;
			cin >> cur;
			areas[--cur].push_back(i);
			if (mp[at] == 0) {
				mp[at] = i+1;
			} else {
				edj[i].push_back(mp[at]-1);
				edj[mp[at]-1].push_back(i);
			}
		}
		prev = cur;
		cur = --f;
		if (mp[at] == 0) {
			mp[at] = i+1;
		} else {
			edj[i].push_back(mp[at]-1);
			edj[mp[at]-1].push_back(i);
		}
	}
	for (size_t i = 0; i < l; i++) {
		int s = st[i];
		for (size_t j = 0; j < m; j++) {
			d[i][j] = -1;
		}
		queue<int> q;
		for (int u : areas[s]) {
			d[i][u] = 0;
			q.push(u);
		}
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (int v : edj[u]) {
				if (d[i][v] == -1) {
					d[i][v] = d[i][u] + 1;
					q.push(v);
				}
			}
		}
	}
	int best = 0;
	int bestv = 1000000000;
	for (int i = 0; i < m; ++i) {
		int sum = 0;
		for (int j = 0; j < l; ++j) {
			sum += d[j][i];
		}
		if (sum < bestv) {
			bestv = sum;
			best = i;
		}
	}
	cout << bestv << endl << best+1;
}
