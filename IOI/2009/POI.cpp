/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<algorithm>

using namespace std;

int val[2000],score[2000];
int s[2000][2000];
int c[2000];

int main(){
	ios::sync_with_stdio(false);
	int n,t,p;
	cin>>n>>t>>p;
	for(int i = 0; i < t; ++i)val[i]=n;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < t; ++j){
			cin>>s[i][j];
			if(s[i][j])--val[j],c[i]++;
		}
	}
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < t; ++j){
			if(s[i][j]) score[i] += val[j];
		}
	}
	int ans = 1;
	--p;
	for(int i = 0; i < n; ++i){
		if(score[p] < score[i] || (score[p] == score[i] && (c[p] < c[i] || (c[p] == c[i] && p > i))))++ans;
	}
	cout<<score[p]<<' '<<ans;
}
