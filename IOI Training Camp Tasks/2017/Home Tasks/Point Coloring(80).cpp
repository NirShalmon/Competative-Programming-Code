/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

struct quad{
    int lw,hw,lb,hb;
};

typedef struct quad quad;

#define maxn 200000
const int inf = 100000001;
pair<int,int> seg[2][500000];
int consec[2][300000];
int n,s;
int p[300000];
quad q[60];

void clr(pair<int,int>* tr){
    for(int i = 0; i < 2*maxn; ++i)tr[i] = {-inf,-1};
}

void add(pair<int,int>* tr,int x,int v,int k){
    if(x < 0 || x >= maxn) cout<<"j";
    x += maxn;
    while(x){
         //   cout<<v<<endl;
        if(tr[x].first < v){
            tr[x] = {v,k};
        }
        x /= 2;
    }
}

pair<int,int> query(pair<int,int>* tr,int l,int r){
    int ans = -inf;
    int bi = maxn*3;
    for(l += maxn,r+=maxn; l < r; l/=2,r/=2){
        if(l < 0) cout<<"f";
        if(l&1) {
            if(tr[l].first > ans){
                ans = tr[l].first;
                bi = l;
            }
            ++l;
        }
        if(r&1){
            --r;
            if(tr[r].first > ans){
                ans = tr[r].first;
                bi = r;
            }
        }
    }
    while(bi < maxn){
        bi *= 2;
        if(bi < 0)cout<<"t";
        if(tr[bi].first != ans)++bi;
    }
    return {ans,bi == maxn * 3 ? -1 : bi-maxn};
}

void read(){
    cin>>n;
    for(int i = 0; i < n;++i) cin>>p[i];
    cin>>s;
    for(int i = 0; i < s; ++i)cin>>q[i].lw>>q[i].hw>>q[i].lb>>q[i].hb;
}

void rnd(){
    n = 10;
    p[0] = rand() % 10+1;
    for(int i = 1; i < n;++i) p[i] = p[i-1] + rand()%10+1;
    s = 1;
    q[0].lw = rand() % 20+1;
    q[0].lb = rand() % 20+1;
    q[0].hw = q[0].lw + rand() % 20;
    q[0].hb = q[0].lb + rand() % 20;
}

bool in(int a,int l,int r){
    return a >= l && a <= r;
}

void consecfill(int* t,int l,int h){
    t[0] = in(p[1] - p[0],l,h) ? 0 : 1;
    for(int i = 1; i < n-1; ++i){
        if(in(p[i+1]-p[i],l,h)) t[i] = t[i-1];
        else t[i] = t[i-1]+1;
    }
}

int fix[2][300000];

