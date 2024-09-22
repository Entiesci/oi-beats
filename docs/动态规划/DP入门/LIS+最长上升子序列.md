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

对于位置i的答案，设位置i的值为$v_i$，我们只需要把所有j满足$v_j≤v_i$的$ans_j$取最大值即可。因为i后面插入的其他数字对i及i前面插入的数字是没有影响的。

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

