# 数位DP

数位 DP 是一种处理数字相关问题的动态规划方法。它通常用于解决以下类型的问题：

1. 计算在给定范围内，满足某些特定数位条件的数字个数。

2. 求解某个数位问题的具体方案数。

3. 找出满足特定数位性质的数字。

数位 DP 的核心思想是将数字的每一位分开考虑，使用记忆化搜索（通常是递归的形式）来避免重复计算，从而提高效率。



以下是数位DP的一般步骤：

1. **数位分离**：将数字的每一位分离出来，存储在一个数组中，便于单独处理每一位。

2. **递归搜索**：定义一个递归函数，该函数的参数通常包括当前处理到哪一位、前面处理的状态（比如是否越界、当前数字是否已经使用了某个数字等）。

3. **记忆化**：为了避免重复计算，通常会使用一个数组或者哈希表来存储已经计算过的状态。

4. **状态转移**：在递归函数中，根据当前的状态和可选的数字，递归地计算出所有可能的情况。

## 模型

> 模型1：单链往下，快速计算

可以参考例题 #1

当我们到达一个lim=0的状态，此时后面的数字我们都可以随便填，那么我们通常可以使用组合数来计算出有多少种填写的方案，直接返回即可。

> 模型2：全部搜索，记忆化优化

如果我们仅仅是一直往下，那么我们就相当于将所有数字都搜索了一遍，时间复杂度是O(N)的。

但是如果我们使用了记忆化搜索，那么我们就将自己复杂度压缩到了所有状态数，通常情况是$O(32^k)$，k是一个≤4的常数。

## 例题 #1 1081. 度的数量

求给定区间 [X,Y] 中满足下列条件的整数个数：这个数恰好等于 K 个互不相等的 B 的整数次幂之和。

例如，设 X=15,Y=20,K=2,B=2，则有且仅有下列三个数满足题意：

17=24+20
18=24+21
20=24+22

### 思路

即对于一个B进制数，求区间$[X_{(10)},Y_{(10)}]$中在B进制下只有两位为1的数的个数。



数位dp可使用于计算区间内含有某种特殊性质的数字的个数。

首先我们吧计算[l,r]转化为计算[1,r]-[1,l-1]，类似前缀和。

在考虑数位dp时，按照前若干位是否达到上界且当前位是否填上界（因为这取决于后面的剩余位能否任意填），可以按照数字的每一位转化为树形结构来考虑。

![image.png](数位DP/image.png)



**理解**

如果上界为$r=\overline{a_{n-1},\dots,a_{0}}$，那么为了保证我们枚举的数不超过r，我们就要按左边的树形结构考虑。

以$a_{n-2}$为例，如果选择左分叉，那么即填$0\sim a_{n-2}-1$，这个数字的最高位就没有占满，所以$n-3\sim 0$为可以随便填了。结合题目性质，我们可以直接计算答案。如果选择右分叉，即填该位可以填的最大值并且前面的所有位都填了最大值，那么即$n-2$及之前的所有位都已经占满了，那么我们就需要递归下去考虑。

---

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

const int N=4e2+5;
const int M=5e4+5;
const int INF=2e18+5;
const int MOD=1e9+7;
const int BASE=17737;
bool f1;
int n,f[N][N],a[N],ans=INF,K,B,l,r,dis[N][20];

bool f2;


void init(){
	// for(int i=0;i<=9;i++)f[1][i]=1;
	for(int i=0;i<N;i++){
		for(int j=0;j<=i;j++){
			if(!j)f[i][j]=1;
			else f[i][j]=f[i-1][j]+f[i-1][j-1];//从i位中挑选j位为1的方案数
		}
	}
}

