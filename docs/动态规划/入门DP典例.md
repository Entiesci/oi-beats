DP | 入门典例

# 目录

- 序列dp问题

- 数字金字塔问题

- 树形dp入门

- 背包入门

# LCIS 最长公共上升子序列

## 题面翻译

求两个串的最长公共上升子序列。输出长度与序列。

The first line contains an integer $n$ ( $1<=n<=500$ ) — the length of the first sequence. The second line contains $n$ space-separated integers from the range $[0,10^{9}]$ — elements of the first sequence. The third line contains an integer $m$ ( $1<=m<=500$ ) — the length of the second sequence. The fourth line contains $m$ space-separated integers from the range $[0,10^{9}]$ — elements of the second sequence.

---

```C++
#include <bits/stdc++.h>
#define rep(l, r, i) for (int i = l, END##i = r; i <= END##i; ++i)
#define per(r, l, i) for (int i = r, END##i = l; i >= END##i; --i)
using namespace std;
#define pb push_back
// #define mpy make_pair
#define int long long
#define pii pair<int, int>
#define ps b
#define pf a

#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)

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

const int N = 1e3 + 15;
const int INF = 1e9 + 5;
const int MOD = 1e9 + 7;
const int M = N * 21;

int n,m,a[N],b[N];
int s[N],top;
int pre[N][N],f[N][N];
    int sp,ans=0;



signed  main(){
	n=rd;
	for(int i=1;i<=n;i++)a[i]=rd;
    m=rd;
	for(int i=1;i<=m;i++)b[i]=rd;
    a[0]=b[0]=-1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i]==b[j]){
                for(int k=0;k<j;k++){
                    if(a[i]>b[k]&&f[i][j]<f[i-1][k]+1){
                        f[i][j]=f[i-1][k]+1;
                        pre[i][j]=k;
                    }
                }
            }else{
                f[i][j]=f[i-1][j];
                pre[i][j]=pre[i-1][j];

            }
        }
    }
    for(int j=1;j<=m;j++){
        if(ans<f[n][j])ans=f[n][j],sp=j;
    }
    cout<<ans<<endl;
    while(sp){
        s[++top]=b[sp];
        sp=pre[n][sp];
    }
    while(top)cout<<s[top--]<<' ';

}
```

# LCS 最长公共子序列

【模板】最长公共子序列

题目描述

给出 $1,2,\ldots,n$ 的两个排列 $P_1$ 和 $P_2$ ，求它们的最长公共子序列。

---

我们先设计dp状态，f_{i,j}表示P_1以i结尾，P_2以j结尾时的LCS长度。那么有转移

- 若P_1[i]=P_2[j]，那么f_{i,j}=f_{i-1-,j-1}+1

- 否则在f_{i-1,j},f_{i,j-1}中取最大值

实现

两层循环即可。

基本的内容不要忘！

```C++
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
int ans,n,p1[MAXN],p2[MAXN],dp[MAXN],web[MAXN];
int main(){
	cin>>n;
	
	for(int i=1;i<=n;i++){
		cin>>p1[i];web[p1[i]]=i;
	}
	for(int i=1;i<=n;i++){
		cin>>p2[i];dp[i]=0x7f;
	}
	dp[0]=0;
	for(int i=1;i<=n;i++){
		int l=0,r=ans,mid;
		if(web[p2[i]]>dp[ans])dp[++ans]=web[p2[i]];
		else{
			while(l<r){
				mid=(l+r)/2;
				if(dp[mid]>web[p2[i]])r=mid;
				else l=mid+1;
			}
			dp[l]=min(web[p2[i]],dp[l]);
		}
	
	}
	cout<<ans;
	return 0;
} 
```

## 输入格式

第一行一个整数N，表示我们要将1到N插入序列中。

接下是N个数字，第k个数字Xk，表示我们将k插入到位置Xk（0<=Xk<=k-1,1<=k<=N）

## 输出格式

N行，第i行表示i插入Xi位置后序列的最长上升子序列的长度是多少。

## 样例 #1

### 样例输入 #1

```C++
3
0 0 2
```

### 样例输出 #1

```C++
1
1
2
```

## 提示

100%的数据 n<=100000

- 对于 $50\%$ 的数据， $n \le 10^3$；

- 对于 $100\%$ 的数据， $n \le 10^5$。

# LIS 最长上升子序列

## 最长上升子序列

这是一个简单的动规板子题。

给出一个由 $n(n\le 5000)$ 个不超过 $10^6$ 的正整数组成的序列。请输出这个序列的**最长上升子序列**的长度。

最长上升子序列是指，从原序列中**按顺序**取出一些数字排在一起，这些数字是**逐渐增大**的。

```C++
int n,m,a[N],f[N];
int s[N],top;

signed main(){
    n=rd;
    f[0]=1;
    for(int i=1;i<=n;i++){
        a[i]=rd;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            if(a[i]>a[j])f[i]=max(f[i],f[j]+1);
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)ans=max(ans,f[i]);
    cout<<ans+1<<endl;
}
```

## 图上LIS | Pathwalks

给定 $n$ 个点 $m$ 条边的有向图，可能不连通，可能有重边，也可能会有自环。求最长的路径(可以经过重复节点)，使得这条路径的编号和权值都**严格**单调递增，其中编号指输入的顺序。路径的长度是指经过边的数量。

输入格式

第一行两个整数 $n,m$。

第二行到第 $m+1$ 行，每行三个整数 $a,b,k$，表示顶点 $a$ 与顶点 $b$ 有一条边相连，边权为 $k$。

输出格式

一行一个整数，表示最长的路径的长度。

