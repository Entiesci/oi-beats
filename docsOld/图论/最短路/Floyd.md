# Floyd

平面上有n个点（n<=100），每个点的坐标均在-10000~10000之间。其中的一些点之间有连线。

若有连线，则表示可从一个点到达另一个点，即两点间有通路，通路的距离为两点间的直线距离。现在的任务是找出从一点到另一点之间的最短路径。



注意，请在**最外层循环枚举中转点k**，在内层枚举有时候会挂掉。

```C++
#include <bits/stdc++.h>
const int inf=1e9;
using namespace std;
int x[105],y[105],n,m,s,t,a,b;
double diss[105][105];
double dis(int i,int j){
	return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}
void flyd(){
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				diss[i][j]=min(diss[i][j],diss[i][k]+diss[k][j]);
}
int main() {
	cin>>n;
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			diss[k][i]=inf;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
	}
	
	cin>>m;
	for(int i=1;i<=m;i++){
		cin>>a>>b;
		diss[a][b]=diss[b][a]=dis(a,b);
	}
	cin>>s>>t;
	
	
	flyd();
	printf("%.2lf",diss[s][t]);
	return 0;
}
```

luogu 模板

```C++
signed main(){
	
	memset(f,0x3f3f,sizeof f);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		f[u][v]=f[v][u]=w;
	}
	
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(i==j)f[i][j]=0;
				f[j][i]=f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
			}
		}
	}
	
	for(int i=1;i<=n;i++){
		
		for(int j=1;j<=n;j++)cout<<f[i][j]<<' ';
		cout<<endl;
	}
	return 0;
}
```

## 判最小环