int dp(int n){//求从0~n里可以满足要求的数字的个数
	if(!n)return 0;//边界
	vector<int> e;//记录n的每一位
	while(n)e.push_back(n%B),n/=B;
	int res=0,lst=0;//lst为右分支的继承信息，该题中是记录前面已经填了的数字中有多少个1
	for(int i=((int)e.size()-1);~i;i--){//高位到地位枚举
		int x=e[i];
		
		if(x){
			//求左边分支，即不占满
			res+=f[i][K-lst];//当前位为0
			if(x>1){//只能填0/1，但是因为x>1故无法占满，没有else分支
				if(K>lst)res+=f[i][K-lst-1];break;
			}else{
				lst++;//x=1占满,lst记录前面已经填了多少个1
				if(lst>K)break;//剪枝
			}
		}
		if(!i){
			//已经到了最后一位
			res+=(lst==K);
		}
	}
	return res;
}
signed main(){
    // freopen("P5431_1.in", "r", stdin);
    // freopen("chfran.out", "w", stdout);
//    ios::sync_with_stdio(false);
//    cin.tie(0);cout.tie(0);
	init();
    l=rd,r=rd,K=rd,B=rd;
	cout<<dp(r)-dp(l-1)<<endl;
	
    return 0;
}
/*


*/
```

## 例题 #2 [USACO14OPEN] Odometer S

农民约翰的牛正开始一个美妙的旅程。牛车的里程表上显示一个整数表示里程，旅程开始时里程数为 $X(100\le X\le 10^{18})$，结束时里程数为 $Y(X\le Y\le 10^{18})$。每当里程表显示一个有趣的数时（包括起点和终点数），牛们会发出愉快的叫声。

对于一个里程数的每一位，如果有至少一半的数字时相同的，则这个里程数一个有趣的数。例如：$3223$ 和 $110$ 是有趣的数，而 $97791$ 和 $123$ 则不是。

请计算，整个旅程中，牛们会发出多少吃愉快的叫声。

---

我的博客

本文知识点参考于：[oi-beats/数位 dp](https://ntsc-yrx.github.io/oi-beats/site/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92/%E6%95%B0%E4%BD%8DDP/)，[个人博客](https://ntsc.flowus.cn/)。

知识点摘录

数位 DP 是一种处理数字相关问题的动态规划方法。它通常用于解决以下类型的问题：

1. 计算在给定范围内，满足某些特定数位条件的数字个数。

2. 求解某个数位问题的具体方案数。

3. 找出满足特定数位性质的数字。

数位 DP 的核心思想是将数字的每一位分开考虑，使用记忆化搜索（通常是递归的形式）来避免重复计算，从而提高效率。

本题是比较复杂的数位 dp，那么第一个难点就是任何定义状态。

题目要求我们求出至少一半的数字是相同的数字的个数，为了方便记录是那个数字，我们就像枚举那个超过一半的数字的值。

这里注意我们可能会重复计算类似 `aabb` 的数字，后面我们要减去。

那么先定义框架。

`dfs(len,val,cntVal,cntOth,zero,lim)` 表示从高到低考虑到第 $len$ 位，枚举的超过一半的数字为 $val$，个数为 $cntVal$，其他的数字的个数为 $cntOth$（不含前导 $0$），当前位是否可以填 $0$，当前位是否 $lim$。

这里提供一个记忆化搜索的数位 dp 模板，适合记忆，方便扩展。

```C++
int dfs(int x,...,bool zero,bool lim){

    //当前填第x位（从高到低），前面是否全是前导0，当前位之前是否全部顶格
    if(f[x][...][zero][lim]!=-1)return f[x][...][zero][lim];
    
    if(!x)return f[x][...][zero][lim]=...;
    int res=0;
    int l=zero?1:0;
    int r=lim?digit[x]:9; 
    for(int i=l;i<=r;i++){
        res+=dfs(x-1,...,0,(lim&&i==r)?1:0);
    }
    if(zero){
        res+=dfs(x-1,...,1,0);
    }

    f[x][...][zero][lim]=res;
    return res;
}

```

当写出状态后，我们的转移其实并没有多困难。

我们只需要在所有可用数字中枚举当前位可以填什么，然后对状态值进行一些改变就可以递归下去了。

统计答案：我们在 $len=0$ 时统计答案就行了！

```C++

