/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include <vector>

using namespace std;

vector<int> t;
int s[6][6][6];

int init(vector<int> towers) {
	/*
	* This function will be called once, at the beginning.
	* Use it to initialize your data structures. The parameter "towers"
	* is a vector with exactly 3 integers (indexed 0, 1, 2). Each integer
	* is between 0 and 10^9. There will always be at least one non-empty
	* tower in the beginning.
	*
	* The function must return 1 or 2:
	* 1 if you want to be first.
	* 2 if you want to be second.
	*/
	t = towers;
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			for (int k = 0; k < 6; ++k) {
				for (int q = 1; q <= i; ++q) {
					if (s[i - q][j][k] == 2) s[i][j][k] = 1;
				}
				for (int q = 1; q <= j; ++q) {
					if (s[i][j - q][k] == 2) s[i][j][k] = 1;
				}
				for (int q = 1; q <= k; ++q) {
					if (s[i][j][k - q] == 2) s[i][j][k] = 1;
				}
				if (s[i][j][k] == 0)s[i][j][k] = 2;
			}
		}
	}
	return s[t[0] % 6][t[1] % 6][t[2] % 6];
}

void system_move(int tower, int cubes) {
	/*
	* This function will be called after the system makes a move.
	* Use it to update your data structures. The parameter "tower" is
	* the index of the tower the system chooses (0 or 1 or 2).
	* The parameter "cubes" is the number of cubes to remove from it.
	*
	* Assume the system's move is legal.
	*/
	t[tower] -= cubes;
}

vector<int> player_move() {
	/*
	* This function will be called when it is your turn.
	* You must return a vector with exactly 2 elements:
	* - Element 0 is the tower you choose (0 or 1 or 2).
	* - Element 1 is the number of cubes (must be a power of a prime).
	*
	* The tower must contain at least the number of cubes you wish to remove
	* from it. If you make an invalid move, the program will terminate
	* and get no points.
	*
	* Remember to update your data structures according to your chosen move!
	*/
	for (int i = 1; i <= t[0] % 6; ++i) {
		if (s[t[0]%6 - i][t[1]%6][t[2]%6] == 2) {
			t[0] -= i;
			return{ 0,i };
		}
	}
	for (int i = 1; i <= t[1] % 6; ++i) {
		if (s[t[0] % 6][t[1] % 6 -i][t[2] % 6] == 2) {
			t[1] -= i;
			return{ 1,i };
		}
	}
	for (int i = 1; i <= t[2] % 6; ++i) {
		if (s[t[0] % 6][t[1] % 6][t[2] % 6 -i] == 2) {
			t[2] -= i;
			return{ 2,i };
		}
	}
}
