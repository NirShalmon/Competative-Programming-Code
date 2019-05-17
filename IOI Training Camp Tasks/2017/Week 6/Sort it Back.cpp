/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>

using namespace std;

int n, k;
int nx[500000];
int pr[500000];
int a[500000];
int d[500001];
vector<int> lis;

void remove(int r) {
	if (pr[r] != -1) nx[pr[r]] = nx[r];
	if (nx[r] != -1) pr[nx[r]] = pr[r];
}

void insertBefore(int r, int m) {
	if (pr[m] != -1) nx[pr[m]] = r;
	nx[r] = m;
	pr[r] = pr[m];
	pr[m] = r;
}

void insertAfer(int r, int m) {
	if (nx[m] != -1) pr[nx[m]] = r;
	pr[r] = m;
	nx[r] = nx[m];
	nx[m] = r;
}

void findLIS() {
	d[1] = 0;
	d[0] = -1;
	pr[0] = -1;
	int l = 1;
	for (int i = 1; i < n; ++i) {
		int lo = 0;
		int hi = l;
		while (lo < hi) {
			int mid = (lo + hi + 1) / 2;
			if (a[i] > a[d[mid]]) {
				lo = mid;
			} else {
				hi = mid - 1;
			}
		}
		pr[i] = d[lo];
		d[lo + 1] = i;
		if (lo == l)++l;
	}
	int p = d[l];
	lis = vector<int>(l);
	while (l-- > 0) {
		lis[l]= a[p];
		p = pr[p];
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> k;
	/*for(int i = 0; i < n; ++i)cin>>a[i];
	findLIS();*/
	for (int i = 0; i < n; ++i) {
		nx[i] = i + 1;
		pr[i] = i - 1;
	}
	nx[n - 1] = -1;
	for (int i = 0; i < k; ++i) {
		char a;
		int r, m;
		cin >> a >> r >> m;
		--r; --m;
		remove(r);
		if (a == 'A') insertBefore(r, m);
		else insertAfer(r, m);
	}
	int c = 0;
	while (pr[c] != -1)++c;
	for (int i = 0; i < n; ++i) {
		a[i] = c;
		c = nx[c];
	}
	findLIS();
	cout << n - lis.size() << endl;
	int j = 1;
	for(int i = lis[0] - 1; i >= 0; --i) cout << "A " << i + 1 << ' ' << i + 2 << endl;
	for (int i = lis[0] + 1; i < n; ++i) {
		if (i == lis[j]) {
			j = (j + 1) % lis.size();
		}else cout << "B " << i + 1 << ' ' << i << endl;
	}
}