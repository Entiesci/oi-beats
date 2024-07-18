# Johnson 全源最短路

大约$O(V^2\log V)$，可以跑1e3。

#### 算法描述

Johnson算法结合了Bellman-Ford算法和Dijkstra算法的优点，用于计算含有负权边的图中所有顶点对之间的最短路径。算法分为三个主要步骤：

1. 使用Bellman-Ford算法找到一个顶点，重新调整图中所有边的权重，使得所有边的权重都变为非负。

2. 对每个顶点使用Dijkstra算法计算最短路径。

3. 使用之前计算的权重调整结果，恢复原始的最短路径长度。

#### 时间复杂度

- **Johnson算法**：$O(V^2 log V + VE)$，对于稀疏图，通常比Floyd-Warshall算法更高效，尤其是当E的数量远小于$V^2$时。

- **Floyd-Warshall算法**：时间复杂度固定为$O(V^3)$，与图的稀疏性无关。

## 例题 #1

题目描述

给定一个包含 $n$ 个结点和 $m$ 条带权边的有向图，求所有点对间的最短路径长度，一条路径的长度定义为这条路径上所有边的权值和。

注意：

1. 边权**可能**为负，且图中**可能**存在重边和自环；

2. 部分数据卡 $n$ 轮 SPFA 算法。

对于 $100\%$ 的数据，$1\leq n\leq 3\times 10^3,\ \ 1\leq m\leq 6\times 10^3,\ \ 1\leq u,v\leq n,\ \ -3\times 10^5\leq w\leq 3\times 10^5$。

对于 $20\%$ 的数据，$1\leq n\leq 100$，不存在负环（可用于验证 Floyd 正确性）

对于另外 $20\%$ 的数据，$w\ge 0$（可用于验证 Dijkstra 正确性）

upd. 添加一组 Hack 数据：针对 SPFA 的 SLF 优化

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=3e3+5,INF=1000000000;
//spfa定义部分
int dis[MAXN],cntt[MAXN];
//djstr定义部分
int ddis[MAXN];

int n,vis[MAXN],cnt,u,w,m,v;	//注意：cnt-边的数量；cntt[]-记录现在这条路走过了多少节点
//邻接表定义部分
int h[MAXN];	//head
struct edge {
	int from,next,to,dis;
} edge[MAXN<<2];

void add(int from,int to,int dis) {	//邻接表

	edge[++cnt].next=h[from];
	edge[cnt].from=from;
	edge[cnt].to=to;
	edge[cnt].dis=dis;
	h[from]=cnt;
}


//求距离
void djstr(int rt) {
	priority_queue<pair<int,int>> pq;
	for(int i=1; i<=n; i++)ddis[i]=INF;	//初始化边权
	memset(vis,0,sizeof(vis));	//记得初始化，因为djstl要循环n次
	pq.push(make_pair(0,rt));	//先从起点开始
	ddis[rt]=0;

	while(pq.size()) {	//搜完全图
		u=pq.top().second;	//取点,并且是当前队列里最小的
		pq.pop();	//记得弹出哦!
		if(vis[u])
			continue;
		vis[u]=1;

		for(int j=h[u]; j; j=edge[j].next) {
			if(ddis[u]+edge[j].dis<ddis[edge[j].to]) {
				ddis[edge[j].to]=ddis[u]+edge[j].dis;	//更新
				if(!vis[edge[j].to])
					pq.push(make_pair(-ddis[edge[j].to],edge[j].to));	//默认是大根堆,于是距离要存负数,起到小根堆的作用.距离要存在pair的first
			}
		}
	}
}


//SPFA用来判断负环！！！

bool spfa() {

	queue <int> q;	//队列存点
	for(int i=1; i<=n; i++)dis[i]=INF;	//记得初始化
	q.push(0);	//首先把起点放进去
	dis[0]=0;
	vis[0]=1;

	while(q.size()) {	//循环,一直到没有点可以访问
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=h[u]; i; i=edge[i].next) {	//遍历出边
			int nxt=edge[i].to;
			if(dis[nxt]<=dis[u]+edge[i].dis)continue;	//如果原来的更优,跳过
			dis[nxt]=dis[u]+edge[i].dis;	//更新距离
			if(!vis[nxt]) {		//如果没有访问过
				q.push(nxt);
				vis[nxt]=1;

				if(++cntt[nxt]>n) // n+1结点，随便更新现在这条路走过了多少节点，如果大于总节点数，则有负环
					return 0;
			}
		}
	}
	return 1;
}
signed main() {
	cin>>n>>m;
	for(int i=1; i<=n; i++)dis[i]=INF;
	for(int i=1; i<=m; i++) {	//邻接表建边
		cin>>u>>v>>w;
		add(u,v,w);
	}
	for(int i=1; i<=n; i++)	//不理解？？？
		add(0,i,0);
	if(!spfa()) {	//存在负环
		cout<<-1;
		return 0;
	}
	//不存在负环
	for(int i=1; i<cnt; i++)
		edge[i].dis+=dis[edge[i].from]-dis[edge[i].to];
	for(int i=1; i<=n; i++) {	//每个点开始一遍djstr
		djstr(i);
		int ans=0;
		for(int j=1; j<=n; j++) {
			if(ddis[j]==INF)
				ans+=j*INF;		//i到不了j
			else
				ans+=j*(ddis[j]-(dis[i]-dis[j]));	//按题目要求求和
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

