/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

pair<int, int> p[20000];
unordered_map<int, int> id;
int b[20000];
int l[20000];
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
	cin >> n >> t;
	for (size_t i = 0; i < n; i++) {
		cin >> p[i].first >> p[i].second;
		id[p[i].second] = i + 1;
	}
	compress();
	int ans = 999999999;
	int ida=1,idb = 1;
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
		for (size_t j = i + 1; j < n; j++) {
			int in = 0;
			if (p[j].second < p[i].second) {
				in = d - (b[j] - l[p[j].second]);
				++d;
			} else in = (b[j] - l[p[j].second]) - d;
			if (in + 2 >= t && in+2 < ans) {
				ans = in + 2;
				ida = id[p[i].first];
				idb = id[p[j].first];
			}
		}
	}
	cout << ida<<' '<<idb;
}
