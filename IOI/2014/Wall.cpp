/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
//#include "bricks.h"

using namespace std;

namespace t{

const int M = 21;//22;

typedef struct func{
	int lowestMin,highestMax;
} func;

func seg[1<<(M+1)];
int l[1<<(M+1)],r[1<<(M+1)];

void clr(func &f){
	f.lowestMin = 100000;
	f.highestMax=0;
}

void init(){
	for(int i = (1<<(M+1))-1; i>0; --i){
		if(i >= (1<<M)) l[i]=i-(1<<M),r[i]=i-(1<<M);
		else{
			l[i] = l[i*2];
			r[i]=r[i*2+1];
		}
	}
	for(int i = 0; i < (1<<(M+1)); ++i){
		clr(seg[i]);
	}
}

//g*f
func res(func &f, func &g){
	func ans;
	if(f.lowestMin <= g.highestMax){
		ans.lowestMin = f.lowestMin;
		ans.highestMax = f.lowestMin;
	}else if(g.lowestMin <= f.highestMax){
		ans.lowestMin = f.highestMax;
		ans.highestMax = f.highestMax;
	}else{
		ans.lowestMin = min(f.lowestMin,g.lowestMin);
		ans.highestMax = max(f.highestMax,g.highestMax);
	}
	return ans;
}

void push(int p){
	seg[2*p] = res(seg[p],seg[2*p]);
	seg[2*p+1] = res(seg[p],seg[2*p+1]);
	clr(seg[p]);
}

//update node p, target range [a,b), func f
void update(int p,int a, int b, func f){
	if(r[p] < a || l[p] >= b) return; //out of range;
	if(a <= l[p] && r[p] < b){ //inside, add f to node
		seg[p] = res(f,seg[p]);
	}else{//outside, recurse
		push(p);
		update(p*2,a,b,f);
		update(p*2+1,a,b,f);
	}
}

int n, k, op[500000],  left[500000],  right[500000],  height[500000],  finalHeight[2000000];
void bricks(){
	init();
	for(int i = 0; i < k; ++i){
		func t;
		t.highestMax = 0;
		t.lowestMin = 100000;
		if(op[i] == 1) t.highestMax = height[i];
		else t.lowestMin = height[i];
		update(1,left[i],right[i]+1,t);
	}
	for(int i = 1; i < (1<<(M)); ++i){
		push(i);
	}
	for(int i = 0; i < n; ++i) cout<< seg[(1<<M)+i].highestMax<<'\n';
}
}

int main(){
	ios::sync_with_stdio(false);
	cin>>t::n>>t::k;
	for(int i = 0; i < t::k; ++i){
		cin>>t::op[i]>>t::left[i]>>t::right[i]>>t::height[i];
	}
	t::bricks();
	/*for(int i = 0; i < t::n; ++i){
		cout<<t::finalHeight[i]<<endl;
	}*/
}
