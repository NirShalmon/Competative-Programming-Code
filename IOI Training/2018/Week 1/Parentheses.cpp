/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

int t[400001];

int main(){
	ios::sync_with_stdio(false);
	int n;
	const int maxn = 200000;
	string s;
	cin>>n>>s;
	n = s.size();
	for(int i = -n; i <= n; ++i) t[i+maxn] = -1;
	t[maxn] = 0;
	int cur = 0;
	int ans = 0;
	for(int i = 0; i < n ;++i){
		if(s[i] == '(') ++cur;
		else{
			t[cur-- + maxn] = -1;
		}
		if(t[cur+maxn] == -1) t[cur+maxn] = i+1;
		else ans = max(i+1-t[cur+maxn],ans);
	}
	cout<<ans;
}