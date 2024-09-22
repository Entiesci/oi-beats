# Breaking the Wall

## 题面翻译

现在有一个正整数序列 $a$ , 你可以选择一个位置 $i$ ，进行一次操作：将 $a_i$ 减去 $2$ ，将 $a_{i-1}$（如果存在）减去 $1$ ，将 $a_{i+1}$（如果存在）减去 $1$，问至少要多少次操作可以使数列中至少出现两个非正整数。

Translated by CmsMartin

## 输入格式

r $n$ ( $2 \le n \le 2 \cdot 10^5$ ) 

 $a_1, a_2, \dots, a_n$ ( $1 \le a_i \le 10^6$ )

## 思路

我们枚举那两个非正整数 $a_i,a_j$ 的位置，我们假定 $a_i>a_j$。

- $|i-j|=1$ 时：

此时我们一次操作可以对于 $a_i+a_j$ 产生 $3$ 的贡献，因此此时的答案为 $\left\lceil\dfrac{a_i+a_j}3\right\rceil$，不过当 $a_i\ge 2\times a_j$ 时，不可能每次操作都产生 $3$ 的贡献，而此时答案应该是 $\left\lceil\dfrac{a_i}2\right\rceil
$。我们扫一遍判每个 $(i,i+1)$ 即可。

- $|i-j|=2$ 时：

无论是在 $i,j$ 中间操作还是对着 $i$ 或 $j$ 操作，对 $a_i+a_j$ 的贡献总是 $2$，因此此时的答案为 $\left\lceil\dfrac{a_i+a_j}2\right\rceil$。我们找到 $a$ 中的最小值和次小值即可。或者扫一遍判每个 $(i-1,i+1)$ 即可。

- $|i-j|>2$ 时：

一次操作只可能对 $a_i$ 或 $a_j$ 中的一个产生 $1$ 的贡献，此时的答案为 $\left\lceil\dfrac{a_i}2\right\rceil+\left\lceil\dfrac{a_j}2\right\rceil$。我们在一次扫描中找到最小值和次小值即可。

## 代码

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
 
 
#define rd read()
inline int read()
{
	int xx=0,ff=1;
	char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') ff=-1;c=getchar();}
	while(c>='0'&&c<='9') xx=xx*10+(c-'0'),c=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}
 
 
const int N=2e5+5;
const int M=5e5+5;
const int INF=1e9+5;
const int MOD=1e9+7;
bool f1;
int m,k,n,qzh;
 
int q;
int T,mn=INF,ans=INF;
int ck[N],r;
int a[N],tot,tmp[N];

void solve1(){
	for(int i=1;i<n;i++){
		if(max(a[i],a[i+1])>=2*min(a[i],a[i+1])){
			ans=min(ans,(max(a[i],a[i+1])+1)/2);
		}else{
			ans=min(ans,(a[i]+a[i+1]+2)/3);
		}
	}
}

void solve2(){
	for(int i=2;i<n;i++){
		ans=min(ans,a[i-1]+a[i+1]+1>>1);
	}
}

void solve3(){
	int mx1=INF,mx2=INF;
	for(int i=1;i<=n;i++){
		int t=a[i]+1>>1;
		if(t<mx1)mx2=min(mx1,mx2),mx1=t;
		else if(t<mx2)mx2=t;
	}
	ans=min(ans,mx1+mx2);
}

main(){
	n=rd;
	for(int i=1;i<=n;i++){
		a[i]=rd;
	}
	solve1();
	solve2();
	solve3();

	cout<<ans<<endl;
	
}
//outp: OK

/*
2
3 2 3 6
*/
```

# Pairs of Segments

## 题面翻译

给定 $n$ 个线段 $[l_i, r_i]$，你需要从中删除尽可能少的线段，满足：

- 剩余线段数量是偶数。

- 剩余的线段可以两两配对，满足：

    - 属于同一对的两个线段有交；

    - 任意不属于同一对的两个线段均无交。

请你求出最少删除多少个线段才能满足要求。

多组数据，$n$ 之和不超过 $2000$，$0 \leq l_i \leq r_i \leq 10^9$。

translated by 一扶苏一

## 思路

我们先把向线段按右端点排序。

设 dp 状态 $dp_{i}$ 为考虑了前 $i$ 个线段，并且选了线段 $i$ 时可以选择的最多的线段数量。对于线段 $i$，可以与其匹配的是线段 $j$ 满足 $i<j,r_j>l_i$，这一点很容易想到。那么为了保证组与组之间不重叠，那么我们上一组的右端点就应该 $≤\min(l_i,l_j)$。

我们把线段按右端点排序，所以右端点小于某一个特定值的线段应该是一个前缀。

所以我们可以这样转移：

$dp_{i}=\max_{j=1}^{i-1}([r_j≥l_i](\max_{k=1}^{l_k<\min(l_i,r_i)} f_k+2))$。

那么我们后面部分的 $\max $ 很明显是一个前缀最大值，我们维护一个前缀最大值数组即可。至于我们要求出k的最大值，那么我们就直接在单调递增的线段数组上二分查询即可。

时间复杂度是枚举 $i$，$O(n)$，第一个 $\max$，$O(n)$，第二个 $\max$ 可以用前缀最大值 $O(1)$ 维护，二分则是 $O(\log n)$ 的。所以总复杂度为 $O(n^2\log n)$。

## 代码

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define ps second
#define pf first
 
 
#define rd read()
inline int read()
{
	int xx=0,ff=1;
	char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') ff=-1;c=getchar();}
	while(c>='0'&&c<='9') xx=xx*10+(c-'0'),c=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}
 
 
const int N=2e5+5;
const int M=5e5+5;
const int INF=1e9+5;
const int MOD=1e9+7;
bool f1;
int m,k,n,qzh;
 
int q;
int T,mn=INF,ans;
int f[N],r;
pii a[N];
int tot,pmx[N];

bool cmp(pii a,pii b){
	return a.pf<b.pf;
}


void init(){
	memset(f,0,sizeof(f));
	memset(pmx,0,sizeof(pmx));
}

void solve(){
	int n=rd;
	for(int i=0;i<n;i++){
		a[i].ps=rd,a[i].pf=rd;
	}
	sort(a, a+n,cmp);
	ans = 0;
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			if (a[j].pf >= a[i].ps) {
				auto pos = lower_bound(a, a+n, make_pair(min(a[j].ps, a[i].ps), -1),cmp);
				if (pos == a+1) {
					f[i] = max(f[i], 2ll);
				} else {
					int k = pos - a - 1;
					f[i] = max(pmx[k] + 2, f[i]);
				}
			}
		}
		pmx[i] = max(pmx[i - 1], f[i]);
		ans = max(f[i], ans);
	}
		
}

signed main() {
	int T=rd;
	while(T--){
		init();
		solve();
		// cerr<<"ans=";
		cout << n - ans << '\n';
	}
}
/*
2
3 2 3 6
*/
```

