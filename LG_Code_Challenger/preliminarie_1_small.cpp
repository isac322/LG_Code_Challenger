#include <cstdio>
#include <algorithm>

using namespace std;

#define NUM 500

int num[NUM + 1];
int cnt[NUM + 1];

int main() {
	//freopen("small.in", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int t;
	scanf("%d", &t);

	for (int i = 0; i < NUM; i++) num[i] = (i + 1)*(i + 1);

	for (int i = 1; i <= NUM; i++) {
		for (int j = i; j <= NUM; j++) {
			for (int k = j; k <= NUM; k++) {
				int v = i*j*k;
				if (v > NUM) break;

				int tmp = i*i + j*j + k*k;
				int *p = find(num, num + NUM, tmp);
				if (p != num + NUM) {
					cnt[v]++;
				}
			}
		}
	}

	for (int i = 1; i <= NUM; i++) cnt[i] += cnt[i - 1];

	while (t--) {
		int n;
		scanf("%d", &n);
		printf("%d\n", cnt[n]);
	}
}