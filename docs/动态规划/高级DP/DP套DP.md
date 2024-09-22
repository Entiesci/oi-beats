

# DP套DP

在了解dp套dp之前，我们先来学习一个dp模式。

也就是我们的状态机dp。通常的状态机有AC自动机。此时我们就先抛出一个例题：

> 问长度为n的，且不包含给出字符串T_i的字符串S的数量。

这道题我们可以对集合T建立一个AC自动机，然后我们就可以所以状态 dp_{i,j}为考虑到S的第i位，且当前第i个字符在状态机的第j个节点上。

这样我们就可以解决这个问题了。



那么dp套dp就是将状态机替换为另一个dp（通常是很经典的模型，如LCS,LIS）。接下来我们推荐过遇到例题来介绍dp套dp。

## 例题 #1 [TJOI2018] 游园会

题目描述

小豆参加了 NOI 的游园会，会场上每完成一个项目就会获得一个奖章，奖章只会是 $\texttt{N}$、$\texttt{O}$、$\texttt{I}$ 的字样。在会场上他收集到了 $K$ 个奖章组成的串。兑奖规则是奖章串和兑奖串的最长公共子序列长度为小豆最后奖励的等级。现在已知兑奖串长度为 $N$，并且在兑奖串上不会出现连续三个奖章为 $\texttt{NOI}$，即奖章中不会出现子串 $\texttt{NOI}$。现在小豆想知道各个奖励等级会对应多少个不同的合法兑奖串。

输入格式

第一行两个数，$N, K$ 分别代表兑奖串S的长度，小豆收集的奖章串T的长度（$N\leq1000,K\leq15$）。

第二行一共 $K$ 个字符，表示小豆得到的奖章串。

输出格式

一共 $K+1$ 行，第行表示小豆最后奖励等级为 $i-1$ 的不同的合法兑奖串的个数，可能这个数会很大，结果对 $10^9+7$ 取模。

- 对于 $100\%$ 的数据，$N\leq1000,K\leq15$。

---

首先既然是计数类dp，那么我们即任意想到定义 dp_{i,j}为考虑S的前i个字符，且与T的匹配长度为j的方案数。但是怎么样转移呢？

我们枚举S的第i+1个字符，然后比较S,T末尾的字符是否相同不就可以转移了吗？这是一个很naive的想法，因为我们的S_{i+1}为什么不能和T_{i+1} 之前的字符去匹配呢？

所以我们的第2维不可以这样定义，我们必须要定义的信息应该是包含了当前的匹配信息的。如果我们有一种“LCS自动机”，那么我们就可以用上面的节点来代表这个状态，但是我们没有。

那么我们可否找到替代品？我们思考：LCS自动机就是在我们向字符串末尾加上一个字符时，战斗机上的指针会跳到下一个节点上去，表示新的状态。我们发现LCS本身就是一个dp，我们可以假设我们已经知道了当前枚举的S，那么我们就可以对其和T建立LCS模型，记数组g_i表示当前S,T的LCS匹配状态，具体来说就是我们当前枚举的S，它和T的前i项的匹配情况。

如果我们可以把这个g数组作为状态填入f数组的第二维，那么我们的这题问题就有解决的希望了。具体来说，我们枚举i，枚举g，那么我们在枚举S_{i+1}填的字符时，就知道了g数组可以转移到的新状态g'。为了求出g'，我们有需要一个**内层dp。**

到此，dp套dp的模型就呈现出来了。现在我们要考虑如何记录g作为一个状态。记录原始数组是不可能的，但是我们注意到g的长度≤15，加之g相邻两项的差值≤1，所以我们可以记g的差分数组进行状态压缩。

在转移时，我们把g还原，然后依据枚举的新加入字符，dp得出新的g'，然后转移即可。

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
//#define int long long
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


const int N = 1e3 + 5;
const int INF = 111;
const int M = 1e7;
const int MOD = 1e9 + 7;


int f[2][35777][3];
int n,m;
int g[N];
string t;
int ans[N];
int r[N];

void process(int id,int gg,char c,int fr,int k){

	//当前填到S的id给字符，LCS匹配数组为g，将要填入字符c，答案从fr处转移来。
	for(int i=1;i<=m;i++){
		g[i]=g[i-1]+((gg>>(m-i))&1);//!!
		// cdbg(g[i]);
	}

	// for(int i=m;i;i--){
	// 	if(c==t[i])g[i]=max(g[i],g[i-1]+1);
	// }
	for(int i=1;i<=m;i++){
		r[i]=max(max(r[i-1],g[i]),g[i-1]+1*(c==t[i]));
	}

	int res=0;

	for(int i=1;i<=m;i++){
		res<<=1;
		res+=r[i]-r[i-1];
	}


	f[id][res][k]+=fr;
	f[id][res][k]%=MOD;

}

int calc(int gg){
	for(int i=1;i<=m;i++){
		g[i]=g[i-1]+((gg>>(m-i))&1);
	}

	return g[m];
}

void solve(){
	n=rd,m=rd;
	cin>>t;
	t=" "+t;


	f[0][0][0]=1;

	for(int i=0;i<n;i++){
		memset(f[(i^1)&1],0,sizeof f[(i^1)&1]);
		for(int j=0;j<(1<<m);j++){
			if(f[i&1][j][0]){
				process((i^1)&1,j,'N',f[i&1][j][0],1);
				process((i^1)&1,j,'O',f[i&1][j][0],0);
				process((i^1)&1,j,'I',f[i&1][j][0],0);
			}if(f[i&1][j][1]){
				process((i^1)&1,j,'N',f[i&1][j][1],1);
				process((i^1)&1,j,'O',f[i&1][j][1],2);
				process((i^1)&1,j,'I',f[i&1][j][1],0);

			}if(f[i&1][j][2]){
				process((i^1)&1,j,'N',f[i&1][j][2],1);
				process((i^1)&1,j,'O',f[i&1][j][2],0);
				//填I不合法
			}
		}
	}


	for(int i=0;i<(1<<m);i++){
		for(int j=0;j<=2;j++){
			(ans[calc(i)]+=f[n&1][i][j])%=MOD;
			
		}
	}

	for(int i=0;i<=m;i++){
		cout<<ans[i]<<endl;
	}
}

signed main() {
    //  freopen("P2619_3.in","r",stdin);
    // freopen("center.out","w",stdout);

    int T=1;
    while(T--){
    	solve();
    }
    return 0;
}
```

