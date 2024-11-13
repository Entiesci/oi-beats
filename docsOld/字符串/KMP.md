[F03【模板】KMP 算法——信息学竞赛算法_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1Ag411o7US/?spm_id_from=333.999.0.0)


# KMP算法

## 介绍

KMP算法的核心是利用匹配失败后的信息，尽量减少模式串与主串的匹配次数以达到快速匹配的目的。具体实现就是通过一个next()函数实现，函数本身包含了模式串的局部匹配信息。KMP算法的时间复杂度O(m+n)

**字符串的模式匹配**

字符串的模式匹配是一种常用的运算。所谓模式匹配,可以简单地理解为在目标(字符串)中寻找一个给定的模式(也是字符串)，返回目标和模式匹配的第一个子串的首字符位置。通常目标串比较大，而模式串则比较短小

**模式匹配的类型**

(1)精确匹配
如果在目标T中至少一处存在模式P，则称匹配成功，否则即使目标与模式只有一个字符不同也不能称为匹配成功，即匹配失败。给定一个字符或符号组成的字符串目标对象T和一个字符串模式P，模式匹配的目的是在目标T中搜索与模式P完全相同的子串,返回T和P匹配的第一个字符串的首字母位置 。
(2)近似匹配
如果模式P与目标T(或其子串)存在某种程度的相似,则认为匹配成功。常用的衡量字符串相似度的方法是根据一个串转换成另一个串所需的基本操作数目来确定。基本操作由字符串的插入、删除和替换来组成 。

**KMP模式匹配算法**

KMP算法是一种改进的字符串匹配算法,其关键是利用匹配失败后的信息,尽量减少模式串与主串的匹配次数以达到快速匹配的目的 。
求得模式的特征向量之后，基于特征分析的快速模式匹配算法(KMP模式匹配算法)与朴素匹配算法类似，只是在每次匹配过程中发生某次失配时，不再单纯地把模式后移一位，而是根据当前字符的特征数来决定模式右移的位数 。

## 算法流程

- 问题：快速找到t在s中出现的所有位置

- 预处理：对t预处理nxt，用于失配时的快速跳转

- 对s进行匹配，双指针。但t失配时，依据nxt快速跳到前面的$t_{nxt}$

## 例题 #1 KMP字符串匹配

题目描述

给出两个字符串 $s_1$ 和 $s_2$，若 $s_1$ 的区间 $[l, r]$ 子串与 $s_2$ 完全相同，则称 $s_2$ 在 $s_1$ 中出现了，其出现位置为 $l$。
现在请你求出 $s_2$ 在 $s_1$ 中所有出现的位置。

定义一个字符串 $s$ 的 border 为 $s$ 的一个**非 $s$ 本身**的子串 $t$，满足 $t$ 既是 $s$ 的前缀，又是 $s$ 的后缀。
对于 $s_2$，你还需要求出对于其每个前缀 $s'$ 的最长 border $t'$ 的长度。

输入格式

第一行为一个字符串，即为 $s_1$。
第二行为一个字符串，即为 $s_2$。

输出格式

首先输出若干行，每行一个整数，**按从小到大的顺序**输出 $s_2$ 在 $s_1$ 中出现的位置。
最后一行输出 $|s_2|$ 个整数，第 $i$ 个整数表示 $s_2$ 的长度为 $i$ 的前缀的最长 border 长度。

对于全部的测试点，保证 $1 \leq |s_1|,|s_2| \leq 10^6$，$s_1, s_2$ 中均只含大写英文字母。

### Solution

```C++
  	#include<bits/stdc++.h>
	using namespace std;
   	char a[1000100],b[1000100];
    int p[1000100],ls1,ls2,j;
    
    void pre(){
    	for(int i=2;i<=ls2;i++){
            while(j>0 && b[i]!=b[j+1]) j=p[j];
            if(b[i]==b[j+1]) j++;
            p[i]=j;
        }
	}
    int main(){
        scanf("%s%s",a+1,b+1);
        ls1=strlen(a+1),ls2=strlen(b+1);
        p[1]=0;
      	pre();

        j=0;
        for(int i=1;i<=ls1;i++){
            while(j>0 && a[i]!=b[j+1]) j=p[j];
            if(a[i]==b[j+1]) j++;
            if(j==ls2) printf("%d\n",i-ls2+1),j=p[j];
        }
        for(int i=1;i<ls2;i++)
        printf("%d ",p[i]);
        printf("%d",p[ls2]);
        return 0;
    }
```

