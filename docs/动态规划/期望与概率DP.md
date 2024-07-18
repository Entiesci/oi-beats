# 期望与概率DP

## 概率DP

### 例题 #1 搞笑世界杯

题目描述

随着世界杯小组赛的结束，法国，阿根廷等世界强队都纷纷被淘汰，让人心痛不已。 于是有人组织了一场搞笑世界杯，将这些被淘汰的强队重新组织起来和世界杯一同比赛。你和你的朋友欣然去购买球票。不过搞笑世界杯的球票出售方式也很特别，它们只准备了两种球票。

- A 类票——免费球票

- B 类票——双倍价钱球票。

购买时由工作人员通过掷硬币决定，投到正面的买 A 类票， 反面的买 B 类票。主办方总是准备了同样多的 A 类票和 B 类票。你和你的朋友十分幸运的排到了某场精彩比赛的最后两个位置。

这时工作人员开始通过硬币售票。不过更为幸运的是当工作人员到你们面前时他发现已无需再掷硬币了，因为剩下的这两张票全是免费票。

你和你的朋友在欣喜之余，想计算一下排在队尾的两个人同时拿到一种票的概率是多少(包括同时拿 A 类票或 B 类票) 假设工作人员准备了 $2n$ 张球票，其中 $n$ 张 A 类票，$n$ 张 B 类票，并且排在队伍中的人每人必须且只能买一张球票(不管掷到的是该买 A 还是该买 B)。

输入格式

输入只有一行一个整数，表示 $2n$。

输出格式

输出只包含一行一个浮点数，为拿到同一种票的概率，精确到小数点后 4 位。

对全部的测试点，保证 $1 \leq n \leq 1250$。

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

const int N = 3e3 + 5;
const int INF = 1e18;
const int M = 1e7;
const int MOD = 1e9 + 7;

double f[N][N];

void solve(){
    int n=rd;
    n>>=1;
    f[0][1]=1;
    f[1][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            f[i][j]=f[i][j-1]*0.5+f[i-1][j]*0.5;
        }
    }
    printf("%.4lf",1-f[n][n]);
}

signed main() {
    int T=1;
    while(T--){
    	solve();
    }
    return 0;
}
```

## 期望DP

### 例题 #1 Assimilation IV

**题面翻译**

给定 $n$ ($1 \le n \le 20$) 个城市和 $m$ ($1 \le m \le 5 \cdot 10^4$)个点.

对于每个城市，给定所有点到该城市的距离与光在一秒内行走距离的比值 $d$ ($1 \le d \le n + 1$)（不一定满足三角不等式）.

从第零秒开始，每隔一秒可以点亮一个未被点亮的城市.

已知点亮城市的顺序随机，求第 n 秒的瞬间被照亮的点数的期望值,答案对 998244353 取模。

**大意**

给出光从每一座城市到每一个点的用时，从第零秒开始，每隔一秒可以点亮一个未被点亮的城市，城市发出的光可以点亮点，求第 $n$ 秒的瞬间被点亮的点数的期望值。

**思路**

是一道不擅长的期望题！

首先我们对于每个点单独计算它被选中的概率，再求和即为答案。

我们发现一种情况和一个长度为 $n $ 的排列（即点亮城市的顺序)一一对应，所以考虑当前点在多少个排列中被覆盖。

如果有某座城市的光覆盖当前点，那么一定存在排列的第 $i$ 位是距离 $≤i $ 的城市。那么 $i$ 可能有很多个，我们要计算这种情况的情况数，我们很容易想到排列组合里的一个技巧——计算不成立的情况。

正难则反。直接计算不好求，那我们就考虑计算没有覆盖当前点。

如果没有覆盖当前点，那么排列的最后一位一定是距离 $>n$ 的城市，倒数第二位一定是距离 $>n-1$ 的城市，依次类推，我们直接乘法原理计算即可。注意，因为我们每座城市都会被点亮，所以如果有一个城市距离当前点的距离为 $1$，那么这个点一定会被点亮。

按照这种方法暴力，我们的复杂度为 $O(m\times n^2)$ 大概是 $2\times 10^7$，经过优化和桶计数，我们可以优化为 $O(nm)$。

**代码**

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

const int N=1e5+5;
const int M=1e5;
const int MOD=998244353;
const int INF=1e5;

int n,m,p,q,T,fac[N],ans;
int c[N][22];

int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=res*a%MOD;
		a=a*a%MOD;
		b>>=1;
	}
	return res;
}

int rd(){
	int t;
	cin>>t;
	return t;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		c[j][rd()]++;//c[j][k]表示离点j距离为k的点的个数
	}
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=(i*fac[i-1])%MOD;
	int inv=ksm(fac[n],MOD-2);
	for(int i=1;i<=m;i++){
		int sum=0,tmp=1;
		for(int j=n;j;j--){
			sum+=c[i][j+1];
			tmp=tmp*sum%MOD;
			sum--;
		}
		ans=(ans+1-inv*tmp%MOD+MOD)%MOD;//1为总方案的概率，inv*tmp为不合法的概率
	}
	cout<<ans<<endl;               
}
```

