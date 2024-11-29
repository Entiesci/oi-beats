# DP技巧

## Connected Component DP 依赖于差分的权值最优化问题

### 例题 #1 Ant Man

题面翻译

有 $n$ 个元素，第 $i$ 个元素有五个参数 $x_i,a_i,b_i,c_i,d_i$。

你需要求出一个 $1 \sim n$ 的排列 $p$，满足 $p_1 = s, p_n = e$，同时最小化这个排列的权值。

一个排列的权值为 $\sum_{i=1}^{n-1} f(p_i, p_{i+1})$，其中 $f(i,j)$ 的值有两种情况：

- 若 $i > j$，则 $f(i,j) = x_i - x_j + c_i + b_j$。

- 若 $i < j$，则 $f(i,j) = x_j - x_i + d_i + a_j$。

$n \le 5 \times 10^3$，$s \ne e$，$1 \le x_1 < x_2 < \cdots < x_n \le 10^9$，$1 \le a_i,b_i,c_i,d_i \le 10^9$。

---

这类dp我们定义$f_{i,j}$为从小到大插入第i个数字，并且当前的联通块数量为j时的最小权值。

我们考虑一开始有n个空位，我们从小到大插入数。每次插入时有4种可能：新建一个联通块，连接在某个联通块左侧/右侧，连接两个联通块。