int dfs(int x,int num,int cnt,int cntOth,bool zero,bool lim){
    if(f[x][cnt][cntOth][zero][lim]!=-1)return f[x][cnt][cntOth][zero][lim];
    
    if(!x)return f[x][cnt][cntOth][zero][lim]=(cnt&&cnt>=cntOth);
    int res=0;
    int l=zero?1:0;
    int r=lim?digit[x]:9;
    for(int i=l;i<=r;i++){
        res+=dfs(x-1,num,cnt+(i==num),cntOth+(i!=num),0,(lim&&i==r)?1:0);
    }
    if(zero){
        res+=dfs(x-1,num,cnt,cntOth,1,0);
    }

    f[x][cnt][cntOth][zero][lim]=res;
    return res;
}

```

计算 `aabb` 个数的时候，我们先枚举 $a,b$ 然后计算。有个很 naive 的想法是我们直接组合数计算不就行了？但是注意文明不能超过某一个上限，所以还是到数位 dp。

```C++
int dfs2(int x,int num1,int num2,int cnt,int cntOth,bool zero,bool lim){
    if(g[x][cnt][cntOth][zero][lim]!=-1)return g[x][cnt][cntOth][zero][lim];
    // if(num1==1&&num2==2)cdbg(x,num1,num2,cnt,cntOth,zero,lim);
    
    if(!x)return g[x][cnt][cntOth][zero][lim]=(cnt&&cnt==cntOth);
    int res=0;
    int l=zero?1:0;
    int r=lim?digit[x]:9;
    for(int i=l;i<=r;i++){
        if(i!=num1&&i!=num2)continue;
        res+=dfs2(x-1,num1,num2,cnt+(i==num1),cntOth+(i==num2),0,(lim&&i==r)?1:0);
    }
    if(zero){
        res+=dfs2(x-1,num1,num2,cnt,cntOth,1,0);
    }

    g[x][cnt][cntOth][zero][lim]=res;
    return res;
}
```

下面是完整代码：

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



const int N = 50 + 10;
const int INF = 2e9;
const int M = 1e3 + 10;
const int MOD = 1e9 + 7;

int f[33][33][33][2][2];
int g[33][33][33][2][2];
int digit[N];

int dfs(int x,int num,int cnt,int cntOth,bool zero,bool lim){
    if(f[x][cnt][cntOth][zero][lim]!=-1)return f[x][cnt][cntOth][zero][lim];
    
    if(!x)return f[x][cnt][cntOth][zero][lim]=(cnt&&cnt>=cntOth);
    int res=0;
    int l=zero?1:0;
    int r=lim?digit[x]:9;
    for(int i=l;i<=r;i++){
        res+=dfs(x-1,num,cnt+(i==num),cntOth+(i!=num),0,(lim&&i==r)?1:0);
    }
    if(zero){
        res+=dfs(x-1,num,cnt,cntOth,1,0);
    }

    f[x][cnt][cntOth][zero][lim]=res;
    return res;
}


int dfs2(int x,int num1,int num2,int cnt,int cntOth,bool zero,bool lim){
    if(g[x][cnt][cntOth][zero][lim]!=-1)return g[x][cnt][cntOth][zero][lim];
    // if(num1==1&&num2==2)cdbg(x,num1,num2,cnt,cntOth,zero,lim);
    
    if(!x)return g[x][cnt][cntOth][zero][lim]=(cnt&&cnt==cntOth);
    int res=0;
    int l=zero?1:0;
    int r=lim?digit[x]:9;
    for(int i=l;i<=r;i++){
        if(i!=num1&&i!=num2)continue;
        res+=dfs2(x-1,num1,num2,cnt+(i==num1),cntOth+(i==num2),0,(lim&&i==r)?1:0);
    }
    if(zero){
        res+=dfs2(x-1,num1,num2,cnt,cntOth,1,0);
    }

    g[x][cnt][cntOth][zero][lim]=res;
    return res;
}

int calc(int x){
    // cdbg(x);
    int a=0,b=0;

    int len=0;
    while(x){
        digit[++len]=x%10;
        x/=10;
    }

    for(int i=0;i<=9;i++){
        memset(f,-1,sizeof f);   
        a+=dfs(len,i,0,0,1,1);
    }

    for(int i=0;i<=9;i++){
        for(int j=i+1;j<=9;j++){
            memset(g,-1,sizeof g);
            b+=dfs2(len,i,j,0,0,1,1);
        }
    }

    // cdbg(a,b);

    return a-b;
}

void solve(){
    int l=rd,r=rd;

    cout<<calc(r)-calc(l-1)<<endl;
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

摘抄[学习笔记 | 数位DP](https://flowus.cn/3b672d07-ba95-4030-aa38-d846d36bead1)

---



## 练习 #1 统计问题 The Counting Problem

**【题目描述】**

给定两个整数 $a$ 和 $b$，求 $a$ 和 $b$ 之间的所有数字中 $0$ ~ $9$ 出现次数。

例如，$a$ = $1024$，$b$ = $1032$，则 $a$ 和 $b$ 之间共有 $9$ 个数如下：

`1024 1025 1026 1027 1028 1029 1030 1031 1032`

其中 `0` 出现 $10$ 次，`1` 出现 $10$ 次，`2` 出现 $7$ 次，`3` 出现 $3$ 次等等……

**【输入格式】**

输入包含至多 $500$ 行数据。每组输入数据占一行，包含两个整数 $a$ 和 $b$（$0<a,b<100000000$），以 `0 0` 作为结尾，且该行不作处理。

**【输出格式】**

每组数据输出一个结果，每个结果占一行，包含十个用空格隔开的数字，第一个数字表示 `0` 出现的次数，第二个数字表示 `1` 出现的次数，以此类推。

---



```C++
/*
CB Ntsc111
*/