## 有后效性的DP（期望DP）

### **例题 #1 图上随机游走类 |** [Cnoi2020] 线形生物

**题目描述**

线形生物要从 $1$ 号台阶走到 $n+1$ 号台阶。

最开始，$1,2,3,\ldots,n$ 号台阶都有一条连向下一台阶的有向边 $i\rightarrow i+1$。

之后 Cirno 加入了 $m$ 条**返祖边** $u_i \rightarrow v_i (u_i \ge v_i)$，它们构成了一个**返祖图**。

线形生物每步会 **等概率地** 选取当前台阶的一条出边并走向对应的台阶。

当走到 $n+1$ 号台阶时，线形生物就会停止行走。

同时，Cirno 会统计线性生物总共走的步数，记作 $\delta$。

Cirno 想知道 $E(\delta)$（即 $\delta$ 的**数学期望**）对 $998244353$ 取模后的结果。

**思路**

考虑期望dp

期望的线性性质：在本题中体现为从 x 点到 y 点的期望步数 $E_{x\to y}=E_{x\to x+1}+…+E_{y-1 \to y}=\sum\limits_{i=x}^{y-1}E_{i\to i+1}$。$E_{y\to x+1}=\sum\limits_{i=y}^{x}E_{i\to i+1}$

对于这类在**图上随机游走**的问题，设 $E_{x\to x+1}$ 表示从 x 点到 x+1 点的期望步数，那么答案就是 $\sum\limits_{x=0}^n E_{x\to x+1}$ 。

 $du_x$ 表示 x 的**返祖边**的条数，而 g(x) 表示 x 的**返祖边**的边集，列出 $E_{x\to x+1}$ 的转移式:

 $E_{x\to x+1}=\frac{1}{du_x+1}\times1+\frac{1}{du_x+1}\sum_{(x,y)\in g(x)} (E_{y\to x+1}+1)$

对上式化简即可。用到了前缀和。

---

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define ps second
#define pf first
 
 
#define rd read()
inline int read()
{
	int xx=0,ff=1;
	char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') ff=-1;c=getchar();}
	while(c>='0'&&c<='9') xx=xx*10+(c-'0'),c=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}
 
 
const int N=2e6+5;
const int M=5e5+5;
const int INF=1e9+5;
const int MOD=998244353;
bool f1;
int m,k,n,qzh;
 
int T,mn=INF,ans;
int f[N],du[N],q[N];

vector<int> e[N];

void add(int a,int b){
    e[a].push_back(b);
    du[a]++;
}

signed main() {
	int id=rd,n=rd,m=rd;
    for(int i=1;i<=m;i++){
        int a=rd,b=rd;
        add(a,b);
    }

    for(int x=1;x<=n;x++){
        f[x]=du[x]+1;
        for(auto v:e[x]){
            f[x]=((f[x]+(q[x-1]-q[v-1])%MOD)%MOD+MOD)%MOD;
        }
        q[x]=(q[x-1]+f[x])%MOD;
    }

    cout<<q[n]<<endl;
}
/*
2
3 2 3 6
*/
```

