#define _CRT_SECURE_NO_WARNINGS
#define MAX 10
#include<stdio.h>
#include<vector>
#include<queue>
using namespace std;

int T, M, A;
int dir[5][2] = { {0,0},{-1,0},{0,1},{1,0},{0,-1} };
struct Info {
	int x, y, c, p;
	Info(int x, int y, int c, int p) {
		this->x = x;
		this->y = y;
		this->c = c;
		this->p = p;
	}
};
struct Info2 {
	int x, y, c;
	Info2(int x, int y, int c) {
		this->x = x;
		this->y = y;
		this->c = c;
	}
};

vector<Info*> bc;//bc 정보
vector< vector< vector<int> > > map;
vector<int> a;//A이동 정보
vector<int> b;//B이동 정보

void bfs(int n,int x, int y, int c) {
	int visited[10][10] = { 0 };
	queue<Info2*> q;
	visited[x][y] = 1;
	q.push(new Info2(x, y, 0));
	map.at(x).at(y).push_back(n);

	while (!q.empty()) {
		Info2* cur = q.front();
		q.pop();
		if (cur->c == c) break;
		for (int i = 1;i < 5;i++) {
			int xx = cur->x + dir[i][0];
			int yy = cur->y + dir[i][1];
			if (xx >= 0 && xx < 10 && yy >= 0 & yy < 10 && visited[xx][yy] == 0) {
				visited[xx][yy] = 1;
				q.push(new Info2(xx, yy, cur->c + 1));
				map.at(xx).at(yy).push_back(n);
			}
		}
	}

}
int run() {
	int sum = 0;
	int s = 0;
	pair<int, int> ra;
	pair<int, int> rb;
	ra.first = 0;
	ra.second = 0;
	rb.first = 9;
	rb.second = 9;

	while (s <= M) {
		int tmp = 0;
		int aidx=-1;
		int bidx=-1;
		bool abig= map.at(ra.first).at(ra.second).size()>map.at(rb.first).at(rb.second).size();
		
		if (abig) {
			for (int i = 0;i < map.at(ra.first).at(ra.second).size();i++) {
				aidx = map.at(ra.first).at(ra.second).at(i);
				for (int j = 0;j < map.at(rb.first).at(rb.second).size();j++) {
					bidx = map.at(rb.first).at(rb.second).at(j);
					if (aidx != bidx && tmp < bc.at(aidx)->p + bc.at(bidx)->p) {
						tmp = bc.at(aidx)->p + bc.at(bidx)->p;
					}
				}
				if (bc.at(aidx)->p > tmp) {
					tmp = bc.at(aidx)->p;
				}
			}
		}
		else {
			for (int i = 0;i < map.at(rb.first).at(rb.second).size();i++) {
				bidx = map.at(rb.first).at(rb.second).at(i);
				for (int j = 0;j < map.at(ra.first).at(ra.second).size();j++) {
					aidx = map.at(ra.first).at(ra.second).at(j);
					if (aidx != bidx && tmp < bc.at(aidx)->p + bc.at(bidx)->p) {
						tmp = bc.at(aidx)->p + bc.at(bidx)->p;
					}
				}
				if (bc.at(bidx)->p > tmp) {
					tmp = bc.at(bidx)->p;
				}
			}
		}
		sum += tmp;
		if (s != M) {
			ra.first += dir[a.at(s)][0];
			ra.second += dir[a.at(s)][1];
			rb.first += dir[b.at(s)][0];
			rb.second += dir[b.at(s)][1];
		}
		s++;
	}
	return sum;
}
int main() {
	scanf("%d", &T);
	for (int i = 0;i < T;i++) {
		bc.clear();
		a.clear();
		b.clear();
		map.clear();
		map = vector< vector< vector<int> > >(10,vector<vector<int>>(10));
		scanf("%d %d", &M, &A);
		int tmp;
		for (int j = 0;j < M;j++) {
			scanf("%d", &tmp);
			a.push_back(tmp);
		}
		for (int j = 0;j < M;j++) {
			scanf("%d", &tmp);
			b.push_back(tmp);
		}
		int a, b, c, d;
		for (int j = 0;j < A;j++) {
			scanf("%d %d %d %d", &a, &b, &c, &d);
			bc.push_back(new Info(b-1, a-1, c, d));
			bfs(j, bc.at(j)->x, bc.at(j)->y, bc.at(j)->c);
		}
		printf("#%d %d\n", i + 1, run());
	}
}
