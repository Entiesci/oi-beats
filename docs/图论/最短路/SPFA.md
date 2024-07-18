# SPFA

### 算法原理

SPFA算法的基本思想是：如果一个顶点的最短路径估计值发生了改变，那么与它相邻的顶点的最短路径估计值可能也会发生变化。因此，只有当一个顶点的最短路径估计值改变后，才需要调整它的相邻顶点。

算法步骤如下：

1. 初始化：选择一个源点，将其最短路径估计值设置为0，其余所有顶点的最短路径估计值设置为无穷大。将源点加入一个队列中。

2. 循环：只要队列非空，就执行以下步骤： a. 从队列中取出一个顶点u。 b. 考虑所有从u出发的边(u, v)，对于每条边，如果v的最短路径估计值可以通过u得到改进（即v的最短路径估计值大于u的最短路径估计值加上边(u, v)的权重），则更新v的最短路径估计值，并将v加入队列。

3. 结束：当队列为空时，算法结束。此时，如果图中不存在负权重环，所有顶点的最短路径估计值就是它们到源点的最短路径长度。

### 算法特点

- **效率**：SPFA算法通常比Bellman-Ford算法快，因为它避免了对所有边进行不必要的松弛操作。

- **适应性**：SPFA算法能够处理带有负权边的图，这是Dijkstra算法所不能直接做到的。

- **时间复杂度**：SPFA算法的平均时间复杂度通常被认为是O(kE)，其中k是一个小于2的常数，E是图中边的数量。但在最坏情况下，时间复杂度可能达到O(VE)，其中V是顶点的数量。

```C++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e4+5;
int vis[MAXN],h[50*MAXN];
int dis[MAXN],cnt,u,w,n,m,v,s;
struct Edge {
	int next,to,dis;
} edge[MAXN*50];
void add(int from,int to,int dis) {
	edge[++cnt].next=h[from];
	edge[cnt].to=to;
	edge[cnt].dis=dis;
	h[from]=cnt;
}

queue <int> q;

void spfa(int rt) {
	dis[rt]=0;
	vis[rt]=1;
	q.push(rt);
	while(q.size()) {   //类似广搜
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=h[u]; i; i=edge[i].next) {
			int nxt=edge[i].to;
			if(dis[nxt]<=dis[u]+edge[i].dis)continue;
			dis[nxt]=dis[u]+edge[i].dis;
			if(!vis[nxt]) {
				vis[nxt]=1;
				q.push(nxt);
			}
		}
	}

}
signed main() {
//	freopen("P3371_2.in","r",stdin);
//	freopen("test.txt","w",stdout);
	cin>>n>>m>>s;

	for(int i=1; i<=n; i++)dis[i]=2147483647;
//	memset(dis,0x3f,sizeof(dis));
	//cout<<dis[1]<<endl;
	for(int i=1; i<=m; i++) {
		cin>>u>>v>>w;
		add(u,v,w);
	}
	spfa(s);
	for(int i=1; i<=n; i++) {
		cout<<dis[i]<<' ';
	}
	return 0;
}
```

## 堆优化Dijkstra和SPFA的区别和优缺点

### 堆优化Dijkstra算法

#### 算法描述

堆优化Dijkstra算法是在Dijkstra算法的基础上，使用优先队列（通常是最小堆）来优化选点的过程，从而将Dijkstra算法的时间复杂度从O(V^2)降低到O((V+E)logV)，其中V是顶点数，E是边数。

#### 优缺点

- **优点**：

    - 时间复杂度较低，尤其是当图的边比较稠密时。

    - 算法稳定，在大多数情况下都可以在预期的时间复杂度内完成计算。

- **缺点**：

    - 需要使用优先队列，因此在空间上比原始的Dijkstra算法更复杂。

    - 对于稀疏图，堆优化Dijkstra算法的优势不如SPFA明显。

### SPFA算法

#### 算法描述

SPFA算法是一种基于Bellman-Ford算法的优化，它使用一个队列来维护待优化的节点，减少了不必要的节点重复入队，通常在稀疏图中比Dijkstra算法更快。

#### 优缺点

- **优点**：

    - 在最坏情况下，时间复杂度仍然优于Dijkstra算法，尤其是在稀疏图中。

    - 实现相对简单，不需要复杂的优先队列。

    - 可以处理带有负权边的图（虽然Dijkstra算法不能直接处理负权边，但通过适当修改也可以处理）。

- **缺点**：

    - 算法的时间复杂度不固定，最坏情况下会退化到O(VE)，但在实际应用中很少遇到。

    - 对于某些特定图，SPFA算法可能会非常慢，因为它可能会多次重复松弛同一个节点。

### 区别

- **数据结构**：堆优化Dijkstra算法通常使用优先队列，而SPFA算法使用普通队列。

- **时间复杂度**：堆优化Dijkstra算法有较为稳定的时间复杂度，而SPFA算法的时间复杂度取决于图的特性和实现细节。

- **适应性**：SPFA算法对于负权边的图有更好的适应性，而堆优化Dijkstra算法通常不直接支持负权边。

- **最坏情况性能**：SPFA算法在最坏情况下的性能不如堆优化Dijkstra算法稳定。

在实际应用中，选择哪种算法要根据具体问题、图的类型以及所需的运行效率来决定。通常，对于稠密图，堆优化Dijkstra算法是一个较好的选择，而对于稀疏图，SPFA算法可能更有优势。然而，由于SPFA算法性能的不确定性，有时也会优先考虑堆优化Dijkstra算法以确保稳定的表现。

## SPFA判负环

题目描述

给定一个 $n$ 个点的有向图，请求出图中是否存在**从顶点 $1$ 出发能到达**的负环。

负环的定义是：一条边权之和为负数的回路。

---

首先我们要知道，对于一个不存在负环的图，从起点到任意一个点最短距离经过的点最多只有 n 个

这样的话，我们用 cnt[ i ] 表示从起点（假设就是 1）到 i 的最短距离包含点的个数，初始化 cnt[ 1 ] = 1，那么当我们能够用点 u 松弛点 v 时，松弛时同时更新 cnt[ v ] = cnt[ u ] + 1，若发现此时 cnt[ v ] > n，那么就存在负环

```C++
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e3+10;

int n,m;
struct Edge{
	int to,w,next;
}edge[MAXN*3];        
int head[MAXN],tot;
inline void Init(){    
	for(int i=0;i<MAXN*3;i++) edge[i].next=0;
	for(int i=0;i<MAXN;i++) head[i]=0;
	tot=0;
}
inline void addedge(int u,int v,int w){
	edge[++tot].to=v;
	edge[tot].w=w;
	edge[tot].next=head[u];
	head[u]=tot;
}

queue<int> Q;
int dis[MAXN],vis[MAXN],cnt[MAXN];
bool spfa(){
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(cnt,0,sizeof(cnt));
	dis[1]=0; vis[1]=true;
	Q.push(1);
	while(!Q.empty()){
		int x=Q.front();
		Q.pop();
		vis[x]=false;
		for(int i=head[x];i;i=edge[i].next){
			int y=edge[i].to,z=edge[i].w;
			if(dis[y]>dis[x]+z){
				dis[y]=dis[x]+z; 
				cnt[y]=cnt[x]+1;  
				if(cnt[y]>=n) return true;  
				if(!vis[y]){
					Q.push(y);
					vis[y]=true;
				}
			}
		}
	}
	return false;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		Init();
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++){
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			addedge(u,v,w);
			if(w>=0) addedge(v,u,w);
		}
		puts(spfa()?"YES":"NO");
	}
	return 0;
}
```

