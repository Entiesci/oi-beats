# 次短路算法/K短路算法

每次更新时，优先更新最短路，若能更新最短路，就令次短路等于之前的最短路，再更新最短路

## 次短路 | 集合位置

题目描述

每次有大的活动，大家都要在一起“聚一聚”，不管是去好乐迪，还是避风塘，或者汤姆熊，大家都要玩的痛快。还记得心语和花儿在跳舞机上的激情与释放，还记得草草的投篮技艺是如此的高超，还记得狗狗的枪法永远是'S'……还有不能忘了，胖子的歌声永远是让我们惊叫的！！

今天是野猫的生日，所以想到这些也正常，只是因为是上学日，没法一起去玩了。但回忆一下那时的甜蜜总是一种幸福嘛。。。

但是每次集合的时候都会出现问题！野猫是公认的“路盲”，野猫自己心里也很清楚，每次都提前出门，但还是经常迟到，这点让大家很是无奈。后来，野猫在每次出门前，都会向花儿咨询一下路径，根据已知的路径中，总算能按时到了。

现在提出这样的一个问题：给出 $n$ 个点的坐标，其中第一个为野猫的出发位置，最后一个为大家的集合位置，并给出哪些位置点是相连的。野猫从出发点到达集合点，总会挑一条最近的路走，如果野猫没找到最近的路，他就会走第二近的路。请帮野猫求一下这条第二最短路径长度。

输入格式

第一行是两个整数 $n(1 \le n \le 200)$ 和 $m$，表示一共有 $n$ 个点和 $m$ 条路，以下 $n$ 行每行两个数 $x_i$，$y_i$，$(-500 \le x_i,y_i \le 500),$ 代表第 $i$ 个点的坐标，再往下的 $m$ 行每行两个整数 $p_j$，$q_j,(1 \le p_j,q_j \le n)$，表示两个点相通。

### 正确算法

我们采用删边的思想，先跑一遍最短路，记录路径。

然后依次删去最短路径上每一条边，分别跑一遍最短路，取所有答案中的最小值即可。

```C++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
const int INF=1e9+5;
int vis[N],h[N],used[N],lst[N];
int cnt,u,w,n,m,v,s;
#define pdi pair<double,int>
using namespace std;
struct node{
	double x,y;
	int head;
	double dis;
	int pre;
}node[205];
struct edge{
	int nxt,to; 
	double dis;
}edge[50005];
double ans=INF<<1;
double calc(double a,double b,double c,double d){
	return (double)sqrt(double(a-c)*double(a-c)+double(b-d)*double(b-d));
}
//距离公式，注意数据类型
void addEdge(int u,int v,double w){
	edge[++cnt].dis=w;
	edge[cnt].to=v;
	edge[cnt].nxt=node[u].head;
	node[u].head=cnt;
}
priority_queue<pdi,vector<pdi>,greater<pdi> >pq;
void djkstr(int x,int y){
	for(int i=1;i<=n;i++){
		node[i].dis=INF;
	}
	node[1].dis=0;
	pq.push({0,1});
	while(pq.size()){
		pdi tmp=pq.top();
		pq.pop();
		double d=tmp.first;
		int u=tmp.second;
		if(node[u].dis!=d)continue;
		for(int e=node[u].head;e;e=edge[e].nxt)	{
			int v=edge[e].to;
			if((u==x&&v==y)||(u==y&&v==x))continue;
			if(node[v].dis<=d+edge[e].dis) continue;
			if(x==-1&&y==-1)node[v].pre=u;
			node[v].dis=d+edge[e].dis;
			pq.push({node[v].dis,v});
		}
	}
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lf%lf",&node[i].x,&node[i].y);
	}

	for(int i=1,u,v;i<=m;i++){
		scanf("%lld%lld",&u,&v);
		double w=calc(node[u].x,node[u].y,node[v].x,node[v].y);
		addEdge(u,v,w);
		addEdge(v,u,w);
	}

	djkstr(-1,-1);

	for(int i=n;i!=1;i=node[i].pre)	{
		djkstr(i,node[i].pre);
		ans=min(ans,node[n].dis);
	}
	if(ans>=INF)puts("-1");
	else printf("%.2lf\n",ans);
	return 0;
}
```

---

以下是未验证的其他算法

### 写法1

