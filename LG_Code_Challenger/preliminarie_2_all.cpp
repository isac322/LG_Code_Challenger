#include <cstdio>
#include <algorithm>

int dp[10001];
int n, a, b;
int times[10001];

int solve(int day) {
	if (day >= n) return 0;

	int &p = dp[day];
	if (p != -1) return p;

	return p = std::min(times[day] * a + solve(day + 1), b + solve(day + 5));
}

using namespace std;

int main() {
	int t;
	scanf("%d", &t);

	while (t--) {
		scanf("%d %d %d", &n, &a, &b);
		std::fill_n(dp, n + 1, -1);
		for (int i = 0; i < n; i++) scanf("%d", times + i);

		printf("%d\n", solve(0));
	}
}