每次插入一个数，就单独计算贡献（对于以及插入的一定比它小，没有插入的一定比它大）。

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
				f[i][j]=min(f[i][j],f[i-1][j]+x[i]+c[i]);//L
				f[i][j]=min(f[i][j],f[i-1][j-1]-x[i]+d[i]);//single
				
			}
		}else if (i==e){
			
			for(int j=1;j<=i;j++){
				//插入i后联通块数量为j
				f[i][j]=min(f[i][j],f[i-1][j]+x[i]+a[i]);//R
				f[i][j]=min(f[i][j],f[i-1][j-1]-x[i]+b[i]);//single
				
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

### 例题 #2 Skyscraper

Japanese Olympiad in Informatics 2015/2016 JOI Open Contes

 The International Olympiad in Informatics will be held in Tsukuba City, Japan. In order to prepare for IOI, we are planning to construct skyscraper buildings in the main street of Tsukuba City. Since we want to create a new sightseeing spot, the buildings have to satisfy the following conditions. We are planning to construct N buildings along a straight line in the main street. The heights of them are A1, A2, A3,..., AN. They are different from each other. Since the order of N buildings are not yet decided, we can permute their heights if necessary. We will decorate them for IOI. Due to the constraints of materials used for decoration, the sum of the absolute values of the differences of the heigts of two adjacent buildings must be less than or equal to L. In other words, if the heights of the buildings from one side of the main street are f1, f2, f3, . . . , fN, we must have |f1 − f2| + |f2 − f3| + ... + |fN−1 − fN| ≤ L. Here, |x| is the absolute value of x. Howmanypermutations of buildings satisfy the above condition

---

上面一题的削弱版，就是没有了a,b,c,d的版本。

## Open and Close Interval Trick

### 例题 #1 Increase Sequence

给定一个序列，可以对若干对区间$[l,r]$中的数+$1$，且保证任意两个区间的左右端点不重合（即$l_1$!=$l_2$且$r_1$!=$r_2$）。

最终要求序列中所有元素值都等于$h$，请输出总方案数对$1e9$+$7$取模后的结果。

$1$≤$n,h$≤$2000$

$0$≤$a_i$≤$2000$

---

可以考虑直接转移。先变为a_i=h-a_i，差分化。于是就是选择若干没有相同端点的区间，使得区间端点-1+1，让最后的数组全0的方案数。

发现对于一个为-1的右端点，可以与前面的任意一个没有匹配的1匹配。

```C++
// Problem: D. Increase Sequence
// Contest: Codeforces - Codeforces Round 266 (Div. 2)
// URL: https://codeforces.com/contest/466/problem/D
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
const int MOD=1e9+7;
/*

策略

k考虑变换a后就是区间减使得最后全0
改为差分数组，那么就是端点加减。发现每个端点最多+-一次，即每个数的abs<=1
问端点选择方案。cnt记当前左端点个数，每次到达一个右端点，可以任意选择左端点中的一个，方案数*cnt
如果是0
，可以作为一次左端点和一次右端点，而也可以跳过，因此*(cnt+1)
*/	


int a[N],cf[N];

signed main(){
	int n=rd,d=rd;
	for(int i=1;i<=n;i++){
		a[i]=d-rd;
	}
	
	for(int i=1;i<=n+1;i++){
		cf[i]=a[i]-a[i-1];
		if(abs(cf[i])>1){
			puts("0");return 0;
		}
	}
	int ans=1,cnt=0;
	for(int i=1;i<=n;i++){
		if(cf[i]==-1){
			ans=ans*cnt%MOD;
			cnt--;
		}if(cf[i]==0){
			ans=ans*(cnt+1)%MOD;
			
		}if(cf[i]==1){
			cnt++;
		}
	}
	
	
	cout<<ans<<endl;
}

```

### 例题 #2 Group Projects

题面翻译

有 $n$ 个学生，每个学生有一个能力值 $a_i$。现在要把这些学生分成一些(任意数量的)组，每一组的“不和谐度”是该组能力值最大的学生与能力值最小的学生的能力值的差。求所有不和谐度之和不超过 $K$ 的分组方案总数。

$1<=n<=200$ , $0<=K<=1000$

The second line contains $n$ space-separated integers $a_{i}$ ( $1<=a_{i}<=500$ ) — the time it takes the $i$ -th student to complete his/her independent piece of work.

---

先将a排序。我们发现排序可并不能优化分组（即分组还是不连续的），但是我们从前往后考虑时，我们就可以方便获取一个分组的最大值和最小值。于是我们就把当前的分组分类：已经完成的分组，缺少右端点的分组。

这里的分组，因为只和左右端点有关，所以我们也可以将其看作是线段，那么问题就是：每个点最多作为一次端点，求线段长度和≤k的分组方案。那么一个点就有4种情况：

- 作为线段左端点

- 作为右端点

- 作为一个中间点

- 作为一个[i,i]的线段

我们设f_{i,j,k}为考虑了前i个点，其中有j个未匹配的左端点，且当前的所有线段的总长度为k时的方案。

转移时，a_i对k的贡献为j\times(a_i-a_{i-1})，可以理解。其它的转移即可。
最后的答案就是所有k≤K的方案。

```C++
#include<bits/stdc++.h>
using namespace std;


const int MOD=1e9+7;

int f[202][202][1005];
int a[202];

signed main(){
    int n,K;
    cin>>n>>K;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }

    sort(a+1,a+n+1);
	f[0][0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=i;j++){
            for(int k=0;k<=K;k++){
                int w=(a[i]-a[i-1])*j;
                if(k+w>1000)break;//注意越界
                (f[i][j][k+w]+=f[i-1][j][k]%MOD)%=MOD;//作为线段[i,i]
                if(j>0)(f[i][j-1][k+w]+=1ll*f[i-1][j][k]*j%MOD)%=MOD;//作为j条未完成线段中的某一个的终点
                (f[i][j+1][k+w]+=f[i-1][j][k]%MOD)%=MOD;//起点 也要加w？注意w是对以前的j有贡献，起点只改变j，w还要对之前的未匹配线段有贡献。
                (f[i][j][k+w]+=1ll*f[i-1][j][k]*j%MOD)%=MOD;//作为j条未完成线段中的某一个的中点
            }
        }
    }

    int ans=0;
    for(int j=0;j<=K;j++)(ans+=f[n][0][j])%=MOD;
    

    cout<<ans<<endl;
}
```

## Change the object to dp

### 例题 #1 Gerald and Giant Chess

给定一个 $h\times w$ 大小的棋盘，其中有 $n$ 个点为黑色。
每次只能向右或向下移动，求从 $(1,1)$ 不经过黑色点到达 $(h,w)$ 的方案数。

The first line of the input contains three integers: $h,w,n$ — the sides of the board and the number of black cells ( $1<=h,w<=10^{5},1<=n<=2000$ ).

##  × 2,  + 1 trick



