/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<algorithm>
#include<set>

using namespace std;
int a[3000][3000];
set<int> s;

int b[3001][3001];

int r, c, h, w;

bool canBe(int k) {
	for (size_t y = 0; y < r; ++y) {
		for (size_t x = 0; x < c; x++) {
			if (a[y][x] < k) {
				b[y+1][x+1] = -1;
			} else if (a[y][x] == k) {
				b[y+1][x+1] = 0;
			} else {
				b[y+1][x+1] = 1;
			}
		}
	}
	for (size_t y = 1; y <= r; y++) {
		for (size_t x = 1; x <= c; x++) {
			b[y][x] += b[y - 1][x] + b[y][x - 1] - b[y - 1][x - 1];
			if (y >= h && x >= w && b[y][x] - b[y - h][x] - b[y][x - w] + b[y - h][x - w] <= 0) {
				return true;
			}
		}
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> r >> c >> h >> w;
	for (int y = 0; y < r; ++y) {
		for (size_t x = 0; x < c; x++) {
			cin >> a[y][x];
		}
	}
	int lo = w * h / 2;
	int hi = r * c - w * h / 2;
	while (lo < hi) {
		int t = (lo + hi) / 2;
		if(canBe(t)){
			hi = t;
		} else {
			lo = t+1;
		}
	}
	cout << hi;
}