#include <bits/stdc++.h>
using namespace std;

#define uint unsigned int
#define pii pair<int, int>
#define pf to
#define ps second
#define int long long

#define err cerr << "Error"
#define rd read()

#define ot write
#define nl putchar('\n')
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

const int M = 800;
const int mxxlog = 10;
int MOD = 1e9 + 57;
const int N = 1000100;

int a, b, n;
int num[105];
int dp[30][1000][9];
int dfs(int pos, int sum, bool lim, bool h, int d) {
    if (pos == -1) {
        return sum;
    }
    if (!lim && !h && ~dp[pos][sum][d])
        return dp[pos][sum][d];
    int End, ans = 0;
    End = lim ? num[pos] : 9;
    for (int i = 0; i <= End; ++i)
        ans += dfs(pos - 1, sum + ((!h || i) && i == d), lim && i == num[pos],
                h && i == 0, d);
    if (!lim && !h)
        dp[pos][sum][d] = ans;
    return ans;
}
int cal(int x, int d) {
    memset(dp, -1, sizeof(dp));
    int pos = 0;
    while (x) {
        num[pos++] = x % 10;
        x /= 10;
    }
    return dfs(pos - 1, 0, 1, 1, d);
}
void solve() {
    a = rd, b = rd;
    if(a>b)swap(a,b);
    if(a+b==0)exit(0);
    for (int i = 0; i <= 9; ++i)
        printf("%lld ", cal(b, i) - cal(a - 1, i));
    puts("");

  return ;
}



signed main(){
    while(1){
        solve();
    }
    return 0;
}
```

## 练习 #2 [SCOI2009] windy 数

题目描述

不含前导零且相邻两个数字之差至少为 $2$ 的正整数被称为 windy 数。windy 想知道，在 $a$ 和 $b$ 之间，包括 $a$ 和 $b$ ，总共有多少个 windy 数？

### 思路

---

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
int n,f[N][20],a[N],ans=INF,dis[N][20];

bool f2;


void init(){
	for(int i=0;i<=9;i++)f[1][i]=1;
	for(int i=2;i<N;i++){
		for(int j=0;j<=9;j++){
			for(int k=0;k<=9;k++){
				if(abs(j-k)>=2)f[i][j]+=f[i-1][k];
			}
		}
	}
}

int dp(int n){
	if(!n)return 0;
	vector<int> e;
	while(n)e.push_back(n%10),n/=10;
	int res=0,lst=-2;
	for(int i=((int)e.size()-1);~i;i--){
		int x=e[i];
		for(int j=(i==e.size()-1)-0;j<x;j++){
			if(abs(j-lst)>=2)res+=f[i+1][j];
		}
		if(abs(x-lst)>=2)lst=x;
		else break;

		if(!i)res++;
	}

	for(int i=1;i<e.size();i++){
		for(int j=1;j<=9;j++){
			res+=f[i][j];//特殊处理位数没有占满的情况，防止前导0被计算
		}
	}
	return res;
}
signed main(){
    // freopen("P5431_1.in", "r", stdin);
    // freopen("chfran.out", "w", stdout);
  
	init();
    int l=rd,r=rd;
	cout<<dp(r)-dp(l-1)<<endl;
	
    return 0;
}
/*


*/
```

