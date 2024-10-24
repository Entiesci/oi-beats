# MEX

在信息学中，"mex" 是 "minimum excludant" 的缩写，它指的是在一个集合中不包含的最小非负整数。具体来说，对于任意一个非负整数集合 S，mex(S) 是第一个不属于 S 的非负整数。

例如，如果集合 S = {0, 1, 2, 3}，那么 mex(S) = 4，因为 4 是第一个不在集合 S 中的非负整数。

mex 函数在算法和竞赛编程中经常用于动态规划问题，尤其是在处理涉及状态的优化问题时。它经常出现在与集合的异或运算相关的问题中，因为 mex 函数与异或运算有着特定的关系，即对于任何两个集合 A 和 B，都有 mex(A) ⊕ mex(B) = mex(A ⊕ B)，其中 ⊕ 表示异或运算。

## 例题 #1 [EGOI2022] SubsetMex / 子集 mex

题目背景

Day 1 Problem A.

题面译自 [EGOI2022 subsetmex](https://stats.egoi.org/media/task_description/2022_subsetmex_en.pdf)。

题目描述

一个*可重集*是元素可以重复出现的集合。例如，$\{0,0,1,2,2,5,5,5,8\}$ 是一个可重集。

给定一个可重集 $S$，值域为 $\N$，和一个目标自然数 $n$（$n\notin S$），你的目标是通过重复进行若干次以下的操作，使得 $n\in S$：

1. 选择一个（可以为空的）子集 $T\subseteq S$，其中 $T$ 不包含重复元素。

2. 在 $S$ 中删除 $T$ 中的元素。（重复元素只删除一个。）

3. 将 $\operatorname{mex}(T)$ 插入 $S$，其中 $\operatorname{mex}(T)$ 是最小的不在 $T$ 中的自然数。$\operatorname{mex}$ 意味着“最小不包含”的值。

你需要求出最少的能使得 $n\in S$ 的操作次数。

由于 $|S|$ 可能很大，它将以一个大小为 $n$ 的列表 $(f_0,\ldots f_{n-1})$ 的形式给出，其中 $f_i$ 代表 $i$ 在 $S$ 中的出现次数。（请回忆 $n$ 是我们想要插入 $S$ 的元素。）

输入格式

第一行一个整数 $t$——数据组数。之后每两行描述一组数据：

- 每组数据的第一行一个整数 $n$，表示要插入 $S$ 的元素。

- 每组数据的第二行 $n$ 个整数 $f_0,f_1,\ldots,f_{n-1}$，按照上述方式描述了集合 $S$。

输出格式

对于每组数据，输出一行一个整数，表示最少操作次数。

**数据范围**

对于全部数据，$1\le t\le 200$，$1\le n\le 50$，$0\le f_i\le 10^{16}$。

---

dfs(x,k) 求出使得[0,x]的cnt都>=k的最少操作次数

从n开始搜索

如果a[x]>k，那么直接返回dfs(x-1,k)

否则我们就需要操作来使得a[x]=k

即dfs(x-1,k-a[x] +k)注意前面要贡献k-a[x]，还要保留自己的k

合并代价为k-a[x]

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


int a[N];

/*

*/

int dfs(int x,int k){
	if(!x)return 0;
	if(a[x]>=k)return dfs(x-1,k);
	return dfs(x-1,k+k-a[x])+k-a[x];
}

void solve(){
	int n=rd;
	for(int i=1;i<=n;i++){
		a[i]=rd;
	}
	cout<<dfs(n,1)+1<<endl;


}

signed main(){
	int T=rd;
	while(T--){
		solve();
	}

	return 0;
}
```

## 例题 #2 Informatics in MAC

[https://codeforces.com/contest/1935/problem/B](https://codeforces.com/contest/1935/problem/B)

在硕士援助中心，Nyam-Nyam 接受了一项信息学方面的家庭作业。

有一个长度为 $n$ 的数组 $a$ ，你想把它分成 $k> 1$ 个子段 $^{\dagger}$ ，使每个子段上的 $\operatorname{MEX} ^{\ddagger}$ 都等于相同的整数。

请帮助 Nyam-Nyam 找到合适的除法，或者确定不存在合适的除法。

$^{\dagger}$ 将数组划分为 $k$ 个子数段的定义是 $k$ 对整数 $(l_1, r_1), (l_2, r_2), \ldots, (l_k, r_k)$ ，使得 $l_i \le r_i$ 和每个 $1 \le j \le k - 1$ ， $l_{j + 1} = r_j + 1$ ，以及 $l_1 = 1$ 和 $r_k = n$ 。这些对表示子段本身。

数组中的 $^{\ddagger}\operatorname{MEX}$ 是不属于该数组的最小非负整数。

例如

- 数组 $[2, 2, 1]$ 的 $\operatorname{MEX}$ 是 $0$ ，因为 $0$ 不属于该数组。

- 数组 $[3, 1, 0, 1]$ 中的 $\operatorname{MEX}$ 是 $2$ ，因为 $0$ 和 $1$ 属于数组，而 $2$ 不属于数组。

- 数组 $[0, 3, 1, 2]$ 中的 $\operatorname{MEX}$ 是 $4$ ，因为 $0$ 、 $1$ 、 $2$ 和 $3$ 属于数组，而 $4$ 不属于数组。

---

```C++
#include <bits/stdc++.h>
#include <queue>
#define rep(l, r, i) for (int i = l, END##i = r; i <= END##i; ++i)
#define per(r, l, i) for (int i = r, END##i = l; i >= END##i; --i)
using namespace std;
#define pb push_back
#define mp make_pair
#define int long long
#define pii pair<int, int>
#define ps second
#define pf first

#define X(j) i[j]
#define Y(j) (dp[j] + (i[j] + L) * (i[j] + L))

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

const int N = 1e5 + 5;
const int INF = 1e18;
struct node {
  int a, b;
} e[N];

bool cmp(node a, node b) { return a.b < b.b; }
int n, a[N];
int cnt[N],h[N],q[N];
int stk[N], top;

signed main(){
  int T=rd;
  while(T--){
    int n=rd;
    for(int i=1;i<=n;i++){
      a[i]=rd;
    }
    int anc=0;
    for(int i=1;i<=n;i++){
      cnt[a[i]]++;
      stk[++top]=a[i];
      while(cnt[anc])anc++;
      q[i]=anc;
    }

    // for(int i=1;i<=n;i++)cerr<<q[i]<<' ';
    // cerr<<endl;

    while(top)cnt[stk[top--]]=0;

    int ans=0;
    for(int i=n;i;i--){
      cnt[a[i]]++;
      stk[++top]=a[i];
      while(cnt[ans])ans++;
      h[i]=ans;
    }
    while(top)cnt[stk[top--]]=0;
    int f=0;
    for(int i=1;i<n;i++){
      if(q[i]==h[i+1])f=i;
    }
    if(!f)cout<<-1<<endl;
    else{
      cout<<2<<endl;
      cout<<1<<' '<<f<<endl;
      cout<<f+1<<' '<<n<<endl;
    }
  }

}
```

## 例题 #3 Mex

小 G 曾经有一个 $0$ 到 $n$ 的排列（下标从 $0$ 开始），但他忘记了这个排列。

现在他想把这个排列找回来，他努力地回想，只能回想起关于这个排列的 $m$ 条信息，每条信息形如 $(l,r,val)$，表示区间 $[l,r]$ 的 ${\rm mex}$ 值为 $val$。一个区间的 ${\rm mex}$ 值是最小的没有在这个区间中出现的自然数。

小 G 把 $n$ 和这 $m$ 条信息告诉了你，希望你能帮他还原出一个排列，或者告诉他他的回忆出现了问题。

思路

代码

```C++

#include <bits/stdc++.h>
#include <queue>
#define rep(l, r, i) for (int i = l, END##i = r; i <= END##i; ++i)
#define per(r, l, i) for (int i = r, END##i = l; i >= END##i; --i)
using namespace std;
#define pb push_back
#define mp make_pair
#define int long long
#define pii pair<int, int>
#define ps second
#define pf first

#define X(j) i[j]
#define Y(j) (dp[j] + (i[j] + L) * (i[j] + L))

const bool enable_dbg = true;

template <typename T, typename... Args>
void dbg(bool flg, T s, Args... args)
{
    if constexpr (enable_dbg)
    {
        cout << s;
        if constexpr (sizeof...(Args))
            dbg(flg, args...);
    }
}

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
void write(int out)
{
    if (out < 0)
        putchar('-'), out = -out;
    if (out > 9)
        write(out / 10);
    putchar(out % 10 + '0');
}

const int N = 5e5 + 5;
const int INF = 1e18;
int n, m, pl[N], pr[N], ql[N], qr[N], z[N];
int l, r, val, q[N];
int fa[N];
int find(int x)
{
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}
void merge(int x, int y)
{
    x = find(x);
    y = find(y);
    fa[x] = y;
}
void solve()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; i++)
        pr[i] = n, ql[i] = n + 1;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &l, &r, &val);
        ql[val] = min(ql[val], l);
        qr[val] = max(qr[val], r);
        if (!val)
            z[l]++, z[r + 1]--;
        else
        {
            pl[val - 1] = max(pl[val - 1], l), pr[val - 1] = min(pr[val - 1], r);
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        pl[i] = max(pl[i], pl[i + 1]);
        pr[i] = min(pr[i], pr[i + 1]);
    }
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 0; i <= n; i++)
    {
        if (i) z[i] += z[i - 1];
        if (pl[0] <= i && pr[0] >= i && !z[i])
        {
            q[i] = 0;
            merge(i, i + 1);
            break;
        }
        if (i == n)
        {
            cout << "-1" << endl;
            return;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        bool f = false;
        for (int j = pl[i]; j <= pr[i]; j++)
        {
            j = find(j);
            if (j >= ql[i] && j <= qr[i])
            {
                j = qr[i];
                continue;
            } // 是否进入不合法区间
            if (j <= pr[i])
            {
                q[j] = i;
                merge(j, find(j) + 1);
                f = true;
                break;
            } // 找到空位
        }
        if (!f)
        {
            cout << "-1" << endl;
            return;
        }
    }
    for (int i = 0; i <= n; i++) cout << q[i] << " ";
    return;
}

signed main()
{
    int T = 1;
    while (T--)
    {
        solve();
    }
    return 0;
}
```

- Subtask 1(15 points)：$n,m\le 10$；

- Subtask 2(20 points)：$n,m\le 20$；

- Subtask 3(10 points)：$val=0$；

- Subtask 4(15 points)：数据随机生成；

- Subtask 5(10 points)：$n\le 10^5$；

- Subtask 6(30 points)：无特殊限制。

对于所有的数据满足：$1 \le n,m\le 5\times 10^5$，$ 0\le l,r\le n$，$0\le val\le n+1$。

Subtask4 的数据生成方式为：随机生成一个排列，再随机 $m$ 个区间求出它们的 ${\rm mex}$ 值作为条件。

本题输入输出量较大，请注意使用效率较高的 IO 方式。

