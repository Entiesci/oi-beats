# Dijkstra

通过已得到最短路径的的点去扩展其他的点，设起点为 s

设定 `dist[s]=0;dist[v]=inf(v!=s)`

- 找到最小的 `dist [ u ]`（且 u 没有被访问过）此时的 `dist [ u ]`就是起点到该点的最短路（为什么？→之后的dis值一定大于dis_u，不会更新dis_u）

- 更新与 u 相连的点

vector 写法

```C++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int vis[N],h[N];
int dis[N],cnt,u,w,n,m,v,s;
struct node {
	int nxt,dis;
};

vector<node> e[N];
priority_queue<pair<int,int>> pq;
void add(int a,int b,int dis) {
	e[a].push_back((node){b,dis});
}

void djstr(int rt) {
	pq.push(make_pair(0,rt));
	int u=rt;	//先从起点开始查
	for(int i=1; i<=n; i++)dis[i]=2147483647;	//初始化边权

	dis[rt]=0;
//	vis[rt]=1;//别写错！！
	
	while(pq.size()) {	//搜完全图
		
		u=pq.top().second;
		
		pq.pop();
		if(vis[u])continue;//记得continue
		vis[u]=1;
		for(int i=0;i<e[u].size();i++){
			int v=e[u][i].nxt,w=e[u][i].dis;
			if(!vis[v]&&dis[u]+w<dis[v]){
				dis[v]=dis[u]+w;	//更新
				pq.push(make_pair(-dis[v],v));
			}
		}
	}
}
signed main() {

	cin>>n>>m>>s;

	for(int i=1; i<=m; i++) {
		cin>>u>>v>>w;
		if(u!=v)add(u,v,w);
	}
	djstr(s);
	for(int i=1; i<=n; i++) {
		cout<<dis[i]<<' ';
	}
	return 0;
}
```

邻接表版本

```C++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e6+5;
int vis[MAXN],h[MAXN];
int dis[MAXN],cnt,u,w,n,m,v,s;
struct Edge {
	int next,to,dis;
} edge[MAXN];
priority_queue<pair<int,int>> pq;
void add(int from,int to,int dis) {
	edge[++cnt].next=h[from];
	edge[cnt].to=to;
	edge[cnt].dis=dis;
	h[from]=cnt;
}

void djstr(int rt) {
	pq.push(make_pair(0,rt));
	int u=rt;	//先从起点开始查
	for(int i=1; i<=n; i++)dis[i]=2147483647;	//初始化边权

	dis[rt]=0;
	//for(int i=1; i<=n; i++)
	while(pq.size()) {	//搜完全图
		
		u=pq.top().second;

		pq.pop();
        if(vis[u])continue;
        vis[u]=1;
		for(int j=h[u]; j; j=edge[j].next) {
			if(!vis[edge[j].to]&&dis[u]+edge[j].dis<dis[edge[j].to]){
				dis[edge[j].to]=dis[u]+edge[j].dis;	//更新
				pq.push(make_pair(-dis[edge[j].to],edge[j].to));
			}
				
		}
		
		/*int min=2147483647;
		for(int j=1; j<=n; j++) {	//重新查找到i距离最小的点
			if(!vis[j]&&dis[j]<min) {
				min=dis[j];
				u=j;
			}
		}*/
	}
}
signed main() {

	cin>>n>>m>>s;

	for(int i=1; i<=m; i++) {
		cin>>u>>v>>w;
		if(u!=v)add(u,v,w);
	}
	djstr(s);
	for(int i=1; i<=n; i++) {
		cout<<dis[i]<<' ';
	}
	return 0;
}
```

## 其他问题