对于全部的测试点，保证 $1 \leq a \leq b \leq 2 \times 10^9$。

## 练习 #3 [ZJOI2010] 排列计数

题目描述

称一个 $1 \sim n$ 的排列 $p_1,p_2, \dots ,p_n$ 是 Magic 的，当且仅当
$\forall i \in [2,n],p_i > p_{\lfloor i/2 \rfloor}$
计算 $1 \sim n$ 的排列中有多少是 Magic 的，答案可能很大，只能输出模 $m$ 以后的值。

### 思路

题意：求 1 至n的所有排列中，满足小根堆性质的排列的个数。

很明显$\forall i \in [2,n],p_i > p_{\lfloor i/2 \rfloor}$就是小根堆的性质。至于为什么是完全二叉树，因为$i→2i,2i+1$就是完全二叉树的记录法啊！

这里建立dp模型：$f_i$表示个不同的数的所有排列中满足小根堆性质的排列的个数。

对于转移，首先在转移时计算出i个节点的完全二叉树中，根节点的左了树包含的节点数 $l$ ，右子树包含的节点数 $r $。

根节点的值必须为最小值。再考虑剩下的 $i - 1$ 个节点。很容易想到，可以在这$i- 1$ 个节点中选出 $l$个节点作为左子树，剩下的 $r$ 个节点作为右子树。

转移 $f_i=C_{i-1}^l\times f_l\times f_r$

---

注意坑点：n可以大于p，所以求组合数要用到Lucas定理。

```C++
/*
CB Ntsc
*/

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define pii pair<int, int>
#define pf first
#define ps second

#define rd read()
// #define nl putc('\n')
#define ot write
#define nl putchar('\n')
inline int rd
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

bool f1;
const int INF = 1e9;
const int N = 1e6+1005;
const int M = 10;
int MOD = 10;

int n,m;
int f[N],fac[N], inv[N],lg[N];
int ans = INF;

int ksm(int c,int k) {
	int p=MOD;
	int res=1;
	while(k){
		if(k&1)res=(res*c)%p;
		c=(c*c)%p;k>>=1;
	}
	return res;
}

void comb_init(){

    lg[0] = -1;
	fac[0]=1;
	for (int i=1;i<=n;++i) fac[i]=fac[i-1]*i%MOD;
	inv[min(MOD-1,n)]=ksm(fac[min(MOD-1,n)],MOD-2);
    for(int i=min(MOD-1,n);i>=1;i--)inv[i-1]=inv[i]*i%MOD;//i!的inv 
    for (int i = 1; i <= n; i++) lg[i] = lg[i >> 1] + 1;
}

// int C(int n,int m){
//     if(n<0||m<0)return 0;
//     if(n<m)return 0;
//     return fac[n]*inv[m]%MOD*inv[n-m]%MOD;
// }

int C(int x, int y) {
    if (!y) return 1;
    int u = C(x / MOD, y / MOD), v = x % MOD, w = y % MOD, z;
    if (v < w) z = 0;
    else z = (fac[v] * inv[w] % MOD) * inv[v - w] % MOD;
    return u * z % MOD;
}

// int cal(int x){
//     int i=1,j=1;
//     while(i<=x){
//         i<<=1;i|=1;
//         j<<=1;
//     }
//     int emt=x-i;
//     int res=(i-j-1)/2+min(j/2,j-emt);
//     // cerr<<x<<' '<<res<<endl;
//     return res;
// }

signed main (){
    n=rd,MOD=rd;

    comb_init();
    // f[1]=f[0]=1;
    // for(int i=2;i<=n;i++){
    //     cerr<<"OK ";
    //     int l=cal(i),r=i-l-1;
    //     cerr<<C(i-1,l)<<endl;
    //     f[i]=C(i-1,l)*f[l]%MOD*f[r]%MOD;
    // }
    f[1] = f[2] = 1; f[3] = 2;
    int l=1,r=1;
    for (int i = 4; i <= n; i++) {
        if (i - (1 << lg[i]) + 1 <= (1 << lg[i] - 1)) l++;
        else r++;
        f[i] = (C(i - 1, l) * f[l] % MOD) * f[r] % MOD;
    }
    cout<<f[n]<<endl;
    return 0;
}



/*
2 5
0 1 1 1 1
0 1 1 2 4
0 2 1 2 1
0 2 1 1 4
*/
```

