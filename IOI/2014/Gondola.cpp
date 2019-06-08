/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int t;
int n, in[100000];

bool valid() {
	int c = -1;
	vector<int> bc(in,in+n);
	for (size_t i = 0; i < n; i++) {
		if (in[i] <= n) {
			int v = (in[i] - i + n) % n;
			if (c == -1) c = v;
			else if (c != v) return false;
		}
	}
	sort(bc.begin(), bc.end());
	for (size_t i = 1; i < n; i++) {
		if (bc[i] == bc[i - 1]) return false;
	}
	return true;
}

vector<int> replacement() {
	vector<pair<int, int>> rep;
	int c = -1;
	for (size_t i = 0; i < n; i++) {
		if (in[i] > n) rep.push_back({ in[i],i });
		else c = (in[i] - i + n) % n;
	}
	if (c == -1) c = 1;
	sort(rep.begin(), rep.end());
	int v = n + 1;
	vector<int> ans;
	for (size_t i = 0; i < rep.size(); i++) {
		bool e = false;
		while (v <= rep[i].first) {
			if(e) ans.push_back(v - 1);
			else {
				int q = (rep[i].second + c) % n;
				q = q == 0 ? n : q;
				ans.push_back(q);
			}
			e = true;
			++v;
		}
	}
	return ans;
}

long long bp[33];
const int mod = 1000000009;

long long power(long long x, long long n) {
	bp[0] = x;
	long long ans = 1;
	for (size_t i = 1; i < 32; i++) bp[i] = (bp[i - 1] * bp[i - 1]) % mod;
	for (size_t i = 0; i < 32; i++) {
		if (n & (1ll << i)) {
			ans = (ans * bp[i]) % mod;
		}
	}
	return ans;
}

long long cnt() {
	vector<int> rep = { n };
	for (size_t i = 0; i < n; i++) {
		if (in[i] > n) rep.push_back(in[i]);
	}
	sort(rep.begin(), rep.end());
	long long ans = 1;
	for (size_t i = 1; i < rep.size(); i++) {
		int exp = rep[i] - rep[i - 1] - 1;
		int x = rep.size() - i;
		if (rep.size() == n + 1 && i == 1) ++exp;
		ans = (ans * power(x, exp)) % mod;
	}
	return ans;
}

int main() {
	//cout << (1ll<<31);
	ios::sync_with_stdio(false);
	cin >> t>>n;
	for (int i = 0; i < n;)cin >> in[i++];
	if (t <= 3) cout << valid();
	else if (t <= 6) {
		auto ans = replacement();
		cout << ans.size() << ' ';
		for (int v : ans) cout << v << ' ';
	} else {
		if (valid()) cout << cnt();
		else cout << 0;
	}
}