或者：

```C++

string a,b;

 void getNxt(){
    nxt[1]=0;
    int j=1;
    for(int i=2;i<=m;i++){
        j=nxt[i-1];
        while(j&&b[j+1]!=b[i])j=nxt[j];
        nxt[i]=j+(b[j+1]==b[i]);
    }
 }


void solve(){

    cin>>a>>b;
    n=a.size();
    m=b.size();
    a=" "+a;
    b=" "+b;

    //匹配 a->b

    getNxt();

    int j=0;
    for(int i=1;i<=n;i++){
        while(j&&b[j+1]!=a[i])j=nxt[j];

        if(b[j+1]==a[i])j++;
        if(j==m){
            cout<<i-m+1<<endl;
            j=nxt[m];
        }
    }

    for(int i=1;i<=m;i++){
        cout<<nxt[i]<<' ';
    }

    
}
```

## 例题 #2 Password

题面翻译

Asterix，Obelix 和他们的临时伙伴 Suffix、Prefix 已经最终找到了和谐寺。然而和谐寺大门紧闭，就连 Obelix 的运气也没好到能打开它。

不久他们发现了一个字符串 $S\ (1\leqslant\vert S\vert\leqslant1000000)$，刻在和谐寺大门下面的岩石上。Asterix 猜想那一定是打开寺庙大门的密码，于是就大声将字符串朗读了出来，然而并没有什么事发生。于是 Asterix 又猜想密码一定是字符串 $S$ 的子串 $T$。

Prefix 认为 $T$ 是 $S$ 的前缀，Suffix 认为 $T$ 是 $S$ 的后缀，Obelix 却认为 $T$ 应该是 $S$ 中的某一部分，也就是说，$T$ 既不是 $S$ 的前缀，也不是 $S$ 的后缀。

Asterix 选择子串 $T$ 来满足所有伙伴们的想法。同时，在所有可以被接受的子串变形中，Asterix 选择了最长的一个。当 Asterix 大声读出子串 $T$ 时，寺庙的大门开了。（也就是说，你需要找到既是 $S$ 的前缀又是 $S$ 的后缀同时又在 $S$ 中间出现过的最长子串）

现在给你字符串 $S$，你需要找到满足上述要求的子串 $T$。

输入格式

一行一个只包含小写字母的字符串 $S$。

输出格式

输出子串 $T$，如果 $T$ 不存在，输出 `Just a legend`。

---



```C++
// Problem: Password
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF126B
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Challenger: Erica N
// ----
#include<bits/stdc++.h>

using namespace std;
#define rd read()
#define ull unsigned long long
#define int long long 
#define itn int
#define ps second 
#define pf first

int  read(){
	int x;
	cin>>x;
	return x;
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
const int N=3e6+5;
const ull P=137;
const int INF=1e9+7;
/*

策略
找到<=nxt[n]的最大的nxt[i]就是答案长度

*/
int n;
string s;
int nxt[N];
int cnt[N];

void getNxt(string s){
	nxt[1]=0;
	for(int i=2;i<=n;i++){
		int j=nxt[i-1];
		while(j&&s[j+1]!=s[i])j=nxt[j];
		if(s[j+1]==s[i])j++;
		nxt[i]=j;
	}
}

signed main(){
	cin>>s;
	n=s.size();
	s=" "+s;
	getNxt(s);
	
	// for(int i=1;i<=n;i++)cdbg(nxt[i]);
	
	int t=n;
	while(nxt[t]){
		cnt[nxt[t]]++;
		t=nxt[t];
	}
	int ans=0;
	for(int i=2;i<n;i++){
		if(cnt[nxt[i]]){
			if(nxt[i]>ans){
				ans=nxt[i];
			}
		}
	}
	
	if(ans==0)puts("Just a legend");
	else cout<<s.substr(1,ans);
}


```

## 例题 #3 Power Strings

求一个字符串由多少个重复的子串连接而成。

例如 `ababab` 由三个 `ab` 连接而成，`abcd` 由 `abcd` 由一个 `abcd` 连接而成。

$1\le |s|\le 10^6$。

---

考察nxt数组的性质，发现只要n是$n-nxt_n$的倍数，那么就可以将$n-nxt_n$作为循环节。否则无循环节

