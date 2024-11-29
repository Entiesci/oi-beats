补充资料

[https://www.cnblogs.com/ailanxier/p/13370753.html](https://www.cnblogs.com/ailanxier/p/13370753.html)



我们有若干组$x≡z_i\pmod {m_i}$需要求解，我们先把它们化为不定方程的形式：

x=z_i+b_im_i。这时我们还不能直接求解，如果直接求解，我们就要面对多个无穷集取交集的问题了。

我们考虑联立两个这样的不定方程，有

$b_im_i-b_jm_j=z_i-z_j$。这里我们可以求出b_i,b_j的一组特解spe(b_i),spe(b_j)。有什么用呢？

$sol(b_i)=spe(b_i)+k*m_j/gcd$

$x=z_i+(spe(b_i)+k*m_j/gcd)\times m_i$

$x=z_i+m_i spe(b_i)+k*lcm$

$x=z_i+m_ispe(b_i)\pmod {lcm}$

这样我们就把两个方程合并在一起了。更多的情况一个个合并即可。注意要判断$b_im_i-b_jm_j=z_i-z_j$是否有解（ax+by=m←>gcd(a,b)|m）

# CRT

孙子定理是中国古代求解一次同余式组（见同余）的方法。是数论中一个重要定理。又称中国余数定理。

中国剩余定理(Chinese Remainder Theorem, CRT)可求解如下形式的一元线性同余方程组（其中$n_1,n_2,\cdots,n_k$两两互质）：


$\begin{cases}x\equiv a_1{\pmod{n_1}}\\x\equiv a_2{\pmod{n_2}}\\\vdots\\x\equiv a_k{\pmod{n_k}}\end{cases}$

过程

1. 计算所有模数的积 $n$;

2. 对于第 $i$ 个方程:
a. 计算$m_i=\frac{n}{n_i}$;

    b. 计算$m_i$在模$n_i$意义下的逆元$m_i^{-1}$;

    注：计算a在mod p时的逆元

        $a\times inv==1(mod p)$

        $a\times inv+bp==1$

        用exgcd求解即可。注意到a,p互质，所以$\gcd(a,p)$实际上就是1

    c. 计算$c_i=m_im_i^{-1}$（不要对$n_i$取模）。

1. 方程组在模$n$意义下的唯一解为：$x=\sum_{i=1}^{k}a_ic_i{\pmod{n}}$。

## 例题 #1 [TJOI2009] 猜数字

题目描述

现有两组数字，每组 $k$ 个。

第一组中的数字分别用 $a_1,a_2,\cdots ,a_k$ 表示，第二组中的数字分别用 $b_1,b_2,\cdots ,b_k$ 表示。

其中第二组中的数字是两两互素的。求最小的 $n\in \mathbb{N}$，满足对于 $\forall i\in [1,k]$，有 $b_i | (n-a_i)$。

输入格式

第一行一个整数 $k$。

第二行 $k$ 个整数，表示：$a_1,a_2,\cdots ,a_k$。

第三行 $k$ 个整数，表示：$b_1,b_2,\cdots ,b_k$。

输出格式

输出一行一个整数，为所求的答案 $n$。

对于 $100\%$ 的数据：

$1\le k \le 10$，$|a_i|\le 10^9$，$1\le b_i\le 6\times 10^3$，$\prod_{i=1}^k b_i\le 10^{18}$。

---

注意$\prod b_i$是$10^{18}$范围，所以取模后乘还是会爆LL，请使用int128或者快速乘。

```C++
/*                                                                                
                      Keyblinds Guide
     				###################
      @Ntsc 2024

      - Ctrl+Alt+G then P : Enter luogu problem details
      - Ctrl+Alt+B : Run all cases in CPH
      - ctrl+D : choose this && dump to the next
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
#define itn long long
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
template<template<typename...> class T, typename c, typename... A>
void err(T<c> a, A... x) { for (auto v: a) cerr << v << ' '; err(x...); }
template<typename T, typename... A>
void err(T a, A... x) { cerr << a << ' '; err(x...); }
#else
#define dbg(...)
#endif


const int N = 1e5+5;
const int INF = 1e18;
const int M = 1e7;
 int MOD = 1e9+7;

int x,y;

int exgcd(int a,int b,int &x,int &y){
	// cdbg(a,b);
	if(b==0){
		x=1,y=0;
		return b;
	}
	int t=exgcd(b,a%b,x,y);
	int tx=x,ty=y;
	x=ty;
	y=tx-(a/b)*ty;
	return t;
}

int inv(int a,int p){
	//计算a在mod p时的逆元
	// a*inv==1(mod p)
	// a*inv+bp==1
	exgcd(a,p,x,y);
	return x;
}

int a[N],b[N],c[N],d[N];
itn ans;

void solve(){
	int n=rd;
	for(int i=1;i<=n;i++)a[i]=rd;
	for(int i=1;i<=n;i++)b[i]=rd;

	itn B=1;
	for(int i=1;i<=n;i++){
		B*=b[i];
	}

	for(int i=1;i<=n;i++){
		d[i]=B/b[i];

		c[i]=(__int128)d[i]%B*inv(d[i],b[i])%B;
	}

	for(int i=1;i<=n;i++){
		ans+=(__int128)c[i]*a[i]%B; //B可能是1e18，因此一定要用int128
		// ans%=B;
		ans=(ans%B+B)%B;
	}


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

# exCRT

ex-CRT，其实就是考虑实际情况中，模数两两不一定互质的情况，不知道谁给它取了一个扩展中国剩余定理的名字。模数不互质，就不能用借助逆元的方法了，需要另一种方法。

---

### **我们先复习一下exgcd**

> $ax+by=c$

**裴蜀定理**

> 对于任意整数a,b，当a，b互质,下面不定方程存在整数解

可以得到递推式：$x=y',y=x'-y'*[a/b]$

此时我们知道了x,y,a,b,就可以将x'=0,y'=1,a=0,b=b代入$x=y',y=(x'-y'*[a/b])$

递归回去，递归到a,b为原始值时x，y就是一组特解了。

```C++
ll exgcd(ll a,ll b,ll &x,ll &y){
	if(b==0){
		x=1,y=0;return a;//辗转相除法结束，a就是gcd(原a,原b)
	}
	int nowgcd=exgcd(b,a%b,x,y)
   int tmpx=x,tmpy=y;	//此时x,y还是x',y',存下来后面要用
	//反代回去，求上一层的x,y
	x=tmpy;
	y=tmpx-(a/b)*tmpy;
	return nowgcd;
}
```

**通解**

$a*x + b*y = gcd(a,b)$的通解为

- $x = x' - b/gcd(a,b)*t$

- $y = y' + a/gcd(a,b)*t 
$t为任意整数。

---

### **接下来我们来实现excrt**

[董晓算法 - 扩展中国剩余定理](https://www.bilibili.com/video/BV1Ut4y1F7HG)

对于同余方程组：

$x≡a1\pmod {m_1}$

$x≡a2\pmod {m_2}$

转化为不定方程组

$x=m_1p+a_1$

$x=m_2q+a_2$

联立2方程

$m_1p+a_1=m_2q+a_2$
$m_1p-m_2q=a_2-a_1$

我们发现，这正是一个标准的不定方程，我们也许可以用exgcd进行求解

但注意exgcd的条件：

$ax+by=c$,c必须是gcd(a,b)的倍数

因此仅当$gcd(m1,m2)|(a2-a1)$时不定方程有解，否则无解

如果有解，我们就可以很轻松地使用exgcd求出方程的一组特解

$p=p'*(a_2-a_1)/gcd$

$q=q'*(a_2-a_1)/gcd$

> 为什么要乘上$(a2-a1)/gcd$ ？$p'$不就是一组特解吗？

=> 注意！我们这里的  $m_1p-m_2q=a_2-a_1$ ，并不是$ax+by=gcd(a,b)$!!!
在$ax+by=gcd(a,b)$中，a,b互质，相当于$ax+by=1$，即上式中$a2-a1=1$
此时 $p=p'*(a_2-a_1)/gcd=p'*1$

而 $m_1p-m_2q=a_2-a_1$ 中 $a_2-a_1$ 仅满足 $a_2-a_1=k*gcd(a,b)$ ，因此要 $*(a2-a1)/gcd$

---

其通解为

$P=p+k*m2/gcd$
$Q=q-k*m2/gcd$

代回 $x=m_1p+a_1$

$\begin{align*}
x&=m_1(p+k*m_2/gcd)+a_1\\&=m_1p+k*m_1m_2/gcd+a_1\\&=m_1p+k*lcm(m_1,m_2)+a_1
\end{align*}$

我们又可以把这个方程转化为一个同余方程

$x≡m_1p+a_1(\mod lcm(m_1,m_2))$

这样我们就成功的把2个同余方程转化为了1个同余方程。如果有n个同余方程，我们可以不断合并下去，直到只剩下一个同余方程，exgcd求解即可。

在合并方程时要根据裴蜀定理判定是否有解！

代码如下

```C++
#include<bits/stdc++.h>
using namespace std;
#define ll __int128
const int N=1e5+5;
ll m[N],a[N];
int n;
ll exgcd(ll a,ll b,ll &x,ll &y){
	if(b==0){
		x=1,y=0;return a;//辗转相除法结束，a就是gcd(原a,原b)
	}
	ll nowgcd=exgcd(b,a%b,x,y);
   ll tmpx=x,tmpy=y;	//此时x,y还是x',y',存下来后面要用
	//反代回去，求上一层的x,y
	x=tmpy;
	y=tmpx-(a/b)*tmpy;
	return nowgcd;
}

ll excrt(ll m[],ll a[]){
	ll p,q,m1,m2,a1,a2;
	m1=m[1],a1=a[1];
  //合并思路：不断把式A2...An与式A1合并
	for(int i=2;i<=n;i++){
		m2=m[i],a2=a[i];
		ll d=exgcd(m1,m2,p,q);
		if((a2-a1)%d){
			return -1;
		}
		p=p*(a2-a1)/d;
		p=(p%(m2/d)+m2/d)%(m2/d);//p可能是负数，要处理为最小的正整数（原理是通解公式）
		a1=m1*p+a1;
		m1=m1*m2/d;
	}
	return (a1%m1+m1)%m1;
}
int main(){
//	freopen("P4777_13.in","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++){
		long long mm,aa;
		cin>>mm>>aa;
		m[i]=mm,a[i]=aa;// x==a %m
	}
	cout<<(long long)excrt(m,a);
	return 0;
}
```

