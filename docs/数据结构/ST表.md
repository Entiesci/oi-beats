# ST表

[https://blog.csdn.net/weixin_43914593/article/details/109500135](https://blog.csdn.net/weixin_43914593/article/details/109500135)

## 例题 #1

这是一道 ST 表经典题——静态区间最大值

题目描述

给定一个长度为 $N$ 的数列，和 $M$ 次询问，求出每一次询问的区间内数字的最大值。

对于 $100\%$ 的数据，满足 $1\le N\le {10}^5$，$1\le M\le 2\times{10}^6$，$a_i\in[0,{10}^9]$，$1\le l_i\le r_i\le N$。

## 讲解

### 代码

```C++
#include <bits/stdc++.h>
using namespace std;
const int N = 4e5+5;
int n, st[N][20], lg2[N], m, a, b;

void pre() {
	for (int j = 1; j <= 18; j++)
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
			st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);

}

int main() {

	scanf("%d%d",&n,&m);
	lg2[0] = -1;
	for (int i = 1; i <= n; i++)
		lg2[i] = lg2[i / 2] + 1;

	for (int i = 1; i <= n; i++) {
		scanf("%d",&st[i][0]);
	}
	pre();
	while (m--) {
		scanf("%d%d",&a,&b);
		int k = lg2[b - a + 1];
		printf("%d\n",max(st[a][k], st[b - (1 << k) + 1][k]));
	}

	return 0;
}
```

## 例题 #2

题目描述

小 Z 是一个小有名气的钢琴家，最近 C 博士送给了小 Z 一架超级钢琴，小 Z 希望能够用这架钢琴创作出世界上最美妙的音乐。

这架超级钢琴可以弹奏出 $n$ 个音符，编号为 $1$ 至 $n$。第 $i$ 个音符的美妙度为 $A_i$，其中 $A_i$ 可正可负。

一个“超级和弦”由若干个编号连续的音符组成，包含的音符个数不少于 $L$ 且不多于 $R$。我们定义超级和弦的美妙度为其包含的所有音符的美妙度之和。两个超级和弦被认为是相同的，当且仅当这两个超级和弦所包含的音符集合是相同的。

小 Z 决定创作一首由 $k$ 个超级和弦组成的乐曲，为了使得乐曲更加动听，小 Z 要求该乐曲由 $k$ 个不同的超级和弦组成。我们定义一首乐曲的美妙度为其所包含的所有超级和弦的美妙度之和。小 Z 想知道他能够创作出来的乐曲美妙度最大值是多少。

### 思路

就是先对于每一个位置i，把$i \sim i+l-1,i \sim i+r-1$放进去表示i开头的可用区间。
然后枚举k次，每次取出最优的区间$i \sim t$，假设它属于块 $\{i \sim i+l-1,i \sim i+r-1\}$，那么我们取出了$i \sim t$后还要把$\{i \sim i+l-1,i \sim t-1\}\{i \sim t+1,i \sim i+r-1\}$丢回优先队列中作为备选项。

### 代码

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

const int N = 5e5 + 5;
const int INF = 1e18;

int n,K,l,r;
int qz[N],lg[N];
int st[N][20];
int a[N];

void init(){
    lg[1]=0;
    for(int i=2;i<=n;i++)lg[i]=(lg[i>>1]+1);
    for(int i=1;i<=n;i++)st[i][0]=i;
    for(int j=1;(1<<j)<=n;j++){
        for(int i=1;i+(1<<j)-1<=n;i++){
            int x=st[i][j-1],y=st[i+(1<<(j-1))][j-1];
            
            if(qz[x]>qz[y])st[i][j]=x;
            else st[i][j]=y;
        }
    }
}

int query(int l,int r){
    int k=lg[r-l+1];
    int x=st[l][k],y=st[r-(1<<k)+1][k];
    return qz[x]>qz[y]?x:y;
}

struct node{
    int o,l,r,t;
    node(){}
    node(int o,int l,int r) : o(o), l(l), r(r), t(query(l, r)) {}
    friend bool operator < (const node& a, const node& b) {
        return qz[a.t] - qz[a.o - 1] < qz[b.t] - qz[b.o - 1];
    }
};

priority_queue<node> q;
void solve(){
    n=rd,K=rd,l=rd,r=rd;
    for(int i=1;i<=n;i++){
        a[i]=rd;
    }
    for(int i=1;i<=n;i++){
        qz[i]=qz[i-1]+a[i];
    }
    init();//建立st表
    for(int i=1;i<=n;i++){
        if(i+l-1<=n)q.push(node(i,i+l-1,min(i+r-1,n)));
    }

    //就是先对于每一个位置i，把i~i+l-1,i~i+r-1放进去表示i开头的可用区间
    //然后枚举k次，每次取出最优的区间i~t，假设它属于块{i~i+l-1,i~i+r-1}，\
    那么我们取出了i~t后还要把{i~i+l-1,i~t-1}{i~t+1,i~i+r-1}丢回优先队列中作为备选项。
    int ans=0;
    while(K--){
        int o=q.top().o,L=q.top().l,R=q.top().r,t=q.top().t;
        q.pop();
        ans+=qz[t]-qz[o-1];
        if(L!=t)q.push(node(o,L,t-1));
        if(t!=R)q.push(node(o,t+1,R));
    }
    cout<<ans<<endl;
}
signed main() {
    int T=1;
    while(T--){
    	solve();
    }
    return 0;
}
```

