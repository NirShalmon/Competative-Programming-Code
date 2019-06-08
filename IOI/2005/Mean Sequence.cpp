/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;


int main() {
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	int up = 2000000000;
	int down = -up;
	int carry = 0, prev = 0, sign = 1;
	for (size_t i = 0; i < n; i++) {
		sign *= -1;
		int t;
		cin >> t;
		carry = 2 * t - carry;
		if (sign == 1) down = max((prev - carry) / 2, down);
		else up = min((carry - prev) / 2, up);
		prev = carry;
	}
	cout << max(0, up - down + 1);
}
