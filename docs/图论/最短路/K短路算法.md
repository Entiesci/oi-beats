# K短路算法

作为中等阶段的OIer，我们先要学习如何使用A*来解决标准的K短路问题。

### 基本思路

1. **修改启发式函数**：传统的A*算法使用启发式函数来估算从当前点到目标点的成本。为了找到K短路，我们可以修改启发式函数，使其不仅考虑到达目标点的成本，还考虑路径的多样性。

2. **重复搜索**：在找到一条最短路径后，修改图中的权重或启发式函数，然后再次运行A*算法，寻找下一条最短路径。

3. **路径去重**：确保找到的每条路径都是独特的，避免重复相同的路径。

## 例题 #1

![image.png](K短路算法/image.png)

做法

1. 预处理出各个节点v到终点T的最短路长度f[v]，做为估价函数值。我们可以在反向图上跑以T为起点的单源最短路（Dijkstra算法），这里的估价函数值等于实际值。

2. 再跑优先队列BFS。堆中维护三元组$(dis(S,v)+f[v],v,d)$，队中的点自动按$dis(S,v)+f[v]$升序排列。我们允许每个点最多入队K次，那么当终点T第K次出队时，对应的距离d必是第K短路的长度。

注：三元组为（当前代价+估价，当前点编号，当前点到起点的距离）

**那么在这道题目中，估价有什么作用呢？**

传统的最短路，我们只是不断用最小值去更新到达终点T的最短路，但我们不知道当前这条路是点击短的。如果我们用A*算法，我们就能控制bfs先走第一短的，再走第二短的...，这样的话我们就可以找到第K短的了。

注意这些

1. 估价函数$f[v]$：从$v$到终点T的最小距离

2. 出队K次 即第K短路

3. 堆中排序字段：$-f[v]$

4. 堆中排序字段：$dis(S,v)+f[v]$

5. 起点与终点重合：求K+1短路

6. 时间复杂度：$K(N+M)\log(N+M)$

敲一遍代码

```C++
/*////////ACACACACACACAC///////////
       . Code by Ntsc .
       . Love by Liye .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define ll long long
#define db double
#define rtn return
using namespace std;

const int N=1e5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;

int h[N],rh[N],to[M],w[M],ne[M],tot;
void add(int h[],int a,int b,int c){
	to[++tot]=b,w[tot]=c,ne[tot]=h[a],h[a]=tot;
}

int n,m,s,t,k;
int f[N],vis[N],cnt[N];
struct node{
	int s,v,d;
	bool operator <(const node &x)const{
		return s>x.s;
	}
};

void djstr(){
	memset(f,0x3f,sizeof f);
	priority_queue<pair<int,int>> q;
	q.push(make_pair(0,t));
	while(q.size()){
		pair<int,int> tmp=q.top();
		q.pop();
		int u=tmp.second;
		if(vis[u])continue;
		vis[u]=1;
		for(int i=rh[u];i;i=ne[i]){
			int v=to[i];
			if(f[v]>f[u]+w[i]){
				f[v]=f[u]+w[i];//f[v]是点v到t的当前距离(当前的djstr是预处理估价函数的,把t当作起点)，也是其估价函数 
				q.push(make_pair(-f[v],v));
			}
		}
	}
}

int ax(){
	priority_queue<node> pq;
	node a={f[s],s,0};
	pq.push(a);
	while(pq.size()){
		node tmp=pq.top();pq.pop();
		int u=tmp.v,d=tmp.d;
		cnt[u]++;
		if(cnt[t]==k)return d;
		for(int i=h[u];i;i=ne[i]){
			int v=to[i];
			if(cnt[v]<k){
				node a={d+w[i]+f[v],v,d+w[i]};
				pq.push(a);
			}
		}
	}
	return -1;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int a,b,c;
		cin>>a>>b>>c;
		add(h,a,b,c);add(rh,b,a,c);
	}
	cin>>s>>t>>k;
	if(s==t)k++;//如果s,t重合,那么0是最短的,A*会统计这一条,但题目要求不能算这条路,因此实际上应该要求第K+1条路 
	djstr();
	cout<<ax()<<endl;
	return 0;
}

```



## 例题 #2 [SCOI2007] k短路

有 $n$ 个城市和 $m$ 条单向道路，城市编号为 $1$ 到 $n$。每条道路连接两个不同的城市，且任意两条道路要么起点不同要么终点不同，因此 $n$ 和 $m$ 满足$m \le n(n-1)$。

给定两个城市 $a$ 和 $b$，可以给 $a$ 到 $b$ 的所有简单路（所有城市最多经过一次，包括起点和终点）排序：先按长度从小到大排序，长度相同时按照字典序从小到大排序。你的任务是求出 $a$ 到 $b$ 的第 $k$ 短路。

输入格式

输入第一行包含五个正整数 $n,m,k,a,b$。

以下 $m$ 行每行三个整数 $u,v,l$，表示从城市 $u$ 到城市 $v$ 有一条长度为 $l$ 的单向道路。

输出格式

如果 $a$ 到 $b$ 的简单路不足 $k$ 条，输出 `No`，否则输出第 $k$ 短路：从城市 $a$ 开始依次输出每个到达的城市，直到城市 $b$，中间用减号 `-` 分割。

- $100\%$ 的数据满足：$2\leq n\leq 50$，$1\leq k\leq 200$，$1\le l\le 10^4$。