```C++
// Problem: Power Strings
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/UVA10298
// Memory Limit: 0 MB
// Time Limit: 3000 ms
// Challenger: Erica N
// ----
#include<bits/stdc++.h>

using namespace std;
#define rd read()
#define ull unsigned long long
#define int long long 
#define itn int
#define ps second 
#define pf first

int  read(){
	int x;
	cin>>x;
	return x;
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
const int N=3e6+5;
const ull P=137;
const int INF=1e9+7;
/*

策略


*/
string s;
int n;
int nxt[N];

void getNxt(){
	nxt[1]=0;
	for(int i=2;i<=n;i++){
		int j=nxt[i-1];
		while(s[j+1]!=s[i]&&j)j=nxt[j];
		if(s[j+1]==s[i])j++;
		nxt[i]=j;
	}
}

void solve(){
	cin>>s;
	if(s[0]=='.')exit(0);
	n=s.size();
	s=" "+s;
	getNxt();
	int l=n-nxt[n];
	if(n%l==0){
		cout<<n/l<<endl;
	}else{
		cout<<1<<endl;
	}
}

signed main(){
	while(1){
		solve();
	}	
}


```

## 练习

对nxt数组的本质探究

[www.luogu.com.cn](https://www.luogu.com.cn/problem/P4391)

## 扩展KMP（exkmp）

[183 扩展 KMP(Z 函数)_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1Y54y1o7Ca/?spm_id_from=333.999.0.0)

给定两个字符串 $a,b$，你要求出两个数组：

- $b$ 的 $z$ 函数数组 $z$，即 $b$ 与 $b$ 的每一个后缀的 LCP（最长公共前缀）长度。

- $b$ 与 $a$ 的每一个后缀的 LCP 长度数组 $p$。

对于一个长度为 $n$ 的数组 $a$，设其权值为 $\operatorname{xor}_{i=1}^n i \times (a_i + 1)$。

```C++
/*////////ACACACACACACAC///////////
       . Code  by  Ntsc .
       . Earn knowledge .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define int long long
#define db double
#define rtn return
using namespace std;

const int N=2e7+5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;

int n,m,q,T,z[N],p[N],ans;
char s[N],t[N];

void get_z(char s[],int n){
	z[1]=n;
	int l=0,r=0;
	for(int i=2;i<=n;i++){
		if(i<=r)z[i]=min(z[i-l+1],r-i+1);
		while(s[1+z[i]]==s[i+z[i]])z[i]++;
		
		if(i+z[i]-1>r)l=i,r=i+z[i]-1;//转移box 
	}
}

void get_p(char s[],char t[],int n,int m){
	int l=0,r=0;
	for(int i=1;i<=m;i++){
		if(i<=r)p[i]=min(z[i-l+1],r-i+1);
		while(s[1+p[i]]==t[i+p[i]]&&1+p[i]<=n&&i+p[i]<=m)p[i]++;
		
		if(i+p[i]-1>r)l=i,r=i+p[i]-1;//转移box 
	}
}

signed main(){
	scanf("%s",t+1);
	scanf("%s",s+1);
	n=strlen(s+1);
	m=strlen(t+1);
	get_z(s,n);
	get_p(s,t,n,m);
	
//	for(int i=1;i<=n;i++)cerr<<z[i]<<' ';
//	cerr<<"z[]end\n";
	for(int i=1;i<=n;i++)ans^=i*(z[i]+1);
	cout<<ans<<endl;
	ans=0;
	for(int i=1;i<=m;i++)ans^=i*(p[i]+1);
	cout<<ans<<endl;
	return 0;
}


```

注意求的是b的z函数

### Z函数

**z 函数
对于一个长度为 n 的字符串 s 。$ z_i$表示 $s $与其后缀 $s[ i , n ] $的最长公共前缀 （ LCP ） 的长度**

![image.png](KMP/image.png)

暴力计算自然是O(n^2)

**Z-box**

手扶着铁窗~~我望~~外边~~~

![image.png](KMP/image 1.png)

对于 i, 我们称区间$ [i,i+ z[i]- 1 ]$ 是的匹配段 ， 也可以叫 Z-box
算法过程中我们维护右端点最靠右的匹配段 。 为了方便 ， 记作[l, r ] 。 s [l,r]一定等于 s  的前缀 。
在计算 z[i] 时我们保证l≤i

举个例子，此时我们已经处理了z[1\sim 5]，此时盒子为[5,8]，那么我们在处理z[6\sim 8]时就可以直接从z[2\sim 4]转移过来。

**算法流程**

![image.png](KMP/image 2.png)

对比一下？马拉车如下：

![image.png](KMP/image 3.png)

我们来解释一下

![image.png](KMP/image 4.png)

1. 我们可以保证s[1,r-l+1]=s[l,r]，但是其余部分我们不能保证。如果i在box内
(1) 如z[i-l+1]<r-i+1，说明z[i-l+1]的对应的字符串全部在box内，所以我们可以保证z[i-l+1]可以完美转移到z[i]
(2) 如z[i-l+1]≥r-i+1，说明z[i-l+1]的对应的字符串前部分在box内，所以我们可以不能保证z[i-l+1]可以完美转移到z[i]，故对于伸出box外的部分，我们要逐个枚举

2. 如果i在box外。那么我们只好暴力枚举了。

但是有一个重点就是box的转移了。要不然这个算法就失去了意义。

求出 $z[i]$ 后 ， 如果 $i + z[i] - 1 > r$, 则更新盒子 $l = i , r = i + z [i]-1$。为什么呢？因为i + z[i] - 1 代表当前z[i]的对应串的右端点。如果i + z[i] - 1 > r，就说明对应串的右端点伸出了当前的box

![image.png](KMP/image 5.png)

很明显，以左图为例，红色box区间已经没有用处了，而现在我们知道蓝色区间对应相等，那么我们就可以把box转移到[l',r']

**代码**

```C++
void get_z(char s[],int n){
	z[1]=n;
	int l=0,r=0;
	for(int i=2;i<=n;i++){
		if(i<=r)z[i]=min(z[i-l+1],r-i+1);
		while(s[1+z[i]]==s[i+z[i]])z[i]++;
		if(i+z[i]-1>r)l=i;r=i+z[i]-1;//转移box 
	}
}
```

时间复杂度分析

时间复杂度完全取决于while，而我们知道，只有当前z[i]对应字符的右边界伸出了box，伸出多少就跑几遍while。而在伸出后我们又会更新box，所以我们的while次数$=r$从$1\sim n=n$次

### P函数

$b$ 与 $a$ 的每一个后缀的 LCP 长度数组 $p$。



```C++
void get_p(char s[],char p[],int n,int m){
	int l=0,r=0;
	for(int i=1;i<=n;i++){
		if(i<=r)p[i]=min(z[i-l+1],r-i+1);
		while(s[1+p[i]]==t[i+p[i]]&&1+p[i]<=n&&i+p[i]<=m)p[i]++;
		
		if(i+p[i]-1>r)l=i;r=i+p[i]-1;//转移box 
	}
}
```

### 练习 #1 [NOIP2020] 字符串匹配

小 C 学习完了字符串匹配的相关内容，现在他正在做一道习题。

对于一个字符串 $S$，题目要求他找到 $S$ 的所有具有下列形式的拆分方案数：

$S = ABC$，$S = ABABC$，$S = ABAB \ldots ABC$，其中 $A$，$B$，$C$ 均是非空字符串，且 $A$ 中出现奇数次的字符数量不超过 $C$ 中出现奇数次的字符数量。

更具体地，我们可以定义 $AB$ 表示两个字符串 $A$，$B$ 相连接，例如 $A = \texttt{aab}$，$B = \texttt{ab}$，则 $AB = \texttt{aabab}$。

并递归地定义 $A^1=A$，$A^n = A^{n - 1} A$（$n \ge 2$ 且为正整数）。例如 $A = \texttt{abb}$，则 $A^3=\texttt{abbabbabb}$。

则小 C 的习题是求 $S = {(AB)}^iC$ 的方案数，其中 $F(A) \le F(C)$，$F(S)$ 表示字符串 $S$ 中出现奇数次的字符的数量。两种方案不同当且仅当拆分出的 $A$、$B$、$C$ 中有至少一个字符串不同。

小 C 并不会做这道题，只好向你求助，请你帮帮他。

输入格式

本题有多组数据，输入文件第一行一个正整数 $T$ 表示数据组数。

每组数据仅一行一个字符串 $S$，意义见题目描述。$S$ 仅由英文小写字母构成。

输出格式

对于每组数据输出一行一个整数表示答案。

对于所有测试点，保证 $1 \le T \le 5$，$1 \le |S| \le 2^{20}$。

---

先考虑把s拆成(AB)^kC的方案数，其中AB合起来是一个循环节，我们先考虑一个循环节有多长。

回顾z函数的意义，z_i 表示从s的第i个字符开始的长度为z_i的前缀和s的长度为z_i的前缀相同。无论是在z函数还是从kmp的nxt函数，我们都可以获取字符串的循环节信息。

我们枚举第一个循环节的长度i，如果有z_i≥i，那么我们就发现了一个周期数至少为2的循环节。那么周期数到底是多少呢？手模一下可以发现是：$T=[\frac{z_i}{i}]+1$

![image.png](KMP/image 6.png)

那么因为本题限制周期数t≥1，取当前s[1,i]为AB，(AB)^kC的方案数就是[\frac{z_i}{i}]+1。

下面我们针对t和T就行讨论，这影响了C中奇数数量字符的个数。

- T-t为偶数，此时C中奇数数量=后缀奇数数量

- T-t为奇数，此时C中奇数数量=后缀奇数数量+AB中奇数数量

统计合法的A和合法的后缀数，用组合数计算。

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

const int N = 1e6 + 5e4;
const int INF = 1e18;
const int M = 30;
const int MOD = 1e9 + 7;


namespace ctree{
    int c[M];
    inline int lowbit(int x){
        return x&-x;
    }
    void change(int x,int v){
        while(x<M){
            c[x]+=v;
            x+=lowbit(x);

        }
    }

    int query(int x){
        int res=0;
        while(x){
            res+=c[x];
            x-=lowbit(x);
        }

        return res;
    }
}using namespace ctree;

string s;
int n;

int z[N];

// void getz(string s,int n){
//     z[1]=n;
//     int l=0,r=0;
//     for(int i=2;i<=n;i++){
//         if(i<=r)z[i]=min(z[i-l+1],r-i+1);
//         while(s[1+z[i]]==s[i+z[i]])z[i]++;
//         if(i+z[i]-1>r)l=i;
//         r=i+z[i]-1;
//     }

//     for(int i=1;i<=n;i++){
//         z[i-1]=z[i];
//     }

// }


void getZ() {
    z[0] = n;
    int now = 0;
    while (now + 1 < n && s[now] == s[now + 1]) {
        now++;
    }
    z[1] = now;
    int p0 = 1;
    for (int i = 2; i < n; ++i) {
        if (i + z[i - p0] < p0 + z[p0]) {
            z[i] = z[i - p0];
        } else {
            now = p0 + z[p0] - i;
            now = max(now, 0ll);
            while (now + i < n && s[now] == s[now + i]) {
                now++;
            }
            z[i] = now;
            p0 = i;
        }
    }
}


int hz[N],qz[N];
int all;


void init(){
    memset(hz,0,sizeof hz);
    memset(qz,0,sizeof qz);
    memset(c,0,sizeof c);
    // memset(z,0,sizeof z);
    all=0;
}

void solve(){

    init();
    cin>>s;
    n=s.size();
    getZ();
    // getz(" "+s,n);
    // dbg("OK2");

    for(int i=0;i<n;i++){
        if(i+z[i]==n)z[i]--;
    }
    // ell;
    // for(int i=1;i<=n;i++)dbg(z[i]);
    // ell;

    for(int i=0;i<n;i++){
        hz[s[i]-'a']++;
    }
    for(int i=0;i<26;i++){
        if(hz[i]&1)all++;
    }
    // dbg("all=",all,el);
    int suf=all;
    int pre=0;
    int ans=0;


    for(int i=0;i<n;i++){
        if(hz[s[i]-'a']&1)suf--;
        else suf++;

        hz[s[i]-'a']--;
        if(qz[s[i]-'a']&1)pre--;
        else pre++;

        qz[s[i]-'a']++;
        if(i&&i<n-1){
            int t=z[i+1]/(i+1)+1;
            ans+=(t>>1)*query(all+1)+(t-t/2)*query(suf+1);

        }
        change(pre+1,1);
    }
    cout<<ans<<endl;
}

signed main() {
    int T=rd;
    while(T--){
    	solve();

    }
    return 0;
}
```

## 题单

[KMP题单](KMP/KMP%E9%A2%98%E5%8D%95%20a45bcd88-875c-439d-93c8-2b3068141366.md)



