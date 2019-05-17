/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n;
string s;
int suf[100001];
int sufRev[100001];
int obj[2][100001];
int lcp[100000];

void cntSort(int *a, int *r) {
	static vector<int> c[100002];
	for (int i = 0; i < n; ++i) c[a[r[i]]+1].push_back(r[i]);	
	int i = n-1;
	for (int j = max(n,200); j >= 0; --j) {
		while (!c[j].empty()) {
			suf[i--] = c[j].back();
			c[j].pop_back();
		}
	}
}

void rdxSort() {
	cntSort(obj[1],suf);
	cntSort(obj[0],suf);
}

void genSuffixArray() {
	for (int i = 0; i < n; ++i) {
		obj[0][i] = s[i];
		obj[1][i] = -1;
	}
	for (int k = 0; (1 << k) < 2 * n; ++k) {
		for (int i = 0; i < s.size(); ++i) suf[i] = i;
		//sort(suf, suf + n, [&](const int &a, const int &b) {return obj[a] < obj[b]; });
		rdxSort();
		for (size_t i = 0; i < n; i++) sufRev[suf[i]] = i;
		for (int i = 1; i < n; ++i) {
			if (obj[0][suf[i]] == obj[0][suf[i - 1]] && obj[1][suf[i]] == obj[1][suf[i - 1]]) sufRev[suf[i]] = sufRev[suf[i - 1]];
		}
		for (int i = 0; i < n; ++i) {
			obj[1][i] = (i + (1 << k)) >= n ? -1 : sufRev[i + (1 << k)];
			obj[0][i] = sufRev[i];
		}
	}
}

void calcLcp() {
	for (size_t i = 0; i < n; i++) sufRev[suf[i]] = i;
	int last = 0;
	lcp[n - 1] = 0;
	for (int i = 0; i < n-1; ++i) {
		int j = suf[sufRev[i] - 1]; //prev suffix in array
		lcp[i] = max(0,last - 1);
		for (int t = last; t + i < n && t + j < n; ++t) {
			if (s[i + t] == s[j + t])++lcp[i];
			else break;
		}
		last = lcp[i];
	}
}



int main() {
	ios::sync_with_stdio(false);
	cin >> s;
	s.push_back('$');
	n = s.size();
	genSuffixArray();
	calcLcp();
	for (int i = 0; i < n; ++i) cout << lcp[i]<<'\n';
}