# Johnson 全源最短路

## 题目描述

给定一个包含 $n$ 个结点和 $m$ 条带权边的有向图，求所有点对间的最短路径长度，一条路径的长度定义为这条路径上所有边的权值和。

注意：

1. 边权**可能**为负，且图中**可能**存在重边和自环；

2. 部分数据卡 $n$ 轮 SPFA 算法。

## 输入格式

第 $1$ 行：$2$ 个整数 $n,m$，表示给定有向图的结点数量和有向边数量。

接下来 $m$ 行：每行 $3$ 个整数 $u,v,w$，表示有一条权值为 $w$ 的有向边从编号为 $u$ 的结点连向编号为 $v$ 的结点。

## 输出格式

若图中存在负环，输出仅一行 $-1$。

若图中不存在负环：

输出 $n$ 行：令 $dis_{i,j}$ 为从 $i$ 到 $j$ 的最短路，在第 $i$ 行输出 $\sum\limits_{j=1}^n j\times dis_{i,j}$，注意这个结果可能超过 int 存储范围。

如果不存在从 $i$ 到 $j$ 的路径，则 $dis_{i,j}=10^9$；如果 $i=j$，则 $dis_{i,j}=0$。

## 样例 #1

### 样例输入 #1

```C++
5 7
1 2 4
1 4 10
2 3 7
4 5 3
4 2 -2
3 4 -3
5 3 4
```

### 样例输出 #1

```C++
128
1000000072
999999978
1000000026
1000000014
```

## 样例 #2

### 样例输入 #2

```C++
5 5
1 2 4
3 4 9
3 4 -3
4 5 3
5 3 -2
```

### 样例输出 #2

```C++
-1
```

## 提示

【样例解释】

左图为样例 $1$ 给出的有向图，最短路构成的答案矩阵为：

```C++
0 4 11 8 11 
1000000000 0 7 4 7 
1000000000 -5 0 -3 0 
1000000000 -2 5 0 3 
1000000000 -1 4 1 0 
```

右图为样例 $2$ 给出的有向图，红色标注的边构成了负环，注意给出的图不一定连通。

![7lb35u4u.png](Johnson+全源最短路+2b76905a-3be5-4a11-bb6e-add7f9b08b8c/7lb35u4u.png)

【数据范围】

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