```C++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
const int INF=1e9+5;
int vis[N],h[N],used[N],lst[N];
int cnt,u,w,n,m,v,s;

double ans=INF,dis[3][N];
struct node {
	int nxt;
	double dis;
};

struct point {
	double x,y;
}p[N];

double getdis(int a,int b){
	return sqrt((p[a].x-p[b].x)*(p[a].x-p[b].x)+(p[a].y-p[b].y)*(p[a].y-p[b].y));
}

vector<node> e[N];
priority_queue<pair<double,int>> pq;
void add(int a,int b,double dis) {
	
//	cerr<<dis<<endl;
	e[a].push_back((node){b,dis});
	e[b].push_back((node){a,dis});
}

void djstr(int rt,int k) {
	pq.push(make_pair(0.00,rt));
	int u=rt;	//先从起点开始查
	for(int i=1; i<=n; i++)dis[k][i]=INF;	//初始化边权

	dis[k][rt]=0.0;
//	vis[rt]=1;//别写错！！
	
	while(pq.size()) {	//搜完全图
		
		u=pq.top().second;
		
		pq.pop();
		if(vis[u])continue;//记得continue
		vis[u]=1;
		for(int i=0;i<e[u].size();i++){
			int v=e[u][i].nxt;
			double w=e[u][i].dis;
			if(!vis[v]&&dis[k][u]+w<dis[k][v]){
				dis[k][v]=dis[k][u]+w;	//更新
//				cerr<<dis[k][v]<<endl;
				pq.push(make_pair(-dis[k][v],v));
				if(k==0)lst[v]=u;
			}
		}
	}
}
signed main() {

	cin>>n>>m;

	for(int i=1;i<=n;i++){
		cin>>p[i].x>>p[i].y;
	}
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		add(a,b,getdis(a,b));
	}
	djstr(1,0);
//	cerr<<"OK";
	memset(vis,0,sizeof vis);
	
	djstr(n,1);
	
//	for(int i=1;i<=n;i++){
//		cerr<<lst[i]<<' ';
//	}
//	
	for(int i=n;i;i=lst[i]){
		used[i]=1;
	}
//	cerr<<"YES";
	for(int i=1;i<=n;i++){
		if(used[i])continue;
//		cerr<<i<<"has ans="<<dis[0][i]+dis[1][i]<<endl;
		ans=min(ans,dis[0][i]+dis[1][i]);
	}
	double mx=INF;
	if(mx==ans)cout<<-1;
	else printf("%.2lf",ans);
	return 0;
}
```

### 写法2

```C++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
const int INF=1e9+5;
int vis[N],h[N],used[N],lst[N];
int cnt,u,w,n,m,v,s;

double ans=INF,dis[N],sdis[N];
struct node {
	int nxt;
	double dis;
};

struct point {
	double x,y;
}p[N];

double getdis(int a,int b){
	return sqrt((p[a].x-p[b].x)*(p[a].x-p[b].x)+(p[a].y-p[b].y)*(p[a].y-p[b].y));
}

vector<node> e[N];
priority_queue<pair<double,int>> pq;
void add(int a,int b,double dis) {
	
//	cerr<<dis<<endl;
	e[a].push_back((node){b,dis});
	e[b].push_back((node){a,dis});
}

void merge(int x,double d){
	// cerr<<"mer p:"<<x<<" d="<<d<<endl;
	if(dis[x]>d){
		sdis[x]=min(sdis[x],dis[x]);
		dis[x]=d;
	}else if(sdis[x]>d)sdis[x]=d;
}

void djstr(int rt) {
	pq.push(make_pair(0.00,rt));
	int u=rt;	//先从起点开始查
	for(int i=1; i<=n; i++)dis[i]=INF;	//初始化边权
	for(int i=1; i<=n; i++)sdis[i]=INF;	//初始化边权

	dis[rt]=0.0;
//	vis[rt]=1;//别写错！！
	
	while(pq.size()) {	//搜完全图
		
		u=pq.top().second;
		
		pq.pop();
		if(vis[u])continue;//记得continue
		vis[u]=1;
		for(int i=0;i<e[u].size();i++){
			int v=e[u][i].nxt;
			double w=e[u][i].dis;
			if(!vis[v]&&dis[u]+w<sdis[v]){
				// dis[v]=dis[u]+w;	//更新
				merge(v,dis[u]+w);
//				cerr<<dis[v]<<endl;
				pq.push(make_pair(-dis[v],v));
			}
		}
	}
}
signed main() {

	cin>>n>>m;

	for(int i=1;i<=n;i++){
		cin>>p[i].x>>p[i].y;
	}
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		add(a,b,getdis(a,b));
	}
	djstr(1);
	double mx=INF;
	ans=sdis[n];
	// cerr<<dis[n]<<' '<<sdis[n]<<endl;
	if(mx==ans)cout<<-1;
	else printf("%.2lf",ans);
	return 0;
}
```

## K短路 | [SCOI2007] k短路

有 $n$ 个城市和 $m$ 条单向道路，城市编号为 $1$ 到 $n$。每条道路连接两个不同的城市，且任意两条道路要么起点不同要么终点不同，因此 $n$ 和 $m$ 满足$m \le n(n-1)$。

给定两个城市 $a$ 和 $b$，可以给 $a$ 到 $b$ 的所有简单路（所有城市最多经过一次，包括起点和终点）排序：先按长度从小到大排序，长度相同时按照字典序从小到大排序。你的任务是求出 $a$ 到 $b$ 的第 $k$ 短路。

输入格式

输入第一行包含五个正整数 $n,m,k,a,b$。

以下 $m$ 行每行三个整数 $u,v,l$，表示从城市 $u$ 到城市 $v$ 有一条长度为 $l$ 的单向道路。

输出格式

如果 $a$ 到 $b$ 的简单路不足 $k$ 条，输出 `No`，否则输出第 $k$ 短路：从城市 $a$ 开始依次输出每个到达的城市，直到城市 $b$，中间用减号 `-` 分割。

- $100\%$ 的数据满足：$2\leq n\leq 50$，$1\leq k\leq 200$，$1\le l\le 10^4$。