$1\leq n,m\leq10^5$，$0\le w_i\le10^5$。

retranslated by @皎月半洒花。

---

因为严格，所以每一条边至多被选中一次，因此不用考虑后效，可以dp

```C++
/*
CB Ntsc111
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned int
#define pii pair<int, int>
#define pf first
#define ps second

#define err cerr << "Error"
#define rd read()
// #define nl putc('\n')
#define ot write
#define nl putchar('\n')
int rd {
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

const int INF = 1e18;
const int N = 1e5 + 5;
const int M = 1e6 + 5;
const int maxlog = 10;

int ans;
int res;
int n, m;

map<int, int> mp[N];

int dfs(int x, int v) {
  int res = 0;
  auto p = mp[x].lower_bound(v);
  res = (p == mp[x].begin()) ? 0 : ((--p)->second);
  return res;
}

signed main() {
  n = rd, m = rd;
  for (int i = 1; i <= m; ++i) {
    int x = rd, y = rd, z = rd;
    res = dfs(x, z);
    ++res;
    if (res > dfs(y, z)) {
      auto p = mp[y].lower_bound(z);
      mp[y][z] = res;
      for (auto q = p; q != mp[y].end(); q = mp[y].erase(q)) {
        if ((q->second) > res)
          break;
      }
    }
    ans = std ::max(ans, res);
  }
  printf("%d\n", ans);
  return 0;
}

/*
4
()()
1 -1 5 11

4
()()
1 6 5 11
*/
```

## 不断插入的多次询问 | [TJOI2013] 最长上升子序列

给定一个序列，初始为空。现在我们将1到N的数字插入到序列中，每次将一个数字插入到一个特定的位置。每插入一个数字，我们都想知道此时最长上升子序列长度是多少？

---

我们发现，因为插入是从小到大插入的，所以我们先把最终的数组求出来，然后进行一次LIS。然后我们把以每一个位置i为结尾的LIS长度都求出来。

对于位置i的答案，设位置i的值为v_i，我们只需要把所有j满足v_j≤v_i的ans_j取最大值即可。因为i后面插入的其他数字对i及i签名插入的数字是没有影响的。

为了快速求出最后的序列，我们可以使用链表。当然，vector也是可以的，这里我们尝试使用vector来解决。

---

不要把线段树写错啊喂，最近又打反又漏pushdown的。

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

const int N = 3e5 + 5;
const int INF = 1e18;

int n;

int t[N<<2];
void pushup(int x,int l,int r){
    t[x]=max(t[x<<1],t[x<<1|1]);
    // cerr<<":pu "<<l<<' '<<r<<" v:"<<t[x]<<endl;
}

void change(int x,int l,int r,int p,int v){
    if(l==r){
        t[x]=v;
        return ;
    }
    int mid=l+r>>1;
    // cerr<<mid<<' '<<p<<endl;
    if(p<=mid)change(x<<1,l,mid,p,v);//NO mid<=p!!!
    else change(x<<1|1,mid+1,r,p,v);
    pushup(x,l,r);
}

int query(int x,int l,int r,int pl,int pr){
    if(pl>pr)return 0;
    if(l>=pl&&r<=pr){
        // cerr<<"return at:"<<l<<' '<<r<<"withv:"<<t[x]<<endl;
        return t[x];}
    int mid=l+r>>1;
    int res=0;
    if(pl<=mid)res=max(res,query(x<<1,l,mid,pl,pr));
    if(pr>mid)res=max(res,query(x<<1|1,mid+1,r,pl,pr));
    return res;
}
int g[N],f[N],ans[N];

void solve(){
    n=rd;
    vector<int> v;
    for(int i=1;i<=n;i++){
        int loc=rd;
        v.insert(v.begin()+loc,i);
    }
    // for(auto a:v)cerr<<a<<' ';

    for(int i=1;i<=n;i++){
        g[v[i-1]]=f[i]=query(1,1,n,1,v[i-1]-1)+1;
        // cerr<<"q:"<<query(1,1,n,1,v[i-1]-1)<<" at:"<<v[i-1]<<endl;
        // cerr<<"change at:"<<v[i-1]<<" v:"<<f[i]<<endl;
        change(1,1,n,v[i-1],f[i]);
    }
    // cerr<<endl;
    // for(int i=1;i<=n;i++)cerr<<f[i]<<endl;
    for(int i=1;i<=n;i++){
        ans[i]=max(ans[i-1],g[i]);
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<endl;
    }

}

signed main() {
    int T=1;
    while(T--){
    	solve();
    }
    return 0;
}
```

# 带修最大子串

线段树。

# 构建回文串/编辑距离

## [IOI2000] 回文字串

回文词是一种对称的字符串。任意给定一个字符串，通过插入若干字符，都可以变成回文词。此题的任务是，求出将给定字符串变成回文词所需要插入的最少字符数。

比如 $\verb!Ab3bd!$ 插入 $2$ 个字符后可以变成回文词 $\verb!dAb3bAd!$ 或 $\verb!Adb3bdA!$，但是插入少于 $2$ 个的字符无法变成回文词。

**注意**：此问题区分大小写。

对于全部数据，$0<l\le 1000$。

---

我们考虑吧原来的串S发过来变成T，求S,T的最长公共子序列，那么剩下的那些字母就是我们需要插入的了（即我们要插入的字符数是S长度减去公共子序列的长度）

# 数字金字塔



# 线性dp典例

[AGC031B] Reversi

[练习 | 洛谷补题计划 [洛布姬]](https://flowus.cn/bc99ca5f-afa0-48c7-9a04-18a45346632b)

