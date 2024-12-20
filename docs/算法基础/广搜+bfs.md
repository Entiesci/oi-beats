# 广搜

如果是以距离（即走过的格子数为距离，或者是每走一步距离就+1）为权，可以直接使用queue，但是如果每走一步的代价不同，则应该使用优先队列。

## 例题 #1 走迷宫

注意，P1238 是dfs而不是bfs哦，不要看到走迷宫就以为是bfs

【题目描述】

当你站在一个迷宫里的时候，往往会被错综复杂的道路弄得失去方向感，如果你能得到迷宫地图，事情就会变得非常简单。

假设你已经得到了一个n×m的迷宫的图纸，请你找出从起点到出口的最短路。

【输入】

第一行是两个整数n和m(1≤n,m≤100)，表示迷宫的行数和列数。

接下来n行，每行一个长为m的字符串，表示整个迷宫的布局。字符`.`表示空地，`#`表示墙，`S`表示起点，`T`表示出口。

【输出】

输出从起点到出口最少需要走的步数。

【输入样例】

```C++
3 3
S#T
.#.
...
```

**代码**

```C++

#include<bits/stdc++.h>
using namespace std;
const int N=105;

struct node{
	int x,y;
};
queue<node>q;

int a[N][N], n, m, ans, d[N][N],vis[N][N];
int fromx, fromy, ansx, ansy;
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};


void bfs() {
	d[fromx][fromy] = 0;
	vis[fromx][fromy] = 1;
	q.push((node){fromx, fromy});
	while (q.size()) {
		node u = q.front();
		q.pop();
		
		if(u.x==ansx&&u.y==ansy){
			cout << d[ansx][ansy] << endl;
			return ;
		}

		for (int k = 0; k < 4; k++) {
			int xx = u.x + dx[k], yy = u.y + dy[k];
          
			if (xx < 1 || xx > n || yy < 1 || yy > m || vis[xx][yy])continue;
			if(!a[xx][yy])continue;
          
			q.push((node){xx,yy});
			d[xx][yy] = d[u.x][u.y] + 1;
			vis[xx][yy]=1;
		}
	}

}

int main() {
	cin >> n >> m;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			char c;
			cin >> c;
			if (c == 'S')fromx = i, fromy = j;
			if (c == 'T')ansx = i, ansy = j;
			if (c == '.' || c == 'S' || c == 'T')a[i][j] = 1;
		}
	bfs();
	return 0;
}
```

## 例题 #2 八数码难题

题目描述

在 $3\times 3$ 的棋盘上，摆有八个棋子，每个棋子上标有 $1$ 至 $8$ 的某一数字。棋盘中留有一个空格，空格用 $0$ 来表示。空格周围的棋子可以移到空格中。要求解的问题是：给出一种初始布局（初始状态）和目标布局（为了使题目简单,设目标状态为 $123804765$（从上到下，从左往右）），找到一种最少步骤的移动方法，实现从初始布局到目标布局的转变。

输入格式

输入初始状态，一行九个数字，空格用 $0$ 表示。

输出格式

只有一行，该行只有一个数字，表示从初始状态到目标状态需要的最少移动次数。保证测试数据中无特殊无法到达目标状态数据。

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
#define ull unsigned long long
#define pii pair<int, int>
#define ps second
#define pf first


#define itn int




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

const int dx[5]={-1,0,0,1},dy[5]={0,-1,1,0};
int c[4][4];

queue<string> q;
map<string,int> dis;
string n;


string reform(){
    string s="";
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)s=s+(char)('0'+c[i][j]);
    return s;
}

void bfs(){

    q.push(n);
    dis[n]=0;
    while(q.size())
    {
        string u=q.front(); 
        q.pop();

        int x0=0,y0=0;
        string n=u;
        if(u=="123804765")break;

        //找到0
        int cur=9;
        for(int i=2;~i;i--)
            for(int j=2;~j;j--)
            {
                c[i][j]=n[--cur]-'0';
                if(!c[i][j])x0=i,y0=j;
            }
        
        for(int k=0;k<4;k++)
        {
            int xx=x0+dx[k],yy=y0+dy[k];
            if(xx<0||yy<0||xx>2||yy>2)continue; 
            swap(c[xx][yy],c[x0][y0]);
            string sta=reform();

            if(!dis.count(sta))
            {
                dis[sta]=dis[u]+1;
                q.push(sta);
            }
            swap(c[xx][yy],c[x0][y0]);
        }
    }

}




void solve()
{
    cin>>n;

    bfs();
    
    cout<<dis["123804765"]<<endl; 
}


