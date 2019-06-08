/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

const int mod = 1000000007;
const int m = 500000;
int seg[2][m << 1];
set<int> nonOnePos;
int n, q;

int mult(int a, int b) {
	return (((long long)a) * b) % mod;
}

int mymax(int a, int b) {
	return max(a,b);
}

void update(int* t,int p, int v, int (*f)(int,int)) {
	p += m;
	t[p] = v;
	while (p / 2) {
		p /= 2;
		t[p] = (*f)(t[p * 2], t[p * 2 + 1]);
	}
}

//[a,b)
int query(int *t, int a, int b, int (*f)(int, int)) {
	if (a >= b) return 1;
	int ans = 1;
	a += m;
	b += m;
	while (a < b) {
		if (a & 1) ans = (*f)(t[a++],ans);
		if ((b & 1)) ans = (*f)(t[--b], ans);
		a /= 2;
		b /= 2;
	}
	return ans;
}

int queryMax(int a, int b) {
	return query(seg[1], a, b, mymax);
}

int queryMult(int a, int b) {
	return query(seg[0], a, b, mult);
}

int answer() {
	auto it = nonOnePos.rbegin();
	int lastNonOne = n;
	int val = 1;
	bool great = false;
	while (it != nonOnePos.rend() && !great) {
		int temp = *it;
		int qres = queryMax(max(*it, 0), lastNonOne);
		int v = seg[0][*it + m];
		val = max(val, qres);
		if (*it >= 0) {
			if ((long long)val * seg[0][*it + m] >= mod) great = true;
			val = mult(val, seg[0][*it + m]);
		}
		lastNonOne = *it;
		++it;
	}
	int qres = queryMult(0, lastNonOne);
	return mult(qres, val);
}

int slowAnswer() {
	long long val = 1;
	bool great = false;
	for (int i = n - 1; i >= 0; --i) {
		if(!great)val = max(val, (long long)seg[1][i + m]);
		if (val * seg[0][i + m] >= mod) great = true;
		val = (val * seg[0][i + m]) % mod;
	}
	return val;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	nonOnePos.insert(-1);
	for (size_t i = 0; i < n; i++) {
		int a;
		cin >> a;
		//a = rand() % 100 + 1;
		update(seg[0], i, a, mult);
		if (a > 1) nonOnePos.insert(i);
	}
	for (size_t i = 0; i < n; i++) {
		int a;
		cin >> a;
		//a = rand() % 100+ 1;
		update(seg[1], i, a, mymax);
	}
	cin >> q;
	cout << answer() << '\n';
	/*if (answer() != slowAnswer()) {
		n = n;
	}*/
	for (size_t i = 0; i < q; i++) {
		int type, pos, val;
		cin >> type >> pos >> val;
		/*type = (rand() % 2) + 1;
		pos = rand() % n;
		val = rand() % 100 + 1;*/
		if (type == 1) {
			if (seg[0][pos + m] == 1 && val != 1) nonOnePos.insert(pos);
			if (seg[0][pos + m] != 1 && val == 1) nonOnePos.erase(pos);
			update(seg[0], pos, val, mult);
		}else update(seg[1], pos, val, mymax);
		/*int t = answer();
		int tt = slowAnswer();*/
		cout << answer() << '\n';
		/*if (t != tt) {
			for (int i = 0; i < n; ++i) {
				cout << seg[0][i + m] << ' ';
			}
			cout << endl;
			for (int i = 0; i < n; ++i) {
				cout << seg[1][i + m] << ' ';
			}
			cout << endl;
			n = n;
		}*/
	}
}
