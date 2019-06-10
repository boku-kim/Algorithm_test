/*1952 [모의 SW 역량테스트] 수영장 */

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<cstring>
#include<algorithm>
using namespace std;

int T;
pair<int, int> month[13];
pair<int, int>tmpm[13];
int pay[4];//1년, 3달, 1달,1일
int check[13];
int day;
int m;
int result;

bool comp(pair<int, int> a, pair<int, int> b) {
	return a.second < b.second;
}
void dfs(int cnt,int cur_cnt, int n,int sum,int dd) {
	if (cur_cnt == cnt) {
		for (int i = 0;i <= m;i++) {
			int ddd = 0;
			int tmps = pay[2]*i;
			int c = 0;
			int index = 12;
			while (c < i) {
				if (check[tmpm[index].first] == 0) {
					ddd += tmpm[index].second;
					c++;
				}
				index--;
			}
			tmps += ((day - (ddd+dd))*pay[3]);
			if (sum + tmps < result) {
				result = sum + tmps;
			}
		}
		return;
	}
	if (n > 12) return;
	int tmpd=0;
	for (int i = 0;i < 3;i++) {
		if (n + i < 13) {
			if (month[n + i].second != 0) {
				m--;
				tmpd += month[n + i].second;
			}
			check[n+i] = 1;
		}
	}
	dfs(cnt, cur_cnt + 1, n + 3, sum + pay[1],dd+tmpd);
	for (int i = 0;i < 3;i++) {
		if (n + i < 13) {
			if (month[n + i].second != 0) {
				m++;
			}
			check[n+i] = 0;
		}
	}
	dfs(cnt, cur_cnt, n + 1, sum,dd);
}
void run() {
	for (int i = 0;i <= 4;i++) {
		dfs(i, 0, 1, 0,0);
	}
}
int main() {
	scanf("%d", &T);
	for (int i = 0;i < T;i++) {
		day = 0;
		m = 0;
		memset(check, 0, sizeof(int) * 13);
		for (int j = 3;j >=0;j--) {
			scanf("%d", &pay[j]);
		}
		int tmp;
		for (int j = 1;j < 13;j++) {
			scanf("%d", &tmp);
			if (tmp != 0) {
				m++;
				day += tmp;
			}
			month[j] = pair<int, int>(j, tmp);
			tmpm[j] = pair<int, int>(j, tmp);
		}
		sort(tmpm, tmpm + 13, comp);
		result = pay[0];
		run();
		printf("#%d %d\n",i+1, result);
	}
}