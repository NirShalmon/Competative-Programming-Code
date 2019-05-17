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

int req[1000000];
int cnt[1000000];
int q[1000000];
int bad;

void add(int i){
	if(cnt[q[i]]++ == req[q[i]]) bad++;
	else if(cnt[q[i]] == req[q[i]]) --bad;
}

void rem(int i){
	if(cnt[q[i]]-- == req[q[i]]) bad++;
	else if(cnt[q[i]] == req[q[i]]) --bad;
}

int main(){
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	vector<int> r;
	long long sum = 0;
	for(int i = 0; i < m; ++i){
		int a;
		cin>>a;
		sum += a;
		r.push_back(a);
	}
	for(int i = 0; i < m; ++i){
		int a;
		cin>>a;
		req[--a] = r[i];
	}
	bad = m;
	for(int i = 0; i < n; ++i){
		cin>>q[i];
		--q[i];
	}
	if(sum > n){
		cout<<0;
		return 0;
	}
	for(int i = 0; i < sum; ++i) add(i);
	int ans = 0;
	if(bad == 0)++ans;
	int i = sum-1;
	while(++i < n){
		add(i);
		rem(i-sum);
		if(bad == 0)++ans;
	}
	cout<<ans;
}