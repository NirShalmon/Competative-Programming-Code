/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n;
vector<int> rf[501];
vector<int> rg[501];

int main() {
	ios::sync_with_stdio(false);
	int t;
	cin >>t>> n;
	while (t--) {
		for (size_t i = 1; i <= n; i++) {
			rf[i].clear();
			rg[i].clear();
		}
		for (size_t i = 1; i <= n; i++) {
			int a;
			cin >> a;
			rf[a].push_back(i);
		}
		for (size_t i = 1; i <= n; i++) {
			int a;
			cin >> a;
			rg[a].push_back(i);
		}
		set<int> pos;
		queue<pair<int, int>> q;
		for (int i = 1; i <= n; ++i) {
			q.push({ i,i });
			pos.insert(i * 1000 + i);
		}
		while (!q.empty()) {
			auto u = q.front();
			q.pop();
			for (int a : rf[u.first]) {
				for (int b : rf[u.second]) {
					int t = a;
					int r = b;
					if (t > r)swap(t, r);
					if (pos.find(t * 1000 + r) == pos.end()) {
						pos.insert(t * 1000 + r);
						q.push({ t,r });
					}
				}
			}
			for (int a : rg[u.first]) {
				for (int b : rg[u.second]) {
					int t = a;
					int r = b;
					if (t > r)swap(t, r);
					if (pos.find(t * 1000 + r) == pos.end()) {
						pos.insert(t * 1000 + r);
						q.push({ t,r });
					}
				}
			}
		}
		if (pos.size() == n * (n + 1) / 2) cout << 1 << endl;
		else cout << 0 << endl;
	}
}

