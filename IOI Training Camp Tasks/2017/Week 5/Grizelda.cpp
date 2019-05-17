/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

pair<int, int> p[10000];
int b[10000];
int l[10000];
int n, t;

void compress() {
	sort(p, p + n);
	for (size_t i = 0; i < n; i++) {
		p[i].first = i;
		swap(p[i].first, p[i].second);
	}
	sort(p, p + n);
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n>>t;
	for (size_t i = 0; i < n; i++) {
		cin >> p[i].first >> p[i].second;
	}
	compress();
	int ans = 0;
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < i; j++) {
			if (p[j].second < p[i].second) ++b[i];
		}
	}
	for (size_t i = 0; i < n; i++) {
		int d = 0;
		for (size_t j = p[i].second; j < n; j++) {
			++l[j];
		}
		for (size_t j = i+1; j < n; j++) {
			int in = 0;
			if (p[j].second < p[i].second) {
				in = d - (b[j] - l[p[j].second]);
				++d;
			} else in = (b[j] - l[p[j].second]) - d;
			if (in <= t) ++ans;
		}
	}
	cout << ans;
}