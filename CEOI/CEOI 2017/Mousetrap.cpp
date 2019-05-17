/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

int n,t,m;
int h[1000000];
int p[1000000];
vector<int> edj[1000000];
bool insub[1000000];
int w[1000000];
vector<pair<vector<int>,int>> pt;

void dfs0(int u){
    if(u == m) insub[u] = true;
    for(int v : edj[u]){
        if(v != p[u]){
            p[v] = u;
            dfs0(v);
            insub[u] |= insub[v];
        }
    }
}

int dfs(int u,int c){
    int cost = edj[u].size() - 2;//edj[u].size() -1;
    if(u == m || !insub[u]) ++cost;
    if(insub[u])c += cost;
    int lc = 0,sc=0;
    int path = -1;
    vector<int> weights;
    for(auto v : edj[u]){
        if(v != p[u]){
            if(insub[v]) path = v;
            else{
                int t = dfs(v,c);
                weights.push_back(t+c);
                if(t > lc){
                    sc = lc;
                    lc = t;
                }else if(t > sc) sc = t;
            }
        }
    }
    cost += sc;
    w[u] = cost;
    if(insub[u]) {
        dfs(path,c);
        sort(weights.begin(),weights.end(),greater<int>());
        pt.push_back({weights,0});
    }
    return w[u];
}

bool test(int x){
    for(int i = 0; i < pt.size(); ++i) pt[i].second = 0;
    int h = 0;
    int l = 0;
    while(l < pt.size()){
        while(h < pt.size() && (pt[h].second >= pt[h].first.size() || pt[h].first[pt[h].second] - pt[h].second+l<= x)) ++h;
        if(h == pt.size()) return true;
        if(l < x)pt[h].second++;
        ++l;
        while(h < pt.size() && (pt[h].second >= pt[h].first.size() || pt[h].first[pt[h].second] - pt[h].second+l<= x)) ++h;
        if(h < l) return false;
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin>>n>>t>>m;
    if(n == 1 || t == m) {
        cout<<0;
        return 0;
    }
    --t;--m;
    for(int i = 0; i < n-1; ++i){
        int a,b;
        cin>>a>>b;
        edj[--a].push_back(--b);
        edj[b].push_back(a);
    }
    for(int i = 0; i < n; ++i) p[i] = -1;
    dfs0(t);
    for(int v : edj[t]){
        if(insub[v]){
            p[v] = t;
            h[v] = 1;
            dfs(v,0);
            /*for(int i = 0; i < pt.size(); ++i){
                for(int j = 0; j < pt[i].first.size(); ++j){
                    cout<<pt[i].first[j]<<' ';
                }
                cout<<endl;
            }*/
            int lo = 0;
            int hi = 5000000;
            while(lo < hi){
                int mid = (lo+hi)/2;
                if(test(mid)) hi = mid;
                else lo = mid+1;
            }
            cout<<lo;
            return 0;
        }
    }
}
