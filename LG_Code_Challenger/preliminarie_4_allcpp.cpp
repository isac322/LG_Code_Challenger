#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

short n, m, r, k, color;

struct RECT {
	short x, y1, y2, end;

	RECT(short _x, short _y1, short _y2, short _end) : x(_x), y1(_y1), y2(_y2), end(_end) {}
	bool operator < (const RECT r) const {
		return x != r.x ? x < r.x : end > r.end;
	}
};

vector<RECT> colorMap[51];

#define SIZE (1<<12)

int tree[(SIZE << 1) + 4], cnt[(SIZE << 1) + 4];
void update(int x, int left, int right, int nodeLeft, int nodeRight, int val) {
	if (left > nodeRight || right < nodeLeft) return;
	if (left <= nodeLeft && right >= nodeRight) cnt[x] += val;
	else {
		int mid = (nodeLeft + nodeRight) >> 1;
		update(x * 2, left, right, nodeLeft, mid, val);
		update(x * 2 + 1, left, right, mid + 1, nodeRight, val);
	}
	tree[x] = 0;
	if (cnt[x] > 0) tree[x] = nodeRight - nodeLeft + 1;
	if (cnt[x] == 0 && nodeLeft < nodeRight) tree[x] = tree[x * 2] + tree[x * 2 + 1];
}

inline int getSize(int index) {
	vector<RECT> &map = colorMap[index];

	int size = 0;
	if (!map.empty()) {
		sort(map.begin(), map.end());

		int px = map[0].x;
		for (int i = 0; i < map.size(); i++) {
			size += (map[i].x - px)*tree[1];
			update(1, map[i].y1, map[i].y2 - 1, 0, SIZE, map[i].end);
			px = map[i].x;
		}
	}

	return size;
}

int main() {
	//freopen("large.in", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int t;
	scanf("%d", &t);

	while (t--) {
		fill_n(tree, (SIZE << 1) + 4, 0);
		fill_n(cnt, (SIZE << 1) + 4, 0);
		scanf("%hd %hd %hd %hd", &m, &n, &k, &r);
		for (short i = 1; i <= k; i++) colorMap[i].clear();

		for (short y = 0; y < n; y++) {
			for (short x = 0; x < m; x++) {
				scanf("%hd", &color);
				short x1 = x > r ? x - r : 0;
				short y1 = y > r ? y - r : 0;
				short x2 = x + r < m ? x + r + 1 : m;
				short y2 = y + r < n ? y + r + 1 : n;

				colorMap[color].push_back(RECT(x1, y1, y2, 1));
				colorMap[color].push_back(RECT(x2, y1, y2, -1));
			}
		}

		int sum = 0;
		for (int i = 1; i <= k; i++) {
			sum += getSize(i);
		}

		printf("%d\n", sum);
	}
}