/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<algorithm>

using namespace std;

#define MN (1<<18)

struct cmp {
	bool operator()(const pair<int, int> &a, const pair<int, int> &b) const{
		if (a.second < b.second) return true;
		else return a.second == b.second && a.first < b.first;
	}
};

int n;
vector<pair<bool, pair<int, int>>> in;
set<pair<int, int>, cmp> s;
map<pair<int, int>, int> mp;
int mx[MN];
int seg[2*MN];
char lg[2*MN];

void update(int i, int v) {
	for (seg[i += MN] = v; i > 0; i >>= 1) {
		seg[i >> 1] = max(seg[i], seg[i ^ 1]);
	}
}

int find(int l, int v) {
	l += MN;
	while (seg[l] < v) {
		if (l & 1) {
			if (lg[++l] != 0) {
				return -1;
			}
		} else {
			l >>= 1;
		}
	}
	while (l < MN) {
		l <<= 1;
		if (seg[l] < v)++l;
	}
	return l - MN;
}

vector<int> xs, ys;

int bsrch(int a, vector<int> &xs) {
	int lo = 0;
	int hi = xs.size() - 1;
	while (lo < hi) {
		int mid = (lo + hi+1) / 2;
		if (xs[mid] > a) {
			hi = mid - 1;
		} else {
			lo = mid;
		}
	}
	return lo;
}


int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; 1 << i < 2*MN; ++i) {
		lg[1<<i] = i;
	}
	for (int t = 0; t < n; ++t) {
		char c;
		cin >> c;
		if (c == 'Q') {
			int q;
			cin >> q;
			in.push_back(make_pair(true, make_pair(--q, -1)));
		} else {
			int a, b;
			cin >> a >> b;
			in.push_back(make_pair(false, make_pair(a, b)));
			xs.push_back(a);
			ys.push_back(b);
		}
		mx[t] = -1;
	}
	for (int i = 0; i < 2 * MN; ++i) {
		seg[i] = -1;
	}
	sort(xs.begin(), xs.end());
	sort(ys.begin(), ys.end());
	vector<pair<int, int>> pnt;
	for (int t = 0; t < n; ++t) {
		if (!in[t].first) {
			int a = bsrch(in[t].second.first,xs);
			int b = bsrch(in[t].second.second,ys);
			mp[make_pair(a, b)] = pnt.size();
			pnt.push_back(make_pair(a, b));
			s.insert(make_pair(a, b));
			if (mx[b] < a) {
				mx[b] = a;
				update(b, mx[b]);
			}
		} else {
			pair<int, int> p = pnt[in[t].second.first];
			if (mx[p.second] > p.first) {
				auto f = s.find(p);
				cout << mp[*(++f)] + 1 << endl;
			} else {
				int lo = find(p.second + 1, p.first);
				if (lo == -1) {
					cout << -1 << endl;
				} else {
					auto vv = s.lower_bound(make_pair(p.first, lo));
					pair<int, int> ans = *vv;
					cout << mp[ans] + 1 << endl;
				}
			}
		}
	}
}