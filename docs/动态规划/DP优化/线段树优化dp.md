# 线段树优化dp

[线段树优化dp题单&题解 - AFewSuns - 博客园](https://www.cnblogs.com/AFewSuns/p/15470358.html#cf1304f2-animal-observation-hard-version)


## 例题 #1 Pillars



给定序列 $a$，长度为 $n$。

找出一个 $a$ 序列的子序列 $b$（设其长度为 $m$），使得

- 对于任意的 $1\le i\lt m$，有 $|b_{i+1}-b_i|\ge d$。

- $m$ 最大。

- 其中 $d$ 是给定的。

您的程序要输出 $m$ 和序列 $b$ 在序列 $a$ 中每个数的下标（下标从 $1$ 开始）。

$1\le n\le 10^5$，$0\le d\le 10^9$，$1\le a_i\le 10^{15}$。若 $b$ 不唯一，输出任意一种。

---

先写出朴素转移，然后上线段树优化即可。

```C++
#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pii pair<int,int> 
#define pf first
#define ps second

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

const int N=3e5+5;

int n,d;
int f[N],pre[N],a[N];
int b[N],tot;

void dfs(int x){
    if(!x)return ;
    dfs(pre[x]);
    cout<<x<<' ';
}


namespace SGT{
	pii t[N<<2];
	
	
	
	void pushup(int x){
		t[x]=t[x<<1].pf>=t[x<<1|1].pf?t[x<<1]:t[x<<1|1];
	}
	
	void change(int x,int l,int r,int p,int id){
		if(l==r){
			t[x]={f[id],id};
			return ;
		}
		int mid=l+r>>1;
		if(p<=mid)change(x<<1,l,mid,p,id);
		else change(x<<1|1,mid+1,r,p,id);
		pushup(x);
	}
	
	pii query(int x,int l,int r,int pl,int pr){
		if(pl>pr)return make_pair(0,0);
		if(pl<=l&&pr>=r)return t[x];
		int mid=l+r>>1;
		pii nl={0,0},nr={0,0};
		if(pl<=mid)nl=query(x<<1,l,mid,pl,pr);
		if(pr>mid)nr=query(x<<1|1,mid+1,r,pl,pr);
		if(nr.pf>nl.pf)nl=nr;
		return nl;
	}
}using namespace SGT;


inline int getId(int x){
	return lower_bound(b+1,b+tot+1,x)-b;
}

signed main(){
    cin>>n>>d;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[++tot]=a[i];
        f[i]=1;
    }
    
    sort(b+1,b+tot+1);
    tot=unique(b+1,b+tot+1)-b-1;
    

    for(int i=1;i<=n;i++){
        // for(int j=1;j<i;j++){ //朴素转移
            // if(abs(a[i]-a[j])<d)continue;
            // if(f[j]+1>f[i]){
                // f[i]=f[j]+1;
                // pre[i]=j;
            // }
        // }
        
        
        int l=getId(a[i]-d+1);
        int r=getId(a[i]+d);
        // cdbg(getId(a[i]),l,r);
        auto v=query(1,1,tot,1,l-1);
        auto u=query(1,1,tot,r,tot);
        if(u.pf>v.pf)v=u;
        f[i]=v.pf+1;
        pre[i]=v.ps;
        
        change(1,1,tot,getId(a[i]),i);
    }

    int ans=1;
    for(int i=1;i<=n;i++){
        if(f[ans]<f[i])ans=i;
    }
    cout<<f[ans]<<endl;
    dfs(ans);

}
```

## 例题 #2 Linear Kingdom Races

你是一个赛车比赛的组织者，想在线性王国中安排一些比赛。

线性王国有 $n$ 条连续的从左到右的道路。道路从左到右依次编号为从 $1$ 到 $n$，因此道路按照升序排列。在这些道路上可能会有几场比赛，每一场比赛都将使用这些道路的某个连续的子序列。而且，如果某场比赛举行了，你将获得一定数额的金钱。没有比赛在时间上重叠，所以每一段道路可以在多个比赛中使用。

不幸的是，**所有道路**的状况都不佳，需要修理。每条路都有与之相关的维修费用，你需要支付这笔费用来修理道路。只有在某场比赛中需要使用的所有道路**都进行了修复**，才能进行比赛。你的任务是修复道路并使你的利润最大化。你的利润被定义为你从比赛中获得的总金额减去你花在修理道路上的钱。**请注意，您可以决定不修任何道路，并获得利润 $0$。**

输出你能获得的最大利润。

输入格式：

第一行包括两个整数 $n,m$（$1 \leq n,m \leq 2\cdot 10^5$），分别表示道路的数量和比赛的数量。

接下来 $n$ 行，每行一个整数，表示这条道路修复需要的代价。

再接下来 $m$ 行，每行包括三个整数 $l_b,u_b,p$（$1 \leq l_b,u_b \leq n,1 \leq p \leq 10^9$），表示第 $b$ 场比赛需要使用道路 $[l_b,u_b]$，你会获得收益 $p$。

输出格式：

输出一个整数，表示你能获得的最大利润。

---

设f_i为考虑前i条路且不选i时的最大价值。朴素写法是枚举j，转移为

$f_i=\max(f_j-cost(j+1,i-1)+w(j+1,i-1))$

其中$cost(j+1,i-1)=pre_{i-1}-pre_j,w(j+1,i-1)=pr_{i-1}-pl_{j}$。pre是花费的前缀和，pl_i代表l≤i的区间的价值和，pr_i表示r如此。

发现可以拆分贡献，即把含i的和含j的分离，就得到了$f[i]=max(f[j]+pre[j]-pl[j])-pre[i-1]+pr[i-1]$。记$mx_j=f[j]+pre[j]-pl[j]$，我们维护mx的前缀最小值即可。交上去发现wa了，因为我们的预处理有问题。

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long


/*
一个物品可以得到贡献p仅当：[l,r]全被选择


*/

const int N=3e5+5;

int f[N];//考虑前i条边，且第i条不修的最大价值
int pl[N],pr[N];
int pre[N];
struct Node{
    int l,r,v;
}t[N];
int n,m;
int c[N];


bool cmpl(Node a,Node b){
    return a.l<b.l;
}

bool cmpr(Node a,Node b){
    return a.r<b.r;
}

int cost(int a,int b){
    return pr[b]-pl[a-1];
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>c[i];
    for(int i=1;i<=n;i++)pre[i]=pre[i-1]+c[i];
    for(int i=1;i<=m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        t[i]={a,b,c};
    }   


    sort(t+1,t+m+1,cmpl);

    int cur=1;
    for(int i=1;i<=n;i++){
        //l<=i的区间的价值和
        pl[i]=pl[i-1];
        while(t[cur].l<=i&&cur<=m){
            pl[i]+=t[cur].v;
            cur++;
        }
    }

    sort(t+1,t+m+1,cmpr);
    
    cur=1;
    for(int i=1;i<=n;i++){
        //r<=i的区间的价值和
        pr[i]=pr[i-1];
        while(t[cur].r<=i&&cur<=m){
            pr[i]+=t[cur].v;
            cur++;
        }
    }




    int ans=0;
    int pmax=0;
    for(int i=1;i<=n+1;i++){
    	f[i]=max(0ll,pmax-pre[i-1]+pr[i-1]);
        // for(int j=0;j<i;j++){
            // f[i]=max(f[i],f[j]-(pre[i-1]-pre[j])+cost(j+1,i-1));
            // f[i]=max(f[i],f[j]+pre[j]-pl[j])-pre[i-1]+pr[i-1];
        // }
        ans=max(ans,f[i]);
        pmax=max(pmax,f[i]+pre[i]-pl[i]);
    }

    cout<<ans<<endl;





}
```

考虑我们的$pl_j=pr_{i+1}$是为了求完全被[j+1,i-1]包含的区间的价值和。但是如果有一个区间包含了[j+1,i-1]，那么就会累加这个区间的**负价值**导致答案偏小。

解决也很经典，我们动态加入区间即可，使得当前pl,pr中统计到的区间的r≤i即可。需要使用线段树来维护mx了。

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long


/*
一个物品可以得到贡献p仅当：[l,r]全被选择


*/

const int N=3e5+5;

#define lson pos<<1
#define rson pos<<1|1
using namespace std;

const int INF=1e9;
struct add
{
	int l,k;
	add(int p,int q)
	{
		l=p,k=q;
	}
};
int n,m;
int v[N];
vector<add> vec[N];
int tree[N<<2],lazy[N<<2];
int dp[N];

namespace SGT{
	
	void pushup(int pos)
	{
		tree[pos]=max(tree[lson],tree[rson]);
	}
	void addtag(int pos,int l,int r,int k)
	{
		tree[pos]+=k;
		lazy[pos]+=k;
	}
	void pushdown(int pos,int l,int r)
	{
		int mid=(l+r)>>1;
		addtag(lson,l,mid,lazy[pos]);
		addtag(rson,mid+1,r,lazy[pos]);
		lazy[pos]=0;
	}
	void update(int pos,int l,int r,int x,int y,int k)
	{
		int mid=(l+r)>>1;
		if(x<=l && r<=y)
		{
			addtag(pos,l,r,k);
			return;
		}
		pushdown(pos,l,r);
		if(x<=mid)
			update(lson,l,mid,x,y,k);
		if(y>mid)
			update(rson,mid+1,r,x,y,k);
		pushup(pos);
	}
	int query(int pos,int l,int r,int x,int y)
	{
		int mid=(l+r)>>1;
		if(x<=l && r<=y)
			return tree[pos];
		pushdown(pos,l,r);
		int ret=-INF;
		if(x<=mid)
			ret=max(ret,query(lson,l,mid,x,y));
		if(y>mid)
			ret=max(ret,query(rson,mid+1,r,x,y));
		return ret;
	}
}using namespace SGT;
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lld",&v[i]);
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%lld%lld%lld",&x,&y,&z);
		vec[y].push_back(add(x,z));
	}
	for(int i=1;i<=n;i++)
	{
		update(1,0,n,0,i-1,-v[i]);
		for(int j=0;j<vec[i].size();j++)
		{
			int ll=vec[i][j].l,kk=vec[i][j].k;
			update(1,0,n,0,ll-1,kk);
		}
		dp[i]=max(query(1,0,n,0,i-1),dp[i-1]);
		update(1,0,n,i,i,dp[i]);
	}
	printf("%lld",dp[n]);
	return 0;
}
```

类似题目还有：[P2605 [ZJOI2010] 基站选址](https://www.luogu.com.cn/problem/P2605)

## 例题 #3 [USACO12OPEN] Bookshelf G

当农夫约翰闲的没事干的时候，他喜欢坐下来看书。多年过去，他已经收集了 $N$ 本书 $(1 \le N \le 100,000)$ ， 他想造一个新的书架来装所有书。

每本书 $i$ 都有宽度 $W_i$ 和高度 $H_i$ 。书需要按顺序添加到一组书架上；比如说，第一层架子应该包含书籍 $1  ... k$ ，第二层架子应该以第 $k + 1$ 本书开始，以下如此。每层架子的总宽度最大为 $L(1 \le L \le 1,000,000,000)$ 。每层的高度等于该层上最高的书的高度，并且整个书架的高度是所有层的高度的总和，因为它们都垂直堆叠。

请帮助农夫约翰计算整个书架的最小可能高度。

有 $N(1 \le N \le 100,000)$ 本书，每本书有一个宽度 $W_i$ ，高度 $H_i$ ，$(1 \le H_i \le 1,000,000; 1 \le W_i \le L)$ 。

现在有足够多的书架，书架宽度最多是 $L (1 \le L \le 1,000,000,000)$ ，把书按顺序 $($先放 $1$ ，再放 $2.....)$ 放入书架。某个书架的高度是该书架中所放的最高的书的高度。

将所有书放入书架后，求所有书架的高度和的最小值。

输入格式

第一行：两个数 $N$ 和 $L$ 。

接下来 $N$ 行每行两个数 $H_i$ 和 $W_i$ 。

输出格式

一个数，书架高度的最小值。

---

先写出朴素dp，再考虑优化。

我们发现转移时我们要找到$\min(f_j+max_{k\in{i,j}}(h_k))$。发现\max是和i,j都有关的。

于是我们考虑线段树上维护一个pair<f,mx>，下标i对应的pair维护的就是$<f_i,\max_{k\in[i+1,now]}(h_k)>$。转移时我们只需要再可以常用的区间求f+mx的最小值即可。

然后我们每次到达一个i就需要先用h_i更新[pre,i]之间的,<f,mx>，其中pre代表最近的一个h>h_i的位置。问题正在此处。如果我们仅仅维护f+mx 的最小值，那么可能会不优。如4+2和2+6我们会保留前者，后来用h更新时更新为了4+h,2+h，那么前者就更劣了。因此线段树上要记录f+mx的最小的pair，还要记录f最小的pair。

```C++
// Problem: P1848 [USACO12OPEN] Bookshelf G
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P1848
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
#define pii pair<int,int>


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


int f[N];//放了前i本的最小高度和
int pw[N],w[N];
int h[N];

namespace SGT{
	struct Node{
		pii mn,fmn;
	}t[N<<2];
	int tag[N<<2];
	
	
	void addtag(int x,int v){
		t[x].mn.ps=max(t[x].mn.ps,v);
		t[x].fmn.ps=max(t[x].fmn.ps,v);
		tag[x]=max(v,tag[x]);
		if(t[x].fmn.ps+t[x].fmn.pf<t[x].mn.pf+t[x].fmn.ps)t[x].mn=t[x].fmn;
	}
	
	void pushdown(int x){
		if(tag[x]){
			addtag(x<<1,tag[x]);
			addtag(x<<1|1,tag[x]);
			tag[x]=0;
		}
	}
	
	
	void pushup(int x){
		t[x].mn=(t[x<<1].mn.pf+t[x<<1].mn.ps<=t[x<<1|1].mn.pf+t[x<<1|1].mn.ps)?t[x<<1].mn:t[x<<1|1].mn;
		t[x].fmn=(t[x<<1].fmn.pf<=t[x<<1|1].fmn.pf)?t[x<<1].fmn:t[x<<1|1].fmn;
	}
	
	void change(int x,int l,int r,int pl,int pr,int v){
		if(pr<1||pr<pl)return ;
		if(pl<=l&&pr>=r){
			addtag(x,v);
			return ;
		}	
		pushdown(x);
		int mid=l+r>>1;
		if(pl<=mid)change(x<<1,l,mid,pl,pr,v);
		if(pr>mid)change(x<<1|1,mid+1,r,pl,pr,v);
		pushup(x);
	}
	
	
	void changef(int x,int l,int r,int p,int v){
		
		if(l==r){
			t[x].mn.pf=t[x].fmn.pf=v;
			return ;
		}
		pushdown(x);
		int mid=l+r>>1;
		if(p<=mid)changef(x<<1,l,mid,p,v);
		else changef(x<<1|1,mid+1,r,p,v);
		pushup(x);// !
	}
	
	int query(int x,int l,int r,int pl,int pr){	
		if(pl<=l&&pr>=r){
			return t[x].mn.pf+t[x].mn.ps;
		}
		pushdown(x);
		int mid=l+r>>1;
		int res=INF;
		if(pl<=mid)res=min(res,query(x<<1,l,mid,pl,pr));
		if(pr>mid)res=min(res,query(x<<1|1,mid+1,r,pl,pr));
		return res;
	}
}using namespace SGT;


int stk[N],top;


signed main(){
	itn n=rd+1,L=rd;
	for(int i=2;i<=n;i++){
		h[i]=rd;
		w[i]=rd;
		pw[i]=pw[i-1]+w[i];
	}
	
	memset(f,0x3f3f,sizeof f);
	f[1]=0;
	changef(1,1,n,1,f[1]);
	
	
	
	for(int i=2;i<=n;i++){
		// for(int j=i;~j;j--){
			// if(pw[i]-pw[j]>L)break;
			// int mx=0;
			// for(int k=j+1;k<=i;k++)mx=max(mx,h[k]);
			// f[i]=min(f[i],f[j]+mx);
		// }
		
		while(top&&h[stk[top]]<h[i])top--;
		// cdbg("cg",stk[top],i-1,h[i]);
		change(1,1,n,max(1ll,stk[top]),i-1,h[i]);
		stk[++top]=i;
		
		int l=lower_bound(pw+1,pw+n+1,pw[i]-L)-pw;
		// l--;
		f[i]=query(1,1,n,max(1ll,l),i-1);
		changef(1,1,n,i,f[i]);
		
		// cdbg(l,i,f[i]);
	}
	
	// cdbg(query(1,1,n,4,4));
	
	cout<<f[n]<<endl;
}
```

## 练习 

### #1 [Optimal Partition](https://codeforces.com/problemset/problem/1667/B)

代码被误删了（痛苦）。就是先写出朴素转移，然后维护两颗权值线段树，发布i额对应小于和大于的情况。用树状数组会更好写。

