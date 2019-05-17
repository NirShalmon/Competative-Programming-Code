/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<algorithm>

#define mp make_pair
#define realint int

using namespace std;

pair<int,int> p[1500];
vector<pair<pair<int,int>,pair<int,int>>> v;

long long clc(long long dx,long long dy,long long ddx, long long ddy){
	return dx * ddy - dy *ddx;
}

long long clc(int i,int j){
	return clc(v[i].first.first,v[i].first.second,v[j].first.first,v[j].first.second);
}

bool cmp(const pair<pair<int,int>,pair<int,int>> &a, const pair<pair<int,int>,pair<int,int>> & b){
if(a.first.first == 0){
		if(b.first.first == 0) return a.first.second < b.first.second;
		return false;
	}
	if(b.first.first == 0){
		return true;
	}
	long long t = clc(a.first.first,a.first.second,b.first.first,b.first.second);
	if(t > 0) return true;
	if(t < 0) return false;
	if(a.second.first < b.second.first) return true;
	if(a.second.first > b.second.first) return false;
	return a.second.second < b.second.second;
}

long long mult(int i,int j){
	return ((long long)v[i].first.first) * v[j].first.first + ((long long)v[i].first.second) * v[j].first.second;
}

realint main(){
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	for(int i = 0; i < n; ++i) {
		cin>>p[i].first>>p[i].second;
	}
	v.reserve(n*(n-1)/2);
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < i; ++j){
			//cout<<i<<' '<<j<<endl;
			v.push_back(mp(mp(p[i].first - p[j].first,p[i].second-p[j].second),mp(i,j)));
			if(v[v.size()-1].first.first <= 0){
				v[v.size()-1].first.first *= -1;
				v[v.size()-1].first.second *= -1;
			}
			if(v[v.size() - 1].first.first == 0 && v[v.size() - 1].first.second < 0){
				v[v.size()-1].first.first *= -1;
				v[v.size()-1].first.second *= -1;
			}
		}
	}
	sort(v.begin(),v.end(),cmp);
	int lp = 0; int rp = 1;
	long long ans = 0;
	while(rp < v.size()){
		while(rp < v.size() && mult(lp,rp) > 0) ++rp;
		if(rp == v.size()) break;
		if(mult(lp,rp) == 0){
			map<int,int> l,r;
			l[v[lp].second.first]++;
			l[v[lp].second.second]++;
			r[v[rp].second.first]++;
			r[v[rp].second.second]++;
			while(rp+1 < v.size() && clc(rp,rp+1) == 0){
				++rp;
				r[v[rp].second.first]++;
				r[v[rp].second.second]++;
			}
			while(lp + 1 < rp && clc(lp,lp+1) == 0){
				++lp;
				l[v[lp].second.first]++;
				l[v[lp].second.second]++;
			}
			for(auto a = l.begin(); a != l.end(); ++a){
				ans += ((long long)(*a).second) * r[(*a).first];
			}
			++rp;++lp;
		}else ++lp;
	}
	cout<<ans;
}