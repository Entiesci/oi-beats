# GCD与LCM

## **最大公因数**





### 辗转相除法

辗转相除法求`gcd(a,b)`算法实现

```C++
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
```

压行后（不知道对不对）

```C++
int gcd(int a, int b) {return b?gcd(b, a % b):a;}
```

### 更相减损术

gcd(a,b)=gcd(a-b,b)，递归条件你为a-b=0时返回b。

```C++
int gcd(int a,int b){
    if(a<b)swap(a,b);
    if(!b)return a;
    if((a&1)==0||(b&1)==0)return gcd(a>>1,b>>1)<<1;
    if((a&1)==0){a>>=1;return gcd(a,b);}
    if((b&1)==0){b>>=1;return gcd(a,b);}
    return gcd(a-b,b);
}
```



### STL

```C++
__gcd(int a,int b)
```





![v2-59ac8410625b8f4f90aa9aa07fd5e55a_b.jpg](GCD与LCM/v2-59ac8410625b8f4f90aa9aa07fd5e55a_b.jpg)



### 练习 #1 Mike and gcd problem

Mike 有一个长度为 $n$ 的序列 $A=[a_1,a_2,\dots,a_n]$。他认为一个序列 $B=[b_1,b_2,\dots,b_n]$ 是优美的，当且仅当其所有元素的 $\gcd$ 大于 $1$，即 $\gcd(b_1,b_2,\dots,b_n)>1$。

Mike 想要对他的序列进行操作来使它变为优美的。每次操作，他可以选择一个下标 $i(1\leqslant i<n)$，删除 $a_i$ 和 $a_{i+1}$，然后把 $a_i-a_{i+1}$ 和 $a_i+a_{i+1}$ 放回这两个位置上。他希望操作次数尽可能少。如果序列可以变为优美的，你需要给出最少操作次数，否则，指出不可能。

$\gcd(b_1,b_2,\dots,b_n)$ 是最大的非负整数 $d$ 使得 $d$ 整除每一个 $b_i(1\leqslant i\leqslant n)$。

#### 输入格式

第一行一个整数 $n(2\leqslant n\leqslant 10^5)$，表示序列 $A$ 的长度。

之后一行，$n$ 个被空格隔开的整数 $a_1,a_2,\dots,a_n(1\leqslant a_i\leqslant10^9)$，表示 $A$ 中的元素。

#### 输出格式

如果可以使序列变为优美的，第一行输出 `YES`，然后第二行输出最小操作次数。

如果不可能使得序列变为优美的，在第一行输出 `NO`。

---

考虑操作对序列的gcd的影响。很容易发现操作有可能会使得gcd变为原来的两倍。结合更相减损术可知gcd不会变小。那么gcd还有无其他可能？设原来两个数关于g极其因子为kg,lg，操作后变为(k+l)g,(k-l)g，可以写成ag,(a-2b)g。发现仅有可能增加的因子为2及其次幂。

那么就很好做了，如果一个序列不满足要求，我们只可以尝试将其gcd变为2.那么就是要去除所有的奇数。发现对于一个奇数串，如果其长度为偶数，那么两两匹配。如果多出来一个奇数，那么两次操作即可变为偶数。

## **最小公倍数**

两个或多个整数公有的倍数叫做它们的公倍数，其中除0以外最小的一个公倍数就叫做这几个整数的最小公倍数。整数a，b的最小公倍数记为 $[a,b] $，同样的，a，b，c的最小公倍数记为$[a,b,c]$，多个整数的最小公倍数也有同样的记号。

与最小公倍数相对应的概念是最大公约数，a，b的最大公约数记为 **$(a,b)$** 。关于最小公倍数与最大公约数，我们有这样的定理： **$(a,b)\times[a,b]=ab$** ($a,b$均为整数)。

### 练习 #1 [USACO20OPEN] Exercise G

题目描述

