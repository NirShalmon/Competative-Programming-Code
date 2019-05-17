/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include "100_towers.h"
#include<unordered_set>

using namespace std;

vector<int> h;
unordered_set<int> a[4]; 

int init(vector<int> towers) {
    h = towers;
	for(int i = 0; i < 100; ++i){
		a[h[i]%4].insert(i);
	}
	if(a[1].size() % 2 == a[2].size()% 2 && a[2].size() % 2 == a[3].size() % 2){
		return 2;
	}else return 1;
}

void enemy_move(int tower, int cubes) {
	a[h[tower]%4].erase(tower);
	h[tower]-=cubes;
	a[h[tower]%4].insert(tower);
}

int f(int i,int j){
	int tower = *a[i].begin();
	h[tower] -= i - j;
	a[i].erase(tower);
	a[j].insert(tower);
	return tower;
}

vector<int> your_move() {
	vector<int> ans;
	if(a[1].size() %2 == a[2].size()%2){
		if(a[1].size() % 2 == 0){
			ans.push_back(f(3,0));
			ans.push_back(3);
		}else{
			ans.push_back(f(2,1));
			ans.push_back(1);
		}
	}else if(a[1].size()%2 == a[3].size()%2){
		if(a[1].size() % 2 == 0){
			ans.push_back(f(2,0));
			ans.push_back(2);
		}else{
			ans.push_back(f(3,1));
			ans.push_back(2);
		}
	}else{
		if(a[2].size() % 2 == 0){
			ans.push_back(f(1,0));
			ans.push_back(1);
		}else{
			ans.push_back(f(3,2));
			ans.push_back(1);
		}
	}
	return ans;
}
