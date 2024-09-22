# 树形DP

树形 DP（树形动态规划）是一种解决树形结构问题的动态规划方法。

树形 DP 可以解决很多树上的问题，如最大独立集、树形背包、最长路径等。掌握树形 DP 的关键在于正确地定义状态和写出状态转移方程。

在树形DP中，我们通常按照以下步骤进行：

1. **状态定义**：定义DP数组的含义，通常`dp[u]`表示以`u`为根的子树能得到的最优解。

2. **状态转移**：根据子问题之间的关系，写出状态转移方程。在树形结构中，这通常涉及到将子节点的信息合并到父节点上。

3. **遍历顺序**：由于树形结构的特殊性，我们通常使用深度优先搜索（DFS）来进行遍历，确保在计算`dp[u]`时，所有`u`的子节点的`dp`值已经被计算过。

4. **边界条件**：初始化DP数组，尤其是叶节点的状态。

## 例题 #1 没有上司的舞会

题目描述

某大学有 $n$ 个职员，编号为 $1\ldots n$。

他们之间有从属关系，也就是说他们的关系就像一棵以校长为根的树，父结点就是子结点的直接上司。

现在有个周年庆宴会，宴会每邀请来一个职员都会增加一定的快乐指数 $r_i$，但是呢，如果某个职员的直接上司来参加舞会了，那么这个职员就无论如何也不肯来参加舞会了。

所以，请你编程计算，邀请哪些职员可以使快乐指数最大，求最大的快乐指数。

输入格式

输入的第一行是一个整数 $n$。

第 $2$ 到第 $(n + 1)$ 行，每行一个整数，第 $(i+1)$ 行的整数表示 $i$ 号职员的快乐指数 $r_i$。

第 $(n + 2)$ 到第 $2n$ 行，每行输入一对整数 $l, k$，代表 $k$ 是 $l$ 的直接上司。

输出格式

输出一行一个整数代表最大的快乐指数。

对于 $100\%$ 的数据，保证 $1\leq n \leq 6 \times 10^3$，$-128 \leq r_i\leq 127$，$1 \leq l, k \leq n$，且给出的关系一定是一棵树。

### 代码

```C++
#include <bits/stdc++.h>
const int N=1e4+5;
using namespace std;
vector <int> son[N];
int f[N][2],n,hap[N],l,k,hasfa[N];
void dp(int x){
	f[x][0]=0;
	f[x][1]=hap[x];
	for(int i=0;i<son[x].size();i++){
		int y=son[x][i];
		dp(y);
		f[x][0]+=max(f[y][1],f[y][0]);
		f[x][1]+=f[y][0];
	}
}
int main(){
	//ios::sync_which_stdio(false);
	cin>>n;
	
	for(int i=1;i<=n;i++){
		cin>>hap[i];
	} 
	for(int i=1;i<=n-1;i++){
		cin>>l>>k;
		hasfa[l]=1;
		son[k].push_back(l);
	}
	int rt=0;
	while(hasfa[++rt]);
	dp(rt);
//	cout<<"rt="<<rt<<endl;
	cout<<max(f[rt][1],f[rt][0])<<endl;
	return 0;
}

```

---

