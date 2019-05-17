/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>

using namespace std;

char k[2510];
bool visited[2510][10010];
int edj[2510][4];

int r, c;

int g(int x, int y) {
	return x + y * c;
}

int main() {
	ios::sync_with_stdio(false);
	while(cin>>r>>c){
		for (size_t i = 0; i < c; i++) {
			edj[i][0] = -1;
			edj[i][1] = -1;
			edj[i][2] = -1;
			edj[i][3] = -1;
		}
		for (size_t i = 1; i < r; i++) {
			edj[c*i][0] = -1;
			edj[c*i][1] = -1;
			edj[c*i][2] = -1;
			edj[c*i][3] = -1;
		}
		for (size_t i = 0; i < r; i++) {
			for (size_t j = 0; j < c; j++) {
				cin >> k[g(j,i)];
			}
		}
		for (size_t i = 0; i < r; i++) {
			for (size_t j = 0; j < c; j++) {
				int t = g(j, i);
				if (j != 0) {
					if (k[t] == k[t - 1]) {
						edj[t][3] = edj[t - 1][3];
					} else {
						edj[t][3] = t - 1;
					}
				}
				if (i != 0) {
					if (k[t] == k[t - c]) {
						edj[t][0] = edj[t - c][0];
					} else {
						edj[t][0] = t - c;
					}
				}
			}
		}
		for (int i = r-1; i >= 0; i--) {
			for (int j = c-1; j >= 0; j--) {
				int t = g(j, i);
				if (j != c-1) {
					if (k[t] == k[t + 1]) {
						edj[t][1] = edj[t + 1][1];
					} else {
						edj[t][1] = t + 1;
					}
				}
				if (i != r-1) {
					if (k[t] == k[t + c]) {
						edj[t][2] = edj[t + c][2];
					} else {
						edj[t][2] = t + c;
					}
				}
			}
		}
		string s;
		cin >> s;
		s.push_back('*');
		for (size_t i = 0; i < r * c; i++) {
			for (size_t j = 0; j < s.size(); j++) {
				visited[i][j] = false;
			}
		}
		queue<pair<pair<int, int>,int>> q;
		q.push({ { 0, 0 },0 });
		while (!q.empty()) {
			auto f = q.front();
			q.pop();
			visited[f.first.first][f.first.second] = true;
			if (k[f.first.first] == s[f.first.second]) {
				f.second++;
				f.first.second++;
				if (f.first.second == s.size()) {
					cout << f.second << endl;
					break;
				}
				q.push(f);
			}
			f.second++;
			for (int i : edj[f.first.first]) {
				if (i != -1 && !visited[i][f.first.second]) {
					visited[i][f.first.second] = true;
					q.push({ {i,f.first.second},f.second});
				}
			}
		}
	}
}