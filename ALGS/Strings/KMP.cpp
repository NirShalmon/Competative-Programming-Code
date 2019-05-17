/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

string p, t;
int sz;
int pi[1100000];

int main() {
	ios::sync_with_stdio(false);
	cin >> p >> t;
	sz = p.size();
	p.push_back('$');
	for (char c : t) p.push_back(c);
	vector<int> ans;
	pi[0] = 0;
	for (int i = 1; i < p.size(); ++i) {
		pi[i] = pi[i-1];
		while (p[pi[i]] != p[i] && pi[i] > 0) {
			pi[i] = pi[pi[i] - 1];
		}
		if (p[pi[i]] == p[i]) ++pi[i];
		if (pi[i] >= sz) cout << i - sz*2 << ' ';
	}
}