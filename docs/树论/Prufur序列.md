Prufur序列

摘抄[学习笔记 | Prufur序列](https://flowus.cn/d2ffd1e5-9bb4-4937-be76-978cbba6da2c)

---

# Prufur序列

定义：对于一颗无根无向树，每次选择其编号最小的叶子节点v，输出与v相连的节点u的编号，并且把v删除。知道仅剩下2个节点。

它可以唯一确定一个无根无向树。

**树→序列**

用优先队列即可O(n \log n)

对于O(n)的做法，我们可以设集合T为叶子节点的集合。动态维护j为T中的最小值。每次我们取出j并且删除，然后判断j的父亲f，如果f<j则删除f，知道f>j则删除j。

```C++
for(int i=1;i<n;i++)cin>>f[i],d[f[i]]++;//度数
	for(int i=1,j=1;i<n-1;j++){
		while(d[j])j++;
		pr[i++]=f[j];
		while(i<n-1&&--d[pr[i-1]]==0&&pr[i-1]<j)pr[i++]=f[pr[i-1]];
		
		
	}for(int i=1;i<n-1;i++)cout<<pr[i]<<' ';
```

**序列→树**

动态维护当前度数为0的最小的点j。然后在枚举到 pr_i时，将j的父节点设置为pr_i，然后将j的度数设为-1，将pr_i的度数-1。同样是O(n)的。





```C++
for(int i=1;i<=n-2;i++)cin>>pr[i],d[pr[i]]++;
	pr[n-1]=n;
	for(int i=1,j=1;i<n;i++,j++){
		while(d[j])j++;
		f[j]=pr[i];
		while(i<n-1&&--d[pr[i]]==0&&pr[i]<j)f[pr[i]]=pr[i+1],i++;
	}
	
	for(int i=1;i<=n-1;i++)cout<<f[i]<<' ';
```

## 引理

n个点的完全图的生成树总共 $n^{n−2}$ 种（由prufur序列生成方法推导）

## 例题 #12418. 光之大陆

在光之大陆的土地上，各种势力盘根错节。

来自光之峡谷的精灵，来自黑暗森林的亡灵，来自古老东方的人类共同生活在一起。

善于打造装置的矮人，善于发明的侏儒，隐匿于山林的巨人也坚守着属于自己的领土。

这些种族之间关系错综复杂，构成了极其庞大的关系网络。

大魔法师小 P 想要研究其中的种族关系。

两个物种之间可以是盟友，也可以不是盟友，如果 $a_1,a_2..a_n$ 满足 $a_i$ 和 $a_{i+1}$ 是盟友，且 $a_n$ 和 $a_1 $是盟友，则他们构成了一个联盟。

由于光之大陆正处于微妙的和平之中。所以一个合理的物种关系应满足如下条件:

1. 对于任意两个物种 A,B，都存在一个序列 $A,a_1,a_2..a_n,B$，使得任意相邻两个种族是盟友(注意 A,B 不一定是盟友)。

2. 对于任意两个联盟 $S_a,S_b$，都不存在一个物种既参加了联盟 $S_a$，又参加了联盟 $S_b$。

小 P 想知道，大陆上的 N 个种族一共有多少种可能的结盟关系，由于结果可能很大，你只需要输出答案 mod M 的值。

### 思路

题意有一点绕。即完全图中有n个点，我们可以把这n个点分成i个集合（i\in[1,n]），每个集合（若集合大小>2）内我们会连成一个简单环。这些都不用管。求方案数。

那么假设我们已经分好了，分成了m个集合，那么将这m个部分拼成一颗生成树的个数为n^{m-2}。思路同prufur。

为什么？我们考虑一个n节点树可以变成一个n-2长度的prufur序列。那么如果这个树是从一颗完全图上生成的，那么prufur序列的每一个位置都有n-2种可能。于是从n个节点的完全图中生成的树的prufur序列一共有n^{n-2}种情况。

至于为什么是n^{m-2}，因为m个集合的生成树的prufur序列有m-2个数，但对于一个点的父节点，虽然只有可能是一个集合，但是可能是这个集合中的任意一个点。所以每一个位置的方案数还是n。



至于把n个点分成m个部分，我们用dp

f_{i,j}表示把i个点分成j个集合的方案的数量。

---



```C++
/*////////ACACACACACACAC///////////
       . Code  by  Ntsc .
       . Earn knowledge .
/*////////ACACACACACACAC///////////

#include <bits/stdc++.h>
#define int long long
#define db double
#define rtn return
using namespace std;

const int N = 2e3 + 5;
const int M = 1e5;
int MOD = 1e9+7;
const int INF = 1e9+5;

int n, m, f[N][N], g[N], C[N][N], ans;

void init(){
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			if(!j)C[i][j]=1;
			else C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
		}
	}
	
	g[1]=1,g[3]=3;
	
	for(int i=4;i<=n;i++)g[i]=g[i-1]*i%MOD;
}
void solve(){
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			for(int k=1;k<=i-j+1;k++){
				f[i][j]=(f[i][j]+f[i-k][j-1]*C[i-1][k-1]*g[k])%MOD;
			}
		}
	}
	int res=g[n-1],p=1;
	for(int k=2;k<=n;k++	){
		res+=f[n][k]*p;
		(p*=n)%=MOD;;
	}
	
	cout<<res%MOD;
}


signed main() {
//    freopen("tree.in", "r", stdin);
//    freopen("tree.out", "w", stdout);
	cin>>n>>MOD;
	
	init();
	solve();
    return 0;
}

```

#### 输入格式

一行，两个正整数 N,M。

#### 输出格式

一个整数，表示方案数 mod M 的值。

#### 数据范围

3≤N≤200,
1≤M≤106

#### 输入样例：

```C++
4 1000000
```

#### 输出样例：

```C++
31
```

## 例题 #2 生成树

题目背景

> 我们是未成熟的斗士 现在绝不认输

我们是未成熟的梦想家 现在绝不哭泣

题目描述

现给定一个无向完全图 $G(V,E)$ 和一个长度为 $|V|$ 的权值数组 $a$．$a_i$ 表示编号为 $i$ 的节点的权值．

定义一条边 $e(u,v)$ 的边值为 $val(e)$，满足 $val(e)=a_u\oplus a_v$，也就是边连接的两个节点的权值的异或和；定义 $G$ 的一个生成树 $T(V,E_t)$ 的权值为 $Val(T)$，满足 $Val(T)=\sum_{e\in E_t}val(e)$，也就是树上边的边权和．

您需要求出 $\sum_{T}Val(T)$．即 $G$ 中所有不同生成树的权值的和．

我们认为两棵生成树是不同的，当且仅当两棵树的边集 $E_t$ 不完全相同，即至少存在一条边，满足其仅属于两棵生成树中的其中一棵．

### 思路

因为是完全图，所以所有的边都是等价的。

生成树总共 $n^{n−2}$ 种（由prufur序列生成方法推导），每种有 $n−1$ 条边，边共 $\frac{n×(n−1)}{2}$​ 条，每条边会被计算 $2×n^{n−3} $次。



---

```C++
/*////////ACACACACACACAC///////////
       . Code  by  Ntsc .
       . Earn knowledge .
/*////////ACACACACACACAC///////////

#include <bits/stdc++.h>
#define int long long
#define db double
#define rtn return
using namespace std;

const int N = 2e6 + 5;
const int M = 1e5;
const int MOD = 998244353;
const int INF = 1e9+5;

int n, m, cnt[N], g[N], a[N], ans;


int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=(res*a)%MOD;
		a=(a*a)%MOD;
		b>>=1;
	}
	return res;
}

signed main() {
//    freopen("tree.in", "r", stdin);
//    freopen("tree.out", "w", stdout);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		for(int j=0;j<=31;j++)cnt[j]+=(((1<<j)&a[i])!=0);
	}
	
	
	
	for(int i=1;i<=n;i++){
		for(int j=0;j<=31;j++){
			if(((1<<j)&a[i]))(ans+=(n-cnt[j])*(1<<j))%=MOD;
			else (ans+=(cnt[j])*(1<<j))%=MOD;
		}
	}
//	cerr<<":OK";
	if(n>2)ans=ans*ksm(n,n-3)%MOD;
	
	cout<<ans%MOD;
    return 0;
}

```

