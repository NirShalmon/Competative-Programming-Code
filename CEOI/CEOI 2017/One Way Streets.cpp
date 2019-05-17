/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

vector<pair<int,int>> altedj;
vector<pair<int,int>> edj[100005]; //other and id
vector<pair<int,int>> xy;
vector<int> getto[100005],getfrom[100005];
vector<pair<int,int>> downedj[100005];
int n,m,p;
int comp[100005];
int h[100005];
int edjs[100005];
int up[18][100005];

int dfs(int u,int entryId){
    int maxup = h[u];
    for(auto t : edj[u]){
        int v = t.first;
        int eid = abs(t.second);
        if(eid != entryId){
            if(h[v] != -1){
                edjs[eid] = 1;
                maxup = min(h[v],maxup);
            }else{
                downedj[u].push_back(t);
                h[v] = h[u] + 1;
                comp[v] = comp[u];
                up[0][v] = u;
                auto ret = dfs(v,eid);
                maxup = min(ret,maxup);
                if(ret <= h[u]){
                    edjs[eid] = 1;
                }
            }
        }
    }
    return maxup;
}

int lca(int u,int v){
    if(h[u] < h[v]) swap(u,v);
    for(int i = 17; i >= 0; --i){
        if(h[u] - (1<<i) >= h[v]){
            u = up[i][u];
        }
    }
    //h[u] == h[v]
    for(int i = 17; i >= 0; --i){
        if(up[i][u] != up[i][v]){
            u = up[i][u];
            v = up[i][v];
        }
    }
    return h[u]-1;
}

pair<int,int> dfs2(int u){
    int d = 0;
    int mh = h[u];
    for(int y : getto[u]){
        ++d;
        mh = min(mh,lca(u,y));
    }
    for(int x : getfrom[u]){
        --d;
        mh = min(mh,lca(u,x));
    }
    for(auto v : downedj[u]){
        auto ret = dfs2(v.first);
        if(edjs[abs(v.second)] == 0 && ret.first != 0 && ret.second <= h[u]){
            long long ld = ret.first;
            if(ld * v.second > 0) edjs[abs(v.second)] = 2;
            else edjs[abs(v.second)] = 3;
        }
        d += ret.first;
        mh = min(ret.second,mh);
    }
    return {d,mh};
}

int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i = 1; i <= m; ++i){
        int a,b;
        cin>>a>>b;
        edj[--a].push_back({--b,i});
        edj[b].push_back({a,-i});
        altedj.push_back({a,b});
    }
    for(int i = 0; i < n; ++i){
        h[i] = -1;
        up[0][i] = -1;
    }
    cin>>p;
    for(int i = 0; i < p; ++i){
        int x,y;
        cin>>x>>y;
        xy.push_back({--x,--y});
        if(y != x){
            getto[x].push_back(y);
            getfrom[y].push_back(x);
        }
    }
    for(int i = 0; i < n; ++i){
        if(h[i] == -1){
            h[i] = 0;
            comp[i] = i;
            dfs(i,0);
        }
    }
    for(int w = 1; w < 18; ++w){
        if((1<<w) <= n){
            for(int i = 0; i < n; ++i){
                up[w][i] = up[w-1][i] == -1 ? -1 : up[w-1][up[w-1][i]];
            }
        }else{
            for(int i = 0; i < n; ++i) up[w][i] = -1;
        }
    }
    for(int i = 0; i < n; ++i){
        if(up[0][i] == -1){
            dfs2(i);
        }
    }
    for(int i = 1; i <= m; ++i){
        if(edjs[i] <= 1)cout<<"B";
        else if(edjs[i] == 2) cout<<"L";
        else cout<<"R";
    }
}
