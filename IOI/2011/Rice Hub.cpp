/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

long long r, l, b;
int x[100000];

int solve() {
	int left = 0;
	int right = 0;
	int ans = 1;
	long long c = 0;
	int prevPos = 0;
	for (right = 1; right < r; ++right) {
		c += x[right] - x[prevPos];
		if ((right - left) % 2 == 0) {
			c -= x[prevPos + 1] - x[prevPos];
			++prevPos;
		}
		while (c > b) {
			c -= x[prevPos] - x[left];
			++left;
			if ((right - left) % 2 == 0) {
				c -= x[prevPos + 1] - x[prevPos];
				prevPos++;
			}
		}
		ans = max(ans, right - left + 1);
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> r >> l >> b;
	for (int i = 0; i < r; ++i)cin >> x[i];
	cout << solve();
}
