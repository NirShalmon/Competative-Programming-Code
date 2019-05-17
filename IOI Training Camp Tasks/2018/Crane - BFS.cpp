/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include <iostream>
#include<set>
#include<vector>
#include<map>
#include<queue>

using namespace std;

map<string, pair<char, pair<char, char>>> s;

string cs(vector<char> stacks[3]) {
	string ans;
	for (char c : stacks[0]) ans.push_back(c);
	ans.push_back('0');
	for (char c : stacks[1]) ans.push_back(c);
	ans.push_back('0');
	for (char c : stacks[2]) ans.push_back(c);
	return ans;
}

string gens(vector<char> stacks[3], char a, char b) {
	stacks[b].push_back(stacks[a].back());
	stacks[a].pop_back();
	string ans = cs(stacks);
	stacks[a].push_back(stacks[b].back());
	stacks[b].pop_back();
	return ans;
}


/*short solve(string state) {
	if (s.find(state) != s.end()) return s[state].first;
	int si = 0;
	vector<char> stacks[3];
	for (char c : state) {
		if (c == '0') ++si;
		else stacks[si].push_back(c);
	}
	short best = 30000;
	pair<char, char> bm = { 0,0 };
	if (stacks[0].size() > 0) {
		int t = solve(gens(stacks, 0, 1));
		if (t < best) {
			best = t;
			bm = { 0,1 };
		}
		t = solve(gens(stacks, 0, 2));
		if (t < best) {
			best = t;
			bm = { 0,2};
		}
	}
	if (stacks[1].size() > 0) {
		int t = solve(gens(stacks, 1, 0));
		if (t < best) {
			best = t;
			bm = { 1,0 };
		}
		 t = solve(gens(stacks, 1,2));
		if (t < best) {
			best = t;
			bm = { 1,2 };
		}
	}
	if (stacks[2].size() > 0) {
		int t = solve(gens(stacks, 2, 0));
		if (t < best) {
			best = t;
			bm = { 2,0 };
		}
		 t = solve(gens(stacks, 2, 1));
		if (t < best) {
			best = t;
			bm = { 2,1 };
		}
	}
	s[state] = { best,bm };
	return best;
}*/

void bfs(string start,string tar) {
	s[start] = { 0,{-1,-1} };
	queue<string> q;
	q.push(start);
	while (!q.empty()) {
		string state = q.front();
		q.pop();
		auto vals = s[state];
		int si = 0;
		vector<char> stacks[3];
		for (char c : state) {
			if (c == '0') ++si;
			else stacks[si].push_back(c);
		}
		if (stacks[0].size() > 0) {
			string r = gens(stacks, 0, 1);
			if (s.find(r) == s.end()) {
				s[r] = { vals.first + 1,{1,0} };
				if (r == tar) return;
				q.push(r);
			}
			r = gens(stacks, 0, 2);
			if (s.find(r) == s.end()) {
				s[r] = { vals.first + 1,{ 2,0 } };
				if (r == tar) return;
				q.push(r);
			}
		}
		if (stacks[1].size() > 0) {
			string r = gens(stacks, 1, 0);
			if (s.find(r) == s.end()) {
				s[r] = { vals.first + 1,{ 0,1 } };
				if (r == tar) return;
				q.push(r);
			}
			r = gens(stacks, 1, 2);
			if (s.find(r) == s.end()) {
				s[r] = { vals.first + 1,{ 2,1 } };
				if (r == tar) return;
				q.push(r);
			}
		}
		if (stacks[2].size() > 0) {
			string r = gens(stacks, 2, 0);
			if (s.find(r) == s.end()) {
				s[r] = { vals.first + 1,{ 0,2 } };
				if (r == tar) return;
				q.push(r);
			}
			r = gens(stacks, 2, 1);
			if (s.find(r) == s.end()) {
				s[r] = { vals.first + 1,{ 1,2 } };
				if (r == tar) return;
				q.push(r);
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	//s["12345678900"] = { 0,{-1,-1} };
	//solve("147025803690");
	//bfs("12345678900");
	//vector<char> v[3] = { {'1','4','7'},{'2','5','8'},{'3','6','9'} };
	//bfs("1234500");
	//vector<char> v[3] = { {'3','2','1'},{'4'},{'5'} };
	//bfs("1200");
	//vector<char> v[3] = { {'2','1'},{},{} };
	string start = "0673CA4B508";
	bfs("34567800BAC", start);
	vector<char> v[3];
	int si = 0;
	for (char c : start) {
		if (c == '0') ++si;
		else v[si].push_back(c);
	}
	cout << (int)s[cs(v)].first << endl;
	while (s[cs(v)].first != 0) {
		auto w = s[cs(v)].second;
		cout << (char)(w.first + 'A') << ' ' << (char)(w.second + 'A') << endl;
		v[w.second].push_back(v[w.first].back());
		v[w.first].pop_back();
	}
}