pair<int,vector<int>> sim(quad w){
    //cout<<w.hb<<w.hw<<w.lb<<w.lw;
    if(w.lw == 8 && w.hw == 17){
        int asdas = 123;
    }
    clr(seg[0]); //wb
    clr(seg[1]); //bw
    consecfill(consec[0],w.lw,w.hw);
    consecfill(consec[1],w.lb,w.hb);
    for(int i = 0; i < n; ++i) fix[1][i] = -1,fix[0][i] = -1;
    int ans = -inf;
    int lcolor = 0;
    int lswap = 0;
    for(int i = 1; i < n; ++i){
        //bw
        int l = p[i] - w.hw;
        int r = p[i] - w.lw;
        int li = lower_bound(p,p+n,l) - p+1; //+1 since the change is one later than the last white
        //cout<<li<<' ';
        if(i != 1) li = max(li,1+lower_bound(consec[1],consec[1]+n-1,consec[1][i-2])-consec[1]);
        int ri = min(i-1,upper_bound(p,p+n,r) - p);
       // cout<<li<<' '<<ri<<endl;
        if(li <= ri){
            pair<int,int> val = query(seg[0],li,ri+1);
            fix[1][i] = val.second;
            if(val.first >= 0)add(seg[1],i,val.first+1,val.second);
        }else add(seg[1],i,-inf,-1);
        if(i == 1 || consec[1][i-2] == 0) add(seg[1],i,1,-1);
        //wb
        l = p[i] - w.hb;
        r = p[i] - w.lb;
        li = lower_bound(p,p+n,l) - p+1; //+1 since the change is one later than the last white
        if(i != 1)li = max(li,1+lower_bound(consec[0],consec[0]+n-1,consec[0][i-2])-consec[0]);
        ri = min(i-1,upper_bound(p,p+n,r) - p);
        if(li <= ri){
            pair<int,int> val = query(seg[1],li,ri+1);
            fix[0][i] = val.second;
            if(val.first >= 0)add(seg[0],i,val.first+1,val.second);
        }else add(seg[0],i,-inf,-1);
        if(i == 1 || consec[0][i-2] == 0) add(seg[0],i,1,-1);
        if(i == n-1 || consec[0][i-1] == consec[0][n-2]) {
            if(ans < seg[1][i+maxn].first){
                ans = seg[1][i+maxn].first;
                lcolor = 0;
                lswap = i;
            }
        }
        if(i == n-1 || consec[1][i-1] == consec[1][n-2]){
            if(ans < seg[0][i+maxn].first){
                ans = seg[0][i+maxn].first;
                lcolor = 1;
                lswap = i;
            }
        }
    }
    //cout<<ans;
    if(ans == -inf) return {ans,vector<int>()};
    vector<int> v;
    int g = n-1;
    int cnt = 0;
    while(g >= 0){
        //while(g >= max(0,lswap)){
            v.push_back(lcolor+1);
            if(g == lswap){
                lcolor ^= 1;
                lswap = fix[lcolor][g];
                ++cnt;
            }
            --g;
        //}
    }
    if(cnt != ans) cout<<"qwe";
    reverse(v.begin(),v.end());
    //check if answer is valid
    /*int lw = -1,lb = -1;
    for(int i = 0; i < v.size(); ++i){
        if(v[i] == 1){
            if(lw != -1){
                if(p[i] - lw < w.lw || p[i]-lw > w.hw){
                    cout<<"dsfasdf";
                }
            }
            lw = p[i];
        }else if(v[i] == 2){
            if(lb != -1){
                if(p[i] - lb < w.lb || p[i]-lb > w.hb){
                    cout<<"dsfasdf";
                }
            }
            lb = p[i];
        }else cout<<"dsfasdf";
    }*/
    return {ans,v};
}

bool valid(vector<int> v,quad w){
    int lw = -1,lb = -1;
            bool ok = true;
            for(int i = 0; i < v.size(); ++i){
                if(v[i] == 1){
                    if(lw != -1){
                        if(p[i] - lw < w.lw || p[i]-lw > w.hw){
                            ok = false;
                        }
                    }
                    lw = p[i];
                }else if(v[i] == 2){
                    if(lb != -1){
                        if(p[i] - lb < w.lb || p[i]-lb > w.hb){
                           ok = false;
                        }
                    }
                    lb = p[i];
                }else ok = false;
            }
    return ok;
}

pair<int,vector<int>> sim2(quad w){
    vector<int> best;
    int ans = -inf;
    for(int i = 0; i < (1<<n); ++i){
        vector<int> v;
        int tmp = 0;
        for(int j = 0; j < n; ++j){
            if(i & (1<<j))v.push_back(2);
            else v.push_back(1);
            if(j && v[j] != v[j-1]) ++tmp;
        }
        if(tmp > ans){
            if(valid(v,w)){
                ans = tmp;
                best = v;
            }
        }
    }
    return {ans,best};
}

int main() {
	ios::sync_with_stdio(false);
    read();
    /*while(true){
        rnd();
        auto a = sim(q[0]);
        auto b = sim2(q[0]);
        if(a.first != b.first){
            if(!valid(a.second,q[0])){
            int aa[10];
            for(int i = 0; i < 10; ++i) aa[i] = a.second[i];
            cout<<"y";
            }
        }
    }*/
    int ans = -inf;
    vector<int> ansv;
    int bs = 1;
   // if(n > 15) return 0;
    for(int i = 0; i < s; ++i) {
        pair<int,vector<int>> val = sim(q[i]);
        if(val.first > ans){
            ans = val.first;
            if(val.second.size())ansv = val.second;
            bs = i+1;
        }
    }
    if(ans == -inf) cout<<0;
    else{
        cout<<bs<<' '<<n-ans-1<<endl;
        for(int x : ansv) cout<<x;
    }
}
