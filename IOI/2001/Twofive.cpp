/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

struct tbl {
	char val[5];
	
	int conv() {
		int sum = 0;
		for (int i = 0, k = 1; i < 5; ++i, k *= 6) {
			sum += val[i] * k;
		}
		return sum;
	}

	tbl(int sum) {
		for (size_t i = 0; i < 5; i++) {
			val[i] = sum % 6;
			sum /= 6;
		}
	}

	tbl(int a, int b, int c, int d, int e) {
		val[0] = a;
		val[1] = b;
		val[2] = c;
		val[3] = d;
		val[4] = e;
	}

	static tbl fromSize(int size) {
		tbl t{ min(size,5), max(0,min(size - 5,5))
			,max(0,min(size - 10,5))
			,max(0,min(size - 15,5))
			,max(0,min(size - 20,5)) };
		return t;
	}
};

int mncrt[5][5];
int x = 0;
int y = 0;
const int maxsum = 6 * 6 * 6 * 6 * 6 * 6;
const int pows[]{ 1,6,6 * 6,6 * 6 * 6,6 * 6 * 6 * 6,6 * 6 * 6 * 6 * 6 };
vector<int> numsleft;
int dp[maxsum];

void inc() {
	if (++x == 5) {
		x = 0;
		++y;
	}
}

void chk() {
	mncrt[x][y] = 0;
	if (x > 0) mncrt[x][y] = max(mncrt[x - 1][y] + 1, mncrt[x][y]);
	if (y > 0) mncrt[x][y] = max(mncrt[x][y - 1] + 1, mncrt[x][y]);
}

bool fill(vector<int> &s) {
	for (int i : s) {
		chk();
		if (mncrt[x][y] > i) return false;
		mncrt[x][y] = i;
		auto ind = find(numsleft.begin(), numsleft.end(), i);
		if (ind == numsleft.end()) return false;
		else numsleft.erase(ind);
		inc();
	}
	while (y < 5) {
		chk();
		inc();
	}
	return true;
}

int rec(tbl t,int mi) {
	if (mi == numsleft.size()) return 1;
	int conv = t.conv();
	if (dp[conv] != -1) return dp[conv];
	int ans = 0;
	for (int i = 0; i < 5; ++i) {
		if (t.val[i] < 5 && (i == 0 || t.val[i - 1] > t.val[i])) {
			if (numsleft[mi] >= mncrt[t.val[i]][i]) {
				//if (dp[conv + pows[i]] != -1) ans += dp[conv + pows[i]];
				//else {
					t.val[i]++;
					ans += rec(t, mi + 1);
					--t.val[i];
				//}
			}
		}
	}
	dp[conv] = ans;
	return ans;
}

int cnt(vector<int> &s) {
	x = 0;
	y = 0;
	numsleft.clear();
	for (int i = 0; i < 25; ++i) numsleft.push_back(i);
	if (!fill(s)) return -1;
	fill(dp, dp + maxsum, -1);
	tbl base = tbl(0).fromSize(s.size());
	return rec(base, 0);
}

string getWord(int id) {
	vector<int> word;
	//int prv = dicSize;
	int tot = 0;
	for (size_t i = 0; i < 25; i++) {
		word.push_back(0);
		int lc = cnt(word);
		int lt = 0;
		int t = lc < 0 ? 0 : lc;
		while (tot + lt + lc <= id) {
			++word[i];
			lc = max(0, cnt(word));
			lt = t;
			t += lc < 0 ? 0 : lc;
		}
		//t -= prv - lc;
		tot += lt;
		//prv = max(0,cnt(word));
	}
	string ans;
	for (int i : word) {
		ans.push_back((char)(i + 'A'));
	}
	return ans;
}

int getId(string s) {
	vector<int> word;
	int ans = 0;
	for (int i = 0; i < 25; ++i) {
		word.push_back(0);
		while (word[i] + 'A' < s[i]) {
			int t = cnt(word);
			ans += max(0, t);
			++word[i];
		}
	}
	return ans + 1;
}

int main() {
	ios::sync_with_stdio(false);
	char c;
	cin >> c;
	if (c == 'W') {
		string s;
		cin >> s;
		auto a =  getId(s);
		cout <<a;
	} else {
		int id;
		cin >> id;
		auto a =  getWord(id-1);
		cout <<a;
	}
}
