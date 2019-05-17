/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include <vector>
#include <utility>
#include "takastan.h"
#include<queue>
#include<set>

using namespace std;

int n;
set<int> edj[100000];
int color[100000];
int colorCnt = 1;
int vis[100000];

/*
Called once at the beginning of the program.

N is the number of towns in Takastan. The towns are numbered 1,...,N.
edges is a vector of N-1 pairs. Each members is a pair of two different numbers between 1 and N,
representing a road between two cities.
*/
void init(int N, vector <pair <int,int> > edges) {
	n = N;
	for (auto e : edges) {
		edj[e.first - 1].insert(e.second - 1);
		edj[e.second - 1].insert(e.first - 1);
	}
}

/*
Called when the road between city u and city v is destroyed. u and v are between 1 and N.
Assume the road {u,v} exists and has not been bombed before.
*/
void bomb(int u, int v) {
	--u; --v;
	edj[u].erase(v);
	edj[v].erase(u);
	if (edj[u].size() == 0) {
		color[u] = colorCnt++;
		return;
	}
	if (edj[v].size() == 0) {
		color[v] = colorCnt++;
		return;
	}
	int vi = vis[u];
	queue<pair<int,set<int>::const_iterator>> q[2];
	vector<int> vl[2] = { {u},{v} };
	++vis[u]; ++vis[v];
	q[0].push({ u,edj[u].begin() });
	q[1].push({ v,edj[v].begin() });
	int i = 0;
	while (true) {
		int o = i & 1;
		bool suc = false;
		if (q[o].empty()) break;
		else {
			auto t = q[o].front();
			q[o].pop();
			if (vis[*t.second] == vi) {
				vl[o].push_back(*(t.second));
				if (edj[*t.second].size() > 0) {
					q[o].push({ *t.second, edj[*t.second].begin() });
				}
				++vis[*t.second];
			}
			++t.second;
			if ((t.second) != edj[t.first].end()) {
				q[o].push({ t.first,t.second });
			}
		}
		++i;
	}
	for (int a : vl[i & 1]) {
		color[a] = colorCnt;
	}
	for (int b : vl[(i + 1) & 1]) {
		vis[b]--;
	}
	++colorCnt;
}


/*
You must answer whether cities u and v are connected. u and v are between 1 and N.
You may be asked about the same pair more than once.
*/
bool connected(int u, int v) {
	return color[--u] == color[--v];
}
