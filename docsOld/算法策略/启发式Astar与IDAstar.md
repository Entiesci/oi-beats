# 启发式Astar与IDAstar

## 概述

![image.png](启发式Astar与IDAstar/image.png)

共性：

![image.png](启发式Astar与IDAstar/image 1.png)

## A*

![image.png](启发式Astar与IDAstar/image 2.png)

### 例题 #1

![image.png](启发式Astar与IDAstar/image 3.png)

做法

![image.png](启发式Astar与IDAstar/image 4.png)

注：三元组为（当前代价+估价，当前点编号，当前点到起点的距离）

**那么在这道题目中，估价有什么作用呢？**

传统的最短路，我们只是不断用最小值去更新到达终点T的最短路，但我们不知道当前这条路是点击短的。如果我们用A*算法，我们就能控制bfs先走第一短的，再走第二短的...，这样的话我们就可以找到第K短的了。

注意这些

![image.png](启发式Astar与IDAstar/image 5.png)

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

**注意！A*就是变形的Dijkstra！**

核心思路：反搜求估价，正搜带估价求第K短



## IDA*

IDA*中的ID就是迭代加深的意思。

是的，迭代加深是IDA*（Iterative Deepening A*）算法的一个关键组成部分。IDA* *算法结合了深度优先搜索（DFS）的空间效率和广度优先搜索（BFS）的完备性。*在IDA* 算法中，迭代加深指的是逐步增加搜索深度的过程，直到找到目标解。
具体来说，IDA*算法的工作流程如下：

1. 使用一个【评估函数】来估算从当前节点到目标节点的成本，这个评估函数通常是路径成本加上启发式估计。

2. 设置一个成本限值（初始时可以设为启发式估计的值），在这个限值下进行深度优先搜索。【迭代加深】

3. 如果在当前限值下搜索失败，说明解不在当前限值范围内，于是增加限值，再次进行深度优先搜索。

4. 重复这个过程，直到找到解或者确定无解。



[230 IDA算法 Booksort_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1jh411P7EE/?spm_id_from=333.999.0.0&vd_source=f45ea4e1e4b3b73d5f07c57b46c43aba)

同样的，具体题目具体分析（题目参考例题 #1）

我们可以很明显的发现提示**迭代加深**的字眼：如果最少操作次数大于或等于5次，则输出5 or more 。



![image.png](启发式Astar与IDAstar/image 6.png)

注意观察为什么要÷2

![image.png](启发式Astar与IDAstar/image 7.png)

### 知识扩展：双向BFS

放图，秒懂

