/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>

using namespace std;

int fen[2][17];

void update(int t,int x,int v) {
	for (; x <= 16; x += x&(-x)) fen[t][x] += v;
}

int query(int t, int x) {
	int ans = 0;
	for (; x; x -= x&(-x)) ans = fen[t][x];
	return ans;
}

int query(int b) {
	return b*query(0, b) - query(1, b);
}

int rangeQuery(int a, int b) {
	return query(b) - query(a - 1);
}

void rangeUpdate(int a, int b, int v) {
	update(0, a, v);
	update(0, b + 1, -v);
	update(1, a, v*(a - 1));
	update(1, b + 1, -v*b);
}

int main() {
	ios::sync_with_stdio(false);
	return 0;
}