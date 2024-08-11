# exGCD

## exGCD理论

### **裴蜀定理**

在数论中，裴蜀定理是一个关于最大公约数（或最大公约式）的定理，裴蜀定理得名于法国数学家艾蒂安·裴蜀。
裴蜀定理说明了对任何整数 a、b和它们的最大公约数 d ，关于未知数 x以及 y 的线性的丢番图方程（称为裴蜀等式）。

它的一个重要推论是：**a,b互质的充分必要条件是存在整数x,y使ax+by=1.**

### 扩展欧几里得算法

扩展欧几里得算法是欧几里得算法（又叫辗转相除法）的扩展。除了计算a、b两个整数的最大公约数，此算法还能找到整数x、y（其中一个很可能是负数）。通常谈到最大公因子时, 我们都会提到一个非常基本的事实: 给予二整数 a 与 b, 必存在有整数 x 与 y 使得$ax + by = gcd(a,b)$。有两个数a,b，对它们进行辗转相除法，可得它们的最大公约数——这是众所周知的。然后，收集辗转相除法中产生的式子，倒回去，可以得到$ax+by=gcd(a,b)$的整数解。

## exGCD实现

我们先来看一个式子

> $ax+by=c$

没错这是我们目前的一道问题——求解二元一次方程。

**裴蜀定理**

> 对于任意整数a,b，当a，b互质,下面不定方程存在整数解

**扩展欧几里得算法**

> 待解方程：$ax+by=gcd(a,b)$

根据欧几里得算法 $gcd(a,b)=gcd(b,a\%b)$
得到

令$a'=b,b'=a\%b$

=> $x'a'+y'b'=gcd(a',b')=gcd(a,b)$

$gcd(a,b)$不断向下，会出现$a=0$

$ax+by=gcd(a,b)$

=> $x*0+y*b=gcd(0,b)=b$

=> $0*0+1*b=b$

=> 我们就规定$x=0,y=1$

此时我们得到了当前不定方程(a=0)的x,y

我们回到上面

$a'=b$ , $b'=a\%b$

$x'a'+y'b'=gcd(a',b')=gcd(a,b)$

=> $b'=a\%b =a-[a/b]*b,a'=b$   代入

=> $x'b/b]*b)=gcd(a,b)$

=> $(x'-y'*[a/b])b+y'a=gcd(a,b)=xa+yb$

因此可以得到递推式：$x=y',y=x'-y'*[a/b]$

回到上面的特解

$0*0+1*b=b$

$x=0,y=1$

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

直接看代码吧

```C++

#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll T,a,b,c,d,x,y,k,p,q;

ll exgcd(ll a,ll b,ll &x,ll &y){
	ll tmp=a;
	if(!b)x=1,y=0;
	else {
		tmp=exgcd(b,a%b,y,x);
		y-=a/b*x;
	}
	return tmp;
}
signed main() {
	cin>>T;
	while(T--){
		scanf("%lld%lld%lld",&a,&b,&c);
		x=y=0;
		d=exgcd(a,b,x,y);
        
        ////AC////
		if(c%d)printf("-1\n");
		else{
			x*=c/d,y*=c/d;
			p=b/d,q=a/d;
			if(x<0)k=ceil((1.00-x)/p),x+=p*k,y-=q*k;
			else k=(x-1)/p,x-=p*k,y+=q*k;
			if(y>0){
				printf("%lld %lld %lld %lld %lld\n",(y-1)/q/q*p,y);
				
			}else{
				printf("%lld %lld\n",x,y/q));
			}
		}
		
	}
	

	return 0;
}
```

在上面的代码中，exgcd()的返回值d是gcd(a,b)的值

同时，我们在推算的过程中更改了x，y的值，在函数结束时x，y就是不定方程的一组特解

**e.g.**

输入：

```C++
1
64 36 4
```

当代码运行到////AC/////处时：

```C++
d=4,x=4,y=-7
```

**裴蜀定理应用**

我们回到开始的不等式与题目中的不等式

$ax+by=gcd(a,b)$

$ax+by=c$

如果一个数m满足：ax+by=m，那么这个m一定是gcd(a,b)的倍数

可以发现，只有c%gcd(a,b)=0时，才会有整数解，因此要特判

```C++
	if(c%d)printf("-1\n");
```

**求通解**

那么我们知道了一组特解x',y'后，通解的表达式是什么呢？

$ax'+by'=gcd(a,b)$

$a(x'+b)+b(y'-a)=gcd(a,b)$

$a(x'/d)=gcd(a,b)$

$a(x'/d)=gcd(a,b) $

t为任意整数。

故$a(x'/d)=gcd(a,b)$仍然有整数解

所以$a*x + b*y = gcd(a,b)$的通解为

- $x = x' - b/gcd(a,b)*t$

- $y = y' + a/gcd(a,b)*t 
$t为任意整数。

---

### 实际操作

【模板】二元一次不定方程 (exgcd)

## 例题 #1

给定不定方程

$ax+by=c$

若该方程无整数解，输出 $-1$。
若该方程有整数解，且有正整数解，则输出其**正整数**解的数量，所有**正整数**解中 $x$ 的最小值，所有**正整数**解中 $y$ 的最小值，所有**正整数**解中 $x$ 的最大值，以及所有**正整数**解中 $y$ 的最大值。
若方程有整数解，但没有正整数解，你需要输出所有**整数解**中 $x$ 的最小正整数值， $y$ 的最小正整数值。

正整数解即为 $x, y$ 均为正整数的解，$\boldsymbol{0}$ **不是正整数**。
整数解即为 $x,y$ 均为整数的解。
$x$ 的最小正整数值即所有 $x$ 为正整数的整数解中 $x$ 的最小值，$y$ 同理。

**【数据范围】**

对于 $100\%$ 的数据，$1 \le T \le 2 \times {10}^5$，$1 \le a, b, c \le {10}^9$。

### 预备知识：计算gcd

**方法**
辗转相除法
**代码**

```C++
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
```

exgcd

```C++
ll exgcd(ll a,ll b,ll &x,ll &y){
	ll tmp=a;
	if(!b)x=1,y=0;
	else {
		tmp=exgcd(b,a%b,y,x);
		y-=a/b*x;
	}
	return tmp;
}
```

### 解题方法

```C++
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll T,a,b,c,d,x,y,k,p,q;

ll exgcd(ll a,ll b,ll &x,ll &y){	//注意后面2个有取地址符！！！
	ll tmp=a;
	if(!b)x=1,y=0;
	else {
		tmp=exgcd(b,a%b,y,x);
		y-=a/b*x;
	}
	return tmp;
}
signed main() {
	cin>>T;
	while(T--){
		scanf("%lld%lld%lld",&a,&b,&c);
		x=y=0;
		d=exgcd(a,b,x,y);
		if(c%d)printf("-1\n");
		else{
			x*=c/d,y*=c/d;
			p=b/d,q=a/d;
			if(x<0)k=ceil((1.00-x)/p),x+=p*k,y-=q*k;
			else k=(x-1)/p,x-=p*k,y+=q*k;
			if(y>0){
				printf("%lld %lld %lld %lld %lld\n",(y-1)/q/q*p,y);
				
			}else{
				printf("%lld %lld\n",x,y/q));
			}
		}
		
	}
	

	return 0;
}
```