【数据范围】
对于 $100\%$ 的数据，$1\le n \le 10^6$, $1\le m \le 10^9$，$m$ 是一个质数。



## 练习 #4 [SDOI2014] 数数

题目描述

我们称一个正整数 $x$ 是幸运数，当且仅当它的十进制表示中不包含数字串集合 $s$ 中任意一个元素作为其子串。例如当 $s = \{22, 333, 0233\}$ 时，$233$ 是幸运数，$2333$、$20233$、$3223$ 不是幸运数。给定 $n$ 和 $s$，计算不大于 $n$ 的幸运数个数。

答案对 $10^9 + 7$ 取模。

### 思路

参考题解

![image.png](数位DP/image 1.png)

![image.png](数位DP/image 2.png)

![image.png](数位DP/image 3.png)

```C++
/*
*/

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define pii pair<int, int>
#define pf first
#define rep(i, a, b) for(int i = a; i <= b; ++i)
#define per(i, a, b) for(int i = a; i >= b; --i)

#define rd read()
#define ot write
#define nl putchar('\n')
int rd{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
void write(int out){
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}

const int N = 2e3+5;
const int MOD = 1e9 + 7;
int tr[N][10], fail[N], in[N], idx;
char s[N], s2[N];
int f[N][N],a[N],n;
queue<int> q;

void add(){
    int now = 0;
    for (int i = 1; s[i]; i++){
        int c = s[i] - '0';
        if (!tr[now][c]) tr[now][c] = ++idx;
        now = tr[now][c];
    }
    in[now] = 1;
}

void getFail(){
    for (int i = 0; i < 10; i++)if (tr[0][i])q.push(tr[0][i]);
    while (q.size()){
        int now = q.front();
        q.pop();
        for (int i = 0; i < 10; i++){
            int c = tr[now][i];
            if (!c){ 
                tr[now][i] = tr[fail[now]][i];
                continue;
            }
            fail[c] = tr[fail[now]][i];
            in[c] |= in[fail[c]];
            q.push(c);
        
        }
    }
}

int dfs(int p, int now, bool flg, bool lim){
    if (in[now]) return 0;
    if (!p) return !flg;
    if (!lim && !flg && ~f[p][now]) return f[p][now];
    int up = lim ? a[p] : 9;
    int res = 0;
    for (int i = 0; i <= up; i++)
        res = (res + dfs(p - 1, (flg && !i) ? 0 : tr[now][i], flg && !i, lim && i == up)) % MOD;
    if (!lim && !flg) f[p][now] = res;
    return res;
}

signed main(){
    scanf("%s", s2 + 1);
    n=rd;
    for (int i = 1; i <= n; i++){
        scanf("%s", s + 1);
        add();
    }
    getFail();

    memset(f, -1, sizeof f);
    int len = strlen(s2 + 1);
    for (int i = 1; i <= len; i++) a[len - i + 1] = s2[i] - '0';
    cout<<dfs(len, 0, 1, 1);
    return 0;
}
```

对于全部的测试点，保证：

$1 \leq n < 10^{1201}$，$1 \leq m \leq 100$，$1 \leq \sum_{i = 1}^m |s_i| \leq 1500$，$\min_{i = 1}^m |s_i| \geq 1$，其中 $|s_i|$ 表示字符串 $s_i$ 的长度。$n$ 没有前导 $0$，但是 $s_i$ 可能有前导 $0$。

