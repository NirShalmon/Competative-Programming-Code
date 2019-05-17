/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n,m;
int id[100000];
int ans[100000];
vector<set<int>> groups;

int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    groups.push_back(set<int>());
    for(int i = 0; i < n; ++i){
        id[i] = 0;
        ans[i] = -1;
        groups[0].insert(i);
    }
    for(int i = 0; i <m; ++i){
        int s;
        cin>>s;
        map<int,vector<int>> r;
        for(int j = 0; j < s; ++j){
            int k;
            cin>>k;
            --k;
            if(r.find(id[k]) == r.end()) r.insert({id[k],vector<int>()});
            r[id[k]].push_back(k);
        }
        for(auto &p : r){
            int gid = p.first;
            if(groups[gid].size() == p.second.size()) continue;
            set<int> ng;
            for(int l : p.second){
                ng.insert(l);
                id[l] = groups.size();
                groups[gid].erase(l);
            }
            groups.push_back(ng);
            if(groups[gid].size() == 1) ans[*groups[gid].begin()] = i;
            if(groups.back().size() == 1) ans[*groups.back().begin()] = i;
        }
    }
    for(int i = 0; i < n; ++i) cout<<ans[i]+1<<' ';
}
