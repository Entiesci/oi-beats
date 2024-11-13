# 区间DP

摘抄[2024暑假S组专题2-DP2-区间dp](https://flowus.cn/617c0599-205c-439f-bd7d-829583507926)

区间dp通过子区间的dp信息，得出更大的区间的dp信息，最后得到全局最优解。

## 例题 #1 区间回文串

题目描述

给你一个字符串s由小写字母组成，有q组询问，每组询问给你两个数，l和r，问在字符串区间l到r的字串中，包含多少回文串。

输入格式

第1行，给出s，s的长度小于5000

第2行给出q(1<=q<=10^6)

第2至2+q行 给出每组询问的l和r

输出格式

输出每组询问所问的数量。





样例输入1

```C++
caaaba
5
1 1
1 4
2 3
4 6
4 5
```



样例输出1

```C++
1
7
3
4
2
```

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

#define rep(i, l, g) for (int i = l, END##i = g; i <= END##i; ++i)
#define per(i, g, l) for (int i = g, END##i = l; i >= END##i; --i)
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


const int N = 3e3 + 5;
const int INF = 1e18;
const int M = 1e7;
const int MOD = 1e9 + 7;

int f[N][N],g[N][N];

string s;

void solve(){
    cin>>s;
    int l=s.size();
    for(int i=0;i<l;i++){
        f[i][0]=0,g[i][0]=1;
        f[i][1]=1,g[i][1]=1;
    }

    for(int i=2;i<=l;i++){
        for(int j=0;j<=l-i;j++){
            if(s[i+j-1]==s[j]&&g[j+1][i-2]){
                f[j][i]=f[j][i-1]+f[j+1][i-1]-f[j+1][i-2]+1;
                g[j][i]=1;
            }else{
                f[j][i]=f[j][i-1]+f[j+1][i-1]-f[j+1][i-2]+0;
                g[j][i]=0;
            }
        }
    }

    int t=rd;
    while(t--){
        int a=rd,b=rd;
        int len=b-a+1;
        cout<<f[a-1][len]<<endl;
    }
}

signed main() {
    // freopen(".in","g",stdin);
    // freopen(".in","w",stdout);

    int T=1;
    while(T--){
    	solve();
    }
    return 0;
}
```

## 例题 #2 括号构造

给出合法序列的定义:
1.空序列是合法序列。
2.如果S是合法序列,那(S)和[S]也是合法序列。
3.如果A和B是合法序列，那么AB也是合法序列。
例如,下面的字符串都是合法序列：
(),[],(()),([]),()[],()[()]
这几个则不是合法序列：
(,[,],)(,([))
现在，给出一些由"(",")","[","]"构成的序列，请添加尽量少的括号，得到一个合法序列

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
int read() {
    int xx = 0, ff = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            ff = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') xx = xx * 10 + (ch - '0'), ch = getchar();
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
const char el = '\n';
const bool enable_dbg = 1;
template <typename T, typename... Args>
void dbg(T s, Args... args) {
    if constexpr (enable_dbg) {
        cerr << s;
        if (1)
            cerr << ' ';
        if constexpr (sizeof...(Args))
            dbg(args...);
    }
}

#define zerol = 1
#ifdef zerol
#define cdbg(x...)            \
    do {                      \
        cerr << #x << " -> "; \
        err(x);               \
    } while (0)
void err() { cerr << endl; }
template <template <typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) {
    for (auto v : a) cerr << v << ' ';
    err(x...);
}
template <typename T, typename... A>
void err(T a, A... x) {
    cerr << a << ' ';
    err(x...);
}
#else
#define dbg(...)
#endif

const int N = 3e2 + 5;
const int INF = 1e18;
const int M = 1e7;
const int MOD = 1e9 + 7;

string s, f[N][N];

void solve() {
    cin >> s;
    int n = s.size();
    s = " " + s;
    for (int i = 1; i <= n; i++) {
        if ((s[i] == '(') || s[i] == ')')
            f[i][i] = "()";
        else
            f[i][i] = "[]";  //缺省匹配
    }

    for (int l = 2; l <= n; l++) {
        for (int j = 1; j + l - 1 <= n; j++) {
            int r = l + j - 1;
            if (s[j] == '(' && s[r] == ')' || s[j] == '[' && s[r] == ']')
                f[j][r] = s[j] + f[j + 1][r - 1] + s[r];
            for (int k = j; k < r; k++) {
                string t = f[j][k] + f[k + 1][r];
                if ((f[j][r] == "") || t.size() < f[j][r].size())
                    f[j][r] = t;
            }
        }
    }

    cout << f[1][n];
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".in","w",stdout);

    int T = 1;
    while (T--) {
        solve();
    }
    return 0;
}
```

## 例题 #3 俄罗斯套娃

题目描述

是一些从外到里大小递减的传统的俄罗斯木头玩偶组成的。当你打开一个俄罗斯套娃时，里面就会露出一个同样的俄罗斯套娃，再打开，就会再露出一个，不断重复。

俄罗斯的俄罗斯套娃博物馆最近收藏了一些外形相似的俄罗斯套娃集,只是里面嵌套的玩偶数量不相等。不幸的是，有一群过分热情的（和明显无人监督的）孩子们拆了他们，并放在一行上。有n个玩偶在一上，每个都有一个整数的大小，你需要重新组装套娃集，你既不知道套娃集的数量，也不知道某个套娃集内玩偶的数量，你只知道一个完好的套娃集内的玩偶大小是从1到某个数字m在组装套娃集时，你必须遵守下列规则：

1.你只能将一个玩偶或者套娃集放入一个更大的玩偶中

2.你只能把相邻两个俄罗斯套娃组合在一起

3.已经被合并的玩偶是不能再重新拆出来的。

你的时间很宝贵，你只想尽快的组装好。唯一需要耗时的部分为打开一个玩偶并马上关上它。所以你要尽可能少的做这种操作。

比如说：合并[1,2,6]与[4]，你需要将大小为4和6的两个玩偶拆开。合并[1,2,5]与[3,4]代价为3。

求将n个玩偶重新拼成一些完好的俄罗斯套娃的最小代价。

输入格式

第一行一个数n，第二行包含n个数，依次表示每个玩偶的大小。

如果答案存在，输出一个数表示将n个玩偶重新拼成一些完好的俄罗斯套娃的最小代价。否则输出“Impossible”

样例输入1

```C++
7
1 2 1 2 4 3 3
```

样例输出1

```C++
Impossible
```

样例输入2

```C++
7
1 2 3 2 4 1 3
```

样例输出2

```C++
7
```

数据限制

1<=n<=500 , 1<=玩偶大小<=500

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
void err(T<t> a, A... x) { for (auto cnt: a) cerr << cnt << ' '; err(x...); }
template<typename T, typename... A>
void err(T a, A... x) { cerr << a << ' '; err(x...); }
#else
#define dbg(...)
#endif


const int N = 3e3 + 5;
const int INF = 1e18;
const int M = 1e7;
const int MOD = 1e9 + 7;


int a[N];
int f[N][N];

int mn[N];
int cnt[N];
int ans[N];


void solve(){
    int n=rd;
    a[0]=INF;
    for(int i=1;i<=n;i++){
        a[i]=rd;
        f[i][i]=0;
    }
    // memset(f,0x3f3f,sizeof f);
    for(itn i=1;i<n;i++){
        for(int l=1,r=i+1;r<=n;l++,r++){
            f[l][r]=INF;

            int t=INF;
            mn[r+1]=INF;
            for(int j=1;j<=n;j++){
                cnt[j]=0;
            }

            for(int j=r;j>=l;j--){
                mn[j]=min(mn[j+1],a[j]);//后缀min
                cnt[a[j]]++;
            }

            for(itn j=1;j<=n;j++){
                cnt[j]+=cnt[j-1];
            }

            for(int j=l;j<r;j++){
                t=min(t,a[j]);
                f[l][r]=min(f[l][r],f[l][j]+f[j+1][r]+(r-l+1)-cnt[max(t,mn[j+1])-1]);
            }
        }
    }


    // memset(ans,0x3f3f,sizeof ans);
    memset(cnt,0,sizeof cnt);


    for(int i=1;i<=n;i++){
        ans[i]=INF;
        for(int j=1;j<=n;j++)cnt[j]=0;
        for(int j=i;j;j--){
            cnt[a[j]]++;;
            int t=0;
            for(int k=1;k<=i-j+1;k++){
                if(cnt[k]!=1){
                    t=1;break;
                }
            }

            if(!t)ans[i]=min(ans[i],ans[j-1]+f[j][i]);
        }
    }

    if(ans[n]>=INF){
        cout<<"Impossible";
        return ;
    }
    cout<<ans[n]<<endl;
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

## 练习 #1 [CSP-S 2021] 括号序列

题目描述

小 w 在赛场上遇到了这样一个题：一个长度为 $n$ 且符合规范的括号序列，其有些位置已经确定了，有些位置尚未确定，求这样的括号序列一共有多少个。

身经百战的小 w 当然一眼就秒了这题，不仅如此，他还觉得一场正式比赛出这么简单的模板题也太小儿科了，于是他把这题进行了加强之后顺手扔给了小 c。

具体而言，小 w 定义“超级括号序列”是由字符 `(`、`)`、`*` 组成的字符串，并且对于某个给定的常数 $k$，给出了“符合规范的超级括号序列”的定义如下：

1. `()`、`(S)` 均是符合规范的超级括号序列，其中 `S` 表示任意一个仅由**不超过** $\bm{k}$ **个**字符 `*` 组成的非空字符串（以下两条规则中的 `S` 均为此含义）；

2. 如果字符串 `A` 和 `B` 均为符合规范的超级括号序列，那么字符串 `AB`、`ASB` 均为符合规范的超级括号序列，其中 `AB` 表示把字符串 `A` 和字符串 `B` 拼接在一起形成的字符串；

3. 如果字符串 `A` 为符合规范的超级括号序列，那么字符串 `(A)`、`(SA)`、`(AS)` 均为符合规范的超级括号序列。

4. 所有符合规范的超级括号序列均可通过上述 3 条规则得到。

例如，若 $k = 3$，则字符串 `((**()*(*))*)(***)` 是符合规范的超级括号序列，但字符串 `*()`、`(*()*)`、`((**))*)`、`(****(*))` 均不是。特别地，空字符串也不被视为符合规范的超级括号序列。

现在给出一个长度为 $n$ 的超级括号序列，其中有一些位置的字符已经确定，另外一些位置的字符尚未确定（用 `?` 表示）。小 w 希望能计算出：有多少种将所有尚未确定的字符一一确定的方法，使得得到的字符串是一个符合规范的超级括号序列？

可怜的小 c 并不会做这道题，于是只好请求你来帮忙。

对于 $100 \%$ 的数据，$1 \le k \le n \le 500$。

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

const int N = 1e3 + 5;
const int INF = 1e18;
const int M = 1e7;
const int MOD = 1e9 + 7;

int f[N][N][6];
int n,K;
string s;

int cmp(int a,int b){
    if((s[a]=='('||s[a]=='?')&&(s[b]==')'||s[b]=='?'))return 1;
    return 0;
}

void momo(int l,int r){
    for(int i=0;i<=5;i++){
        f[l][r][i]%=MOD;
    }
}

void solve(){
    n=rd,K=rd;
    cin>>s;
    s=" "+s;
    for(int i=1;i<=n;i++)f[i][i-1][0]=1;
    rep(len,1,n){
        rep(l,1,n-len+1){
            int r=l+len-1;
            if(len<=K) f[l][r][0]=f[l][r-1][0]&&(s[r]=='*'||s[r]=='?');
            momo(l,r);
            if(len>=2){
                if(cmp(l,r)) f[l][r][1]=(f[l+1][r-1][0]+f[l+1][r-1][2]+f[l+1][r-1][3]+f[l+1][r-1][4]);
                rep(i,l,r-1){
                    f[l][r][2]+=f[l][i][3]*f[i+1][r][0];
                    f[l][r][3]+=(f[l][i][2]+f[l][i][3])*f[i+1][r][1];
                    f[l][r][4]+=(f[l][i][4]+f[l][i][5])*f[i+1][r][1];
                    f[l][r][5]+=f[l][i][4]*f[i+1][r][0];
                    momo(l,r);
                }
            }
            f[l][r][5]+=f[l][r][0];
            f[l][r][3]+=f[l][r][1];
            momo(l,r);
        }
    }


    cout<<f[1][n][3]<<endl;

}

signed main() {
    int T=1;
    while(T--){
    	solve();
    }
    return 0;
}
```

## 环形DP

### 例题 #1 [USACO05JAN] Naptime G

题目描述

贝茜是一只非常缺觉的奶牛．她的一天被平均分割成 $N$ 段（$3 \leq N \leq 3830$），但是她要用其中的 $B$ 段时间（$2 \leq B \lt N$）睡觉。每段时间都有一个效用值 $U_i$（$0 \leq U_i \leq 2 \times 10^5$），只有当她睡觉的时候，才会发挥效用。

有了闹钟的帮助，贝茜可以选择任意的时间入睡，当然，她只能在时间划分的边界处入睡、醒来。

贝茜想使所有睡觉效用的总和最大。不幸的是，每一段睡眠的第一个时间阶段都是“入睡”阶段，而旦不记入效用值。

时间阶段是不断循环的圆（一天一天是循环的嘛），假如贝茜在时间 $N$ 和时间 $1$ 睡觉，那么她将得到时间 $1$ 的效用值。

输入格式

第一行两个整数 $N,B$。

接下来 $N$ 行，每行一个整数，表示第 $i$ 个时段的效用值。

---

环形dp通常有两种解决方法

- 破环为链，复制一份置于其后。

这样做可以使得我们把环形dp转化为区间dp，最后取长度为n的所有答案中的最优值即可。

- 枚举边界情况

这样做我们就需要分类讨论，但是也可以解决环形这条麻烦。

本题我们发现，因为区间dp是 $O(n^2)$的，不允许我们采用方法1，所以我们就采用方法2.

我们进行两次dp，第一次强制不选第n和第1个小时。第二次强制选第n和第1个小时。然后在最后的答案中选择最大值即可。

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
#define pii pair<int, int>
#define ps second
#define pf first
#define ull unsigned long long

#define itn int
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
    if(1)cerr<<' ';
    cerr << s;
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


const int N = 3.9e3 + 5;
const int INF = 1e18;
const int M = 1e7;
const int MOD = 1e9 + 7;

bool FLA;



 itn f[N][N][2];
 itn a[N];
 int n,m;


bool FLB;



void runDp(){
	for(itn i=2;i<=n;i++){
		for(int j=0;j<=m;j++){
			f[i][j][0]=max(f[i-1][j][0],f[i-1][j][1]);
			if(j-1>=0)f[i][j][1]=max(f[i-1][j-1][0],f[i-1][j-1][1]+a[i]);
		}
	}
}

void solve(){
    cerr<<((&FLB)-(&FLA))/1024.0/1024.0<<" Mib"<<endl;
    
    n=rd,m=rd;
    for(int i=1;i<=n;i++){
    	a[i]=rd;
	}
	
	memset(f,-0x3f3f,sizeof f);
	f[1][0][0]=0;
	f[1][1][1]=0;
	
	runDp();
	
	itn ans=max(f[n][m][0],f[n][m][1]);
	
	memset(f,-0x3f3f,sizeof f);
	
	f[1][1][1]=a[1];
	runDp();
	
	ans=max(ans,f[n][m][1]);
	
	
	cout<<ans<<endl;
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

## 二维区间DP

### 例题 #1 切蛋糕 Cake slicing

有一个n行m列(1<=n,m<=20)的网络蛋糕上有k个樱桃。每次可以用一刀沿着网络线把蛋糕切成两块，并且只能够直切不能拐弯。要求最后每一块蛋糕上恰好有一个樱桃，且切割线总长度最小。

输入输出格式

输入格式:每次输入有若干组数据。每组数据第一行有三个正整数n m k(行，列，樱桃个数)，之后的k行每行两个正整数(樱桃的坐标)

输出格式:输出有若干行，对应每组数据。每行输出两个正整数(id,最小的切割长度)

---

二维区间dp，通常的合并方式（转移方式）是将一个大矩形分割为两个小矩形来转移。状态我们需要表示为当前负责的区间（矩形）

算法实现我们通常用记忆化搜索（dfs）

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

#define cdbg(x...) do { cerr << #x << " -> "; err(x); } while (0)
void err() { cerr << endl; }
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) { for (auto v: a) cerr << v << ' '; err(x...); }
template<typename T, typename... A>
void err(T a, A... x) { cerr << a << ' '; err(x...); }


const int N = 3e1 + 5;
const int INF = 1e18;
const int M = 1e7;
const int MOD = 1e9 + 7;

int x[N];
int y[N];
int f[N][N][N][N];
int p[N][N];

inline int check(int x,int y,int a,int b){
    return p[a][b]-p[a][y-1]-p[x-1][b]+p[x-1][y-1];
}

int dfs(int x,int y,int a,int b){
    if(INF>f[x][y][a][b])return f[x][y][a][b];
    if(check(x,y,a,b)==1)return f[x][y][a][b]=0;

    for(int i=x;i<a;i++){
        if(check(x,y,i,b)>=1&&check(i+1,y,a,b)>=1){
            f[x][y][a][b]=min(f[x][y][a][b],dfs(x,y,i,b)+dfs(i+1,y,a,b)+b-y+1);
        }
    }

    
    for(int i=y;i<b;i++){
        if(check(x,y,a,i)>=1&&check(x,i+1,a,b)>=1){
            f[x][y][a][b]=min(f[x][y][a][b],dfs(x,y,a,i)+dfs(x,i+1,a,b)+a-x+1);
        }
    }

    return f[x][y][a][b];
}

void solve(){
    int n,m,K;
    int T=0;
    while(cin>>n>>m>>K){
        T++;
        printf("Case %lld: ",T);
        memset(p,0,sizeof p);
        for(int i=1;i<=n;i++){
            int x=rd,y=rd;
            p[x][y]=1;
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                p[i][j]+=p[i-1][j]+p[i][j-1]-p[i-1][j-1];
            }
        }

        memset(f,0x3f3f,sizeof f);

        cout<<dfs(1,1,n,m)<<endl;
    }



}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);

    int T=1;
    while(T--){
    	solve();
    }
    return 0;
}
```

## 练习

[模板 | [NOI1995] 石子合并](%E5%8C%BA%E9%97%B4DP/%E6%A8%A1%E6%9D%BF++++NOI1995++%E7%9F%B3%E5%AD%90%E5%90%88%E5%B9%B6%20d7b6161d-e72d-4d33-9c3b-d4f4e6890c33.md)

[Sequence of Balls](%E5%8C%BA%E9%97%B4DP/Sequence+of+Balls%20d5dc4ce8-0195-4297-b5fe-758c2dfc4a58.md)

