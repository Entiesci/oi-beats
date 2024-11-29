# DAG上DP

DAG上dp，我们需要处理的是各个节点的更新顺序。通常情况下我们可能想到拓扑排序，但实际上我们更多地去运用最短路算法。在最短路过程中dp。



拓扑排序上dp请参考 拓扑排序 [拓扑排序](https://flowus.cn/53a7ca1c-3e23-4e4d-9b41-1744d2ef3d62)

## 例题 #1 [BJWC2012] 冻结

题目描述

我们考虑最简单的旅行问题吧： 现在这个大陆上有 $N$ 个城市，$M$ 条双向的道路。城市编号为 $1$ ~ $N$，我们在 $1$ 号城市，需要到 $N$ 号城市，怎样才能最快地到达呢？

这不就是最短路问题吗？我们都知道可以用 Dijkstra、Bellman-Ford、Floyd-Warshall等算法来解决。

现在，我们一共有 $K$ 张可以使时间变慢 50%的 SpellCard，也就是说，在通过某条路径时，我们可以选择使用一张卡片，这样，我们通过这一条道路的时间 就可以减少到原先的一半。需要注意的是：

1. 在一条道路上最多只能使用一张 SpellCard。

2. 使用一张SpellCard 只在一条道路上起作用。

3. 你不必使用完所有的 SpellCard。

给定以上的信息，你的任务是：求出在可以使用这不超过 $K$ 张时间减速的 SpellCard 之情形下，从城市 $1$ 到城市 $N$ 最少需要多长时间。

---

### 思路

在最短路上dp。设$dp_{i,j}$为到达城市i，使用了j张卡的最少时间。思路正确，首先也不难。因为这里优先队列不好排序了，并且题目也不需要，所以我们用spfa而不是dijkstra

这里开拓下思路，本题用分层图也可以实现哦。因为K不大，可以存下KM条边。

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
            if(j<K) add(x+j*n,y+(j+1)*n,d/2),add(y+j*n,x+(j+1)*n,d/2);
        }
    }
	spfa();
    return 0;
}
```



## 例题 #2 拓扑序计数

from pjudge.ac

题目描述

本题中涉及到的图论定义：

- 一个 n 个点，点的编号为 1,2,…,n 的有向图 G=(V,E) 的**拓扑序**是一个 1,2,…,n 的排列 p，且若 E 中存在 x→y 的边，就有 p 中 x 出现在 y 之前。

今天，算法竞赛机器人小 G 学习了拓扑排序相关知识。凭着强大的机器学习本领，它很快便一并学会了如何计算一个有向无环图的拓扑序个数。接着，它开始思考一个拓展问题：给定一个有向无环图 G 和两个 G 中的点 u,v，请你求出有多少种 G 的拓扑序满足 u 排在 v 之前。

你知道稍加思考后小 G 也能秒掉这题。不巧，就在这时停电了，依靠插头进食的小 G 也因此停止工作了。所以你只好自己解决这个拓展问题了。

为了让问题更富有挑战性，设 G 中总点数为 n，请你对所有 n(n−1) 对 (u,v) 都求出答案。

输入格式

本题有多组数据，第一行是数据组数 T。

对于每组数据：第一行两个正整数 n,m，分别为 G 的点数和边数。接下来 m 行，每行两个正整数 x,y，表示有向图里一条 x→y 的边。保证没有重边且 x<y（也就是 [1,2,…,n] 总是一个合法拓扑序）。

**保证同一个测试点中至多有 5 组数据满足 n>10。**

输出格式

对每组数据输出一个 n×n 的矩阵，第 i 行第 j 列是 v=i,u=j 时的答案，注意 (v,u) 的顺序和 (i,j) 是反的。特别地，当 i=j 时请你输出 0。

---

考虑算出f_i为拓扑序从前往后加点，有点集i时的方案，g_i为拓扑序从后往前删点，剩下点集i时的方案。

以求f为例，我们貌似还要记录当前路径的最后一个点是什么，这样复杂度会来到$O(2^nn^2)$不可接受。我们发现只要i中有可以直接到达x的点，那么我们就可以从$f_{i-x}$转移到f_i。至于如何判断，我们将可以直接到x的点集压缩为一个数字，与i位与非0即可。

答案就是$ans_{u,v}=\sum_{S~\text{include}~u~ \text{exclude}~ v}f_{S} · g_{S|v}$。需要卡常

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=22;

int f[1<<N]; //拓扑序从前往后加点，有点集i时的方案
int g[1<<N]; //拓扑序从后往前删点，剩下点集i时的方案

vector<int> e[N];
int to[N],nxt[N];
int ind[N];

void add(int a,int b){
	// cerr<<a<<' '<<b<<endl;
	// e[a].push_back(b);
	to[b]|=1<<a;
	nxt[a]|=1<<b;
	ind[b]++;
}

int a,b;
int n,m;

void solve(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a>>b;
		a--;b--;
		add(a,b);
	}
	
	for(int i=0;i<(1<<n);i++)f[i]=0,g[i]=0;
	// for(int i=0;i<n;i++){
		// if(!ind[i])f[1<<i]=1;
	// }
	
	f[0]=1;
	for(int i=1;i<(1<<n);i++){
		for(int j=0;j<n;j++){
			if((i>>j)&1){
				if(to[j]==(to[j]&(i^(1<<j))))f[i]+=f[i^(1<<j)];
				else if(!to[j])f[i]+=f[i^(1<<j)];
			}
		}
	}
	
	
	g[(1<<n)-1]=1;
	for(int i=(1<<n)-1;i;i--){
		for(int j=0;j<n;j++){
			if((i>>j)&1){
				int s=(i^(1<<j));
				 if(nxt[j]&s)continue;
				 g[s]+=g[i];
			}
		}
	}
	
	
	
	for(int j=0;j<n;j++){
		for(int i=0;i<n;i++){
			if(i==j)cout<<0<<' ';
			else{
				int res=0;
				
				if(i<j){
					int b1=i,b2=j-i-1,b3=n-j-1;
					for(int s1=0;s1<(1<<b1);s1++){
						for(int s2=0;s2<(1<<b2);s2++){
							for(int s3=0;s3<(1<<b3);s3++){
								int s=(s3<<(j+1))|(s2<<(i+1))|(1<<i)|s1;
								res+=f[s]*g[s|(1<<j)];	
							}
						}
					}
				}else{
					
					int b1=j,b2=i-j-1,b3=n-i-1;
					for(int s1=0;s1<(1<<b1);s1++){
						for(int s2=0;s2<(1<<b2);s2++){
							for(int s3=0;s3<(1<<b3);s3++){
								int s=(s3<<(i+1))|(s2<<(j+1))|(1<<i)|s1;
								res+=f[s]*g[s|(1<<j)];	
							}
						}
					}
				}
				// for(int s=1;s<(1<<n);s++){
// 					
					// if((s>>j)&1)continue;
					// if((s>>i)&1){
						// // if(j==2&&i==0){
							// // cerr<<f[s]<<' '<<g[s|(1<<j)]<<' '<<s<<endl;
						// // }
						// res+=f[s]*g[s|(1<<j)];					
					// }
				// }
				cout<<res<<' ';
			}
			
		}
		cout<<'\n';	
		
	}
	
	for(int j=n-1;~j;j--){
		for(int s=(1<<j);s<(1<<(j+1));s++){
			ans[j]+=
		}
	}
	
	for(int i=0;i<n;i++){
		// while(e[i].size())e[i].pop_back();
		nxt[i]=0;
		to[i]=0;
		// ind[i]=0;
	}
	
	
}
signed main(){
	// freopen("tram.in","r",stdin);
	// freopen("tram.out","w",stdout);
	
	
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}
```

