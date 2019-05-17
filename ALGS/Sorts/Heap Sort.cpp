/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;

int n;
int a[100001];

#define up(u) (u>>1)
#define right(u) ((u<<1)+1)
#define left(u) (u<<1)

void push(int x) {
	int u = n++;
	a[u] = x;
	while (u > 1 && a[u] < a[up(u)]) {
		swap(a[u], a[up(u)]);
		u = up(u);
	}
}

int pop() {
	int ans = a[1];
	a[1] = a[--n];
	int u = 1;
	while((left(u) < n &&a[u] > a[left(u)]) || (right(u) < n &&a[u] > a[right(u)])) {
		if (right(u) < n && a[right(u)] < a[left(u)]) {
			swap(a[u], a[right(u)]);
			u = right(u);
		} else {
			swap(a[u], a[left(u)]);
			u = left(u);
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	int t,q;
	n = 1;
	cin >> t;
	while (t--) {
		cin >> q;
		push(q);
	}
	while (n > 1) cout << pop() << ' ';
}