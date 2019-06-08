/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n;
string s[25001];
int longestIndex = 1;
string longest;

int getCommon(const string &a) {
	int ans = 0;
	while (ans < a.size() && ans < longest.size() && a[ans] == longest[ans])++ans;
	return ans;
}

bool cmp(const string &a, const string &b) {
	int ac = getCommon(a);
	int bc = getCommon(b);
	if (ac != bc) return ac < bc;
	return a < b;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	s[0] = "";
	for (size_t i = 1; i <= n; i++) {
		cin >> s[i];
		if (s[i].size() > s[longestIndex].size())longestIndex = i;
	}
	longest = s[longestIndex];
	sort(s+1, s+1 + n,cmp);
	vector<char> ans;
	for (size_t i = 1; i <= n; i++) {
		int com = 0;
		while (s[i - 1].size() > com && s[i].size() > com && s[i][com] == s[i - 1][com])++com;
		int deletes = s[i-1].size() - com;
		for (size_t j = 0; j < deletes; j++) {
			ans.push_back('-');
		}
		for (int j = com; j < s[i].size(); ++j) ans.push_back(s[i][j]);
		ans.push_back('P');
	}
	cout << ans.size() << '\n';
	for (size_t i = 0; i < ans.size(); i++) {
		cout << ans[i] << '\n';
	}
}