![https://tse1-mm.cn.bing.net/th/id/OIP-C.On44jvHe-eDNm83-a7xq0QHaHH?pid=ImgDet&rs=1](https://tse1-mm.cn.bing.net/th/id/OIP-C.On44jvHe-eDNm83-a7xq0QHaHH?pid=ImgDet&rs=1)

本题中一边BFS从初始状态开始搜，一边BFS从排好序后开始搜（打乱地搜），限制步数为2，如果有一对BFS搜索最终状态相同，即找到一条符合线路

### IDA*算法

 

![image.png](启发式Astar与IDAstar/image 8.png)

考察以下案例

![image.png](启发式Astar与IDAstar/image 9.png)

我们发现了3个错误连接，分别为**1-4，5-2，3-6**

在极佳状态下，我们一次操作最多能修正3个错误连接。那么我们每DFS到一个状态，就去统计当前还剩下的错误状态的个数n，如果$\lceil n\div 3\rceil + 当前已经移动的步数 > 4$，那么我们就进行剪枝。

怎么样，是不是想法很简单？

![image.png](启发式Astar与IDAstar/image 10.png)

IDA*算法需要具体题目具体讨论，没有固定的代码模板，这里也就不写了

本题的**IDA*核心思想**是：

制定一个估价函数，求出当前状态下达到目的还需要的最少步数（假设一切理想），如果仍然无法满足要求，就果断砍掉。

### 例题 #1 Booksort

题目描述

给定 $n$ 本书，编号为 $1 \sim n$。

在初始状态下，书是任意排列的。

在每一次操作中，可以抽取其中连续的一段，再把这段插入到其他某个位置。

我们的目标状态是把书按照 $1 \sim n$ 的顺序依次排列。

求最少需要多少次操作。

输入格式

第一行包含整数 $T$，表示共有 $T$ 组测试数据。

每组数据包含两行，第一行为整数 $n$，表示书的数量。

第二行为 $n$ 个整数，表示 $1 \sim n$ 的一种任意排列。

同行数之间用空格隔开。

输出格式

每组数据输出一个最少操作次数。

如果最少操作次数大于或等于 $5$ 次，则输出 `5 or more`。

每个结果占一行。

$1 \le n \le 15$

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
#define ull unsigned long long
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


const int N = 3e2 + 5;
const int INF = 1e18;
const int M = 1e7;
const int MOD = 1e9 + 7;

int dep;

int cur[N];
int pst[6][N];
int n;

int f(){
    int res=0;
    for(itn i=0;i<n-1;i++){
        if(cur[i+1]!=cur[i]+1)res++;
    }

    return ceil(1.0*res/3);
}



bool dfs(int x){
    if(f()+x>dep)return 0;
    
    itn f=1;
    
    for(itn i=0;i<n;i++){
        if(cur[i]!=i+1)f=0;
    }

    if(f)return 1;

    for(itn i=0;i<n;i++){
        for(int j=i;j<n;j++){
            for(int k=j+1;k<n;k++){
                memcpy(pst[x],cur,sizeof cur);
                int a=0,b=0;
                for(a=j+1,b=i;a<=k;a++,b++)cur[b]=pst[x][a];
                for(a=i;a<=j;a++,b++)cur[b]=pst[x][a];

                if(dfs(x+1))return 1;
                memcpy(cur,pst[x],sizeof cur);
            }
        }
    }

    //
    return 0;
}

void solve(){
    n=rd;
    for(int i=0;i<n;i++)cur[i]=rd;
    dep=0;
    while(dep<5&& !dfs(0))dep++;
    if(dep>=5){
        cout<<"5 or more"<<endl;
    }else{
        cout<<dep<<endl;
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".in","pst",stdout);

    int T=rd;
    while(T--){
    	solve();
    }
    return 0;
}
```

### 例题 #2 旋转游戏 The Rotation Game

如图 1 所示，有一个 “#” 形的棋盘，上面有 1,2,3 三种数字各 8 个。给定 8 种操作，分别为图中的 A∼H。这些操作会按照图中字母与箭头所指明的方向，把一条长度为 8 的序列循环移动 1 个单位。例如下图最左边的 “#” 形棋盘执行操作 A 时，会变为图中间的 “#” 形棋盘，再执行操作 C 后会变为图中最右边的 “#” 形棋盘。

![https://cdn.luogu.org/upload/pic/40731.png](启发式Astar与IDAstar/40731.png)

输入输出格式

**输入格式：**

　　输入包括不超过 $30$ 组测试数据。每个测试数据只包括一行，包含 $24$ 个整数，每相邻两个整数之间用 $1$ 个空格隔开，表示这个 “#” 形棋盘的初始状态。（这些整数的排列顺序是从上至下，同一行的从左至右。例如 $\text{1 1 1 1 3 2 3 2 3 1 3 2 2 3 1 2 2 2 3 1 2 1 3 3}$ 表示图 $1$ 最左边的状态。）每两组测试数据之间没有换行符。输入文件以一行 $0$ 结束。

**输出格式：**

　　对于每组测试数据，输出两行。第一行用字符 $\text{A}\sim \text{H}$ 输出操作的方法，**每两个操作字符之间没有空格分开**，如果不需要任何步数，输出 `No moves needed`。第二行输出最终状态中最中间的 $8$ 个格子里的数字。如果有多组解，输出操作次数最少的一组解；如果仍有多组解，输出字典序最小的一组。任意相邻两组测试数据的输出之间不需输出换行符。

---

本题估价函数的计算就是当前环内有多少个差异数，即若选i为环内数，则z=环内非i的个数，z对于三个i的最小值就是当前估价。越小越接近答案

乐观估价函数，一次移动不是最多可以使两个方块移动到正确的位置吗，为什么是1？

因为并不能保证每次 都 使两个方块移动到正确位置，这样会把可行方案剪掉的

这里设计的估价函数：假定数最多的为最终结果（若其它数为结果，那么操作数一定更大），再模拟一下可以看出一次操作最多只会增添一个当前最多的数

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
#define ull unsigned long long
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


const int N = 3e2 + 5;
const int INF = 1e18;
const int M = 1e7;
const int MOD = 1e9 + 7;

int a[N];
int anspos[9]={7,8,9,12,13,16,17,18};
itn ans[N];
int bac[9]={5, 4, 7, 6, 1, 0, 3, 2};//各操作的逆操作编号


const int mve[9][9] = {
	{1, 3, 7, 12, 16, 21, 23}, 
	{2, 4, 9, 13, 18, 22, 24}, 
	{11, 10, 9, 8, 7, 6, 5}, 
	{20, 19, 18, 17, 16, 15, 14}, 
	{24, 22, 18, 13, 9, 4, 2}, 
	{23, 21, 16, 12, 7, 3, 1}, 
	{14, 15, 16, 17, 18, 19, 20}, 
	{5, 6, 7, 8, 9, 10, 11}
};//每种操作涉及到哪几个位置,借用chlchl大佬的

bool check(){
    for(int i=1;i<8;i++){
        if(a[anspos[i]]!=a[7])return 0;
    }
    return 1;
}


int dep;

int f(){
    //估价
    int vis[4]={0};
    for(int i=0;i<8;i++){
        vis[a[anspos[i]]]++;
    }

    int res=20;
    for(int i=1;i<=3;i++){
        res=min(res,8-vis[i]);
    }

    return res;
}


void calc(int op){
    int x = a[mve[op][0]];
	for(int i=0;i<6;i++)
		a[mve[op][i]] = a[mve[op][i + 1]];
	a[mve[op][6]] = x;
}

bool dfs(int x,int pre){
    if(f()+x>dep)return 0;
    if(check())return 1;
    for(int i=0;i<8;i++){
        if(pre==bac[i])continue;
        calc(i);
        ans[x]=i;
        if(dfs(x+1,i))return 1;
        calc(bac[i]);
    }
    return 0;
}

void solve(){
    for(itn i=1;i<=24;i++){
        a[i]=rd;
        if(!a[i])exit(0);

    }

    if(check()){
        puts("No moves needed");
        cout<<a[7]<<endl;
        return ;
    }

    dep=1;
    while(!dfs(0,-1))dep++;

    for(itn i=0;i<dep;i++){
        cout<<(char)('A'+ans[i]);

    }
    cout<<endl<<a[7]<<endl;
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".in","w",stdout);

    int T=1;
    while(T){
    	solve();
    }
    return 0;
}
```

