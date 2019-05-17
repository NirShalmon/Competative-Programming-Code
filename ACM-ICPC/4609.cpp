/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

bool isComposite[10000000];
int tens[10];
vector<int> primes;

void act(vector<int> &a) {
	sort(a.begin(), a.end());
	do {
		int t = 0;
		for (int i = 0; i < a.size(); ++i) {
			t += a[i] * tens[i];
		}
		if (!isComposite[t]) {
			primes.push_back(t);
		}
	}while (next_permutation(a.begin(), a.end()));
}

int main() {
	ios::sync_with_stdio(false);
	isComposite[0] = true;
	isComposite[1] = true;
	for (size_t i = 2; i < 3500; i++) {
		if (!isComposite[i]) {
			for (size_t j = i * i; j < 10000000; j += i) {
				isComposite[j] = true;
			}
		}
	}
	tens[0] = 1;
	for (size_t i =1; i < 10; i++) {
		tens[i] = tens[i - 1] * 10;
	}
	int c;
	cin >> c;
	for (size_t r = 0; r < c; r++) {
		primes.clear();
		string n;
		cin >> n;
		vector<int> d;
		for (size_t i = 0; i < n.size(); i++) {
			d.push_back( n[i] - 48);
		}
		vector<int> v;
		for (int i = 1; i < (1<<d.size()); ++i) {
			v.clear();
			for (int b = 0; b < 7; ++b) {
				if (i & (1 << b)) {
					v.push_back(d[b]);
				}
			}
			act(v);
		}
		sort(primes.begin(), primes.end());
		cout << unique(primes.begin(), primes.end()) - primes.begin() << endl;
	}
}
