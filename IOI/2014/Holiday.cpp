/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<functional>

using namespace std;

#define mn (1<<17)

int n, s, d, at[100000];
long long dp[4][250000];
long long bestwithi[250001], cpy[250001];
const long long inf = 1000000000000000000ll;
long long seg[mn<<1];
vector<int> sv,tsv;
int on[mn << 1];
int p;

bool cmp(const int &a, const int &b) {
	return at[a] > at[b];
}

void update(int x,bool o) {
	int v = at[tsv[x]];
	x = (sv[tsv[x]] + mn);
	int m = o ? 1 : -1;
	for (; x; x >>= 1) {
		on[x] += m;
		seg[x] += m*v;
	}
}

long long query(int k) {
	long long ans = 0;
	int x = 1;
	if (on[1] <= k) 
		return seg[1];
	while (x < mn) {
		if (on[x * 2] <= k) {
			ans += seg[x * 2];
			k -= on[x * 2];
			if (on[x * 2 + 1] == k) return ans + on[x * 2 + 1];
			x = x * 2 + 1;
		} else {
			x *= 2;
		}
	}
	return ans;
}

void rec(int st, int et, int sd, int ed,int type) {
	if (st == et) return;
	int mid = (st + et) / 2;
	while (p < sd) update(p++, true);
	while (p > sd) update(--p, false);
	long long ans = 0;
	int bestp = 0;
	while (p < ed) {
		update(p, true);
		long long res = query(mid - type*p);
		if (res > ans) {
			ans = res;
			bestp = p;
		}
		p++;
	}
	bestwithi[mid] = ans;
	rec(mid + 1, et, bestp, ed,type);
	rec(st, mid, sd, bestp + 1,type);
}

void init(vector<int> &v) {
	tsv = v;
	sort(v.begin(), v.end(), cmp);
	for (int i = 0; i < v.size(); ++i) sv[v[i]] = i;
	for (int i = 0; i < mn << 1; ++i)on[i] = 0, seg[i] = 0;
	p = 0;
}

void calc1(vector<int> v) {
	if (v.size() == 0) {
		fill(bestwithi, bestwithi + d + 1, 0);
		return;
	}
	init(v);
	rec(0, d + 1, 0, v.size(),1);
}

void calc2(vector<int> v) {
	if (v.size() == 0) {
		fill(bestwithi, bestwithi + d + 1, 0);
		return;
	}
	init(v);
	rec(0, d + 1, 0, v.size(),2);
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> s >> d;
	sv = vector<int>(n);
	vector<int> ind;
	for (int i = 0; i < n; ++i) {
		cin >> at[i];
		ind.push_back(i);
	}
	long long ans = 0;
	calc1(vector<int>(ind.begin() + s, ind.begin() + n));
	ans = bestwithi[d];
	vector<int> left;
	for (int i = s; i >= 0; --i) left.push_back(i);
	calc1(left);
	ans = max(bestwithi[d], ans);
	calc2(left);
	for (int i = 0; i <= d; ++i) cpy[i] = bestwithi[i];
	calc1(vector<int>(ind.begin() + s + 1, ind.begin() + n));
	for (int i = 0; i <= d - 1; ++i) {
		ans = max(ans, cpy[i] + bestwithi[d - 1 - i]);
	}
	calc2(vector<int>(ind.begin() + s, ind.begin() + n));
	for (int i = 0; i <= d; ++i) cpy[i] = bestwithi[i];
	left.erase(left.begin());
	calc1(left);
	for (int i = 0; i <= d - 1; ++i) {
		ans = max(ans, cpy[i] + bestwithi[d - 1 - i]);
	}
	cout << ans;

}
