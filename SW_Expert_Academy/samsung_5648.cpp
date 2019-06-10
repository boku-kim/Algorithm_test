/* 5648. [모의 SW 역량테스트] 원자 소멸 시뮬레이션 */

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;

int T, N;
int result;
bool alive[1000];
struct Info {
	int x, y, d,e;
	Info() {}
	Info(int x, int y, int d,int e) {
		this->x = x;
		this->y = y;
		this->d = d;
		this->e = e;
	}
};
bool comp(Info* a, Info* b) {
	if (a->x == b->x) return a->y < b->y;
	return a->x < b->x;
}
vector< Info* > atom;

void run() {
	for (int i = 0;i < N;i++) {
		if (alive[i] == 0) continue;
		Info* cur;
		int sidx = i;
		float sec=-1;
		queue<int> q1;//저장큐
		queue<int> q2;
		q2.push(i);
		while (!q2.empty()) {
			bool changed = false;
			cur =atom.at( q2.front());
			for (int j = 0;j < N;j++) {
				Info* tmp=atom.at(j);
				if (tmp->d != cur->d && alive[j]) {
					if (cur->d == 0) {
						float dist=-1;
						if (tmp->d == 1 && tmp->x == cur->x && tmp->y > cur->y) {
							 dist = (float)(tmp->y - cur->y) / 2.0;
						}
						else if (tmp->d == 2 && tmp->x-cur->x==tmp->y-cur->y) {
							dist = tmp->x - cur->x;
						}
						else if (tmp->d == 3 && cur->x-tmp->x==tmp->y-cur->y) {
							dist = cur->x - tmp->x;
						}
						if (dist <= -1) continue;
						if (sec == -1 || dist < sec) {
							sec = dist;
							changed = true;
							while (!q1.empty()) {
								alive[q1.front()] = 1;
								q1.pop();
							}
							q1.push(j);
							alive[j] = 0;
						}
						else if (dist == sec) {
							q1.push(j);
							alive[j] = 0;
						}
					}
					else if (cur->d == 1) {
						float dist=-1;
						if (tmp->d == 0 && tmp->x == cur->x && cur->y > tmp->y) {
							dist = (float)(cur->y - tmp->y) / 2.0;
						}
						else if (tmp->d == 2 && tmp->x - cur->x == cur->y - tmp->y) {
							dist = tmp->x - cur->x;
						}
						else if (tmp->d == 3 && cur->x - tmp->x == cur->y - tmp->y) {
							dist = cur->x - tmp->x;
						}
						if (dist <= -1) continue;
						if (sec == -1 || dist < sec) {
							sec = dist;
							changed = true;
							while (!q1.empty()) {
								alive[q1.front()] = 1;
								q1.pop();
							}
							q1.push(j);
							alive[j] = 0;
						}
						else if (dist == sec) {
							q1.push(j);
							alive[j] = 0;
						}
					}
					else if (cur->d == 2) {
						float dist=-1;
						if (tmp->d == 0 && cur->x-tmp->x==cur->y-tmp->y) {
							dist = cur->x - tmp->x;
						}
						else if (tmp->d == 1 && cur->x - tmp->x == tmp->y - cur->y) {
							dist = cur->x - tmp->x;
						}
						else if (tmp->d == 3 && cur->y==tmp->y && tmp->x<cur->x) {
							dist = (float)(cur->x-tmp->x)/2.0;
						} 
						if (dist <= -1) continue;
						if (sec == -1 || dist < sec) {
							sec = dist;
							changed = true;
							while (!q1.empty()) {
								alive[q1.front()] = 1;
								q1.pop();
							}
							q1.push(j);
							alive[j] = 0;
						}
						else if (dist == sec) {
							q1.push(j);
							alive[j] = 0;
						}
					}
					else {
						float dist=-1;
						if (tmp->d == 0 && tmp->x - cur->x == cur->y - tmp->y) {
							dist = tmp->x - cur->x;
						}
						else if (tmp->d == 1 && tmp->x - cur->x == tmp->y - cur->y) {
							dist = tmp->x - cur->x;
						}
						else if (tmp->d == 2 && cur->y == tmp->y && cur->x<tmp->x) {
							dist = (float)(tmp->x - cur->x) / 2.0;
						}
						if (dist <= -1) continue;
						if (sec == -1 || dist < sec) {
							sec = dist;
							changed = true;
							while (!q1.empty()) {
								alive[q1.front()] = 1;
								q1.pop();
							}
							q1.push(j);
							alive[j] = 0;
						}
						else if (dist == sec) {
							q1.push(j);
							alive[j] = 0;
						}
					}
				}
			}
			if (changed==false) {
				if (q2.size()<=1) {
					if (q1.empty()) {
						break;
					}
					else {
						result += atom.at(sidx)->e;
						while (!q1.empty()) {
							result += atom.at(q1.front())->e;
							q1.pop();
						}
					}
				}
				q2.pop();
			}
			else {
				alive[sidx] = 1;
				sidx = q2.front();
				alive[sidx] = 0;
				while (!q2.empty()) {
					q2.pop();
				}
				for (int p = 0;p < q1.size();p++) {
					q2.push(q1.front());
					q1.push(q1.front());
					q1.pop();
				}
			}
		}
	}
}
int main() {
	scanf("%d", &T);
	for (int i = 0;i < T;i++) {
		atom.clear();
		memset(alive, 1, sizeof(bool) * 1000);
		result = 0;
		scanf("%d", &N);
		int a, b, c, d;
		for (int j = 0;j < N;j++) {
			scanf("%d %d %d %d", &a, &b, &c,&d);
			atom.push_back(new Info(a, b,c, d));
		}
		run();
		printf("#%d %d\n", i + 1, result);
	}
}