Farmer John（又）想到了一个新的奶牛晨练方案！
如同之前，Farmer John 的 $N$ 头奶牛站成一排。对于 $1\le i\le N$ 的每一个 $i$，从左往右第 $i$ 头奶牛的编号为 $i$。他告诉她们重复以下步骤，直到奶牛们与她们开始时的顺序相同。

给定长为 $N$ 的一个排列 $A$，奶牛们改变她们的顺序，使得在改变之前从左往右第 $i$ 头奶牛在改变之后为从左往右第 $A_i$ 头。
例如，如果 $A=(1,2,3,4,5)$，那么奶牛们总共进行一步。如果 $A=(2,3,1,5,4)$，那么奶牛们总共进行六步。每步之后奶牛们从左往右的顺序如下：

0 步：$(1,2,3,4,5)
$1 步：$(3,1,2,5,4)
$2 步：$(2,3,1,4,5)
$3 步：$(1,2,3,5,4)
$4 步：$(3,1,2,4,5)
$5 步：$(2,3,1,5,4)
$6 步：$(1,2,3,4,5)
$**求所有正整数 $K$ 的和，使得存在一个长为 $N$ 的排列，奶牛们需要进行恰好 $K$ 步。**

由于这个数字可能非常大，输出答案模 $M$ 的余数（$10^8\le M\le 10^9+7$，$M$ 是质数）。

对于 $100\%$ 的数据，$1\le N\le 10^4$。

---

转换题意，发现是置换环问题

一个K合法，当且仅当存在一种分法满足以下要求：每个环的长度的lcm为K，且每个环的长度和为n。

我们设第i个环的长度为l_i，那么就是要使得$\sum l_i=n,\text{lcm}(l_i)=K$。

转移到lcm(l_i)实际上是对于所有l中含有的因子p，取最大的次幂q。意思是说对于一个l中含有的因子p，取$p^{q_{i,p}}$加入到lcm中，其中i满足在[1,n]中，l_i的p的次幂是所有l_i中最高的。于是我们就可以让每个置换环的长度恰好为lcm中的一个p^q。可以证明只要K合法，那么就存在这样的构造使得置换环的长度≤n且lcm=K。

于是我们就要在质数表中选择若干质数p和任意指数，使得它们的和≤n。因为要记录合法的K之和，假设我们知道了\sum l=i的K之和ans(i)，现在我们要新加一个长度为p^q的置换环进去，那么K就变成了K\times p^q，于是就有ans(i+p^q)=ans(i)\times p^q。

那么我们就可以设f_{i,j}为考虑质数表中的前i个数，且当前选择的数的和为j（即n=j）时合法的K的数量。

最后的答案为\sum_{i\in[0,n]}f_{tot,i}，之所以不是f_{tot,n}，是因为如果项数不足n，那么就在i的位置上放i即可。

转移时考虑$f_{i,j}=\sum_{k,p^k≤j} f_{i-1,j-p^k}\times p^k$

```C++
// Problem: P6280 [USACO20OPEN] Exercise G
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6280
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Challenger: Erica N
// ----
// 
#include<bits/stdc++.h>

using namespace std;
#define rd read()
#define ull unsigned long long
#define int long long 
#define pb push_back
#define itn int
#define ps second 
#define pf first


#define rd read()
int read()
{
  int xx = 0, ff = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9')
  {
    if (ch == '-')
      ff = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')
    xx = xx * 10 + (ch - '0'), ch = getchar();
  return xx * ff;
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
const int N=2e5+5;
const ull P=137;
const int INF=1e18+7;
int MOD=1e9+7;
/*

策略
置换环问题
每个环的长度的lcm为K
即每个环的长度均为K的因数
即将n分成K的因数
*/	
int isp[N],p[N];
int cnt;
int n;

void init(){
	for(int i=2;i<=n;i++){
		if(!isp[i]){
			isp[i]=i;
			p[++cnt]=i;
		}
		
		
		for(int j=1;j<=cnt;j++){
			if(p[j]*i>n)break;
			isp[i*p[j]]=p[j];
			if(i%p[j]==0)break;
		}
	}
}

int f[N];

signed main(){
	n=rd;
	
	init();
	
	// for(int i=1;i<=10;i++)cdbg(p[i]);
	f[0]=1;
	
	for(int i=1;i<=cnt;i++){
		for(int j=n;j>=p[i];j--){
			int t=p[i];
			while(t<=j){
				f[j]+=f[j-t];
				t*=p[i];
			}
		}
	}
	
	int ans=0;
	for(int i=0;i<=n;i++)ans+=f[i];
	
	cout<<ans<<endl;
}


```

