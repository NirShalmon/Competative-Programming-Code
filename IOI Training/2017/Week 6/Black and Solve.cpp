/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>

using namespace std;

int n, t;
int cc[500001];
int rc[500001];

int main() {
	ios::sync_with_stdio(false);
	cin >> t >> n;
	while (t--) {
		int sum = 0;
		for (size_t i = 0; i <= n; i++) {
			cc[i] = 0;
			rc[i] = 0;
		}
		for (size_t i = 0; i < n; i++) {
			int a;
			cin >> a;
			cc[a]++;
			sum += a;
		}
		for (size_t i = 0; i < n; i++) {
			int a;
			cin >> a;
			rc[a]++;
			sum -= a;
		}
		if (sum != 0) {
			cout << 0 << endl;
			continue;
		}
		int cLarger = n - cc[0];
		int csum = 0;
		int rsum = 0;
		int tl = n;
		for (size_t i = 1; tl <= n; i++) {
			while (rc[tl] == 0 && tl >= 1)--tl;
			if (tl < 1) {
				break;
			}
			csum += cc[i] * i;
			rsum += tl;
			cLarger -= cc[i];
			--rc[tl];
			if (csum + cLarger * i < rsum) {
				cout << 0 << endl;
				goto end;
			}
		}
		cout << 1 << endl;
	end:
		n = n;
	}
}