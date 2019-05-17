/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include "paint.h"

#include <cstdlib>

using namespace std;

vector<int> p;
string st;
bool wp[200000],bp[200000];
int dp[201][200000];
int whiteCount[200000];

bool rec(int i,int l){
    if(i == st.size()){
        return l == p.size();
    }
    if(dp[l][i] != -1) return dp[l][i];
    bool w = false,b = false;
    if(st[i] != 'X'){
        if(i == st.size() - 1){
            if(l == p.size()) w = true;
        }else w |= rec(i+1,l);
    }
    if(l < p.size() && i + p[l] <= st.size() && ((i == 0 && whiteCount[p[0]-1] == 0) || whiteCount[i+p[l]-1] - whiteCount[i-1] == 0)){
        if(i + p[l] == st.size()) b |= rec(i+p[l],l+1);
        else if(st[i+p[l]] != 'X') b |= rec(i+p[l]+1,l+1);
    }
    if(b) {
        for(int j = i; j < i+p[l]; ++j) bp[j] =true;
        if(i + p[l] != st.size()) wp[i+p[l]] = true;
    }
    wp[i] |= w;
    dp[l][i] = b || w ? 1 : 0;
    return dp[l][i];
}

std::string solve_puzzle(std::string s, std::vector<int> c) {
    whiteCount[0] = s[0] == '_';
    for(int i = 1; i < s.size(); ++i) whiteCount[i] = whiteCount[i-1] + (s[i] == '_');
    st = s;
    p = c;
    for(int i = 0; i < s.size(); ++i){
        for(int j = 0; j < c.size() + 1; ++j) dp[j][i] = -1;
    }
    rec(0,0);
    for(int i = 0; i < s.size(); ++i){
        if(wp[i] && bp[i]) s[i] = '?';
        else s[i] = wp[i] ? '_' : 'X';
    }
    return s;
}
