/* 1953. [모의 SW 역량테스트] 탈주범 검거 */

#include<iostream>
#include<vector>
#include<queue>
#define MAX 50
using namespace std;

int T, N, M, R, C, L;
vector< vector<int> > map;
//현재 파이프에서 갈 수 있는 방향 0~6번 파이프 순, 동서남북 순
int road[7][4] = { {1,1,1,1},{0,0,1,1},{1,1,0,0},{1,0,0,1},{1,0,1,0},{0,1,1,0},{0,1,0,1} };
//동 서 남 북
int dir[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
//x 방향으로 나왔을 때 가능한 다음 파이프 번호,동서남북 순
int pipe[4][4] = { { 0,2,5,6 },{0,2,3,4},{0,1,3,6},{ 0,1,4,5 } }; 
struct Info {
	int x, y, s;
	Info() {}
	Info(int x, int y, int s) {
		this->x = x;
		this->y = y;
		this->s = s;
	}
};
int bfs() {
	int visited[MAX][MAX] = { 0 };
	queue<Info*> q;
	visited[R][C] = 1;
	q.push(new Info(R, C, 1));
	int result=1;
	while (!q.empty()) {
		Info *cur = q.front();
		int state = map.at(cur->x).at(cur->y) - 1;
		if (cur->s == L)break;
		q.pop();
		for (int i = 0;i < 4;i++) {
			if (road[state][i]) {
				int x = cur->x + dir[i][0];
				int y = cur->y + dir[i][1];
				if (x >= 0 && x < N && y >= 0 && y < M && visited[x][y] == 0
					&& map.at(x).at(y)!=0) {
					for (int j = 0;j < 4;j++) {
						if (pipe[i][j] == map.at(x).at(y)-1) {
							visited[x][y] = 1;
							q.push(new Info(x, y, cur->s + 1));
							result++;
							break;
						}
					}
				}
			}
		}
	}
	return result;
}
int main() {
	cin >> T;
	for (int i = 0;i < T;i++) {
		map.clear();
		cin >> N >> M >> R >> C >> L;
		map = vector< vector<int> >(N, vector<int>(M, 0));
		for (int j = 0;j < N;j++) {
			for (int k = 0;k < M;k++) {
				cin >> map.at(j).at(k);
			}
		}
		cout << "#" << i + 1 << " " << bfs() << endl;
	}
}