[无向图的最小环问题 - 洛谷](https://www.luogu.com.cn/problem/P6175)


## 传递闭包

给定一张点数为 $n$ 的有向图的邻接矩阵，图中不包含自环，求该有向图的传递闭包。

一张图的邻接矩阵定义为一个 $n\times n$ 的矩阵 $A=(a_{ij})_{n\times n}$，其中

$a_{ij}=\left\{
\begin{aligned}
1,i\ 到\ j\ 存在直接连边\\
0,i\ 到\ j\ 没有直接连边 \\
\end{aligned}
\right.$

一张图的传递闭包定义为一个 $n\times n$ 的矩阵 $B=(b_{ij})_{n\times n}$，其中

$ b_{ij}=\left\{\begin{aligned}1,i\ 可以直接或间接到达\ j\\0,i\ 无法直接或间接到达\ j\\\end{aligned}\right.$

### 大意

判断任意两点之间的连通性

### 代码

```C++
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		
		for(int j=1;j<=n;j++)cin>>f[i][j];
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				f[i][j]|=f[i][k]&f[k][j];
              //也可以写f[j][i]=f[i][j]|=f[i][k]&f[k][j];
              //但是不能写f[j][i]|=f[i][k]&f[k][j];
			}
		}
	}
	
	for(int i=1;i<=n;i++){
		
		for(int j=1;j<=n;j++)cout<<f[i][j]<<' ';
		cout<<endl;
	}
	return 0;
}
```

## k路floyd矩阵乘法优化

给定一张 $T$ 条边的无向连通图，求从 $S$ 到 $E$ 经过 $N$ 条边的最短路长度。

**思路**

首先，我们有两个矩阵，如果其中一个矩阵代表恰好经过x条边的最短路，另外一个矩阵代表恰好经过y条边的最短路。那么将这两个矩阵合并就代表恰好经过x+y条边的最短路。怎么合并呢？结合下面这个式子理解一下：

c[i][j]=min(c[i][j],a[i][k]+b[k][j]);

Std

```C++
/*////////ACACACACACACAC///////////
       . Code  by  Ntsc .
       . Earn knowledge .
/*////////ACACACACACACAC///////////

#include <bits/stdc++.h>
#define int long long
#define db double
#define rtn return
using namespace std;

const int N = 5e2 + 5;
const int M = 1e5;
const int MOD = 1e9+7;
const int INF = 1e9+5;

int n, t,s,e,m,vis[M],tot;


#define rd read()
inline int read()
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}



struct node {
	int a[N][N];
	node() {
		memset(a,0x3f3f,sizeof a); //一定要写！
	}
	
	node operator *(const node &x)const{     //重载运算符
	    node z;
		for(int k=1;k<=tot;++k)
	        for(int i=1;i<=tot;++i)
	            for(int j=1;j<=tot;++j)
	                z.a[i][j]=min(z.a[i][j],a[i][k]+x.a[k][j]);
	    return z;
	}
}dis,ans;

signed main() {
//    freopen("tree.in", "r", stdin);
//    freopen("tree.out", "w", stdout);
	cerr<<"OO";
	n=rd;t=rd;s=rd;e=rd;
	
	for(int i=1;i<=t;i++){
		int w=rd,u=rd,v=rd;
		if(!vis[u])vis[u]=++tot;
		if(!vis[v])vis[v]=++tot;
		dis.a[vis[u]][vis[v]]=dis.a[vis[v]][vis[u]]=w;
	}
	
	cerr<<"OK";
	
	n--;
	ans=dis;
	while(n){
		if(n&1)ans=ans*dis;
		dis=dis*dis;
		n>>=1;
	}
	
	cout<<ans.a[vis[s]][vis[e]];
    return 0;
}

```

## 伪全源最短路

可用dijkstra跑若干次

[www.luogu.com.cn](https://www.luogu.com.cn/problem/P5764)


## 记录路径的floyd

给定一个完全图，已知两点之间的距离，以及通过某个点的时间（起点和终点不需要花费时间）。你需要回答一些询问，输出两点之间的最短路径，同时需要输出方案。如果有多个方案，输出字典序最小的方案。

```C++
/*  Erica N  */
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define int long long
#define ull unsigned long long
#define pii pair<int, int>
#define ps second
#define pf first
#define itn int

#define rd read()
int read(){
    int xx = 0, ff = 1;char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-')ff = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9')xx = xx * 10 + (ch - '0'), ch = getchar();
    return xx * ff;
}

#define cdbg(x...) do { cerr << #x << " -> "; err(x); } while (0)
void err() { cerr << endl; }
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) { for (auto v: a) cerr << v << ' '; err(x...); }
template<typename T, typename... A>
void err(T a, A... x) { cerr << a << ' '; err(x...); }


const int N = 3e3 + 5;
const int INF = 1e18;
const int M = 1e7;
const int MOD = 1e9 + 7;

int ans[N];
int d[N][N];
int pre[N][N];
int nxt[N][N];
int w[N];

void solve(){
    int n=rd,m=rd;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            d[i][j]=rd;
        }
    }

    for(int i=1;i<=n;i++){
        w[i]=rd;
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            pre[i][j]=i;
            nxt[i][j]=j;
        }
    }


    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j)continue;
            d[i][j]+=w[i];
        }
    }



    for(int k=1;k<=n;k++){
        for(itn i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(d[i][j]>d[i][k]+d[k][j]){
                    d[i][j]=d[i][k]+d[k][j];
                    pre[i][j]=pre[k][j];
                    nxt[i][j]=nxt[i][k];
                }else if(d[i][j]==d[i][k]+d[k][j]&&nxt[i][j]>nxt[i][k]){
                    d[i][j]=d[i][k]+d[k][j];
                    pre[i][j]=pre[k][j];
                    nxt[i][j]=nxt[i][k];
                }
            }
        }
    }
    // cdbg("OK");

    int top=0;

    while(m--){
        int a=rd,b=rd;
        int tb=b;
        // cdbg(a,pre[a][a]);
        printf("From %lld to %lld :\n",a,b);
        printf("Path: ");
        while(b!=a){
            // cdbg(b,a);
            ans[++top]=pre[a][b];
            b=pre[a][b];
        }

        while(top){
            cout<<ans[top--]<<"-->";
        }
        cout<<tb<<endl;
        if(a==tb)printf("Total cost : %lld\n",0ll);
        else printf("Total cost : %lld\n",d[a][tb]-w[a]);
        if(m)cout<<endl;
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);

    int T=1;
    while(T--){
    	solve();
    }
    return 0;
}
```

