/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<bits/stdc++.h>

using namespace std;

template<typename T>
class heap {
private:
	vector<T> val;

	int left(int i) {
		return i * 2 + 1;
	}

	int right(int i) {
		return i * 2 + 2;
	}

	int up(int i) {
		return (i - 1) / 2;
	}

	void heapifyUp(int i) {
		while (i != 0 && val[i] < val[up(i)]) {
			swap(val[i], val[up(i)]);
			i = up(i);
		}
	}

	void heapifyDown(int i) {
		while ((right(i) < size() && val[right(i)] < val[i]) || (left(i) < size() && val[left(i)] < val[i])) {
			if (right(i) >= size() || val[right(i)] >= val[left(i)]) {
				swap(val[i], val[left(i)]);
				i = left(i);
			}else {
				swap(val[i], val[right(i)]);
				i = right(i);
			}
		}
	}

public:

	void clear() {
		val.clear();
	}

	int size() {
		return val.size();
	}
	
	bool empty() {
		return size() == 0;
	}

	T getMin() {
		return val[0];
	}

	void eraseMin() {
		swap(val[0], val[size() - 1]);
		val.pop_back();
		heapifyDown(0);
	}

	void add(T v) {
		val.push_back(v);
		heapifyUp(size() - 1);
	}
};

int n;
heap<int> h;

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		h.add(a);
	}
	while(h.size()){
		cout << h.getMin() << ' ';
		h.eraseMin();
	}
} 