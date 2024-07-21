# DAG上DP

DAG上dp，我们需要处理的是各个节点的更新顺序。通常情况下我们可能想到拓扑排序，但实际上我们更多地去运用最短路算法。在最短路过程中dp。

## 例题 #1 [BJWC2012] 冻结

题目描述

我们考虑最简单的旅行问题吧： 现在这个大陆上有 $N$ 个城市，$M$ 条双向的道路。城市编号为 $1$ ~ $N$，我们在 $1$ 号城市，需要到 $N$ 号城市，怎样才能最快地到达呢？

这不就是最短路问题吗？我们都知道可以用 Dijkstra、Bellman-Ford、Floyd-Warshall等算法来解决。

现在，我们一共有 $K$ 张可以使时间变慢 50%的 SpellCard，也就是说，在通过某条路径时，我们可以选择使用一张卡片，这样，我们通过这一条道路的时间 就可以减少到原先的一半。需要注意的是：

1. 在一条道路上最多只能使用一张 SpellCard。

2. 使用一张SpellCard 只在一条道路上起作用。

3. 你不必使用完所有的 SpellCard。

给定以上的信息，你的任务是：求出在可以使用这不超过 $K$ 张时间减速的 SpellCard 之情形下，从城市 $1$ 到城市 $N$ 最少需要多长时间。

### 思路

在最短路上dp。设$dp_{i,j}$为到达城市i，使用了j张卡的最少时间。思路正确，首先也不难。因为这里优先队列不好排序了，并且题目也不需要，所以我们用spfa而不是dijkstra

这里开拓下思路，本题用分层图也可以实现哦。因为K不大，可以存下KM条边。

---

```C++
#include<bits/stdc++.h>
// luogu-judger-enable-o2
#define rep(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define per(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
#define int long long
#define pii pair<int,int>

#define lc(x) (x<<1)
#define rc(x) (x<<1|1)

#define rd read()
inline int read(){
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out){
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}

const int M=2e6+5;
const int N = 3e3 + 100; 
const int INF=1e9+5;
const int MOD=998244353;


struct edge{
    int next,to,dis;
}e[M];
int cnt,head[N],n,m,K,dis[N];
bool vis[N];
inline void add(int x,int y,int d){
    e[++cnt].next=head[x];
    e[cnt].to=y;
    e[cnt].dis=d;
    head[x]=cnt;
}
void spfa(){
    queue<int> q;
    memset(dis,0x3f,sizeof(dis));
    q.push(1);
    dis[1]=0;vis[1]=1;
    while(q.size()){
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(int v,i=head[u];i;i=e[i].next){
            if(dis[v=e[i].to]>dis[u]+e[i].dis) {
                dis[v]=dis[u]+e[i].dis;
                if(vis[v])continue;
                vis[v]=1,q.push(v);
            }
		}
    }
    int res=1e9;
    for(int i=1;i<=K+1;i++)
        res=min(res,dis[n*i]);
    cout<<res<<endl;
}
signed main(){
	n=rd,m=rd,K=rd;
    memset(e,0x3f,sizeof(e));
    for(int i=1;i<=m;i++) {
        int x=rd,y=rd,d=rd;
        for(int j=0;j<=K;j++) {
            add(x+j*n,y+j*n,d),add(y+j*n,x+j*n,d);
            if(j<K) add(x/2);
        }
    }
	spfa();
    return 0;
}
```