signed main() {
    
    

    int T=1;
    while(T--){
    	solve();
    }
    return 0;
}
```

## 例题 #3「DAOI R1」Flame

简化题意

给出一个 $n$ 个点，$m$ 条边的无向图，每一个点有一个标记，初始有 $k$ 个点的标记为 `1`（将给出这 $k$ 个点的编号），其余的点标记为 `0`。

每一秒，对于每个标记为 `1` 的点，与它**有边相连**的点的标记都会变成 `1`。

求最少需要多少秒，图中标记为 `1` 的点与其相邻的边可以构成一个简单环。

**换言之，求最少多少秒后存在一个由 `1` 构成的集合形成简单环。**

输入格式

第一行三个正整数：$n,m,k$；

下面 $m$ 行，每行两个正整数：$x,y$（第 $x$ 座业火祭坛与第 $y$ 座业火祭坛有业火之路连接）；

最后一行 $k$ 个正整数：已被点燃（拥有火种）的祭坛编号。

输出格式

若可以逃离，输出 D 还有多少时间。

反之若无法生成业火监狱，输出 `Poor D!`。

数据规模

|Subtask|$n\leq$|$m\leq$|$k\leq$|分值|
|-|-|-|-|-|
|$0$|$10^6$|$n-1$|$10^4$|$5$|
|$1$|$10^6$|$2\times10^6$|$1$|$10$|
|$2$|$10$|$45$|$1$|$5$|
|$3$|$200$|$500$|$10$|$10$|
|$4$|$2\times 10^3$|$5\times 10^3$|$50$|$10$|
|$5$|$5\times10^5$|$6\times10^5$|$500$|$30$|
|$6$|$10^6$|$2\times10^6$|$10^4$|$30$|

---

我们使用$vis_x$表示点x首次被某个联通块联通的时间。这里的联通块指的是被火焰蔓延到的一堆联通的点。

然后在bfs时注意不要重复走已经走过的边即可。如果联通了两个之前已经被联通了的点（即这两个点已经在同一个联通块内），那么就更新答案。

使用并查集维护。

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
// #define inr int
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
    cerr << s << ' ';
		if constexpr (sizeof...(Args))
			dbg(args...);
	}
}

const int N = 2e6 + 5;
const int INF = 1e18;
const int M = 1e7;
const int MOD = 1e9 + 7;

struct node{
	int v,id;
};

vector<node> e[N];

void add(int a,int b,int id){
	e[a].pb({b,id});
	e[b].pb({a,id});
}
int fa[N];

int find(int x){
	if(x==fa[x])return x;
	return fa[x]=find(fa[x]);
}
int ans;

queue<int> q;
bool del[N];
int vis[N];

void bfs(){
	
	while(q.size()){

		int x=q.front();
		q.pop();
		if(vis[x]>=ans)return ;
		for(auto v:e[x]){
			if(del[v.id])continue;
			int faa=find(x);
			int fbb=find(v.v);
			if(faa==fbb)ans=min(ans,max(vis[x],vis[v.v]));

			fa[faa]=fbb;
			del[v.id]=1;
			if(!vis[v.v]){
				q.push(v.v);
				vis[v.v]=vis[x]+1;
			}
		}
	}
}

signed main(){
	int n=rd,m=rd,K=rd;
	if(n>m){
		puts("Poor D!");
		return 0;
	}

	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		add(rd,rd,i);
	}
	for(int i=1;i<=K;i++){
		int x=rd;
		q.push(x);
		vis[x]=1;
	}

	ans=INF;
	bfs();

	cout<<ans-1<<endl;

}
```

## 部分区域限制通过的走迷宫

