CRT

补充资料

[https://www.cnblogs.com/ailanxier/p/13370753.html](https://www.cnblogs.com/ailanxier/p/13370753.html)

# CRT

孙子定理是中国古代求解一次同余式组（见同余）的方法。是数论中一个重要定理。又称中国余数定理。

![343_1576490077743_2B4D67EE859892B169FF34D4BA697A72](CRT与exCRT/343_1576490077743_2B4D67EE859892B169FF34D4BA697A72)

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
		m[i]=mm,a[i]=aa;
	}
	cout<<(long long)excrt(m,a);
	return 0;
}
```

