#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <limits>
#include <functional>

using namespace std;

typedef pair<int, int> INTP;
const int &INF = numeric_limits<int>::max();

vector<INTP> map[500];
int dist[500];
int vertex;

void dijkstra(int start, int end) {
	fill_n(dist, vertex, INF);
	dist[start] = 0;

	priority_queue<INTP, vector<INTP>, greater<INTP> > que;
	que.push(make_pair(0, start));

	while (que.size()) {
		const int here = que.top().second;

		if (here == end) break;

		que.pop();

		for (vector<INTP>::iterator i = map[here].begin(); i != map[here].end(); i++) {
			if (dist[i->first] > dist[here] + i->second) {
				dist[i->first] = dist[here] + i->second;
				que.push(make_pair(dist[i->first], i->first));
			}
		}
	}
}

int main() {
	int t, cost, sum;
	bool fail;
	scanf("%d", &t);

	vector<pair<int, pair<short, short> > > arr;

	while (t--) {
		arr.clear();
		fail = false;
		scanf("%d", &vertex);

		for (int i = 0; i < vertex; i++) map[i].clear();

		for (int i = 0; i < vertex - 1; i++) {
			for (int j = i + 1; j < vertex; ++j) {
				scanf("%d", &cost);
				arr.push_back(make_pair(cost, make_pair(i, j)));
			}
		}

		sort(arr.begin(), arr.end());

		for (vector<pair<int, pair<short, short> > >::iterator iter = arr.begin(); iter != arr.end(); iter++) {
			short &i = iter->second.first, &j = iter->second.second;
			int &cost1 = iter->first;

			dijkstra(i, j);

			int &c = dist[j];

			if (c != INF && c < cost1) {
				fail = true;
				break;
			}
			else if (c > cost1) {
				map[i].push_back(make_pair(j, cost1));
				map[j].push_back(make_pair(i, cost1));
			}
		}

		if (fail) puts("-1");
		else {
			sum = 0;
			for (int i = 0; i < vertex; i++) {
				for (vector<INTP>::iterator j = map[i].begin(); j != map[i].end(); j++) sum += j->second;
			}
			printf("%d\n", sum >> 1);
		}
	}
}