## 练习 #1 最轻的天平

题目描述

天平的两边有时不一定只能挂物品，还可以继续挂着另一个天平，现在给你一些天平的情况和它们之间的连接关系，要求使得所有天平都能平衡所需物品的总重量最轻，一个天平平衡当且仅当“左端点的重量*左端点到支点的距离=右端点的重量*右端点到支点的距离”。注意题目中的输入保证这些天平构成一个整体。

输入格式

第一行包含一个 $N(N \le 100)$，表示天平的数量，天平编号为 $l$ 到 $N$，接下来包含 $N$ 行描述天平的情况，每行 $4$ 个整数 $P,Q,R,B$，$P$ 和 $Q$ 表示横杆上支点到左边的长度与到右边的距离的比例为 $P:Q$，$R$ 表示左边悬挂的情况，如果 $R=0$ 说明悬挂的是物品，否则表示左边悬挂的是天平 $R:B$ 表示右边的悬挂情况，如果 $B=O$ 表示右边悬挂的是物品，否则右边悬挂着天平 $B$。

对于所有的输入，保证 $W\times L<2^{31}$，其中 $w$ 为最轻的天平重量，而 $L$ 为输入中描述左右比例时出现的最大值。

输出格式

输出一个整数表示使得所有天平都平衡所需最轻的物品总重量。

---

分情况讨论：下设l,r为天平左边/右边的最小重量和。

- l=r=0，那么按p,q最简比即可。

