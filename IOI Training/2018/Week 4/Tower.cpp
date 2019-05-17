/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

vector<long long> inc[41];

int main(){
	ios::sync_with_stdio(false);
	long long n,k;
	cin>>n>>k;
	if(k>40)k=40;
	if(k == 1) {
		cout<<n-1;
		return 0;
	}
	if(n == 1){
		cout<<n-1;
		return 0;
	}
	int p = 0;
	inc[2].push_back(1);
	for(int i = 1; inc[2].back() < n; ++i) inc[2].push_back(inc[2].back()+i); 
	for(int a = 3; a <= k; ++a){
		inc[a].push_back(1);
		for(int i = 0; inc[a].back() < n; ++i) inc[a].push_back(inc[a].back()+inc[a-1][i]);
	}
	cout<<inc[k].size()-1;
}


