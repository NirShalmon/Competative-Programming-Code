/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;

int q[1000];

int main(){
	ios::sync_with_stdio(false);
	int n;
	int a=0,b=0,c=0;
	cin>>n;
	for(int i = 0; i < n; ++i) {
		cin>>q[i];
		if(q[i] == 1) ++a;
		else if(q[i] == 2) ++b;
		else ++c;
	}
	vector<pair<int,int>> v;
	for(int i = 0; i <a ; ++i){
		if(q[i] != 1){
			if(q[i] == 2){
				for(int j = a; j < n; ++j){
					if(q[j] == 1){
						swap(q[i],q[j]);
						v.push_back(make_pair(i+1,j+1));
						break;
					}
				}
			}else{
				bool flag = false;
				for(int j = a+b; j < n; ++j){
					if(q[j] == 1){
						swap(q[i],q[j]);
						v.push_back(make_pair(i+1,j+1));
						flag = true;
						break;
					}
				}
				if(!flag){
					for(int j = a; j < n; ++j){
						if(q[j] == 1){
							swap(q[i],q[j]);
							v.push_back(make_pair(i+1,j+1));
							break;
						}
					}
				}
			}
		}
	}
	for(int i = a; i < n; ++i){
		for(int j = a+b; j < n; ++j){
			if(q[i] == 3 && q[j] == 2){
				swap(q[i],q[j]);
				v.push_back(make_pair(i+1,j+1));
			}
		}
	}
	cout<<v.size()<<endl;
	for(int i = 0;  i < v.size(); ++i){
		cout<<v[i].first<<' '<<v[i].second<<endl;
	}
}

//112223333
//221333231
//122333231
//112333232
//

