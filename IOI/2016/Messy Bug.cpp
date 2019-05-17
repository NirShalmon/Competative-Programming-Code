/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include <vector>
#include<iostream>

#include "messy.h"

using namespace std;

int N;

string unit(int i){
    string s;
    s.reserve(N);
    for(int j = 0; j < i; ++j) s.push_back('0');
    s.push_back('1');
    for(int j = i+1; j < N; ++j) s.push_back('0');
    return s;
}

string range(pair<int,int> rng){
    int l = rng.first;
    int r = rng.second;
    string s;
     s.reserve(N);
    for(int i = 0; i < l; ++i) s.push_back('0');
    for(int i = l; i < r; ++i) s.push_back('1');
    for(int i = r; i < N; ++i) s.push_back('0');
    return s;
}

string gen(vector<int> v){
    string s = range({0,0}); //0s
    for(auto x : v) s[x] = '1';
    return s;
}

string on(string s,int i){
    s[i] = '1';
    return s;
}

pair<int,int> rng(int sz,int ind){
    return {ind * (N/sz),(ind+1)*(N/sz)};
}

int lg(int x){
    int ans = 0;
    while(x){
        x /=2;
        ++ans;
    }
    return ans-2;
}

vector<vector<vector<int>>> v = {{vector<int>(),vector<int>()}};

std::vector<int> restore_permutation(int n, int w, int r) {
    N = n;
    for(int i = 0; i < n/2; ++i) add_element(unit(i));
    int sz = 2;
    int ind = 1;
    for(int h = 4; h <= n; h *=2){
        for(int i = 0; i < h; i += 2){
            string base = range(rng(sz,ind));
            for(int k = rng(h,i).first; k < rng(h,i).second; ++k){
                add_element(on(base,k));
            }
            ind = i;
            sz = h;
        }
    }
    compile_set();
    for(int i = 0; i < n; ++i){
        if(check_element(unit(i))) v[0][0].push_back(i)/*,cout<<i<<" went left"<<endl*/;
        else v[0][1].push_back(i)/*,cout<<i<<" went right"<<endl*/;
    }
    ind = 1;
    sz = 2;
    for(int h = 4; h <= n; h *= 2){
        v.push_back({});
        for(int i = 0; i < h/2; ++i){
            string base = gen(v[lg(sz)][ind]);
            v[lg(h)].push_back(vector<int>());
            v[lg(h)].push_back(vector<int>());
            for(int x : v[lg(h)-1][i]){
                if(check_element(on(base,x))) v[lg(h)][i*2].push_back(x)/*,cout<<x<<" went left"<<endl*/;
                else v[lg(h)][i*2+1].push_back(x)/*,cout<<x<<" went right"<<endl*/;
            }
            ind = i*2;
            sz = h;
        }
    }
    vector<int> ans(n);
    ind = 0;
    for(vector<int> t : v[lg(n)]){
        ans[t[0]] = ind++;
    }
    return ans;
}
