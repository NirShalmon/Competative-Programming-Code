/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n;
vector<vector<char>> lines;

void prnt(vector<char> &s) {
	for (int i = s.size()-1; i >= 0; --i) cout << (int)s[i] << ' ';
	cout << endl;
}

void rec(vector<vector<char>> v,vector<char> &s) {
	if (v.size() == 0) {
		prnt(s);
		return;
	}
	for (int h = 0; h < v.size(); ++h) {
		if (h == v.size() - 1 || v[h].size() > 1) {
			vector<vector<char>> tv = v;
			char a = h - 1;
			char q = *v[h].rbegin();
			tv[h].pop_back();
			if (tv[h].size() == 0) tv.pop_back();
			while (a >= 0) {
				if (tv[a][0] > q) goto next;
				int i = 0;
				while (i + 1 < tv[a].size() && tv[a][i + 1] < q)++i;
				swap(tv[a][i], q);
				--a;
			}
			s.push_back(q);
			rec(tv, s);
			s.pop_back();
		}
	next:
		h = h;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	lines = vector<vector<char>>(n);
	for (size_t i = 0; i < n; i++) {
		int a;
		cin >> a;
		for (size_t j = 0; j < a; j++) {
			int t;
			cin >> t;
			lines[i].push_back(t);
		}
	}
	vector<char> qq;
	rec(lines, qq);
}


