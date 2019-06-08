/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n, m,w;
int a[20000];
int idx[20000];
int place[20000];
bool vis[20000];
vector<vector<int>> cycles;

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m>>w;
	for (size_t i = 0; i < n; i++) {
		cin >> a[i];
		idx[i] = i;
	}
	sort(idx, idx + n, [&](int b, int c) {return a[b] < a[c]; });
	for (size_t i = 0; i < n; i++) {
		place[idx[i]] = i;
	}
	vector<int> cur;
	for (size_t i = 0; i < n; i++) {
		if (!vis[i] && place[i] != i) {
			vis[i] = true;
			cur.clear();
			cur.push_back(i);
			int t = place[i];
			while (t != i) {
				cur.push_back(t);
				vis[t] = true;
				t = place[t];
			}
			cycles.push_back(cur);
		}
	}
	vector<vector<pair<int, int>>> ans;
	vector<pair<int, int>> v;
	int c = 0;
	for (int i = 0; i < cycles.size(); ++i) {
		int j = 0;
		beg:
		++c;
		while (c < w && j + 1 < cycles[i].size()) {
			v.push_back({ cycles[i][j],cycles[i][j + 1] });
			++j;
			++c;
		}
		if (j + 1 == cycles[i].size()) {
			v.push_back({ cycles[i].back(),cycles[i][0] });
			if (c >= w - 1) {
				ans.push_back(v);
				v.clear();
				c = 0;
			}
		}
		else {
			v.push_back({ cycles[i][j],cycles[i][0] });
			cycles[i][j] = cycles[i][0];
			ans.push_back(v);
			v.clear();
			c = 0;
			goto beg;
		}
	}
	if (v.size() != 0) ans.push_back(v);
	cout << ans.size() << endl;
	for (size_t i = 0; i < ans.size(); i++) {
		cout << ans[i].size() << ' ';
		for (int j = 0; j < ans[i].size(); ++j) {
			cout << ans[i][j].first+1 << ' ' << ans[i][j].second +1<< ' ';
		}
		cout << endl;
	}
}
