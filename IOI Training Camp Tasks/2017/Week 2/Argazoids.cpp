/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>

using namespace std;

int cnt[5000002];
int s[5000002];

int main(){
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	for(int i = 0; i < n; ++i){
		int a;
		cin>>a;
		cnt[a]++;
	}
	vector<int> piles;
	for(int i = 0; i <= n; ++i){
		int pile = 0;
		while(cnt[i]){
			if(pile < piles.size()){
				if(i >= piles[pile]){
					--cnt[i];
					if(++piles[pile] > i) ++pile;
				}else ++pile;
			}else{
				piles.push_back(1);
				--cnt[i];
			}
		}
	}
	cout<<piles.size();
}