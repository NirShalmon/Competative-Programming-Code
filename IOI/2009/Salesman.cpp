/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

typedef struct event{
	int loc, val;
} ev;

const int m = 1 << 19;

int n, u, d, s;
vector<ev> events[500000];
pair<int, int> seg[3][m * 2]; //seg 0: val - D*i. seg 1: val. seg 2: val + U*i.
int fromL[500000],fromR[500000],val[500000];

void update(int p, int v) {
	if (v != -100000000 && v < seg[1][p + m].first) return;
	seg[0][p + m] = { v - d*p,p };
	seg[1][p + m] = { v,p };
	seg[2][p + m] = { v + u*p,p };
	p = (p + m) / 2;
	while (p >= 1) {
		seg[0][p] = seg[0][p * 2] > seg[0][p * 2 + 1] ? seg[0][p * 2] : seg[0][p * 2 + 1];
		seg[1][p] = seg[1][p * 2] > seg[1][p * 2 + 1] ? seg[1][p * 2] : seg[1][p * 2 + 1];
		seg[2][p] = seg[2][p * 2] > seg[2][p * 2 + 1] ? seg[2][p * 2] : seg[2][p * 2 + 1];
		p /= 2;
	}
}

//max of seg[s] on [l,r)
//returns val,pos
pair<int, int> query(int s, int l, int r) {
	pair<int, int> ans = { -100000000,-1 };
	l += m; r += m;
	while (l < r) {
		if (l & 1) {
			if (seg[s][l].first > ans.first) {
				ans = seg[s][l];
			}
			l++;
		}
		if (r & 1) {
			--r;
			if (seg[s][r].first > ans.first) {
				ans = seg[s][r];
			}
		}
		l /= 2; r /= 2;
	}
	return ans;
}



int main() {
	ios::sync_with_stdio(false);
	cin >> n >> u >> d >> s;
	swap(u, d);
	for (int i = 0; i < n; ++i) {
		int t, l, m;
		cin >> t >> l >> m;
		events[--t].push_back({ --l,m });
	}
	--s;
	for (int i = 0; i < m; ++i) update(i, -100000000);
	update(s, 0);
	for (int i = 0; i < 500000; ++i) {
		if (events[i].empty()) continue;
		sort(events[i].begin(), events[i].end(), [&](const ev &a, const ev &b) {return a.loc < b.loc; });
		for (size_t j = 0; j < events[i].size(); j++) {
			auto a = query(2, 0, events[i][j].loc);
			auto b = query(0, events[i][j].loc, m);
			val[j] = events[i][j].val + max(a.first - u*events[i][j].loc, b.first + d*events[i][j].loc);
			fromL[j] = fromR[j] = val[j];
			if (j >= 1) {
				fromL[j] = max(fromL[j], fromL[j - 1] - u*(events[i][j].loc - events[i][j - 1].loc) + events[i][j].val);
			}
		}
		for (int j = (int)events[i].size() - 2; j >= 0; --j) {
			fromR[j] = max(fromR[j], fromR[j + 1] - d*(events[i][j + 1].loc - events[i][j].loc) + events[i][j].val);
		}
		for (size_t j = 0; j < events[i].size(); j++) {
			update(events[i][j].loc, max(fromR[j], fromL[j]));
		}
	}
	auto lop = query(2, 0, s);
	auto rop = query(0, s, m);
	cout << max(lop.first - u*s, rop.first + d*s);
}