摘抄[学习笔记 | 树形dp](https://flowus.cn/e1c9cc6f-9c2a-45af-ae85-d6232a02501c)

## 例题 #2 [SCOI2015] 小凸玩密室

题目描述

小凸和小方相约玩密室逃脱，这个密室是一棵有 $n$ 个节点的完全二叉树，每个节点有一个灯泡。点亮所有灯泡即可逃出密室。每个灯泡有个权值 $a_i$，每条边也有个权值 $b_i$。点亮第一个灯泡不需要花费，之后每点亮一个新的灯泡 $v$ 的花费，等于上一个被点亮的灯泡 $u$ 到这个点 $v$ 的距离 $D_{u,v}$，乘以这个点的权值 $a_v$。在点灯的过程中，要保证任意时刻所有被点亮的灯泡必须连通，在点亮一个灯泡后必须先点亮其子树所有灯泡才能点亮其他灯泡。请告诉他们，逃出密室的最少花费是多少。

### 思路

本题同时考察完全二叉树性质。

---

观察遍历顺序:

1.先点亮这个点

2.在儿子中选一个点递归,点亮这个儿子的子树(最后一个必定是一个叶子)

3.返回这个点

4.递归另一个儿子

5.向上回溯

考虑如果n比较小就是常见的树形DP,转移枚举是从兄弟节点的哪个叶子转移即可

既然无法枚举叶子结点,不妨倒推,对叶子节点处理转移到哪里的花费,之后倒推回根节点,对于结点x,枚举先递归左子树还是右子树,处理完x的子树后,x下一步有两种选择：

1.回溯到x的某个祖先

2.回溯到x的某个祖先的另一个儿子(子树中不包含x的那一个)

$f_{i,j,0/1}$表示处理完i的子树后,下一个转移到i的j级祖先(0)/j级祖先的另一个儿子(1)

定义disi,[j]表示i到i的j级祖先的距离,fa(i,j)表示i的j级祖先是谁,brother(i,j)表示i的j级祖先的另一个儿子

对于结点x:

- x是叶子结点

$f_{x,i,0}=dis_{x,i},∗a[fa(x,i)]$

$f_{x,i,1}=(dis_{x,i}+dis[brother(x,i)][1])∗a[brother(x,i)]$

对于叶子结点直接处理它到下一个点的距离*点权

---

- x不是叶子结点:

定义ls(p)表示p的左儿子,rs(p)表示p的右儿子

- x有左儿子无右儿子:

$f_{x,i,0}=f_{ls(x),i+1,0}+dis_{ls(x),1}∗a_{ls(x)}$

$f_{x,i,1}=f_{ls(x),[i+1],1}+dis_{ls(x),1}∗a_{ls(x)}$

只有左儿子自然只能从左儿子转移,代价要加上从x到ls(x)的代价

- x有左右儿子:

在先走左儿子还是先走右儿子中取min

$f_{x,i,0}=min(f_{ls(x),1,1}+f_{rs(x),[i+1]0}+dis{ls(x),1}∗a{ls(x)},~~f_{rs(x),1,1}+f_{ls(x),[i+1]0}+dis{rs(x),1}∗a{rs(x)});$

$f_{x,i,1}=min(\mathop {f_{ls(x),1,1}+f_{rs(x), i+1,1}+dis_{ls(x),1}∗a_{ls(x)}}\limits_{左儿子}~~,\mathop{f_{rs(x),1,1}+f_{ls(x),i+1,1}+dis_{rs(x),1}∗a_{rs(x)}}\limits_{右儿子});$

求答案就是枚举起点向上跳,有兄弟就把兄弟加上

---

inf要开1e18！！

```C++
/*
Edit by Ntsc.
*/

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define pii pair<int, int>
#define pf first
#define ps second

#define rd read()
#define ot write
#define nl putchar('\n')
inline int rd{
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

const int N=4e5+5;
const int M=5e4+5;
const int INF=2e18+5;
const int MOD=1e9+7;
const int BASE=17737;
bool f1;
int n,f[N][20][2],a[N],ans=INF,dis[N][20];

bool f2;

//完全二叉树性质
#define fa(i,j) ((1<<(j-1)<=i)?(i>>j):-1)
#define bro(i,j)((i>>(j-1))^1)

//f[i][j][0]为处理好了i子树内的所有点后前往其j级父亲的代价
//f[i][j][1]为处理好了i子树内的所有点后前往其j级父亲的另外一个儿子的代价
/*
为什么可以这样子定义呢？
我们发现，当我们点亮了点x后，下一步只能点亮ls(x)或者rs(x)。然后如果我们点亮了*s(x)子树内的所有
点，那么我们会以一个节点v为结尾跳到x或者rs(x)。
我们不知道我们会从那个节点v为结尾，但是我们可以预处理出每个节点v跳到x和rs(x)的代价

*/

void solve(){
	for(int i=n;i;i--){
		//预处理
		for(int j=1;~fa(i,j);j++){
			//枚举i的第j级祖先
			f[i][j][1]=f[i][j][0]=INF;
			
			if((i*2)>n){
				//说明是叶子节点
				f[i][j][0]=dis[i][j]*a[fa(i,j)];//直接从i往上跳到i的第j级祖先
				f[i][j][1]=(dis[i][j]+dis[bro(i,j)][1])*a[bro(i,j)];//直接从i往上跳到i的第j级祖先然后到另一个儿子，a只使用另一个儿子的a
			}
			else if((i*2+1)>n){
				//右儿子不存在
				//dis[x][i]记录x到其i级祖先的距离
				f[i][j][0]=f[i<<1][j+1][0]+dis[i<<1][1]*a[i<<1];
				//要想从i往上走j级，首先要把i的子树完全访问。//为什么要加上dis[i<<1][1]*a[i<<1];
				f[i][j][1]=f[i<<1][j+1][1]+dis[i<<1][1]*a[i<<1];
				
			}else{
				f[i][j][0]=min(f[i][j][0],f[i<<1][1][1]+f[i<<1|1][j+1][0]+dis[i<<1][1]*a[i<<1]);
				f[i][j][0]=min(f[i][j][0],f[i<<1|1][1][1]+f[i<<1][j+1][0]+dis[i<<1|1][1]*a[i<<1|1]);
				f[i][j][1]=min(f[i][j][1],f[i<<1][1][1]+f[i<<1|1][j+1][1]+dis[i<<1][1]*a[i<<1]);
				f[i][j][1]=min(f[i][j][1],f[i<<1|1][1][1]+f[i<<1][j+1][1]+dis[i<<1|1][1]*a[i<<1|1]);
			}
		}
	}
  
//cerr<<"ans="<<ans<<endl;
	for(int s=1;s<=n;s++){
		//枚举起点
		int res=f[s][1][0];
		for(int i=fa(s,1),last=s;~i;i=fa(i,1),last=fa(last,1)){
			if(bro(last,1)<=n)res+=dis[bro(last,1)][1]*a[bro(last,1)]+f[bro(last,1)][2][0];
			else res+=dis[i][1]*a[fa(i,1)];
		}
		ans=min(ans,res);
	}


	
}


signed main(){
    // freopen("P5431_1.in", "r", stdin);
    // freopen("chfran.out", "w", stdout);
//    ios::sync_with_stdio(false);
//    cin.tie(0);cout.tie(0);
    
    n=rd;
    for(int i=1;i<=n;i++){
    	a[i]=rd;
    	
	}
	
	for(int i=2;i<=n;i++){
		dis[i][1]=rd;
		for(int j=2;~fa(i,j);j++)dis[i][j]=dis[fa(i,1)][j-1]+dis[i][1];
	}
	
//	dfs(1,0);
	solve();
	cout<<ans<<endl;
    return 0;
}
/*


*/
```

对于 $100$% 的数据， $1 \leq n \leq 2 * 10^5, 1 \leq a_i, b_i \leq 10^5$

## 例题 #3 二叉苹果树

题目描述

有一棵苹果树，如果树枝有分叉，一定是分二叉（就是说没有只有一个儿子的结点）

这棵树共有 $N$ 个结点（叶子点或者树枝分叉点），编号为 $1 \sim N$，树根编号一定是 $1$。

我们用一根树枝两端连接的结点的编号来描述一根树枝的位置。下面是一颗有 $4$ 个树枝的树：

```C++
2   5
 \ / 
  3   4
   \ /
    1
```

现在这颗树枝条太多了，需要剪枝。但是一些树枝上长有苹果。

给定需要保留的树枝数量，求出最多能留住多少苹果。

### 思路

依赖背包可做。

有$O(n^3)$转移的想法，可过。即记录$f_{i,j}$为以i为根的子树中选择i条边减去的最小价值。转移可以使用$O(n^2)$

---

```C++
/*
Edit by Ntsc.
*/

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ull unsigned long long
#define pii pair<int, int>
#define pf first
#define ps second

#define rd read()
#define ot write
#define nl putchar('\n')
inline int rd{
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

const int N=1e3+5;
const int M=5e6+5;
const int INF=2e9+5;
const int MOD=1e9+7;
const int BASE=17737;
bool f1;
int n,m;

int f[N][N];

struct node{
	int v,w;
};
vector<node> e[N];//状态



void add(int c,int b,int a){
	// cerr<<"add"<<a<<" "<<b<<" "<<c<<endl;
	e[a].push_back({b,c});
	e[b].push_back({a,c});
}

void dfs(int x,int fa){
	for(auto v:e[x]){
		if(v.v==fa)continue;
		dfs(v.v,x);
		for(int j=m;~j;j--){
			for(int k=0;k<j;k++)f[x][j]=max(f[x][j],f[x][j-k-1]+f[v.v][k]+v.w);
		}
	}
}

signed main(){
	n=rd,m=rd;
	for(int i=1;i<n;i++){
		add(rd,rd,rd);
	}
	dfs(1,0);

	cout<<f[1][m]<<endl;
		
    return 0;
}
/*
5 2
1 3 1
1 4 10
2 3 20
3 5 20

*/
```

$1 \leqslant Q < N \leqslant 100$，每根树枝上的苹果 $\leqslant 3 \times 10^4$。

## 例题 #4 战略游戏

题目背景

Bob 喜欢玩电脑游戏，特别是战略游戏。但是他经常无法找到快速玩过游戏的办法。现在他有个问题。

描述

他要建立一个古城堡，城堡中的路形成一棵无根树。他要在这棵树的结点上放置最少数目的士兵，使得这些士兵能瞭望到所有的路。

注意，某个士兵在一个结点上时，与该结点相连的所有边将都可以被瞭望到。

请你编一程序，给定一树，帮 Bob 计算出他需要放置最少的士兵。

### 思路

想一想，本题恰好是“没有上司的舞会”反过来。

- 没有上司的舞会：每条边上最多选择一个点。最大权值。

- 战略游戏：每条边上最少选择一个点。最小权值。



注意节点开始的编号！

---

```C++
/*
Edit by Ntsc.
*/

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ull unsigned long long
#define pii pair<int, int>
#define pf first
#define ps second

#define rd read()
#define ot write
#define nl putchar('\n')
inline int rd{
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

const int N=1e5+5;
const int M=5e6+5;
const int INF=2e9+5;
const int MOD=1e9+7;
const int BASE=17737;
bool f1;
int n,m;

int dp[N][2];

vector<int> e[N];



void add(int a,int b){
	// cerr<<"add "<<a<<" "<<b<<endl;
	e[a].push_back(b);
	e[b].push_back(a);
}

void dfs(int x,int fa){
	for(auto v:e[x]){
		if(v==fa)continue;
		dfs(v,x);
	}
	dp[x][1]=1;
	for(auto v:e[x]){
		if(v==fa)continue;
		dp[x][0]+=dp[v][1];
		dp[x][1]+=min(dp[v][0],dp[v][1]);
	}
}

signed main(){
    // freopen("P5431_1.in", "r", stdin);
    // freopen("chfran.out", "w", stdout);
    // ios::sync_with_stdio(false);
    // cin.tie(0);cout.tie(0);
	
	n=rd;
	for(int i=0;i<n;i++){
		int x=rd,k=rd;
		while(k--){
			add(x,rd);
		}
	}

	dfs(0,-1);
	cout<<min(dp[0][1],dp[0][0])<<endl;
    return 0;
}
/*
5 2
1 3 1
1 4 10
2 3 20
3 5 20

*/
```

对于全部的测试点，保证 $1 \leq n \leq 1500$。

## 换根DP

有些时候，题目要求最优化一个值，但是它和选择哪个节点作为根节点，或者是从那个节点开始扩散有关，时间复杂度有要求我们不能采用 $n$ 次 dfs（树形 dp），这时我们就需要使用换根 dp 了。

换根 dp 是树形 dp 的一种，它通过第一遍dfs得到的数据（如将 $1$ 作为根节点跑出的各个节点的 dp 值），在第二次 dfs 中加以利用，通过转移式快速根据已有信息求出将邻接点作为根节点时的答案。

### 例题 #1深度之和最大

#### 题目描述

给出一个N个点的树,找出一个点来,以这个点为根的树时,所有点的深度之和最大

#### 输入格式

给出一个数字N,代表有N个点.N<=1000000 下面N-1条边.

#### 输出格式

输出你所找到的点,如果具有多个解,请输出任意一个

---

换根dp

```C++
/*                                                                                
                      Keyblinds Guide
     				###################
      @Ntsc 2024

      - Ctrl+Alt+G then P : Enter luogu problem details
      - Ctrl+Alt+B : Run all cases in CPH
      - ctrl+D : choose this and dump to the next
      - ctrl+Shift+L : choose all like this
      - ctrl+K then ctrl+W: close all
      - Alt+la/ra : move mouse to pre/nxt pos'
	  
*/
#include <bits/stdc++.h>
#include <queue>
using namespace std;

#define rep(i, l, r) for (int i = l, END##i = r; i <= END##i; ++i)
#define per(i, r, l) for (int i = r, END##i = l; i >= END##i; --i)
#define pb push_back
#define mp make_pair
#define int long long
#define pii pair<int, int>
#define ps second
#define pf first

// #define innt int
#define itn int
// #define inr intw
// #define mian main
// #define iont int

#define rd read()
int read(){
    int xx = 0, ff = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
		if (ch == '-')
			ff = -1;
		ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
      xx = xx * 10 + (ch - '0'), ch = getchar();
    return xx * ff;
}
void write(int out) {
	if (out < 0)
		putchar('-'), out = -out;
	if (out > 9)
		write(out / 10);
	putchar(out % 10 + '0');
}

#define ell dbg('\n')
const char el='\n';
const bool enable_dbg = 1;
template <typename T,typename... Args>
void dbg(T s,Args... args) {
	if constexpr (enable_dbg){
    cerr << s;
    if(1)cerr<<' ';
		if constexpr (sizeof...(Args))
			dbg(args...);
	}
}

#define zerol = 1
#ifdef zerol
#define cdbg(x...) do { cerr << #x << " -> "; err(x); } while (0)
void err() { cerr << endl; }
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) { for (auto v: a) cerr << v << ' '; err(x...); }
template<typename T, typename... A>
void err(T a, A... x) { cerr << a << ' '; err(x...); }
#else
#define dbg(...)
#endif


const int N = 3e6 + 5;
const int INF = 1e18;
const int M = 1e7;
const int MOD = 1e9 + 7;

vector<int>e[N];

void add(int a,int b){
    e[a].push_back(b);
    e[b].push_back(a);
}


int sz[N];
int sum[N];
int n;

void dfs(int x,int fa){
    sz[x]=1;
    for(auto v:e[x]){
        if(v==fa)continue;
        dfs(v,x);
        sz[x]+=sz[v];
    }

}

// 换根dp
void dfs2(int x,int fa){
    for(auto v:e[x]){
        if(v==fa)continue;
        sum[v]=sum[x]+n-sz[v]*2;
        dfs2(v,x);
    }
}

void solve(){
    n=rd;
    for(itn i=1;i<n;i++){
        add(rd,rd);
    }


    dfs(1,0);
    dfs2(1,0);
    int ans=-INF;
    int ansid=1;

    for(int i=1;i<=n;i++){
        if(sum[i]>ans){
            ans=sum[i];
            ansid=i;
        }
    }

    cout<<ansid<<endl;
}



signed main() {
    // freopen(".in","r",stdin);
    // freopen(".in","w",stdout);

    int T=1;
    while(T--){
    	solve();
    }
    return 0;
}
```

### 例题 #2 k步以内

#### 题目描述

有一棵n个节点的树，边权值都为1，每一个节点有一个权值。依次输出每一个节点距离k以内的节点的权值和。

#### 输入格式

第一行包括两个正整数n(1<=n<=100,000)，k(1<=k<=20)，分别表示这棵树节点的数量和所规定的距离。

接下来n-1行，每行包括两个整数a,b (1<=a,b<=n)，表示有一条从a连向b的边。

接下来n行，每行包括一个整数vi，表示节点i的权值。

#### 输出格式

输出共n行，每行包括一个整数，分别表示每一个节点距离k以内的节点的权值和。

---

```C++
/*                                                                                
                      Keyblinds Guide
     				###################
      @Ntsc 2024

      - Ctrl+Alt+G then P : Enter luogu problem details
      - Ctrl+Alt+B : Run all cases in CPH
      - ctrl+D : choose this and dump to the next
      - ctrl+Shift+L : choose all like this
      - ctrl+K then ctrl+W: close all
      - Alt+la/ra : move mouse to pre/nxt pos'
	  
*/
#include <bits/stdc++.h>
#include <queue>
using namespace std;

#define rep(i, l, r) for (int i = l, END##i = r; i <= END##i; ++i)
#define per(i, r, l) for (int i = r, END##i = l; i >= END##i; --i)
#define pb push_back
#define mp make_pair
#define int long long
#define pii pair<int, int>
#define ps second
#define pf first

// #define innt int
#define itn int
// #define inr intw
// #define mian main
// #define iont int

#define rd read()
int read(){
    int xx = 0, ff = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
		if (ch == '-')
			ff = -1;
		ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
      xx = xx * 10 + (ch - '0'), ch = getchar();
    return xx * ff;
}
void write(int out) {
	if (out < 0)
		putchar('-'), out = -out;
	if (out > 9)
		write(out / 10);
	putchar(out % 10 + '0');
}

#define ell dbg('\n')
const char el='\n';
const bool enable_dbg = 1;
template <typename T,typename... Args>
void dbg(T s,Args... args) {
	if constexpr (enable_dbg){
    cerr << s;
    if(1)cerr<<' ';
		if constexpr (sizeof...(Args))
			dbg(args...);
	}
}

#define zerol = 1
#ifdef zerol
#define cdbg(x...) do { cerr << #x << " -> "; err(x); } while (0)
void err() { cerr << endl; }
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) { for (auto v: a) cerr << v << ' '; err(x...); }
template<typename T, typename... A>
void err(T a, A... x) { cerr << a << ' '; err(x...); }
#else
#define dbg(...)
#endif


const int N = 3e5 + 5;
const int INF = 1e18;
const int M = 1e7;
const int MOD = 1e9 + 7;



vector<int> e[N];
int f[33][N];

void add(int a,int b){
    e[a].push_back(b);
    e[b].push_back(a);
}

void solve(){
    itn n=rd,K=rd;
    for(int i=1;i<n;i++){
        add(rd,rd);
    }
    for(int i=1;i<=n;i++){
        f[0][i]=rd;
        f[1][i]=f[0][i];
    }

    for(int i=1;i<=K;i++){
        for(itn j=1;j<=n;j++){
            if(i!=1)f[i][j]-=f[i-2][j]*(e[j].size()-1);
            for(auto v:e[j])f[i][j]+=f[i-1][v];
        }
    }


    for(int i=1;i<=n;i++){
        cout<<f[K][i]<<endl;
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".in","w",stdout);

    int T=1;
    while(T--){
    	solve();
    }
    return 0;
}
```

