# 其他DP

## 依赖于差分的权值最优化问题

### 例题 #1 Ant Man

题面翻译

- 有 $n$ 个元素，第 $i$ 个元素有五个参数 $x_i,a_i,b_i,c_i,d_i$。

- 你需要求出一个 $1 \sim n$ 的排列 $p$，满足 $p_1 = s, p_n = e$，同时最小化这个排列的权值。

- 一个排列的权值为 $\sum_{i=1}^{n-1} f(p_i, p_{i+1})$，其中 $f(i,j)$ 的值有两种情况：

    - 若 $i > j$，则 $f(i,j) = x_i - x_j + c_i + b_j$。

    - 若 $i < j$，则 $f(i,j) = x_j - x_i + d_i + a_j$。

- $n \le 5 \times 10^3$，$s \ne e$，$1 \le x_1 < x_2 < \cdots < x_n \le 10^9$，$1 \le a_i,b_i,c_i,d_i \le 10^9$。

---

这类dp我们定义f_{i,j}为从小到大插入第i个数字，并且当前的联通块数量为j时的最小权值。



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


const int N = 5e3 + 5;
const int INF = 2e9;
const int M = 1e7;
const int MOD = 1e9 + 7;


int d[N];
int x[N];
int a[N];
int f[N][N];//0:M 1:L 2:R
int b[N];
int c[N];

void solve(){
	int n=rd;
	int s=rd,e=rd;
	for(int i=1;i<=n;i++){
		x[i]=rd;
	}
	for(int i=1;i<=n;i++)a[i]=rd;
	for(int i=1;i<=n;i++)b[i]=rd;
	for(int i=1;i<=n;i++)c[i]=rd;
	for(int i=1;i<=n;i++)d[i]=rd;

	memset(f,0x3f3f,sizeof f);
	f[0][0]=0;

	for(int i=1;i<=n;i++){

		if(i==s){
			for(int j=1;j<=i;j++){
				//插入i后联通块数量为j
				f[i][j]=min(f[i][j],f[i-1][j]+x[i]+c[i]);//Lok
				f[i][j]=min(f[i][j],f[i-1][j-1]-x[i]+d[i]);//singleok
				
			}
		}else if (i==e){
			
			for(int j=1;j<=i;j++){
				//插入i后联通块数量为j
				f[i][j]=min(f[i][j],f[i-1][j]+x[i]+a[i]);//Rok
				f[i][j]=min(f[i][j],f[i-1][j-1]-x[i]+b[i]);//singleok
				
			}
		}else{
			for(int j=1;j<=i;j++){
				//插入i后联通块数量为j
				if(i<s||j>1)f[i][j]=min(f[i][j],f[i-1][j]+x[i]+c[i]-x[i]+b[i]);//L 
				//注意适用条件，防止超出端点！
				if(i<e||j>1)f[i][j]=min(f[i][j],f[i-1][j]+x[i]+a[i]-x[i]+d[i]);//R
				f[i][j]=min(f[i][j],f[i-1][j+1]+x[i]+a[i]+x[i]+c[i]);//M
				if(j>((i>s)+(i>e)))f[i][j]=min(f[i][j],f[i-1][j-1]-x[i]+d[i]-x[i]+b[i]);//single
				
			}

		}
	}


	cout<<f[n][1]<<endl;
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

