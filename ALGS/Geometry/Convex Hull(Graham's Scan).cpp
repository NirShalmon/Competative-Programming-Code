/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

long long n, x[100000], y[100000];
int idx[100000];

long long mult(int baseA, int a, int baseB, int b) {
	return  (x[a] - x[baseA]) * (y[b] - y[baseB]) - (y[a] - y[baseA]) * (x[b] - x[baseB]);
}

bool cmp(int a, int b) {
	auto t = mult(idx[0], a,idx[0], b);
	if (t != 0) return t > 0;
	if(y[a] != y[b]) return y[a] < y[b]; //closer first
	return x[a] < x[b];
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (size_t i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
		idx[i] = i;
	}
	sort(idx, idx + n, [&](int a, int b) {return (y[a] != y[b]) ? (y[a] < y[b]) : (x[a] < x[b]); }); //to find lowest leftmost point
	sort(idx + 1, idx + n, cmp); //order by angle
	vector<int> p = { idx[0],idx[1] };
	for (int i = 2; i < n; ++i) {
		while (p.size() >= 2 && mult(p[p.size() - 2], p.back(), p.back(), idx[i]) <= 0) p.pop_back();
		p.push_back(idx[i]);
	}
	for (int i : p) cout << x[i] << ' ' << y[i] << '\n';
}