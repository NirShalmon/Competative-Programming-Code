/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>

using namespace std;

int n, a;
#define max 1000001
int c[max];

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a;
		++c[a];
	}
	for (int i = 0; i < max; ++i) 
		while(c[i]--) cout << i << ' ';	
}