- l,r中有一个非0，假设l非0，那么求出最小的l'使得p|l'，结果为(p+q)*(l'/p)

- l,r均非0。此时是最棘手的。先变化为lrp:lrq。再考虑约分：gcd(lp,rq)是可以被除掉的。注意gcd(lq,rp)不能被除掉。因为lrp除掉lp得到实际上是kr/p，于是又kl/q:kr/p=p:q。

```C++
// Problem: P1961 最轻的天平
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P1961
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Challenger: Erica N
// ----
// 
#include<bits/stdc++.h>

using namespace std;
#define rd read()
#define ull unsigned long long
#define int long long 
#define pb push_back
#define itn int
#define ps second 
#define pf first


#define rd read()
int read()
{
  int xx = 0, ff = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9')
  {
    if (ch == '-')
      ff = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')
    xx = xx * 10 + (ch - '0'), ch = getchar();
  return xx * ff;
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
const int N=2e5+5;
const ull P=137;
const int INF=1e18+7;
/*

策略


*/	

int ind[N],l[N],r[N];
int p[N],q[N];

int dfs(int x){
	if(!x)return 1;
	int sl=0,sr=0;
	sl=dfs(l[x]);
	sr=dfs(r[x]);
	
	// cdbg(x,sl,sr,p[x],q[x]);
	
	int g=__gcd(sl*p[x],sr*q[x]);
	int tl=sl*sr*q[x]/g;
	int tr=sr*sl*p[x]/g;
	// int l=__gcd(sl,sr);
	// sl=sl*g/l,sr=sr*g/l;
	return tl+tr;
}


signed main(){
	int n=rd;
	for(int i=1;i<=n;i++){
		 p[i]=rd,q[i]=rd,l[i]=rd,r[i]=rd;
		int g=__gcd(p[i],q[i]);
		// p[i]/=g;
		// q[i]/=g;
		if(l[i])ind[l[i]]++;
		if(r[i])ind[r[i]]++;
		
	}
	
	
	int st=1;
	for(int i=1;i<=n;i++){
		if(!ind[i])st=i;
	}
	
	
	cdbg("ok");
	cout<<dfs(st);
}
```

## 练习 #2 辗转相除优化辗转相减 Game 

爱丽丝和鲍勃正在玩一个游戏。最开始，爱丽丝有 x 个筹码，鲍勃有 y 个筹码。

游戏进行若干轮。在每一轮中，爱丽丝获胜的概率为 p0​，鲍勃获胜的概率为 p1​，平局的概率为 1−p0​−p1​。

如果出现平局，游戏立即进入下一轮。否则，如果获胜者的筹码数量不小于失败者的筹码数量，获胜者将赢得整个游戏，游戏结束；否则，失败者将失去与获胜者当前筹码数量相等的筹码，游戏进入下一轮。

请注意，在每轮游戏结束后，任何人的筹码都不会增加。

你需要找出爱丽丝最终赢得整个游戏的概率。

输入

第一行包含一个整数 T (1≤T≤105)，表示测试用例的数量。$1≤x,y≤10^9$

---

实现可以发现可以通过辗转相减来模拟流程。但是这样太太慢了，所以我们考虑如何加速。

我们发现，当x>y时，除非alice一直输知道·状态为x%y,y时，bob才有可能获胜。因此就是w+dfs(x%y,y,p')，其中w是alice在中途获胜的概率。

当x<y时，也是一样的。因此我们都可以直接变成辗转相除来优化。求w时用等比数列求和即可。

等比数列求和公式：$S_n=\frac{a_1-a_nq}{1-q}$，其中q为比值。

```C++
// Problem: J - Game
// Contest: Virtual Judge - 思维
// URL: https://vjudge.net/contest/670080#problem/J
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Challenger: Erica N
// ----
// 
#include<bits/stdc++.h>

using namespace std;
#define rd read()
#define ull unsigned long long
#define int long long 
#define pb push_back
#define itn int
#define ps second 
#define pf first


#define rd read()
int read(){
  int xx = 0, ff = 1;char ch = getchar();
  while (ch < '0' || ch > '9'){
    if (ch == '-')ff = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')xx = xx * 10 + (ch - '0'), ch = getchar();
  return xx * ff;
}
#define zerol = 1
#ifdef zerol
#define cdbg(x...) do { cerr << #x << " -> "; err(x); } while (0)
void err() {cerr << endl;}
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) {
	for (auto v: a) cerr << v << ' ';err(x...);
}
template<typename T, typename... A>
void err(T a, A... x) {
	cerr << a << ' ';err(x...);
}
#else
#define dbg(...)
#endif
const int N=2e5+5;
const ull P=137;
const int INF=1e18+7;

const int MOD=998244353;
/*

策略


*/	

inline int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=res*a%MOD;
		b>>=1;
		a=a*a%MOD;
	}
	return res;
}
int a0,a1;

int dfs(int x,int y,int p){
	if(!x)return 0l;
	if(!y)return p;
	if(x>y){
		int t=ksm(a1,x/y);
		int res=(1-t+MOD)*p%MOD;
		res=(res+dfs(x%y ,y,p*t%MOD))%MOD;
		return res;
	}else{
		return dfs(x,y%x,ksm(a0,y/x)*p%MOD);
	}
}

void solve(){
	int x=rd,y=rd;
	 a0=rd,a1=rd;
	 rd;
	 int b=a0+a1;//平局没用
	a0=a0*ksm(b,MOD-2)%MOD;
	a1=a1*ksm(b,MOD-2)%MOD;
	
	cout<<dfs(x,y,1)%MOD<<endl;
}

signed main(){
	int t=rd;
	while(t--){
		solve();
	}
}


```

