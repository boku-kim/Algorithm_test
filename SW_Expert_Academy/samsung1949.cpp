/* 1949 [모의 SW 역량테스트] 등산로 조성 */

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int T,N,K;
vector< vector<int> > map;
int result;
int maximum;
int dir[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
vector<  vector<int> > visited;

void dfs(int x, int y,int state,int h,int cnt) {
	if (result < cnt) 
		result = cnt;
	for (int i = 0;i < 4;i++) {
		int xx = x + dir[i][0];
		int yy = y + dir[i][1];
		if (xx >= 0 && xx < N && yy >= 0 && yy < N
			&& visited.at(xx).at(yy) == 0) {
			if (h > map.at(xx).at(yy)) {
				visited.at(xx).at(yy) = 1;
				dfs(xx, yy, state, map.at(xx).at(yy),cnt+1);
				visited.at(xx).at(yy) = 0;
			}
			else if (state==0) {
				for (int j = 1;j <= K;j++) {
					if (h > (map.at(xx).at(yy) - j)) {
						visited.at(xx).at(yy) = 1;
						dfs(xx, yy, 1, map.at(xx).at(yy) - j, cnt + 1);
						visited.at(xx).at(yy) = 0;
						break;
					}
				}
			}
		}
	}
}
void run() {
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			if (map.at(i).at(j) == maximum) {
				visited = vector<  vector<int>  >(N, vector<int>(N,0));
				visited.at(i).at(j) = 1;
				dfs(i, j,0,map.at(i).at(j),1);
			}
		}
	}
}
int main() {
	cin >> T;
	for (int i = 0;i < T;i++) {
		cin >> N >> K;
		map.clear();
		result = 0;
		map = vector< vector<int> >(N, vector<int>(N, 0));
		maximum = 0;
		for (int j = 0;j < N;j++) {
			for (int k = 0;k < N;k++) {
				cin >> map.at(j).at(k);
				if (map.at(j).at(k) > maximum) {
					maximum = map.at(j).at(k);
				}
			}
		}
		run();
		cout << "#" << i + 1 << " " << result << endl;
	}
}