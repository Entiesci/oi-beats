# SPFA

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


堆优化Dijkstra和SPFA的区别和优缺点：待补充

# SPFA判负环

## 题目描述

给定一个 $n$ 个点的有向图，请求出图中是否存在**从顶点 $1$ 出发能到达**的负环。

负环的定义是：一条边权之和为负数的回路。

## 输入格式

**本题单测试点有多组测试数据**。

输入的第一行是一个整数 $T$，表示测试数据的组数。对于每组数据的格式如下：

第一行有两个整数，分别表示图的点数 $n$ 和接下来给出边信息的条数 $m$。

接下来 $m$ 行，每行三个整数 $u, v, w$。

- 若 $w \geq 0$，则表示存在一条从 $u$ 至 $v$ 边权为 $w$ 的边，还存在一条从 $v$ 至 $u$ 边权为 $w$ 的边。

- 若 $w < 0$，则只表示存在一条从 $u$ 至 $v$ 边权为 $w$ 的边。

## 输出格式

对于每组数据，输出一行一个字符串，若所求负环存在，则输出 `YES`，否则输出 `NO`。

## 样例 #1

### 样例输入 #1

```C++
2
3 4
1 2 2
1 3 4
2 3 1
3 1 -3
3 3
1 2 3
2 3 4
3 1 -8
```

### 样例输出 #1

```C++
NO
YES
```

## 提示

#### 数据规模与约定

对于全部的测试点，保证：

- $1 \leq n \leq 2 \times 10^3$，$1 \leq m \leq 3 \times 10^3$。

- $1 \leq u, v \leq n$，$-10^4 \leq w \leq 10^4$。

- $1 \leq T \leq 10$。

#### 提示

请注意，$m$ **不是**图的边数。

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

