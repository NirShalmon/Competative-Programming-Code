/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n;
string s;
int pos[1000000], len[1000000], par[1000000],path[1000000];
map<char, int> to[1000000], link[1000000];
int sz = 2;

void attach(int child, int parent, char firstChar, int childLen) {
	to[parent][firstChar] = child;
	par[child] = parent;
	len[child] = childLen;
}

void extend(int i) {
	int v, vlen = n - i, old = sz - 1, pathsz = 0;
	for (v = old; link[v].count(s[i]) == 0; v = par[v]) {
		path[pathsz++] = v;
		vlen -= len[v];
	}
	int w = link[v][s[i]];
	if (to[w].count(s[i + vlen]) != 0) { //w!=w'
		int u = to[w][s[i + vlen]];
		for (pos[sz] = pos[u]-len[u]; s[pos[sz]] == s[i + vlen]; pos[sz] += len[v]) {
			v = path[--pathsz];
			vlen += len[v];
		}
		attach(sz, w, s[pos[u] - len[u]], len[u] - (pos[u] - pos[sz]));
		attach(u, sz, s[pos[sz]], pos[u] - pos[sz]);
		link[v][s[i]] = sz;
		w = sz++;
	}
	link[old][s[i]] = sz;
	attach(sz, w, s[i + vlen], n - i - vlen);
	pos[sz++] = n;
}



int main() {
	ios::sync_with_stdio(false);
	cin >> s;
	s.push_back('$');
	n = s.size();
	len[1] = 1; pos[1] = 0; par[1] = 0;
	for (int i = 0; i < 255; ++i) link[0][i] = 1;
	for (int i = n - 1; i >= 0; --i) extend(i);
}