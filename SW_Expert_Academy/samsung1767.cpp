/* 1767. [SW Test 샘플문제] 프로세서 연결하기 */

#include<iostream>
#include<vector>
using namespace std;

int T, N;
int dir[4][2] = { {0,1},{0,-1},{1,0}, {-1,0} };
vector< pair<int, int> > core;
vector< vector<int> > map;
int side_core;
int ans_cnt;
int ans_len;

bool ispossible(int n, int d) {
	int x = core.at(n).first;
	int y = core.at(n).second;
	x += dir[d][0];
	y += dir[d][1];
	while (x >= 0 && x < N && y >= 0 && y < N) {
		if (map.at(x).at(y) != 0) 
			return false;
		x += dir[d][0];
		y += dir[d][1];
	}
	return true;
}
int visitCheck(int n,int d) {
	int x = core.at(n).first;
	int y = core.at(n).second;
	x += dir[d][0];
	y += dir[d][1];
	int cnt=0;
	while (x >= 0 && x < N && y >= 0 && y < N) {
		map.at(x).at(y) = 2;
		cnt++;
		x += dir[d][0];
		y += dir[d][1];
	}
	return cnt;
}
void reverseCheck(int n, int d) {
	int x = core.at(n).first;
	int y = core.at(n).second;
	x += dir[d][0];
	y += dir[d][1];

	while (x >= 0 && x < N && y >= 0 && y < N ) {
		map.at(x).at(y) = 0;
		x += dir[d][0];
		y += dir[d][1];
	}
}
void dfs(int n,int cnt,int len) {
	if (n >= core.size()) {
		if (ans_cnt < cnt) {
			ans_cnt = cnt;
			ans_len = len;
		}
		else if (ans_cnt == cnt) {
			if (ans_len > len) {
				ans_len = len;
			}
		}
		return;
	}
	for (int i = 0;i < 5;i++) {
		if (i != 4) {
			if (ispossible(n,i)) {
				int tmp = visitCheck(n, i);
				dfs(n + 1, cnt + 1, len + tmp);
				reverseCheck(n, i);
			} 
		}
		else if(ans_cnt <= cnt+core.size()-n-1){
			dfs(n + 1, cnt, len);
		}
	}
}
int main() {
	cin >> T;
	for (int i = 0;i < T;i++) {
		cin >> N;
		core.clear();
		map.clear();
		ans_cnt = 0;
		ans_len = 0;
		side_core = 0;
		map = vector< vector<int> >(N, vector<int>(N, 0));
		for (int j = 0;j < N;j++) {
			for (int k = 0;k < N;k++) {
				cin >> map.at(j).at(k);
				if (map.at(j).at(k) == 1) {
					if (j == 0 || j == N - 1 || k == 0 || k == N - 1) {
						side_core++;
					}
					else {
						core.push_back(pair<int, int>(j, k));
					}
				}
			}
		}
		dfs(0,0,0);
		cout << "#" << i + 1 << " " << ans_len << endl;
	}
}