[www.luogu.com.cn](https://www.luogu.com.cn/problem/P5195)


## 通过时间不同的走迷宫（差时bfs）（类spfa）

[练习 | 车万（东方）的题](https://flowus.cn/1b45e393-14ef-49bf-b25d-c1d9b03314a0)

## 01bfs

![image.png](广搜+bfs/image.png)

## 双向bfs

可以认为是bfs版的meet in the middle

### 例题 #1 [NOIP2002 提高组] 字串变换

已知有两个字串 $A,B$ 及一组字串变换的规则（至多 $6$ 个规则），形如：

- $A_1\to B_1$。

- $A_2\to B_2$。

规则的含义为：在 $A$ 中的子串 $A_1$ 可以变换为 $ B_1$，$A_2$ 可以变换为 $B_2\cdots$。

例如：$A=\texttt{abcd}$，$B＝\texttt{xyz}$，

变换规则为：

- $\texttt{abc}\rightarrow\texttt{xu}$，$\texttt{ud}\rightarrow\texttt{y}$，$\texttt{y}\rightarrow\texttt{yz}$。

则此时，$A$ 可以经过一系列的变换变为 $B$，其变换的过程为：

- $\texttt{abcd}\rightarrow\texttt{xud}\rightarrow\texttt{xy}\rightarrow\texttt{xyz}$。

共进行了 $3$ 次变换，使得 $A$ 变换为 $B$。

输入格式

第一行有两个字符串 $A,B$。

接下来若干行，每行有两个字符串 $A_i,B_i$，表示一条变换规则。

输出格式

若在 $10$ 步（包含 $10$ 步）以内能将 $A$ 变换为 $B$，则输出最少的变换步数；否则输出 `NO ANSWER!`。

对于 $100\%$ 数据，保证所有字符串长度的上限为 $20$。

**【题目来源】**

NOIP 2002 提高组第二题

---

本题既有初始状态又有结束状态，所以我们考虑双向搜索算法。这里选择双向bfs。很明显本题还可以使用meet in the middle 或者迭代加深。



```C++
/*
                      Keyblinds Guide
     				###################
      @Ntsc 2024

      - Ctrl+Alt+getId then P : Enter luogu problem details
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
#define int long long
#define ull unsigned long long
#define pii pair<int, int>
#define ps second
#define pf first
#define mp make_pair

// #define innt int
#define itn int
// #define inr intw
// #define mian main
// #define iont int

#define rd read()
int read() {
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
	if constexpr (enable_dbg) {
		cerr << s;
		if(1)cerr<<' ';
		if constexpr (sizeof...(Args))
			dbg(args...);
	}
}

#define zerol = 1
#ifdef zerol
#define cdbg(x...) do { cerr << #x << " -> "; err(x); } while (0)
void err() {
	cerr << endl;
}
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) {
	for (auto v: a) cerr << v << ' ';
	err(x...);
}
template<typename T, typename... A>
void err(T a, A... x) {
	cerr << a << ' ';
	err(x...);
}
#else
#define dbg(...)
#endif



const int N = 2e3 + 10;
const int INF = 2e9;
const int M = 1e6 + 10;
const int MOD = 1e9 + 7;


queue<pair<string,int> > qa,qb;
map<string,bool > visa,visb;
int n;
string s[N],t[N];
void bfs(string a,string b){
    qa.push(mp(a,0));
    qb.push(mp(b,0));

    visa[a]=1;
    visb[b]=1;

    int dep=-1;
    while(++dep<=5){
        while(qa.size()&&qa.front().ps==dep){
            string x=qa.front().pf;
            cdbg("sa",x);
            qa.pop();
            for(int i=1;i<=n;i++){
                int pos=0;

                for(int pos=0;pos<x.size();pos++){
                    if(x.find(s[i],pos)==x.npos)break;
                    string xx=x;
                    xx.replace(xx.find(s[i],pos),s[i].length(),t[i]);
                    if(visa.find(xx)!=visa.end()){
                        continue;
                    }

                    if(visb.find(xx)!=visb.end()){
                        cout<<(dep+1)*2-1<<endl;
                        return ;
                    }

                    qa.push(mp(xx,dep+1));
                    visa[xx]=1;

                }

            }
        }


        while(qb.size()&&qb.front().ps==dep){
            string x=qb.front().pf;
            cdbg("sb",x);
            qb.pop();
            for(int i=1;i<=n;i++){
                int pos=0;

                for(int pos=0;pos<x.size();pos++){
                    if(x.find(t[i],pos)==x.npos)break;
                    string xx=x;
                    xx.replace(xx.find(t[i],pos),t[i].length(),s[i]);
                    if(visb.find(xx)!=visb.end()){
                        continue;
                    }

                    if(visa.find(xx)!=visa.end()){
                        cout<<(dep+1)*2<<endl;
                        return ;
                    }

                    qb.push(mp(xx,dep+1));
                    visb[xx]=1;

                }

            }
        }
    }

    puts("NO ANSWER!");
    
}

string a,b;

void solve(){
    cin>>a>>b;
    while(cin>>s[n+1]>>t[n+1])n++;

    // for(int i=1;i<=n;i++)cdbg(s[i],t[i]);

    bfs(a,b);


    
}

signed main() {
    // freopen("kujou.in","r",stdin);
    // freopen("kujou.out","w",stdout);

    int T=1;
    while(T--){
    	solve();
    }

    return 0;
}

```

## 练习

### #1 最短路建模+01边权最短路 Small Multiple

对于任意非负整数x和m(2≤m)，定义fm(x)为x在m进制下的各位数字之和。给定两个整数k,m(2≤m≤10)，你需要计算在所有k的倍数的正数x中,fm(x)的最小值。

输入第一行包含两个整数k,m(2≤m≤10)。

在一行中输出一个整数，表示答案。

对于30%的数据，1≤k≤100

对于100%的数据，1≤k≤10^6

---

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
// void write(int out) {
// 	if (out < 0)
// 		putchar('-'), out = -out;
// 	if (out > 9)
// 		write(out / 10);
// 	putchar(out % 10 + '0');
// }
#define cdbg(x...) do { cerr << #x << " -> "; err(x); } while (0)
void err() { cerr << endl; }
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) { for (auto v: a) cerr << v << ' '; err(x...); }
template<typename T, typename... A>
void err(T a, A... x) { cerr << a << ' '; err(x...); }


const int N = 3e6 + 5;
const int INF = 1e18;
const int M = 1e7;
const int MOD = 1e9 + 7;


list<pii> q;
bitset<N> vis;
int n,m;

void bfs(){
    q.pb({1,1});
    vis[1]=1;
    while(q.size()){
        int x=q.front().pf,v=q.front().ps; //余数，值
        q.pop_front();
        if(!x){
            cout<<v<<endl;
            exit(0);
        }
        if(!vis[m*x%n]){
            q.push_front({m*x%n,v});
            vis[m*x%n]=1;
        }
        if(!vis[(x+1)%n])q.push_back({(x+1)%n,v+1});
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);


     n=rd,m=10;
    bfs();

}


```

